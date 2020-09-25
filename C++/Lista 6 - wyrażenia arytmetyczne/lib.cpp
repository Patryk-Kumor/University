#pragma once
#include "lib.h"

vector<pair<string, double>>Zmienna::tablica;

//---------------------------------------------------------

Zmienna::Zmienna(string s1)
{
	this->s = s1;
};
double Zmienna::oblicz()
{
	return Zmienna::Szukaj(s);
}
string Zmienna::opis()
{
	return this->s;
}

Liczba::Liczba(double l) 
{
	val = l;
}
double Liczba::oblicz()
{
	return val;
}
string Liczba::opis()
{
	return to_string(val);
}

//---------------------------------------------------------

pi::pi()
{
	PI=PI;
}
double pi::oblicz()
{
	return PI;
}
string pi::opis()
{
	return "pi";
}

e::e()
{
	E = E;
}
double e::oblicz()
{
	return E;
}
string e::opis()
{
	return "e";
}
fi::fi()
{
	FI = FI;
}
double fi::oblicz()
{
	return FI;
}
string fi::opis()
{
	return "fi";
}

//---------------------------------------------------------

Sin::Sin(wyrazenie *a1)
{
	this->a = a1;
}
double Sin::oblicz()
{
	return sin(2* 3.1415*(a->oblicz()/360));
}
string Sin::opis()
{
	return "sin("+ a->opis() +")";
}

Cos::Cos(wyrazenie *a1)
{
	this->a = a1;
}
double Cos::oblicz()
{
	return cos(2 * 3.1415*(a->oblicz() / 360));
}
string Cos::opis()
{
	return "cos(" + a->opis() + ")";
}

Exp::Exp(wyrazenie *a1)
{
	this->a = a1;
}
double Exp::oblicz()
{
	return exp(a->oblicz());
}
string Exp::opis()
{
	return "exp(" + a->opis() + ")";
}

Ln::Ln(wyrazenie *a1)
{
	this->a = a1;
}
double Ln::oblicz()
{
	return log(a->oblicz());
}
string Ln::opis()
{
	return "ln(" + a->opis() + ")";
}

Bezwgl::Bezwgl(wyrazenie *a1)
{
	this->a = a1;
}
double Bezwgl::oblicz()
{
	return abs(a->oblicz());
}
string Bezwgl::opis()
{
	return "|" + a->opis() + "|";
}

Przeciw::Przeciw(wyrazenie *a1)
{
	this->a = a1;
}
double Przeciw::oblicz()
{
	return -(a->oblicz());
}
string Przeciw::opis()
{
	return "-(" + a->opis() + ")";
}

Odwrot::Odwrot(wyrazenie *a1)
{
	this->a = a1;
}
double Odwrot::oblicz()
{
	return 1/(a->oblicz());
}
string Odwrot::opis()
{
	return "1/(" + a->opis() + ")";
}

//---------------------------------------------------------

Dodaj::Dodaj(wyrazenie *a1, wyrazenie *b1)
{
	this->a = a1; this->b = b1;
}
double Dodaj::oblicz()
{
	double w = a->oblicz() + b->oblicz();
	return w;
}
string Dodaj::opis()
{
	return "("+a->opis() + "+"+ b->opis()+")";
}

Odejmij::Odejmij(wyrazenie *a1, wyrazenie *b1)
{
	this->a = a1; this->b = b1;
}
double Odejmij::oblicz()
{
	double w = a->oblicz() - b->oblicz();
	return w;
}
string Odejmij::opis()
{
	return "(" + a->opis() + "-" + b->opis() + ")";
}

Mnoz::Mnoz(wyrazenie *a1, wyrazenie *b1)
{
	this->a = a1; this->b = b1;
}
double Mnoz::oblicz()
{
	double w = a->oblicz() * b->oblicz();
	return w;
}
string Mnoz::opis()
{
	return "(" + a->opis() + "*" + b->opis() + ")";
}

Dziel::Dziel(wyrazenie *a1, wyrazenie *b1)
{
	if (b1->oblicz() == 0) cerr << ("NIE WOLNO ");
	this->a = a1; this->b = b1;
}
double Dziel::oblicz()
{
	if (b->oblicz() == 0) cerr << ("NIE WOLNO ");
	double w = a->oblicz() / b->oblicz();
	return w;
}
string Dziel::opis()
{
	return "(" + a->opis() + "/" + b->opis() + ")";
}

Logarytm::Logarytm(wyrazenie *a1, wyrazenie *b1)
{
	if (((a1->oblicz() < 0) || (b1->oblicz() < 0)) || ((a1->oblicz() ==1))) cerr << ("NIE WOLNO ");
	this->a = a1; this->b = b1;
}
double Logarytm::oblicz()
{
	if (((a->oblicz() < 0) || (b->oblicz() < 0)) || ((a->oblicz() == 1))) cerr << ("NIE WOLNO ");
	return log(b->oblicz())/log(a->oblicz());
}
string Logarytm::opis()
{
	if (((a->oblicz() < 0) || (b->oblicz() < 0)) || ((a->oblicz() == 1))) cerr << ("NIE WOLNO ");
	return "log" + a->opis() + "(" + b->opis() + ")";
}

Potega::Potega(wyrazenie *a1, wyrazenie *b1)
{
	this->a = a1; this->b = b1;
}
double Potega::oblicz()
{
	double w = pow( a->oblicz(), b->oblicz() );
	return w;
}
string Potega::opis()
{
	return  a->opis() + "^" + "("+ b->opis() + ")";
}

Modulo::Modulo(wyrazenie *a1, wyrazenie *b1)
{
	this->a = a1; this->b = b1;
}
double Modulo::oblicz()
{
	double w = fmod(a->oblicz(), b->oblicz());
	return w;
}
string Modulo::opis()
{
	return  a->opis() + "mod" + b->opis();
}