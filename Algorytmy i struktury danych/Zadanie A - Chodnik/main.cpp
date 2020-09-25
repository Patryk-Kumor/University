#include <iostream>
#include <vector>
#include <tuple>
#include <stack>

using namespace std; 

int main()
{
    // Pobieranie liczby n
    int n;
    scanf("%d", &n);
    // Uzupelnianie tablicy - dodawanie do tablicy wektorow kolejnych wierszy
    vector <tuple<short int,short int>> v[10001];
    short int l, m, r; 
    bool is_zero = false;
    for (int i = 0; i<n; i++) {
        scanf("%hd %hd %hd", &l, &m, &r);
        if (r==0) { is_zero = true; }
        v[l].push_back(make_tuple(r, m));
    }
    // Jezeli nie odnaleziono (w r) koncowego zera - koniec
    if (!is_zero) { printf("BRAK"); return 0; }
    // Jezeli korzen (0) nie ma dzieci - koniec, bo i tak brak sciezki
    if (v[0].size() == 0) { printf("BRAK"); return 0; }
    //-------------------------------------------------
    short int path[10001] = {-1}; 
    bool seen[10001] = {false}; 
    stack <short int> s; 
    // DFS iteracyjny
    s.push(0);
    short int verticle;
    short int w;
    while (!s.empty()) {
        verticle = s.top(); s.pop();   
        if (seen[verticle])
            continue;     
        seen[verticle] = true;
        // Dla kazdego dziecka i tego verticla oznaczamy jak do niego trafilismy
        for (int j = 0; j < (int) v[verticle].size(); j++) {
        //for (int j = v[verticle].size()-1; j>=0 ; j--) {
            w = get<0>(v[verticle].at(j));
            if (w==0){
                path[w] = verticle;
            }
            if (!seen[w]) {
                path[w] = verticle;
                s.push(w);
            }
        }
    }
    //-------------------------------------------------  
    while (!s.empty()) { s.pop(); }
    // Teraz nalezy odtworzyc sciezke wzgledem tablic path[verticle] = parent
    short int i = path[0];
    if (i == -1) { printf("BRAK"); return 0; }
    else
    {
        s.push(i);
        while (i != 0) {
            i = path[i];
            s.push(i);
        }
        printf("%d\n", (int)s.size());
        while (!s.empty()) {
            l = s.top(); s.pop();
            if (s.empty()) { 
                r = 0; 
            }
            else { 
                r = s.top(); 
            }       
            for (int j = 0; j < (int) v[l].size(); j++) {
                w = get<0>(v[l].at(j));
                if (w == r) {
                    m = get<1>(v[l].at(j));
                }
            }
            printf("%hd %hd %hd\n", l, m, r); 
        }
    }
    return 0;
}
