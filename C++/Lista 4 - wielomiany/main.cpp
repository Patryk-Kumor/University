#include "lib.h"

using namespace std;

void inter(wielomian W1, wielomian W2)
{
	char wybor = '1';
	string elem;

	cout << endl;
	cout << "---Wielomiany---" << endl;
	cout << "1.Dodaj" << endl;
	cout << "2.Odejmij" << endl;
	cout << "3.Mnoz" << endl;
	cout << "4.Zakoncz" << endl;

	while (wybor != '4')
	{
		wybor = _getch();

		switch (wybor)
		{
		case '1':
			cout << W1 + W2 << endl;
			break;
		case '2':
			cout << W1 - W2 << endl;
			break;
		case '3':
			cout << W1 * W2 << endl;
			break;

		default:
			if (wybor != '4')
				throw string("Bledna komenda");
		}
	}
	wybor = NULL;
};

void main()
{
	cout << "---TESTSY STANDARTOWDYCH KONSTRUKTOROW---""" << endl << endl;

	wielomian w1;
	cout << "-domyslny -> "<< w1 << endl;
	wielomian w2(3, 2.0);
	cout << "-stopien: 3, stala: 2.0 -> " << w2 << endl;
	double T[] = { 1,2,3,4,5 };
	wielomian w3(4, T);
	cout << "-tablica T: { 1,2,3,4,5 }  -> "<< w3 << endl;
	initializer_list<double> lista{ 1, 2, 3, 4, 5 };
	wielomian w4(lista);
	cout << "-initializer_list: { 1, 2, 3, 4, 5 } -> " << w4 << endl<<endl;

	wielomian wc1 = w1;
	cout << "-kopia w1 -> " << wc1 <<endl;
	wielomian wc2(w2);
	cout << "-kopia w2 -> " << wc2 << endl;
	wielomian wc3;
	wc3 = w3;
	cout << "-kopia w3 -> " << wc3 << endl << endl;

	//----------------------------------------------//

	cout << "---TESTSY WYJATKOW---""" << endl << endl;
	
	wielomian ww1(3, 0.0);

	double tab1[] = { 4.1,4.2,4.3,4.4,0 };
	wielomian ww2(4, tab1);

	initializer_list<double> list{ 1, 3.5, 4.2, 4.44, 0 };
	wielomian ww3(lista);

	double tab2[] = { 4.1,4.2,4.3,4.4 };
	double tab3[] = { -4.1,-4.2,-4.3,-4.4 };
	wielomian ww4(3, tab2);
	wielomian ww5(3, tab2);
	wielomian ww6(3, tab3);
	cout << ww4 << endl;
	cout << ww5 << endl;
	cout << ww6 << endl;

	cout << ww4 + ww6 << endl;
	cout << ww4 - ww5 << endl;;
	cout << ww4 - ww5 << endl;
	cout << ww4[4] << endl;
	cout << ww4[-1] << endl << endl;

	//----------------------------------------------//

	cout << "---TESTSY OPERATOROW---""" << endl << endl;

	cout << "Podaj pierwszy wielomian:";
	wielomian W1;
	cin >> W1;
	cout << " * Pierwszy wielomian = " << W1 <<endl<<endl;

	cout << "Podaj drugi wielomian:";
	wielomian W2;
	cin >> W2;
	cout << " * Drugi wielomian = " << W2 << endl << endl;

	inter(W1, W2);

}
