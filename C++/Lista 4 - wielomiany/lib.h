#pragma once

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <conio.h>

using namespace std;

class wielomian
{
	private:

		int stopien;
		double *wspolczynniki;

	public:

		wielomian(int s = 0, double wsp = 1.0); // konstruktor tworzacy jednomian, domyslny: 1x^0
		wielomian(int st, const double wsp[]); // konstruktor tworzacy wielomian
		wielomian(initializer_list<double> wsp); // lista wspolczynnikow

		wielomian(const wielomian &w); // konstruktor kopijacy
		//wielomian(const wielomian &&w); // konstruktor przenoszacy // RIP. // DANGER // HELP

		wielomian& operator = (const wielomian &w); // przypisanie kopijace
		wielomian& operator = (wielomian &&w); // przypisanie przenoszace 
		
		~wielomian(); // destruktor

		friend istream& operator >> (istream &streamin, wielomian &w);
		friend ostream& operator << (ostream &streamout, const wielomian &w);

		friend wielomian operator + (const wielomian &u, const  wielomian &v);
		friend wielomian operator - (const wielomian &u, const wielomian &v);
		friend wielomian operator * (const wielomian &u, const wielomian &v);

		//friend wielomian operator * (double c);
		wielomian& operator += (const wielomian &v);
		wielomian& operator -= (const wielomian &v);
		wielomian& operator *= (const wielomian &v);
		wielomian& operator *= (double c);
		double operator () (double x) const; // obliczenie wartosci wielomianu w x-sie
		double operator [] (int i) const; // odczytanie i-tego wspolczynnika


};