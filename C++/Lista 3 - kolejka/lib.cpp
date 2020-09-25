#include "lib.h"

kolejka::kolejka()
{
	pojemnosc = 4;
	ile = 0;
	poczatek = 0;
	T = new string[pojemnosc];
}
kolejka::kolejka(int poj)
{
	pojemnosc = poj;
	ile = 0;
	poczatek = 0;
	T = new string[pojemnosc];
}
kolejka::kolejka(initializer_list<string> l)
{
	pojemnosc = l.size();
	T = new string[pojemnosc];
	int o = 0;
	for (string i : l)
	{
		T[o] = i;
		o++;
	}
	ile = l.size();
	poczatek = 0;
}
kolejka::kolejka(kolejka  &kopia)
{
	pojemnosc = kopia.pojemnosc;
	T = new string[pojemnosc];
	ile = kopia.ile;
	poczatek = kopia.poczatek;
	for (int i = 0; i<pojemnosc; i++)
		T[i] = kopia.T[i];
}
kolejka::kolejka(kolejka &&przypis)
{
	pojemnosc = przypis.pojemnosc;
	T = new string[pojemnosc];
	ile = przypis.ile;
	poczatek = przypis.poczatek;
	for (int i = 0; i<pojemnosc; i++)
		T[i] = przypis.T[i];
	przypis.T = nullptr;
	przypis.ile = 0;
	przypis.poczatek = 0;
	przypis.pojemnosc = 0;
}
kolejka & kolejka:: operator=(kolejka &kopia)
{
	pojemnosc = kopia.pojemnosc;
	T = new string[pojemnosc];
	ile = kopia.ile;
	poczatek = kopia.poczatek;
	for (int i = 0; i<pojemnosc; i++)
		T[i] = kopia.T[i];
	return *this;
}

kolejka & kolejka :: operator=(kolejka && przypis)
{
	pojemnosc = przypis.pojemnosc;
	T = new string[pojemnosc];
	ile = przypis.ile;
	poczatek = przypis.poczatek;
	for (int i = 0; i<pojemnosc; i++)
		T[i] = przypis.T[i];
	przypis.T = nullptr;
	przypis.ile = 0;
	przypis.poczatek = 0;
	przypis.pojemnosc = 0;
	return *this;
}




void kolejka::wstaw(string elem)
{
	if (ile == pojemnosc) { throw string("Kolejka jest pelna"); }
	else
	{
		T[ile] = elem;
		ile++;
	}
}
string kolejka::pobierz()
{
	string pomoc;
	
	if (ile >= 1)
	{
		pomoc = this->T[0];
	}
	else { throw string("blad"); }
	for (int i = 0; i < ile; i++)
	{
		T[i] = T[i + 1];
	}
	T[ile]="";
	ile--;
	return pomoc;
}
string kolejka::sprawdz()
{
	if (ile != 0)
	{
		return T[0];
	}
	else
		return "Kolejka Pusta !";
}
int kolejka::rozmiar()
{
	return ile;
}
void kolejka::wypisz()
{
	if (T != nullptr)
	{
		int i = 0;

		while (T[i] != "" && i + 1 < ile)
		{
			i++;
		}
		while (i >= 0)
		{
			cout << i << "-element to: " << this->T[i] << endl;
			i--;
		}
	}
	else
		throw string("Kolejka nie istnieje/jest pusta");
}
kolejka::~kolejka()
{
	cout << "Usunieto ";
	delete[] T;
}
