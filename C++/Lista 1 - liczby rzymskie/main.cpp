#include <iostream>
#include <string>
#include <list>
#include <cstdlib>

using namespace std;


const int B[] = { 9000, 8000, 7000, 6000, 5000, 4000, 3000, 1000, 900, 500, 400, 100,90, 50, 40, 10, 9, 5, 4, 1 };
const string R[] ={ "|XC|", "|LXXX|", "|LXX|", "|LX|", "|L|", "|XL|","|XXX|", "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

string rzymska;


int arab2bin(const char * x)
{
	int i = 0;
    if (x[i] == '0') return 0;
    
    while(x[i]!='\0')
        {
        if  (( x[i]>'9' ) || ( x[i]<'0')  )
            {return 0;}
        i++;
        }
    if (i > 4) return 0;
    
    return atoi(x);

}

string bin2rzym(int x)
{
	string rzymska = "";

		while (x > 0) {
		for (int i = 0; i < 20; i++) {
			if (B[i] <= x) {
				rzymska += R[i];
				x -= B[i];
				break;
			}
		}
	}



		return rzymska;
}


int main(int argc, char * argv[])
{
	for (int j = 1; j < argc; j++)
	{
		int wynik = arab2bin(argv[j]);
		
		if (wynik!=0)
		{
			string rzym = bin2rzym(wynik);
			cout << rzym << " = " << argv[j] << endl;
		}
		else
			cout << "Niepoprawny!" << " = " << argv[j] << endl;

	}
	return 0;

}

