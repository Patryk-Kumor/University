#include <iostream>
#include <vector>

using namespace std; 

int main()
{
    int F = 0;
    int C = 0;
    // Pobieranie liczby 0 < F <= 10^6
    scanf("%d", &F);
    // Pobieranie liczby 0 < C <= 100
    scanf("%d", &C);
    // Wektory przechowujace monety (iterowane od 1)
    vector <int> value; 
    value.push_back(0);
    vector <int> weigh;
    weigh.push_back(0);
    // Pobieranie C monet <nominal, waga> gdzie zachodzi 0 < nominal, waga <= 10^5
    int n = 0;
    int w = 0;
    for (int i = 1; i<=C; i++) {
        scanf("%d %d", &n, &w);
        value.push_back(n);
        weigh.push_back(w);
    }
    // Wyniki czastkowe od 0 do F dla poszczegolnych wag
    vector <long long> GainMax(F+1, 0);
    vector <int> GainMaxCoin(F+1, 0);
    vector <long long> GainMin(F+1, 0);
    vector <int> GainMinCoin(F+1, 0); 
    // Wypelnianie tablic wynikowych iteracyjnie od dolu korzystajac z wlasnosci problemu plecakowego:
    // K(0) = 0
    // K(w) = max {i: w_i < w} ( K(w - w_i) + v_i )
    // Aktualna waga
    for (int i = 0; i<=F; i++){ 
        // Monety iterowanie od 1 do C
        for (int j = 1; j<=C; j++){ 
            // Aktualnie rozwazana moneta
            int c_j =  value.at(j);  
            int w_j =  weigh.at(j);
            // Jezeli waga monety nie przekracza dostepnego wolnego miejca
            if (w_j <= i) { 
                // Szukanie maksimum
                // Warunek poczatkowy, czyli uzupelniona do konca waga lub kiedy istnieje rozwazanie w tablicy, 
                // wpp jesli zero w tablicy, oznacza brak rozw
                if ((i-w_j == 0) || (GainMax.at(i - w_j) != 0)) {
                    // Sprawdzamy czy nowy koszt jest wiekszy niz stary
                    if (GainMax.at(i - w_j) + c_j > GainMax.at(i)){
                        GainMax.at(i) = GainMax.at(i - w_j) + c_j;
                        GainMaxCoin.at(i) = j;
                    }                 
                }
                // Szukanie minimum
                if ((i-w_j == 0) || (GainMin.at(i - w_j) != 0) ){
                    // Jesli natrafiamy na nowe miejsce w tablicy 
                    // (jest w nim zero, to nalezy je zamienic na jedyne rozwiazanie, bo zero zawsze mniejsze)
                    if ((i>0) && (GainMin[i]==0) && (i-w_j >= 0)){
                        GainMin.at(i) = GainMin.at(i - w_j) + c_j;
                        GainMinCoin.at(i) = j;
                    }
                    // Sprawdzamy czy nowy koszt jest mniejszy niz stary 
                    else if (GainMin.at(i - w_j) + c_j < GainMin.at(i)){
                        GainMin.at(i) = GainMin.at(i - w_j) + c_j;
                        GainMinCoin.at(i) = j;
                    } 
                }                
            }
        }
    }
    // Wypisywanie rozwiazania
    if ((GainMax.at(F) == 0) || (GainMin.at(F) == 0)){
        printf("NIE");
        return 0;
    }
    else {
        int coinCount[C+1] = {0};
        printf("TAK\n");
        printf("%lld\n", GainMin.at(F));
        // Obliczanie potrzebnych monet MIN
        int temp = F;
        int coin_id = 0;
        int we = 0;
        while (temp>0) {
            coin_id = GainMinCoin.at(temp);
            we = weigh.at(coin_id);
            coinCount[coin_id] = coinCount[coin_id]+1;
            temp = temp - we;
        }
        for (int i = 1; i<=C; i++){
            printf("%d ", coinCount[i]);
            coinCount[i] = 0;
        }
        printf("\n%lld\n", GainMax.at(F));
        // Obliczanie potrzebnych monet MAX
        temp = F; 
        while (temp>0) {
            coin_id = GainMaxCoin.at(temp);
            we = weigh.at(coin_id);
            coinCount[coin_id] = coinCount[coin_id]+1;
            temp = temp - we;
        }
        for (int i = 1; i<=C; i++){
            printf("%d ", coinCount[i]);
        }
        return 0;
    }
}