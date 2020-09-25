#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std; 

int main()
{   
    // Pobieranie liczb m i n takich ze 1 <= m, n <= 10^9
    // m - dlugosc, n - szerokosc
    int m, n;
    scanf("%d %d", &m, &n);
    // Pobieranie liczby 1 <= k <= 10^6
    // k - ilosc pobieranych grzadek
    int k;
    scanf("%d", &k);
    // Uzupelnianie wektora przechowujacego punkty <(a,b),c> posortowane po X
    vector <tuple<int,int,int>> points_byX;
    // Uzupelnianie wektora przechowujacego wartosci <zrodlo> do poprzedniej grzadki dla
    // aktualnie przetwarzanego punktu.
    // Zrodlo -1 oznacza nieodwiedzony punkt lub punkt bez poprzednika, czyli startowy
    // bedziemy z tego na koncu budowac sciezke przejscia
    vector <int> points_byX_source;
    int a, b, c;
    for (int i = 0; i<k; i++) {
        // 1 <= a <= m
        // 1 <= b <= n
        // 1 <= c <= 10^6
        scanf("%d %d %d", &a, &b, &c);
        points_byX.push_back(make_tuple(a,b,c));
        points_byX_source.push_back(-1);
    }
    // Sortowanie po wartosci X
    sort(points_byX.begin(), points_byX.end());
    // Dodanie ostatniego punktu koncowego <m, n> dla ktorego koszt dotarcia ma byc maksymalny 
    points_byX.push_back(make_tuple(m,n,0));
    points_byX_source.push_back(-1);
    // Uzupelnianie mapy przechowujacej wartosci maksymalne w wierszach o danej wartosci y
    // tzn. map[wartosc wiersza] = <koszt najdrozszej sciezki juz obliczonej w tym wierszu, indeks punktu z ktorego docieramy>
    map <int, pair<long long int,int>> points_map;
    points_map.insert(make_pair(0, make_pair(0,-1)));
    // Bierzemy aktualnie rozwazana grzadke
    long long int opt = 0;
    for (int i = 0; i<=k; i++) {
        a = get<0>(points_byX.at(i));
        b = get<1>(points_byX.at(i));
        c = get<2>(points_byX.at(i));
        // Znajdujemy wiersz o wartosci <=b (czyli po wspolrzednej y)
        // Upper_bound zwraca iterator do pierwszego elementu PO wartosci b (wspolrzedna y)
        // Dlatego cofamy sie o jeden iter, jesli chcemy pierwsza wartosc mniejsza-rowna b
        map <int,pair<long long int,int>>::iterator iter = points_map.upper_bound(b); 
        --iter;
        // Wartosc slownika 
        pair<long long int,int> value = (iter)->second;
        // Wartosc pierwszego elementu w parze (wartosc dla poprzedzajacego punktu) + cena w danym aktualnym punkcie
        // Taki znaleziony punkt znajduje sie najdalej "zaraz przed" naszym punktem i
        // tzn. albo jest w obecnym wierszu "po lewej", albo znajduje sie w nizszych wierszach
        // a dzieki temu, ze przetwarzamy punkty w kolejnosci po x, to punkty znajdujace sie
        // "na prawo" maja na pewno wartosc 0 - bo nie byly jeszcze rozwazane   
        opt = get<0>(value) + c;
        // Musimy usunac teraz kolejne nadmiarowe punkty tzn. te juz rozwazane, ktore maja wyzsza wartosc wiersza y,
        // ale maja mniejsza wartosc kosztu dotarcia, z uwagi na to, ze w kolejnych iteracjach podczas rozwazania 
        // punktow "wyzej" na osi moze sie zdarzyc, ze wezmiemy punkt lezacy wyzej ale z mniejszym kosztem dotarcia
        iter++;
        map <int,pair<long long int,int>>::iterator iter_beg = iter; 
        while (iter != points_map.end() && (get<0>(iter->second) < opt) ) {
            iter++;
        }
        points_map.erase(iter_beg, iter);
        // Nadajemy wartosci kosztu przejcia do slownika (nowa lub nadpisanie)
        // oraz nadajemy dla punktu i indeks punktu zrodlowego 
        points_map[b] = make_pair(opt,i);
        points_byX_source.at(i) = get<1>(value);
    }    
    // Wypisanie maksymalnej wartosci przejscia z punktu <m,n>
    printf("%lld\n", opt);  
    // Budowa sciezki przejscia z punktow  
    vector <int> path;
    // Zaczynamy od koncowego punktu <m,n> o indeksie k
    // i zapisujemy kolejno odwiedzone indeksy az do poczatku
    int iter = points_byX_source.at(k);
    // Teoretycznie sciezka punktowa moze byc znacznie krotsza niz caly zbior punktow
    // wiec lepiej przeiterowaÄ po wektorze wzgledem zrodel 
    while (iter >= 0){
        path.push_back(iter);
        iter = points_byX_source.at(iter);
    }
    // Wypisanie ilosci punktow na sciezce oraz kolejnych punktow 
    printf("%d\n", (int)path.size());
    for (int i=path.size()-1; i>=0; i--){
        a = get<0>(points_byX.at(path.at(i)));
        b = get<1>(points_byX.at(path.at(i)));
        printf("%d %d\n", a, b);
    }      
}