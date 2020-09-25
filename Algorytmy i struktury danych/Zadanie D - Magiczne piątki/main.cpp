#include <iostream>
#include <vector>
#include <algorithm>

using namespace std; 

int select_k(int k, vector <int> vec){
    // Jesli |vec| jest male to posortuj tablice i zwroc k'ty element
    if ((int)vec.size() < 20){
        sort(vec.begin(), vec.end());
        return vec.at(k);
    }
    else{
        // Mediany ze zbiorow (podzielone na 5 elementow)
        vector <int> medians;
        int i=0;
        for (i=0; i < (int)vec.size()-5; i=i+5){
            sort(vec.begin()+i, vec.begin()+i+5);
            medians.push_back(vec.at(i+2)); // srodkowy element w ciagu 5 elementowym
        }
        // Ostatnia piatka elementow, mozliwie "niepelna"
        sort(vec.begin()+i, vec.end());        
        medians.push_back(vec.at((int)(i + vec.size() - 1) / 2)); // srodkowy element w ostatniej piatce
        // Rekurencyjnie zwracamy srodkowy element wsrod median - mediana median
        int p = select_k(medians.size()/2, medians);
        // Podzial ciagu na mniejsze, rownie i wieksze wobec p
        vector <int> vec_smaller;
        vector <int> vec_bigger;
        int equal_count = 0;
        for (i=0; i<(int)vec.size(); i++){
            if (vec.at(i) < p){
                vec_smaller.push_back(vec.at(i));
            }
            else if (vec.at(i) > p){
                vec_bigger.push_back(vec.at(i));
            }
            else{
                equal_count++;
            }
        }
        // Zwracanie wyniku rekurencyjnie
        if (k < (int)vec_smaller.size()){
            return select_k(k, vec_smaller);
        }
        else if (k < (int)vec_smaller.size() + equal_count){
            return p;
        }
        else{
            return select_k(k - vec_smaller.size() - equal_count, vec_bigger);
        }
    }
}

int main()
{
    vector <int> vectorInt;
    // Pobieranie liczby n i k takiego ze 1 <= k <= n <= 10^6
    int n, k;
    scanf("%d %d", &n, &k);
    // Uzupelnianie wektora globalnego
    int x;
    for (int i = 0; i<n; i++) {
        // 0 <= x <= 10^9
        scanf("%d", &x);
        vectorInt.push_back(x);
    }
    // Obliczanie wyniku
    // Wektory iterujemy od zera, stad k-1
    int res = select_k(k-1, vectorInt);
    // Wypisywanie wyniku
    printf("%d", res);
}