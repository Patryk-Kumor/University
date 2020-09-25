#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <math.h>
#include <limits>

using namespace std; 

// Sortowanie wzgledem drugiego elementu pary
bool second_item_order(const pair<int, int>& a, const pair<int, int>& b) { 
    if (a.second == b.second){
        return (a.first < b.first);
    }
    return (a.second < b.second); 
} 

// Obliczanie odleglosci miedzy dwoma punktami
double dist(const pair<int, int>& a, const pair<int, int>& b) { 
    double x = a.first - b.first;
    double y = a.second - b.second;
    return sqrt( x*x + y*y ); 
}

// Globalny wektor przechowujacy punkty
vector < pair<int,int> > vectorX;

// Rekurencyjna funkcja obliczajaca najmniejszy obwod sposrod punktow w wektorze od beg do end
tuple<double, int,int, int,int, int,int>  find_triangle(int beg, int end){
    int len = end - beg + 1; 
    int p1 = -1;
    int p2 = -1;
    int p3 = -1;
    double sum = INFINITY;
    double sum_temp = INFINITY;
    double dist_ab = INFINITY;
    // Znajdowanie bruteforce na max 5 punktach    
    if (len >= 3 && len <= 5) {
        for (int i = beg; i <= end; i++){ // pierwszy punkt
            for (int j = i+1; j <= end; j++){ // drugi punkt
                dist_ab = dist(vectorX.at(i), vectorX.at(j));
                for (int k = j+1; k <= end; k++) { // trzeci punkt
                    sum_temp = dist_ab + dist(vectorX.at(i), vectorX.at(k)) + dist(vectorX.at(j), vectorX.at(k));
                    if (sum_temp < sum){
                        sum = sum_temp;
                        p1 = i; 
                        p2 = j; 
                        p3 = k;
                    }
                }
            }
        }
        return make_tuple(sum, vectorX.at(p1).first, vectorX.at(p1).second, 
                               vectorX.at(p2).first, vectorX.at(p2).second, 
                               vectorX.at(p3).first, vectorX.at(p3).second);
    }
    else {
        // Indeks punktu na linii podzialu
        int mid = (beg + end) / 2;
        // Rekurencyjne wywolania
        tuple<double, int,int, int,int, int,int> res;
        tuple<double, int,int, int,int, int,int> res1 = find_triangle(beg, mid);
        tuple<double, int,int, int,int, int,int> res2 = find_triangle(mid + 1, end);       
        // Znajdowanie mniejszego sposrod wybranych punktow
        if (get<0>(res1) < get<0>(res2)){
            res = res1;
        }
        else {
            res = res2;
        }
        // Niech p bedzie mniejszym obwodem
        double p = get<0>(res);         
        // Wartosc x'a srodkowego punktu - wspolrzedna naszej linii podzialu
        double mid_x =  vectorX.at(mid).first;
        // Szukamy punktow na lewo i prawo w odleglosci max p/2 i zapisujemy je w wektorze
        vector <pair<int,int>> vectorY;
        // Sprawdzamy na lewo od linii srodkowej 
        double i_x;
        for (int i=mid; i>=beg; i--){
            i_x = vectorX.at(i).first;
            if (mid_x - i_x <= (p+1)/2){
                vectorY.push_back( vectorX.at(i) );
            }
        }
        // Sprawdzamy na prawo od linii srodkowej 
        for (int i=mid+1; i<=end; i++){
            i_x = vectorX.at(i).first;
            if (i_x - mid_x <= (p+1)/2){
                vectorY.push_back( vectorX.at(i) );
            }
        }
        // Posortujmy po Y
        sort(vectorY.begin(), vectorY.end(), second_item_order); 
        // Obliczanie wartosci obwodow nie dalej polozonych niz 8 dalej
        for (int i = 0; i < (int)vectorY.size(); i++){ // pierwszy punkt
            for (int j = i+1; j < i+8 && j < (int)vectorY.size(); j++){ // drugi punkt
                dist_ab = dist(vectorY.at(i), vectorY.at(j));
                for (int k = j+1; k < i+8 && k < (int)vectorY.size(); k++) { // trzeci punkt
                    sum_temp = dist_ab + dist(vectorY.at(i), vectorY.at(k)) + dist(vectorY.at(j), vectorY.at(k));
                    if (sum_temp < sum){
                        sum = sum_temp;
                        p1 = i; 
                        p2 = j; 
                        p3 = k;
                    }
                }
            }
        }        
        // Res to ten lepszy wynik z rekurencji, sprawdzamy czy znaleziony obwod byl lepszy 
        if (get<0>(res) < sum){
            return res;
        }
        else{
            return make_tuple(sum, vectorY.at(p1).first, vectorY.at(p1).second, 
                                   vectorY.at(p2).first, vectorY.at(p2).second, 
                                   vectorY.at(p3).first, vectorY.at(p3).second);           
        }
    }    
}

int main()
{
    // Pobieranie liczby n z zakresu [3, 500 000]
    int n;
    scanf("%d", &n);
    // Uzupelnianie - dodawanie do wektorow kolejnych wierszy z punktami
    // -10^7 <= x, y <= 10^7
    int x, y;
    for (int i = 0; i<n; i++) {
        scanf("%d %d", &x, &y);
        vectorX.push_back(make_pair(x, y));
    }
    // Sortowanie po X
    sort(vectorX.begin(), vectorX.end());
    // Obliczanie
    tuple <double, int,int, int,int, int,int> res = find_triangle(0, n-1);
    // Wypisywanie
    printf("%d %d\n", get<1>(res), get<2>(res));
    printf("%d %d\n", get<3>(res), get<4>(res));
    printf("%d %d",   get<5>(res), get<6>(res));
}