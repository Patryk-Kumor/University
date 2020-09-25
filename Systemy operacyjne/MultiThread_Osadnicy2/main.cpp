#include "iostream"
#include <fstream>
#include <pthread.h>
#include <deque>
#include <unistd.h>


using namespace std;


//Klasa przetrzymująca terminy przydatności do spożycia
class Jedzenie
{
public:
    deque<int> food;
    int food_termin;
    Jedzenie()
    {
        deque<int> food;
    }
    Jedzenie(int ilosc, int termin)
    {
	food_termin = termin;
        int i;
        for (i=0; i<ilosc; i++)
        {
            food.push_back(termin);
        }
    }
    int Ile()
    {
        return food.size();
    }
    void Termin()
    {
        int i; int ile_przeterminowanych = 0;
        for (i=0; i<Ile(); i++)
        {
            food[i] -= 1;
            if (food[i] <= 0) { ile_przeterminowanych++; }
        }
        for (i=0; i<ile_przeterminowanych; i++)
        {
            if (Ile() > 0)
            {
                food.pop_front();
            }
        }
    }
    void Usun()
    {
        if (Ile() > 0)
        {
            food.pop_front();
        }
    }
    void Dodaj(int ile)
    {
        for (int i=0; i<ile; i++)
        {
            food.push_back(food_termin);
        }
    }
    void Dodaj()
    {
        food.push_back(food_termin);
    }
    void Wypisz()
    {
        int i;
        for (i=0; i<Ile(); i++)
        {
            cout << food[i] << endl;
        }
    }
};


//Klasa przetrzymująca wiek dorosłych ( >18 ) osadników
class Osadnicy
{
public:
    deque<int> osadnicy;
    int maks_wiek;
    Osadnicy()
    {
        deque<int> osadnicy;
    }
    Osadnicy(int ilosc, int termin)
    {
        maks_wiek = termin;
        int i;
        for (i=0; i<ilosc; i++)
        {
            osadnicy.push_back(18);
        }
    }
    int Ile()
    {
        return osadnicy.size();
    }
    void Wiek()
    {
        int i; int ile_przeterminowanych = 0;
        for (i=0; i<Ile(); i++)
        {
            osadnicy[i] += 1;
            if (osadnicy[i] >= maks_wiek) { ile_przeterminowanych++; }
        }
        for (i=0; i<ile_przeterminowanych; i++)
        {
            if (Ile() > 0)
            {
                osadnicy.pop_back();
            }          
        }
    }
    void Dodaj()
    {
        osadnicy.push_front(18);
    }
    void Usun_Najstarszego()
    {
        if (Ile() > 0)
        {
            osadnicy.pop_back();
        }
    }
    void Usun_Losowego()
    {
    if (Ile() > 0)
    {
        int Maks = osadnicy.size();
        int E = rand()%Maks+1;
        osadnicy.erase(osadnicy.begin()+E);}
    }
    void Wypisz()
    {
        int i;
        for (i=0; i<Ile(); i++)
        {
            cout << osadnicy[i] << endl;
        }
    }
};


//Klasa przetrzymująca wiek dorosłych ( <18 ) osadników
class Dzieci
{
public:
    deque<int> osadnicy;
    int maks_wiek;
    int ile_doroslych;
    Dzieci()
    {
        deque<int> osadnicy;
    }
    Dzieci(int ilosc)
    {
        maks_wiek = 18;
        ile_doroslych = 0;
        int i;
        for (i=0; i<ilosc; i++)
        {
            osadnicy.push_back(1);
        }
    }
    int Ile()
    {
        return osadnicy.size();
    }
    void Wiek()
    {
        int i; int ile_przeterminowanych = 0;
        for (i=0; i<Ile(); i++)
        {
            osadnicy[i] += 1;
            if (osadnicy[i] >= maks_wiek) { ile_przeterminowanych++; }
        }
        for (i=0; i<ile_przeterminowanych; i++)
        {
            osadnicy.pop_back();
        }
        ile_doroslych += ile_przeterminowanych;
    }
    int Dorosli()
    {
        int temp = ile_doroslych;
        ile_doroslych = 0;
        return temp;
    }
    void Dodaj()
    {
        osadnicy.push_front(1);
    }
    void Usun_Najstarszego()
    {
        osadnicy.pop_back();
    }
    void Usun_Losowego()
    {
        int Maks = osadnicy.size();
        int E = rand()%Maks+1;
        osadnicy.erase(osadnicy.begin()+E);
    }
    void Wypisz()
    {
        int i;
        for (i=0; i<Ile(); i++)
        {
            cout << osadnicy[i] << endl;
        }
    }
};


//Czy zima?
bool is_winter;
//Deklaracje globalne zasobów
pthread_mutex_t m_meat = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_plants = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_food = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_wood = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_houses = PTHREAD_MUTEX_INITIALIZER;
Jedzenie meat; 
Jedzenie plants; 
Jedzenie food; 
int wood; 
int houses;
int full_houses;
//Deklaracje globalne aktorów
pthread_mutex_t m_hunters = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_gatherers = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_cooks = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_woodcutters = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_builders = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_kids = PTHREAD_MUTEX_INITIALIZER;
Osadnicy hunters;
Osadnicy gatherers;
Osadnicy cooks;
Osadnicy woodcutters;
Osadnicy builders;
Dzieci kids;


void *hunting(void *arg)
{
    //Łowy
    int H = rand()%6+1;
    int Z = rand()%6+1;
    if ((not is_winter and (H>=Z)) or (is_winter and (H>(Z-2))))
    {
        pthread_mutex_lock(&m_meat);
        if (is_winter) 
        {
            meat.Dodaj(6); 
            pthread_mutex_unlock(&m_meat);
        }
        else
        { 
            meat.Dodaj(4); 
            pthread_mutex_unlock(&m_meat);
        }        
    }
    //Żywienie
    pthread_mutex_lock(&m_food);
    if (food.Ile()>0)
    {
        food.Usun();
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_food);
        pthread_mutex_lock(&m_hunters);
        hunters.Usun_Losowego();
        pthread_mutex_unlock(&m_hunters);
        pthread_exit(NULL);
        return NULL;
    }
    //Sen
    pthread_mutex_lock(&m_houses);
    if (full_houses<houses)
    {
        full_houses++;
        pthread_mutex_unlock(&m_houses);
    }
    else
    {
        pthread_mutex_unlock(&m_houses);
        pthread_mutex_lock(&m_hunters);
        hunters.Usun_Losowego();
        pthread_mutex_unlock(&m_hunters);
        pthread_exit(NULL);
        return NULL;
    }
    pthread_exit(NULL);
    return NULL;
}
void *gathering(void *arg)
{
    //Zbieranie
    int L = rand()%12+1;
    if ((not is_winter and (L>=6)) or (is_winter and (L>=9)))
    {
        pthread_mutex_lock(&m_plants);
        if (is_winter)
        { 
            plants.Dodaj(4);
            pthread_mutex_unlock(&m_plants);
        }
        else
        { 
            plants.Dodaj(8);
            pthread_mutex_unlock(&m_plants);
        }
    }
    //Żywienie
    pthread_mutex_lock(&m_food);
    if (food.Ile()>0)
    {
        food.Usun();
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_food);
        pthread_mutex_lock(&m_gatherers);
        gatherers.Usun_Losowego();
        pthread_mutex_unlock(&m_gatherers);
        pthread_exit(NULL);
        return NULL;
    }
    //Sen
    pthread_mutex_lock(&m_houses);
    if (full_houses<houses)
    {
        full_houses++;
        pthread_mutex_unlock(&m_houses);
    }
    else
    {
        pthread_mutex_unlock(&m_houses);
        pthread_mutex_lock(&m_gatherers);
        gatherers.Usun_Losowego();
        pthread_mutex_unlock(&m_gatherers);
        pthread_exit(NULL);
        return NULL;
    }
    pthread_exit(NULL);
    return NULL;
}
void *cooking(void *arg)
{
    //Gotowanie mięsa
    pthread_mutex_lock(&m_meat);
    if ( meat.Ile() > 0)
    {
        meat.Usun();
        pthread_mutex_unlock(&m_meat);
        int L = rand()%6+1;
        pthread_mutex_lock(&m_food);
        food.Dodaj(L);
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_meat);
    }
    //Gotowanie warzyw
    pthread_mutex_lock(&m_plants);
    if ( plants.Ile() > 0)
    {
        plants.Usun();
        pthread_mutex_unlock(&m_plants);
        int L = rand()%4+1;
        pthread_mutex_lock(&m_food);
        food.Dodaj(L);
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_plants);
    }
    //Żywienie
    pthread_mutex_lock(&m_food);
    if (food.Ile()>0)
    {
        food.Usun();
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_food);
        pthread_mutex_lock(&m_cooks);
        cooks.Usun_Losowego();
        pthread_mutex_unlock(&m_cooks);
        pthread_exit(NULL);
        return NULL;
    }
    //Sen
    pthread_mutex_lock(&m_houses);
    if (full_houses<houses)
    {
        full_houses++;
        pthread_mutex_unlock(&m_houses);
    }
    else
    {
        pthread_mutex_unlock(&m_houses);
        pthread_mutex_lock(&m_cooks);
        cooks.Usun_Losowego();
        pthread_mutex_unlock(&m_cooks);
        pthread_exit(NULL);
        return NULL;
    }
    pthread_exit(NULL);
    return NULL;
}
void *cutting(void *arg)
{
    //Cięcie
    int L = rand()%2;
    if (L == 1)
    {
        pthread_mutex_lock(&m_wood);
        wood++;
        pthread_mutex_unlock(&m_wood); 
    }   
    //Żywienie
    pthread_mutex_lock(&m_food);
    if (food.Ile()>0)
    {
        food.Usun();
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_food);
        pthread_mutex_lock(&m_woodcutters);
        woodcutters.Usun_Losowego();
        pthread_mutex_unlock(&m_woodcutters);
        pthread_exit(NULL);
        return NULL;
    }
    //Sen
    pthread_mutex_lock(&m_houses);
    if (full_houses<houses)
    {
        full_houses++;
        pthread_mutex_unlock(&m_houses);
    }
    else
    {
        pthread_mutex_unlock(&m_houses);
        pthread_mutex_lock(&m_woodcutters);
        woodcutters.Usun_Losowego();
        pthread_mutex_unlock(&m_woodcutters);
        pthread_exit(NULL);
        return NULL;
    }
    pthread_exit(NULL);
    return NULL;
}
void *building(void *arg)
{
    //Budowa
    pthread_mutex_lock(&m_wood);
    if (wood >= 100)
    {
        wood -= 100;
        pthread_mutex_unlock(&m_wood);
        pthread_mutex_lock(&m_houses);
        houses++;
        pthread_mutex_unlock(&m_houses);
    }
    else
    {
        pthread_mutex_unlock(&m_wood);
    }
    //Żywienie
    pthread_mutex_lock(&m_food);
    if (food.Ile()>0)
    {
        food.Usun();
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_food);
        pthread_mutex_lock(&m_builders);
        builders.Usun_Losowego();
        pthread_mutex_unlock(&m_builders);
        pthread_exit(NULL);
        return NULL;
    }
    //Sen
    pthread_mutex_lock(&m_houses);
    if (full_houses<houses)
    {
        full_houses++;
        pthread_mutex_unlock(&m_houses);
    }
    else
    {
        pthread_mutex_unlock(&m_houses);
        pthread_mutex_lock(&m_builders);
        builders.Usun_Losowego();
        pthread_mutex_unlock(&m_builders);
        pthread_exit(NULL);
        return NULL;
    }
    pthread_exit(NULL);
    return NULL;
}
void *kids_stuff(void *arg)
{
    //Żywienie
    pthread_mutex_lock(&m_food);
    if (food.Ile()>0)
    {
        food.Usun();
        pthread_mutex_unlock(&m_food);
    }
    else
    {
        pthread_mutex_unlock(&m_food);
        pthread_mutex_lock(&m_kids);
        kids.Usun_Losowego();
        pthread_mutex_unlock(&m_kids);
        pthread_exit(NULL);
        return NULL;
    }
    //Sen
    pthread_mutex_lock(&m_houses);
    if (full_houses<houses)
    {
        full_houses++;
        pthread_mutex_unlock(&m_houses);
    }
    else
    {
        pthread_mutex_unlock(&m_houses);
        pthread_mutex_lock(&m_kids);
        kids.Usun_Losowego();
        pthread_mutex_unlock(&m_kids);
        pthread_exit(NULL);
        return NULL;
    }
    pthread_exit(NULL);
    return NULL;
}


//Zapis do pliku
ofstream log;
void to_file(int i)
{
    log << "\n-- Dzień "<< i << " --- \n";
	if (is_winter) { log << "Zima \n"; }
	else { log << "Lato  \n"; }
	log << "Aktorzy: \n -";
    log << "myśliwi ["<< hunters.Ile() <<"], zbieracze ["<< gatherers.Ile() <<"], ";
    log << "kucharze ["<< cooks.Ile() <<"], drwale ["<< woodcutters.Ile() <<"], ";
    log << "budowlańcy ["<< builders.Ile() <<"], dzieci ["<< kids.Ile() <<"]\n";
    log << "Zasoby: \n -pożywienie ["<< food.Ile() <<"], mięso ["<< meat.Ile() <<"], ";
    log << "rośliny ["<< plants.Ile() <<"], drewno ["<< wood <<"], domy ["<< houses <<"]\n\n";
}


//MAIN
int main(int argc, char* argv[])
{
    //Wymaga 11 argumentów
    if (argc == 12) 
    {
        //Aktorzy: myśliwi, zbieracze, kucharze, drwale, budowlańcy, dzieci
        int H = atoi(argv[1]); hunters = Osadnicy(H,75);
        int G = atoi(argv[2]); gatherers = Osadnicy(G,75);
        int C = atoi(argv[3]); cooks = Osadnicy(C,80);
        int W = atoi(argv[4]); woodcutters = Osadnicy(W,65);
        int B = atoi(argv[5]); builders = Osadnicy(B,70);
        int K = atoi(argv[6]); kids = Dzieci(K);
        //Zasoby: pożywienie, mięso, rośliny, drewno, domy 
        int M = atoi(argv[7]); meat = Jedzenie(M,25);
        int P = atoi(argv[8]); plants = Jedzenie(P,15);
        int F = atoi(argv[9]); food = Jedzenie(F,30);
        wood = atoi(argv[10]);
        houses = atoi(argv[11]);
        full_houses = 0;        
        //Plik                      
        log.open("my_log.txt");
        //Opis wstępny przy rozpoczęciu symulacji
        cout << "\n--- Symulacja rozpoczęta --- \n" << "Aktorzy: \n -";
        cout << "myśliwi ["<< hunters.Ile() <<"], zbieracze ["<< gatherers.Ile() <<"], ";
        cout << "kucharze ["<< cooks.Ile() <<"], drwale ["<< woodcutters.Ile() <<"], ";
        cout << "budowlańcy ["<< builders.Ile() <<"], dzieci ["<< kids.Ile() <<"]\n";
        cout << "Zasoby: \n -pożywienie ["<< food.Ile() <<"], mięso ["<< meat.Ile() <<"], ";
        cout << "rośliny ["<< plants.Ile() <<"], drewno ["<< wood <<"], domy ["<< houses <<"]\n";
        //Pętla właściwa
        is_winter = true;
        for (int i=0; i<=365; i++)
        {
            //Cykl lato/zima
            if (((i > 90)&&(i<180)) || ((i > 270)&&(i<365)))
            {
               is_winter = true;
            }
            else
            {
               is_winter = false;
            }
            //Deklaracje
            full_houses = 0;
            int h = hunters.Ile(); pthread_t hunters_t[h];
            int g = gatherers.Ile(); pthread_t gatherers_t[g];
            int c = cooks.Ile(); pthread_t cooks_t[c];           
            int w = woodcutters.Ile(); pthread_t woodcutters_t[w];
            int b = builders.Ile(); pthread_t builders_t[b];
            int k = kids.Ile(); pthread_t kids_t[k];
            int sum = h + g + c + w + b;
            //Tworzenie wątków 
            for (int i = 0; i<h; i++)
            {
                pthread_create(&hunters_t[i],NULL,hunting,NULL);
            }
            for (int i = 0; i<g; i++)
            {
                pthread_create(&gatherers_t[i],NULL,gathering,NULL);
            }
            for (int i = 0; i<c; i++)
            {
                pthread_create(&cooks_t[i],NULL,cooking,NULL);
            }
            for (int i = 0; i<w; i++)
            {
                pthread_create(&woodcutters_t[i],NULL,cutting,NULL);
            }
            for (int i = 0; i<b; i++)
            {
                pthread_create(&builders_t[i],NULL,building,NULL);
            }
            for (int i = 0; i<k; i++)
            {
                pthread_create(&kids_t[i],NULL,kids_stuff,NULL);
            }                                                         
	        //Oczekiwanie na wątki        
            for (int i = 0; i<h; i++)
            {
                pthread_join(hunters_t[i],NULL);
            }
            for (int i = 0; i<g; i++)
            {
                pthread_join(gatherers_t[i],NULL);
            }
            for (int i = 0; i<c; i++)
            {
                pthread_join(cooks_t[i],NULL);
            }
            for (int i = 0; i<w; i++)
            {
                pthread_join(woodcutters_t[i],NULL);
            }
            for (int i = 0; i<b; i++)
            {
                pthread_join(builders_t[i],NULL);
            }
            for (int i = 0; i<k; i++)
            {
                pthread_join(kids_t[i],NULL);
            }
            //Procedury cyklu
            if (is_winter and i % 2) 
            { food.Termin(); meat.Termin(); plants.Termin(); }
            if (is_winter and not(i % 2)) 
            {  }     
            else
            { food.Termin(); meat.Termin(); plants.Termin(); }                             
            //Starzenie się osadników
            hunters.Wiek(); gatherers.Wiek(); cooks.Wiek();
            woodcutters.Wiek(); builders.Wiek(); kids.Wiek(); 
            //Dorastanie dzieci
            int K = kids.Dorosli();     
            if (K > 0)
            {
                for (int i = 0; i<K; i++)
                {
                    //Randomizacja zawodów
                    int L = rand()%5;
                    if (L == 0) { hunters.Dodaj(); }
                    if (L == 1) { gatherers.Dodaj(); }
                    if (L == 2) { cooks.Dodaj(); }
                    if (L == 3) { woodcutters.Dodaj(); }
                    if (L == 4) { builders.Dodaj(); } 
                }              
            }
            //Nowe dzieci
            if ((sum % 2) and (sum != 0))
            {
                kids.Dodaj();
            }
	    //Zapis do pliku my_log.txt
            to_file(i);
        }
        //Podsumowanie      
        cout << "\n\n--- Symulacja zakończona --- \n" << "Aktorzy: \n -";
        cout << "myśliwi ["<< hunters.Ile() <<"], zbieracze ["<< gatherers.Ile() <<"], ";
        cout << "kucharze ["<< cooks.Ile() <<"], drwale ["<< woodcutters.Ile() <<"], ";
        cout << "budowlańcy ["<< builders.Ile() <<"], dzieci ["<< kids.Ile() <<"]\n";
        cout << "Zasoby: \n -pożywienie ["<< food.Ile() <<"], mięso ["<< meat.Ile() <<"], ";
        cout << "rośliny ["<< plants.Ile() <<"], drewno ["<< wood <<"], domy ["<< houses <<"]\n";
        //Koniec
        log.close();      
    }
    else
    {
        cout << "Niepoprawna liczba argumentów \n";
    } 
}

