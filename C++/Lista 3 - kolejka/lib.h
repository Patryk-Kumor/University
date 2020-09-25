#pragma once

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <conio.h>

using namespace std;

class kolejka
{
public:
	string *T;
	int pojemnosc;
	int ile;
	int poczatek;

	kolejka();
	kolejka(int poj);
	~kolejka();

	void wstaw(string elem);
	string pobierz();
	string sprawdz();
	int rozmiar();
	void wypisz();

	kolejka(initializer_list<string> l);
	kolejka(kolejka  &kopia);
	kolejka(kolejka &&przypis);
	kolejka & operator=(kolejka &kopia);
	kolejka & operator=(kolejka &&kopia);
};
