# Projekt: System Zarządzania Partią Polityczną.

## Opis systemu

Partia prowadzi rejestr działań rządowych i samorządowych, które wspiera lub przeciw którym protestuje.

Partią zarządza zespół liderów będących członkami partii.

Członkowie partii mogą proponować akcje oraz głosować za i przeciw ich prowadzeniu.

Członkiem partii zostaje się poprzez aktywny udział w jej życiu. Po roku nieaktywności, rozumianej jako brak wywołań funkcji API autoryzowanych danymi danej osoby, traci się prawa członka partii, a takie konto jest trwale zamrażane (tzn. dany członek nie może wykonać żadnej czynności, ale wszystkie informacje na jego temat są dalej przechowywane i raportowane). Zasada ta dotyczy wszystkich członków partii, również liderów (nie należy się martwić o to co się dzieje z partią po zamrożeniu wszystkich liderów).


## Technologie

System Linux. Język programowania dowolny – wybór wymaga zatwierdzenia przez prowadzącego pracownię - zalecany język Python. Baza danych – PostgreSQL w wersji >=9.5. Testy będą przeprowadzane na komputerze z Ubuntu 18.04, PostgreSQL 10.7 .

## Implementacja

Twój program po uruchomieniu powinien przeczytać ze standardowego wejścia ciąg wywołań funkcji API, a wyniki ich działania wypisać na standardowe wyjście.

Wszystkie dane powinny być przechowywane w bazie danych, efekt działania każdej funkcji modyfikującej bazę, dla której wypisano potwierdzenie wykonania (wartość OK) powinien być utrwalony. Program będzie uruchamiany wielokrotnie z następującymi parametrami:

- pierwsze uruchomienie - program wywołany z parametrem `--init`

Wejście zawiera w pierwszym wierszu wywołanie funkcji open z następującymi danymi login: init, password: qwerty, w kolejnych wierszach wywołania funkcji leader.

- kolejne uruchomienia

Wejście zawiera w pierwszym wierszu wywołanie funkcji open z następującymi danymi login: app, password: qwerty, a następnie wywołania dowolnych funkcji API za wyjątkiem funkcji open i leader.

## Dodatkowe informacje i założenia 
- Można założyć, że przed uruchomieniem z parametrem --init baza nie zawiera jakichkolwiek tabel.
- Baza danych oraz użytkownik init będą istnieli w momencie pierwszego uruchomienia bazy.
- Przy pierwszym uruchomieniu program powinien utworzyć wszystkie niezbędne elementy bazy danych (tabele, więzy, funkcje wyzwalacze, użytkownik app z odpowiednimi uprawnieniami) zgodnie z przygotowanym przez studenta modelem fizycznym.
- Należy utworzyć użytkownika app, nadać mu odpowiednie uprawnienia i hasło (moduł pgcrypto będzie dostępny).
- Hasła należy przechowywać w bezpieczny sposób.
- Baza nie będzie modyfikowana pomiędzy kolejnymi uruchomieniami.
- Program nie będzie miał praw do tworzenia i zapisywania jakichkolwiek plików. 
- Program będzie mógł czytać pliki z bieżącego katalogu (np. dołączony do rozwiązania studenta plik .sql zawierający polecenia tworzące niezbędne elementy bazy).
 

## Format wejścia

Każda linia pliku wejściowego zawiera obiekt JSON (http://www.json.org/json-pl.html). Każdy z obiektów opisuje wywołanie jednej funkcji API wraz z argumentami.

Przykład: 

Obiekt
```
{ "leader": { "timestamp": 1557475000, "password": "abcde", "member": 1}} 
```
oznacza wywołanie funkcji o nazwie `leader` z argumentem `timestamp` przyjmującym wartość `1557475000`, argumentem `password` - wartość `abcde` oraz `member` – wartość `1`.

W pierwszej linii wejścia znajduje się wywołanie funkcji open z argumentami umożliwiającymi nawiązanie połączenia z bazą danych.


## Format wyjścia

Dla każdego wywołania wypisz w osobnej linii obiekt JSON zawierający obiekt z polami: status (zwracane zawsze), data (tylko dla funkcji zwracających krotki), debug (opcjonalne). 

Wartość pola status to "OK" albo "ERROR".
 
Tabela data zawiera wszystkie krotki wynikowe. Każda krotka to tabela zawierająca wartości wszystkich jej atrybutów w kolejności podanej w specyfikacji.

Dopuszczalna jest dodatkowa para o kluczu debug i wartości typu string z ew. informacją przydatną w debugowaniu (jest ona całkowicie dobrowolna i będzie ignorowana w czasie testowania, powinna mieć niewielki rozmiar).


## Przykładowe wejście i wyjście

Pierwsze uruchomienie (z parametrem `--init`):
```
{ "open": { "database": "student", "login": "init", "password": "qwerty"}}
{ "leader": { "timestamp": 1557473000, "password": "abc", "member": 1}}
{ "leader": { "timestamp": 1557474000, "password": "asd", "member": 2}}
```

###### Oczekiwane wyjście
```
{"status": "OK"}
{"status": "OK"}
{"status": "OK"}
```

###### Kolejne uruchomienie:
```
{ "open": { "database": "student", "login": "app", "password": "qwerty"}}
{ "protest": { "timestamp": 1557475700, "password": "123", "member": 3, "action":500, "project":5000, "authority":10000}}
{ "support": { "timestamp": 1557475701, "password": "123", "member": 3, "action":600, "project":5000}}
{ "upvote": { "timestamp": 1557475702, "password": "asd", "member": 2, "action":500}}
{ "downvote": { "timestamp": 1557475703, "password": "abc", "member": 1, "action":500}}
{ "downvote": { "timestamp": 1557475704, "password": "abc", "member": 1, "action":600}}
{ "votes": { "timestamp": 1557475705, "password": "abc", "member": 1}}
{ "trolls": { "timestamp": 1557477055 }}
```

###### Oczekiwane wyjście (dla czytelności zawiera znaki nowej linii, pierwsza linia powtarza się 6 razy)
```
{"status": "OK"}
...
{"status": "OK",
  "data": [[ 1, 0, 2],
           [ 2, 1, 0],
           [ 3, 0, 0]]
}
{"status": "OK",
  "data": [ [ 3, 1, 2, "true"] ]
}
```
## Format opisu API
```
<function> <arg1> <arg2> … <argn> // nazwa funkcji oraz nazwy jej argumentów
```
opis działania funkcji

// lista atrybutów wynikowych tabeli data lub informacja o braku tego pola

## Wywołania API

Identyfikatory `<member>`, `<action>`, `<project>`, `<authority>` są typu number i są globalnie unikalne (tzn. nie może zdarzyć się, że np. wartość `<member>` jest równa wartości `<authority>`). **Każde wywołanie skutkujące naruszeniem globalnej unikalności  identyfikatorów powinno zwrócić błąd**. 

Wartość `<password>` jest typu string, jej długość nie przekracza 128 znaków.

Wartość `<timestamp>` jest typu number i reprezentuje UNIX timestamp. **Gwarantowane jest, że wszystkie wywołania będą podane na wejściu w kolejności rosnących timestampów.**

Argumenty funkcji w nawiasach `[ ]` są opcjonalne (tzn. nie muszą być podane w wywołaniu funkcji).

**Można założyć, że wszystkie wywołania będą zawsze w prawidłowym formacie, a wszystkie wartości będą odpowiedniego typu.**

###### Status "ERROR"

Jeśli wywołanie funkcji nie odpowiada niniejszej specyfikacji należy zwrócić status "ERROR" (nie piszemy wariantów fail-safe itp.).

Jeśli wywołanie funkcji jest autoryzowane danymi członka pozbawionego praw należy zwrócić status "ERROR".


## Nawiązywanie połączenia i definiowanie liderów


###### open

```
open <database> <login> <password>
```
Przekazuje dane umożliwiające podłączenie Twojego programu do bazy - nazwę bazy, login oraz hasło, wywoływane dokładnie jeden raz, w pierwszej linii wejścia

// nie zwraca pola data

###### leader

```
leader <timestamp> <password> <member>
```
Tworzy nowego członka partii, który będzie jej liderem o unikalnym identyfikatorze `<member>` z hasłem `<password>`. 
Jest uznawane jako wzięcie aktywnego udziału w życiu partii w momencie `<timestamp>`.

// nie zwraca pola data


## Lista funkcji API

###### support protest

```
support <timestamp> <member> <password> <action> <project> [ <authority> ]

protest <timestamp> <member> <password> <action> <project> [ <authority> ]
```

Dodawanie nowej akcji `<action>` wsparcia (support) lub sprzeciwu (protest) wobec działania `<project>` prowadzonego przez organ władzy `<authority>`. 
* Jeśli `<member>` jest członkiem partii to `<password>` musi być jego hasłem.  
* Jeśli członek o podanym id nie istnieje dodawany jest nowy członek o podanym id i haśle. 
* Jeśli id jest zamrożone to jest zgłaszany błąd. 
* Jeśli `<project>` jest działaniem dodanym wcześniej to wartość `<authority>` jest ignorowana, wpp `<authority>` musi być podana.

// nie zwraca pola data

###### upvote downvote

```
upvote <timestamp> <member> <password> <action> 

downvote <timestamp> <member> <password> <action> 
```

Członek `<member>` głosuje za (upvote) albo przeciw (downvote) przeprowadzeniu akcji `<action>`.

* Można głosować co najwyżej jeden raz w sprawie każdej akcji.

* Jeśli `<member>` jest członkiem partii to `<password>` musi być jego hasłem.  
* Jeśli członek o podanym id nie istnieje dodawany jest nowy członek o podanym id i haśle. 
* Jeśli id jest zamrożone to jest zgłaszany błąd. 
* Jeśli akcja `<action>` nie została wcześniej dodana to jest zgłaszany błąd.

// nie zwraca pola data

###### actions
```
actions <timestamp> <member> <password> [ <type> ] [ <project> | <authority> ] 
```

Zwraca listę wszystkich akcji wraz z typem, id projektu, id organu władzy oraz z liczbami głosów za i przeciw akcji z następującymi zastrzeżeniami:

* Jeśli podano `<type>` w postaci tekstu "support" albo "protest" należy ograniczyć się do akcji podanego typu.
* Jeśli podano `<project>` należy ograniczyć się do akcji dotyczących danego `<project>`.
* Jeśli podano `<authority>` należy ograniczyć się do akcji dotyczących działań danego `<authority>`.
* `<password>` to hasło członka `<member>` będącego liderem.

Atrybuty zwracanych krotek, krotki muszą być posortowane wg `<action>` rosnąco
```
// <action> <type> <project> <authority> <upvotes> <downvotes>
```

###### projects

```
projects <timestamp> <member> <password> [ authority ]
```

Zwraca listę wszystkich działań wraz z id organu władzy prowadzącego dane działanie.
* Jeśli `<authority>` jest podane to zwraca wyłącznie działania podanego `<authority>`
* `<password>` to hasło członka `<member>` będącego liderem.

Atrybuty zwracanych krotek, krotki muszą być posortowane wg `<project>` rosnąco
```
// <project> <authority>
```

###### votes

```
votes <timestamp> <member> <password> [ <action> | <project> ]
```

Zwraca listę wszystkich członków (w tym tych, którzy do tej pory nie głosowali) wraz z sumarycznymi liczbami oddanych przez nich głosów za (`<upvotes>`) i przeciw (`downvotes`).
* Jeśli podano `<action>` to wynik powinien ograniczyć się do głosów dotyczących akcji `<action>`
* Jeśli podano `<project>` to wynik powinien ograniczyć się do głosów dotyczących akcji związanych z projektem `<project>`

`<password>` to hasło członka `<member>` będącego liderem.

Atrybuty zwracanych krotek, krotki muszą być posortowane wg `<member>` rosnąco
```
// <member> <upvotes> <downvotes>
```

###### trolls

```
trolls <timestamp>
```

Zwraca listę wszystkich użytkowników, którzy zaproponowali akcje mające sumarycznie więcej downvotes niż upvotes wg stanu na chwilę `<timestamp>`. Z wstępnych badań wynika, że ranking trolli będzie bardzo często używaną funkcją, zaprojektuj bazę tak aby ta funkcja działała szybko.

Atrybuty zwracanych krotek, krotki muszą być posortowane wg wartości różnicy `<downvotes> - <upvotes>` malejąco, w drugiej kolejności wg `<member>` rosnąco, atrybut `<active>` to wartość "true"/"false" w zależności od tego czy dany członek zachowuje prawa członka.
```
// <member> <upvotes> <downvotes> <active>
```
