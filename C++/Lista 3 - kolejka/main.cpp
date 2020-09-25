#include "lib.h"

void inter(kolejka x)
{
	char wybor='1';
	string elem;

	cout << endl;
	cout << "---Kolejka---" << endl;
	cout << "1.Wstaw" << endl;
	cout << "2.Pobierz" << endl;
	cout << "3.Sprawdz" << endl;
	cout << "4.Rozmiar" << endl;
	cout << "5.Wypisz" << endl;
	cout << "6.Zakoncz" << endl;

	while (wybor != '6')
	{
		wybor = _getch();

		switch (wybor)
		{
		case '1':
			cout << "Podaj element do wstawienia: ";
			cin >> elem;
			x.wstaw(elem);
			break;
		case '2':
			cout << x.pobierz() << endl;
			break;
		case '3':
			cout << x.sprawdz() << endl;
			break;
		case '4':
			cout << x.rozmiar() << endl;
			break;
		case '5':
			x.wypisz();
			break;
		default:
			if (wybor != '6')
				throw string("Bledna komenda");
		}
	}
	wybor = NULL;
};

void main()
{
	cout << "TEST KOLEJKA" << endl;

	kolejka* kol = new kolejka();

	kolejka k(10);
	k.wstaw("pierwszy");
	k.wstaw("drugi");
	k.wstaw("trzeci");
	k.wstaw("czwarty");
	cout << endl;

	k.wypisz();
	cout << endl;
	cout << "Pierwszy element:" << k.sprawdz() << endl << endl;

	k.pobierz();
	k.wypisz();
	cout << "Rozmiar:"<< k.rozmiar() << endl;
	cout << "Pierwszy element:" << k.sprawdz() << endl << endl;

	kolejka k2{"Smok","Miecz", "Skyrim", "Dovha"};
	k2.wypisz();

	kolejka k3 = k2;

	

	kolejka k4(40);
	cout << endl;
	k4.wypisz();
	inter(k4);


};