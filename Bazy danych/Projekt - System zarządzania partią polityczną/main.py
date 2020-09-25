# -*- coding: utf-8 -*-
import argparse
import psycopg2
import json
import sys


# Funkcja przetwarzająca jsona <open> podczas pierwszego uruchomienia programu
def f_open_init(arg):
    try:
        # Ustanowienie połączenia między bazą danych
    	# Dane dostępowe są pobrane z obiektu json
        global conn
        conn = psycopg2.connect(host="localhost", port="5432",
                                dbname=arg['open']['database'],
                                user=arg['open']['login'],
                                password=arg['open']['password'])
        # Inicjalizacja kursora odpowiadającego za polecenia bazodwanowe
        global cur
        cur = conn.cursor()
        # Pobieranie zawartości z pliku .sql
        database_create = open('base.sql','r') 
        # Execute poleceń tworzących niezbęde tabele, wiązania i role z pliku .sql
        cur.execute(database_create.read())
        # Commit zmian w bazie danych
        conn.commit()
        print '{"status" : "OK"}'
    except Exception:
        # Rollback w przypadku błędów w pliku .sql
        conn.rollback()
        # Gdy open się nie powiedzie - kończymy cały program
        print '{"status" : "ERROR", "debug" : "Polecenie open się nie udało - program kończy pracę" }' 
        sys.exit(0)  


# Funkcja przetwarzająca jsona <open> podczas kolejnych uruchomień programu
def f_open_app(arg):
    try:
        # Ustanowienie połączenia między bazą danych
    	# Dane dostępowe są pobrane z obiektu json
        global conn
        conn = psycopg2.connect(host="localhost", port="5432",
                                dbname=arg['open']['database'],
                                user=arg['open']['login'],
                                password=arg['open']['password'])
        # Inicjalizacja kursora odpowiadającego za polecenia bazodwanowe
        global cur
        cur = conn.cursor()
        print '{"status" : "OK"}'
    except Exception:
        # Gdy open się nie powiedzie - kończymy cały program
        print '{"status" : "ERROR", "debug" : "Polecenie open się nie udało - program kończy pracę" }' 
        sys.exit(0)  


# Sprawdzanie czy istnieje wolne ID w bazie danych
def check_id(id_num):
    cur.execute("SELECT * FROM global_ids WHERE ID = %s;", (id_num,))    
    wynik = len(cur.fetchall())
    return wynik == 0


# Funkcja dodająca krotkę member do bazy
def add_member(member, password, timestamp, is_leader):
    # Dodawanie membera wraz z haszowaniem hasła oraz dodawanie ID do tabeli z globalnymi id
    cur.execute("""INSERT INTO member (ID, leader, activity, password, activity_date) 
                       VALUES (%s, %s, True, crypt(%s, gen_salt('md5')), to_timestamp(%s));
                   INSERT INTO global_ids (ID) VALUES (%s);""",
                (member, is_leader, password, timestamp, member))


# Funkcja przetwarzająca jsona <leader>
def f_leader(arg):
    # Sprawdzamy czy istnieje taki member/ czy istnieje gdzieś takie ID
    if check_id(arg['leader']['member']): 
        # Jeżeli nie ma znalezionych krotek/ nie istnieje nic o takim id - droga wolna do dodania membera(leadera)
        try:
            add_member(arg['leader']['member'], arg['leader']['password'], arg['leader']['timestamp'], True)
            conn.commit()
            print '{"status" : "OK"}'
        except Exception:
            # Rollback jeśli coś poszło nie tak
            conn.rollback()
            print '{"status" : "ERROR", "debug" : "Nie można dodać członka (w funkcji leader)" }' 
    else: 
        # Jezeli znaleziono krotki - id jest juz zajete, więc nie można dodać takiego leadera
        print '{"status" : "ERROR", "debug" : "ID jest już używany" }'   


# Funkcja sprawdzająca czy istnieje member o danym id 
# [Jeśli istnieje -> zwracamy krotkę (poprawność_hasła, aktywność, różnica w czasie aktywności, czy_leader),
# Jeśli nie istnieje -> zwracamy None]
# Zwracamy aktywność membera, oraz liczymy różnicę pomiędzy czasami aktywności 
# (do późniejszego sprawdzenia czy należy już zamrozić użytkownika czy nie)
def check_member(id_num, password, timestamp):                        
    cur.execute("""SELECT password = crypt(%s, password), activity, age(to_timestamp(%s), activity_date), leader 
                    FROM member WHERE ID = %s;""",
                (password, timestamp, id_num))    
    krotki = cur.fetchall()
    if len(krotki) == 1: 
	# Musimy mieć dokładnie jedną krotkę (poprawność_hasła, aktywność, różnica w czasie, czy_leader) dotyczącą jednego membera
        return krotki[0]
    else:
        return None


# Autoryzacja istniejącego membera lub jego utworzenie
# Zwracamy true(1) jeśli wszystko się powiodło, wpp false(0)
def authorize_or_create_member(member, password, timestamp):
    mem = check_member(member, password, timestamp)
    # Jeśli znaleziono membera o takim id
    if mem:
        # Jeśli hasło poprawne       
        if mem[0]:
            # Jeśli użytkownik nadal aktywny
            if mem[1]:
                #Sprawdzamy różnicę czasów i aktualizujemy
                interval = mem[2].days
                if interval > 365:
                    # User był aktywny - ale różnica większa niż rok (trzeba go uśpić)
                    print '{"status" : "ERROR", "debug" : "Członek jest już nieaktywny"}'
                    return 0
                else:
                    # User był aktwyny - i różnica mniejsza niż rok -> aktualizacja daty ostatniej aktywności
                    # Aktualizacja daty aktywności
                    cur.execute("UPDATE member SET activity_date = to_timestamp(%s) WHERE id = %s;", (timestamp, member,))   
                    return 1
            else:
                # Nieaktwny (zamrożony) member
                print '{"status" : "ERROR", "debug" : "Członek jest nieaktywny"}'
                return 0
        else:
            # Niepoprawne hasło
            print '{"status" : "ERROR", "debug" : "Niepoprawne hasło"}'
            return 0
    else:
        # Należy utworzyć membera
        if check_id(member):
            try:
                add_member(member, password, timestamp, False) #false = bo nie jest to leader
                return 1
            except Exception :
                # W przypadku braku możliwości dodania krotki w member, kończymy funkcję zewnętrzną
                conn.rollback()
                print '{"status" : "ERROR", "debug" : "Nie można dodać nowego członka" }'
                return 0 
        else:
            # ID jest już gdzieś używane
            print '{"status" : "ERROR", "debug" : "ID jest zajęte"}'
            return 0          


# Sprawdzanie istnienia projektu o zadanym ID
def find_project(project):
    cur.execute("SELECT * FROM project WHERE id = %s;", (project,))
    wynik = len(cur.fetchall())
    return wynik == 1


# Sprawdzanie istnienia authority o zadanym ID
def find_authority(authority):
    cur.execute("SELECT * FROM authority WHERE id = %s;", (authority,))
    wynik = len(cur.fetchall())
    return wynik == 1


# Utworzenie akcji dotyczącej projektu 
def create_action(p_or_s, action, project, authority, member):
    # Jeśli mamy wolne id
    if check_id(action):
        #Jeśli znajdziemy już istniejący projekt
        if find_project(project):
            try:
                # Tworzenie akcji do istniejącego projektu
                cur.execute("INSERT INTO global_ids (id) VALUES (%s);", (action,))
                cur.execute("INSERT INTO action (id, type, memberID, projectID) VALUES (%s, %s, %s, %s);",
                            (action, p_or_s, member, project))
                return 1
            except Exception:
                return 0
        #Jeśli nie istnieje żaden projekt
        else:
            try:
                # Dodajemy authority jeśli nie istniało żadne wcześniej oraz gdy globalne id jest wolne
                there_is_authority = find_authority(authority)
                if not there_is_authority and check_id(authority): 
                    cur.execute("INSERT INTO global_ids (id) VALUES (%s);", (authority,))
                    cur.execute("INSERT INTO authority (id) VALUES (%s);", (authority,))
                    there_is_authority = True
                if there_is_authority:
                    # Dodajemy projekt jeśli globalne id jest wolne
                    if check_id(project): 
                        cur.execute("INSERT INTO global_ids (id) VALUES (%s);", (project,))
                        cur.execute("INSERT INTO project (id, authorityID) VALUES (%s, %s);", (project, authority))
                    else:
                        return 0
                    # Tworzymy akcję do wcześniej utworzonego projektu 
                    cur.execute("INSERT INTO global_ids (id) VALUES (%s);", 
                                (action,))
                    cur.execute("INSERT INTO action (id, type, memberID, projectID) VALUES (%s, %s, %s, %s);", 
                                (action, p_or_s, member, project))
                    return 1
                else:
                    return 0
            except Exception:
                return 0
    else:
        # ID action jest już w użyciu
        return 0   
    return 0      


# Funkcja przetwarzająca jsona <protest>
def f_protest(arg):
    if authorize_or_create_member(arg['protest']['member'], arg['protest']['password'], arg['protest']['timestamp']):  
        # Opcjonalny argument authority
        if 'authority' in arg['protest']: authority = arg['protest']['authority']
        else: authority = None
        # Wywołanie funkcji tworzącej akcję
        if create_action('protest', arg['protest']['action'], arg['protest']['project'], authority, arg['protest']['member']):
            conn.commit()
            print '{"status" : "OK"}'
        else: 
            conn.rollback()
            print '{"status" : "ERROR", "debug" : "Nie można dodać akcji"}'
    else:
        conn.rollback()


# Funkcja przetwarzająca jsona <support>
def f_support(arg):
    if authorize_or_create_member(arg['support']['member'], arg['support']['password'], arg['support']['timestamp']):  
        # Opcjonalny argument authority
        if 'authority' in arg['support']: authority = arg['support']['authority']
        else: authority = None
        # Wywołanie funkcji tworzącej akcję
        if create_action('support', arg['support']['action'], arg['support']['project'], authority, arg['support']['member']):
            conn.commit()
            print '{"status" : "OK"}'
        else: 
            conn.rollback()
            print '{"status" : "ERROR", "debug" : "Nie można dodać akcji"}'
    else:
        conn.rollback()


# Sprawdzamy czy member już oddał głos na action
def find_vote(member, action):
    cur.execute("SELECT * FROM vote WHERE memberID = %s AND actionID = %s;", (member, action))
    wynik = len(cur.fetchall())
    return wynik == 1


# Szukamy danej akcji i zwracamy membera który ją stworzył
def find_action(action):
    cur.execute("SELECT memberID FROM action WHERE id = %s;", (action,))
    wynik = cur.fetchall()
    if len(wynik) == 1:
        return wynik[0]
    else:
        return None


# Funkcja oddająca głos przez użytkownika
def vote(for_or_against, member, action):
    if find_vote(member, action):
        # Jeśli głos już oddano, nie można oddać dalej głosu
        return 0
    else:
        krotka = find_action(action)
        # Jeśli akcja została wcześniej poprawnie dodana
        if krotka:
            try:
                if for_or_against == 1: boolean = True
                else: boolean = False
                # Znajdujemy akcję (zawiera info o autorze akcji)
                # Tu już wiemy że i action i member autor istnieją
                cur.execute("INSERT INTO vote (value, memberID, actionID) VALUES (%s, %s, %s);", (boolean, member, action))
                # Dodajemy wartości z vote w odpodnie pola w action
                if for_or_against == 1: cur.execute("UPDATE action SET positive_votes = positive_votes + 1 WHERE id = %s;", (action,))
                if for_or_against == -1: cur.execute("UPDATE action SET negative_votes = negative_votes + 1 WHERE id = %s;", (action,))
                # Dodajemy wartość w ratio autora akcji
                if for_or_against == 1: cur.execute("UPDATE member SET action_ratio = action_ratio - 1, action_up = action_up + 1 WHERE id = %s;", (krotka[0],))
                if for_or_against == -1: cur.execute("UPDATE member SET action_ratio = action_ratio + 1 WHERE id = %s;", (krotka[0],))
                return 1
            except Exception as err:
                return 0
        else:
            #Taka akcja nie istnieje
            return 0
    return 0


# Funkcja przetwarzająca jsona <upvote>
def f_upvote(arg):
    # Jeżeli nie było błędów podczas autoryzacji membera/dodawania go
    if authorize_or_create_member(arg['upvote']['member'], arg['upvote']['password'], arg['upvote']['timestamp']):
        # Oddajemy głos 
        if vote(1, arg['upvote']['member'], arg['upvote']['action']):
            conn.commit()
            print '{"status" : "OK"}'
        else:
            conn.rollback()   
            print '{"status" : "ERROR", "debug" : "Nie można oddać głosu (za)"}'
    else:
        conn.rollback()   


# Funkcja przetwarzająca jsona <downvote>
def f_downvote(arg):
    # Jeżeli nie było błędów podczas autoryzacji membera/dodawania go
    if authorize_or_create_member(arg['downvote']['member'], arg['downvote']['password'], arg['downvote']['timestamp']):  
        # Oddajemy głos 
        if vote(-1, arg['downvote']['member'], arg['downvote']['action']):
            conn.commit()
            print '{"status" : "OK"}'
        else:
            conn.rollback()   
            print '{"status" : "ERROR", "debug" : "Nie można oddać głosu (przeciw)"}'
    else:
        conn.rollback() 


# Funkcja sprawdzająca leadera 
def authorize_leader(member, password, timestamp):
    mem = check_member(member, password, timestamp)
    # Jeśli znaleziono membera o takim id
    if mem:
        # Jeśli jest leaderem
        if mem[3]:
            # Jeśli hasło poprawne       
            if mem[0]:
                # Jeśli użytkownik nadal aktywny
                if mem[1]:
                    #Sprawdzamy różnicę czasów i aktualizujemy
                    interval = mem[2].days
                    if interval > 365:
                        # User był aktywny - ale różnica większa niż rok 
                        return 0
                    else:
                        # User był aktwyny - i różnica mniejsza niż rok -> aktualizacja daty ostatniej aktywności
                        # Aktualizacja daty aktywności
                        cur.execute("UPDATE member SET activity_date = to_timestamp(%s) WHERE id = %s;", (timestamp, member,))                                
                        return 1
                else:
                    # Nieaktwny (zamrożony) member
                    return 0
            else:
                # Niepoprawne hasło
                return 0
        else:
            #member nie jest leaderem
            return 0
    else:
        #Nie ma takiego membera
        return 0


# Sprawdzanie aktywności wszystkich użytkowników
def skan(timestamp):
    try:
        # Aktualizujemy zawartość acitivity jeśli interval pomiędzy datą ostatniej aktywności a naszym timestampem
        # jest większy niż rok
        cur.execute("""UPDATE member SET activity = False 
                       WHERE activity_date <= (to_timestamp(%s) - interval '1 year'); """, (timestamp,))
        # last_activity_date musi się zawierać w (timestamp - 1year) by użytkownik był nadal aktywny
        conn.commit()
        return 1    
    except Exception as err:
        return 0


# Funkcja pomocnicza do formatowania stringu w "data"
def format_fetch(wynik):
    wynik = str(map(list, wynik)).replace('L', '')
    #wynik = wynik.replace('True', '"true"').replace('False', '"false"').replace('L', '')
    return wynik


# Funkcja przetwarzająca jsona <actions>
def f_actions(arg):
    # Sprawdzamy istnienie leadera, jego hasło i aktywność
    if authorize_leader(arg['actions']['member'], arg['actions']['password'], arg['actions']['timestamp']):
        try:
            # Sprawdzamy czy użyto opcjonalnego argumentu 'type'
            if 'type' in arg['actions']:
                # Sprawdzamy wszystkie pozostałe opcjonalne argumenty
                if 'project' in arg['actions']:
                    cur.execute("""SELECT action.id, action.type, action.projectID, project.authorityID, positive_votes, negative_votes FROM action
                                    JOIN project ON(action.projectID = project.id)
                                    WHERE action.type = %s AND project.id = %s
                                    ORDER BY action.id;""", (arg['actions']['type'],arg['actions']['project']) )
                elif 'authority' in arg['actions']:
                    cur.execute("""SELECT action.id, action.type, action.projectID, project.authorityID, positive_votes, negative_votes FROM action
                                    JOIN project ON(action.projectID = project.id)
                                    WHERE action.type = %s AND project.authorityID = %s
                                    ORDER BY action.id;""", (arg['actions']['type'],arg['actions']['authority']) )
                else:
                    cur.execute("""SELECT action.id, action.type, action.projectID, project.authorityID, positive_votes, negative_votes FROM action
                                    JOIN project ON(action.projectID = project.id)
                                    WHERE action.type = %s
                                    ORDER BY action.id;""", (arg['actions']['type'],))
            else:
                # Sprawdzamy wszystkie pozostałe opcjonalne argumenty (ale bez dodatkowego argumentu 'type')
                if 'project' in arg['actions']:
                    cur.execute("""SELECT action.id, action.type, action.projectID, project.authorityID, positive_votes, negative_votes FROM action
                                    JOIN project ON(action.projectID = project.id)
                                    WHERE project.id = %s
                                    ORDER BY action.id;""", (arg['actions']['project'],) )
                elif 'authority' in arg['actions']:
                    cur.execute("""SELECT action.id, action.type, action.projectID, project.authorityID, positive_votes, negative_votes FROM action
                                    JOIN project ON(action.projectID = project.id)
                                    WHERE project.authorityID = %s
                                    ORDER BY action.id;""", (arg['actions']['authority'],) )
                else:
                    cur.execute("""SELECT action.id, action.type, action.projectID, project.authorityID, positive_votes, negative_votes FROM action
                                    JOIN project ON(action.projectID = project.id)
                                    ORDER BY action.id;""")
            # Pobieramy i formatujemy krotki wynikowe
            wynik = cur.fetchall()
            print '{"status" : "OK", "data" : %s}' % format_fetch(wynik).replace("'", '"')
        except Exception:
            print '{"status" : "ERROR", "debug" : "Błąd podczas zapytania bazodanowego" }' 
    else:
        print '{"status" : "ERROR", "debug" : "Błąd leadera"}'  


# Funkcja przetwarzająca jsona <projects>
def f_projects(arg):
    # Sprawdzamy istnienie leadera, jego hasło i aktywność
    if authorize_leader(arg['projects']['member'], arg['projects']['password'], arg['projects']['timestamp']):
        try:
            # Sprawdzamy dodatkowy argument 'authority'
            if 'authority' in arg['projects']:
                cur.execute("SELECT id, authorityID FROM project WHERE authorityID = %s ORDER BY id;", (arg['projects']['authority'],))
            else:
                cur.execute("SELECT id, authorityID FROM project ORDER BY id;")
            # Pobieramy i formatujemy krotki wynikowe
            wynik =  cur.fetchall()
            print '{"status" : "OK", "data" : %s}' % format_fetch(wynik).replace("'", '"')
        except Exception:
            print '{"status" : "ERROR", "debug" : "Błąd podczas zapytania bazodanowego" }' 
    else:
        print '{"status" : "ERROR", "debug" : "Błąd leadera"}'  


# Funckja pomocnicza przewarzająca krotki z bazy na krotki wynikowe
# Potrzebujemy (id, upvotes, downvotes)
def helper_votes_tuple(tuples):
    return (tuples[0], tuples[1], tuples[2]-tuples[1])


# Funkcja przetwarzająca jsona <votes>
def f_votes(arg):
    # Sprawdzamy istnienie leadera, jego hasło i aktywność
    if authorize_leader(arg['votes']['member'], arg['votes']['password'], arg['votes']['timestamp']):
        try:
            # Sprawdzamy opcjonalny argument 'action'
            if 'action' in arg['votes']:
                cur.execute("""SELECT mem.id, sum(case when value then 1 else 0 end) as votes_for, count(value) as votes 
                                FROM MEMBER as mem LEFT JOIN
                                (SELECT member.id, vote.value, action.id as actionid, project.id as projectid, project.authorityid as authorityid
                                FROM member
                                    LEFT JOIN vote ON(member.id = vote.memberID)
                                    LEFT JOIN action ON(vote.actionid = action.id)
                                    LEFT JOIN project ON(action.projectid = project.id)
                                WHERE action.id = %s
                                ) as foo ON(mem.id = foo.id)
                                GROUP BY mem.id ORDER BY mem.id;""", (arg['votes']['action'],))
            # Sprawdzamy opcjonalny argument 'project'
            elif 'project' in arg['votes']:
                cur.execute("""SELECT mem.id, sum(case when value then 1 else 0 end) as votes_for, count(value) as votes 
                                FROM MEMBER as mem LEFT JOIN
                                (SELECT member.id, vote.value, action.id as actionid, project.id as projectid, project.authorityid as authorityid
                                FROM member
                                    LEFT JOIN vote ON(member.id = vote.memberID)
                                    LEFT JOIN action ON(vote.actionid = action.id)
                                    LEFT JOIN project ON(action.projectid = project.id)
                                WHERE action.projectid = %s
                                ) as foo ON(mem.id = foo.id)
                                GROUP BY mem.id ORDER BY mem.id;""", (arg['votes']['project'],))
            # W przypadku braku opcjonalnych argumentów
            else:
                cur.execute("""SELECT mem.id, sum(case when value then 1 else 0 end) as votes_for, count(value) as votes 
                                FROM MEMBER as mem LEFT JOIN
                                (SELECT member.id, vote.value, action.id as actionid, project.id as projectid, project.authorityid as authorityid
                                FROM member
                                    LEFT JOIN vote ON(member.id = vote.memberID)
                                    LEFT JOIN action ON(vote.actionid = action.id)
                                    LEFT JOIN project ON(action.projectid = project.id)
                                ) as foo ON(mem.id = foo.id)
                                GROUP BY mem.id ORDER BY mem.id;""")
            # Pobieramy i formatujemy krotki wynikowe
            wynik = cur.fetchall()
            wynik = map(helper_votes_tuple, wynik)
            print '{"status" : "OK", "data" : %s}' % format_fetch(wynik).replace("'", '"')
        except Exception:  
            print '{"status" : "ERROR", "debug" : "Błąd podczas zapytania bazodanowego" }' 
    else:
        print '{"status" : "ERROR", "debug" : "Błąd leadera"}'        


# Funkcja przetwarzająca jsona <trolls>
def f_trolls(arg):
    # Funkcja skan powinna zwrócić 1 gdy nie napotkano żadnych błędów podczas update'u w bazie_danych
    if skan(arg['trolls']['timestamp']):                                                  
        cur.execute("""SELECT id, action_up, action_ratio + action_up, activity FROM member
                       WHERE action_ratio > 0 ORDER BY action_ratio desc, id;""")
        # Pobieramy i formatujemy krotki wynikowe
        wynik = cur.fetchall()
        print '{"status" : "OK", "data" : %s}' % format_fetch(wynik).replace('True', '"true"').replace('False', '"false"')    
    else:
        print '{"status" : "ERROR", "debug" : "błąd bazy danych - update aktywności"}' 


# Funkcja przyporządkowująca odpowiednie funkcje do dalszej obróbki jsonów 
def if_case(dic, case):
    if args.init:
        if case == 'open':
            f_open_init(dic)
        elif case == 'leader':
            f_leader(dic)
        else:
            # Koniec - zakładamy ze dane jsony są poprawne -> nie zwrócimy błędów
            print '{"status": "ERROR", "debug": "Niepoprawne wywołania init"}'
    else:
        if case == 'open':
            f_open_app(dic)
        elif case == 'protest':
            f_protest(dic)
        elif case == 'support':
            f_support(dic)
        elif case == 'upvote':
            f_upvote(dic)
        elif case == 'downvote':
            f_downvote(dic)
        elif case == 'actions':
            f_actions(dic)
        elif case == 'projects':
            f_projects(dic)
        elif case == 'votes':
            f_votes(dic)
        elif case == 'trolls':
            f_trolls(dic)
        else:
            # Koniec - zakładamy ze dane jsony są poprawne -> nie zwrócimy błędów
            print '{"status": "ERROR", "debug": "Brak uprawnień init/ nieobsługiwany json"}'


# Funkcja czytająca w pętli na standardowym wejściu
def from_standard_input():
    while True:
        try:
            # Czytanie ze standardowego wejścia linii z jsonami w tekście
            line = sys.stdin.readline()
            if not line:
                break
            # Wczytanie tekstu i przetworzenie jsona
            dic = json.loads(line)
            # Case funkcji       
            case = dic.keys()[0] 
            if_case(dic, case)
        except KeyboardInterrupt as err:
            #Koniec pracy programu - przerwanie użytkownika
            break
        except Exception:
            print '{"status" : "ERROR", "debug" : "Błąd json - prawdopodobny brak argumentu (lub niepoprawna zawartość)" }'    


# Czytanie z pliku wejściowego (flaga --f)
def from_file():
    # Przetwarzanie linijek pliku wejściowego
    for line in args.f[0]:
        try:
            # Wczytanie jsona
            dic = json.loads(line)
            # Case funkcji       
            case = dic.keys()[0]
            if_case(dic, case)
        except Exception:
            print '{"status" : "ERROR", "debug" : "Błąd json - prawdopodobny brak argumentu (lub niepoprawna zawartość)" }'    
            

# Przygotowanie parsera argumentów
parser = argparse.ArgumentParser(description='System Zarządzania Partią Polityczną')
parser.add_argument("--f", 
                       type=file,
                       nargs=1, 
                       help="Flaga wywołania z pliku, wymaga argumentu w postaci ścieżki pliku z danymi json")
parser.add_argument("--init", 
                       action="store_true", 
                       help="Flaga pierwszego wywołania")
args = parser.parse_args()
# Jeżeli flaga --f => czytaj z pliku na starcie
if args.f:
        from_file()
        from_standard_input()
else:
        from_standard_input()





