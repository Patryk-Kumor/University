#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <utility>

using namespace std;

class wyrazenie
{
public:
	virtual double oblicz() = 0;
	virtual string opis() = 0;
};

//---------------------------

class operator1argumentowy : public wyrazenie
{
public:
	wyrazenie *a;
};
class operator2argumentowy : public operator1argumentowy
{
public:
	wyrazenie *b;
};

//---------------------------

class Liczba : public wyrazenie
{
public:
	double val;
	Liczba(double l);
	double oblicz() override;
	string opis() override;
};
class Stala : public wyrazenie
{
public:
	double stala;
	double PI = 3.14159265359;
	double E = 2.718281828459;
	double FI = 1.618033988;
};

class Zmienna: public wyrazenie
{
	static vector<pair<string, double>> tablica;

public:
	string s;
	void static Dodaj(string x, double val) 
	{
		pair <string, double> temp;
		temp = std::make_pair(x, val);
		tablica.push_back(temp);
	};
	double static Szukaj(string x)
	{
		for (size_t i = 0; i < tablica.size(); i++)
			if (tablica[i].first == x) return tablica[i].second;
	};
	void static Zmien(string x, double val)
	{
		for (size_t i = 0; i < tablica.size(); i++)
			if (tablica[i].first == x) { tablica[i].second = val; };
	};
	Zmienna(string s1);
	double oblicz();
	string opis(); 
};

//---------------------------

class pi : public Stala
{
public:
	pi();
	double oblicz();
	string opis();
};
class e : public Stala
{
public:
	e();
	double oblicz();
	string opis();
};
class fi : public Stala
{
public:
	fi();
	double oblicz();
	string opis();
};

//---------------------------

class Sin : public operator1argumentowy
{
public:
	Sin(wyrazenie *a);
	double oblicz();
	string opis();
};
class Cos : public operator1argumentowy
{
public:
	Cos(wyrazenie *a);
	double oblicz();
	string opis();
};
class Exp : public operator1argumentowy
{
public:
	Exp(wyrazenie *a);
	double oblicz();
	string opis();
};
class Ln : public operator1argumentowy
{
public:
	Ln(wyrazenie *a);
	double oblicz();
	string opis();
};
class Bezwgl : public operator1argumentowy
{
public:
	Bezwgl(wyrazenie *a);
	double oblicz();
	string opis();
};
class Przeciw : public operator1argumentowy
{
public:
	Przeciw(wyrazenie *a);
	double oblicz();
	string opis();
};
class Odwrot : public operator1argumentowy
{
public:
	Odwrot(wyrazenie *a);
	double oblicz();
	string opis();
};

//---------------------------

class Dodaj : public operator2argumentowy
{
public:
	Dodaj(wyrazenie *a, wyrazenie *b);
	double oblicz();
	string opis();
};
class Odejmij : public operator2argumentowy
{
public:
	Odejmij(wyrazenie *a, wyrazenie *b);
	double oblicz();
	string opis();
};
class Mnoz : public operator2argumentowy
{
public:
	Mnoz(wyrazenie *a, wyrazenie *b);
	double oblicz();
	string opis();
};
class Dziel : public operator2argumentowy
{
public:
	Dziel(wyrazenie *a, wyrazenie *b);
	double oblicz();
	string opis();
};

class Logarytm : public operator2argumentowy
{
public:
	Logarytm(wyrazenie *a, wyrazenie *b);
	double oblicz();
	string opis();
};
class Modulo : public operator2argumentowy
{
public:
	Modulo(wyrazenie *a, wyrazenie *b);
	double oblicz();
	string opis();
};
class Potega : public operator2argumentowy
{
public:
	Potega(wyrazenie *a, wyrazenie *b);
	double oblicz();
	string opis();
};