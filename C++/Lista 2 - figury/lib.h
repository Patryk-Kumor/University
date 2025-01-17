#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <iostream>
#include <math.h>

using namespace std;


class punkt
{
public:
	double x;
	double y;
	punkt() //Konstruktor
	{
		x = 0;
		y = 0;
	}
	punkt(double a, double b) //Konstruktor zdefiniowany przez zmienne
	{
		x = a;
		y = b;
	}
	punkt(punkt &p) //Konstruktor kopiujacy
	{
		x = p.x;
		y = p.y;
	}
	void nadpisz(double a, double b)
	{
		x = a;
		y = b;
	}
	void przesun(double a, double b)
	{
		x += a;
		y += b;
	}
	void  wypisz()
	{
		cout << "x=" << x << ", y=" << y << "  ";
	}
	void obrot_punkt(double kat, punkt P)
	{
		double a = x;
		double b = y;
		x = (a - P.x)*cos(kat) - (b - P.y)*sin(kat);
		y = (a - P.x)*sin(kat) + (b - P.y)*cos(kat);

	}
	double odleglosc(punkt P, punkt Q)
	{
		return sqrt(pow((Q.x - P.x), 2) + pow((Q.y - P.y), 2));
	}
};



class odcinek : punkt
{
public:
	punkt A;
	punkt B;
	double dlugosc = ( odleglosc(A,B) );
	odcinek()
	{
	}
	double lenght()
	{
		return odleglosc(A, B);
	}
	odcinek(punkt A1, punkt B1) //Konstruktor
	{
		if ((A1.x == B1.x) || (A1.y == B1.y))
			throw string("NIE. To jest jeden punkt");
		else
		{
			A = A1;
			B = B1;
		}
	}
	odcinek(odcinek &o)  //Konstruktor kopiujacy
	{
		A.x = o.A.x;
		A.y = o.A.y;
		B.x = o.B.x;
		B.y = o.B.y;
		dlugosc = o.dlugosc;
	}
	void nadpisz(punkt A1, punkt B1)
	{
		if ((A1.x == B1.x) || (A1.y == B1.y))
			throw string("NIE. To jest jeden punkt");
		else
		{
			A = A1;
			B = B1;
		}
	}
	void przesun(double a, double b)
	{
		A.x += a;
		A.y += b;
		B.x += a;
		B.y += b;
	}
	void obrot_odcinek(double kat, punkt P)
	{
		A.obrot_punkt(kat, P);
		B.obrot_punkt(kat, P);
	}
	bool czy_lezy(punkt P)
	{
		double o1, o2, o3;
		o1 = odleglosc(A, P);
		o2 = odleglosc(P, B);
		o3 = dlugosc;
		if (o1 + o2 == o3)
			return true;
		else
			return false;
	}
	punkt srodek()
	{
		punkt srodek;
		srodek.x = (A.x + B.x) / 2;
		srodek.y = (A.y + B.y) / 2;
		return srodek;
	}
	void wypisz()
	{
		A.wypisz();
		B.wypisz();
	}	
	double odleglosc(punkt P, punkt Q)
	{
		return sqrt(pow((Q.x - P.x), 2) + pow((Q.y - P.y), 2));
	}

};



class trojkat : punkt
{
public:
	punkt A;
	punkt B;
	punkt C;
	trojkat()   //Konstruktor
	{
		A.x = 0;
		A.y = 0;
		B.x = 0;
		B.y = 0;
		C.x = 0;
		C.y = 0;
	}
	trojkat(trojkat &t)    //Konstruktor kopiujacy
	{
		A.x = t.A.x;
		A.y = t.A.y;
		B.x = t.B.x;
		B.y = t.B.y;
		C.x = t.C.x;
		C.y = t.C.y;
	}
	void nadpisz(punkt P, punkt Q, punkt R)
	{
		if (((P.y - Q.y) / (P.x - Q.x) == (P.y - R.y) / (P.x - R.x)) & ((P.y - R.y) / (P.x - R.x) == (Q.y - R.y) / (Q.x - R.x))) { throw string("wspolliniowe!"); }
		A.x = P.x;
		A.y = P.y;
		B.x = Q.y;
		B.y = Q.y;
		C.x = R.y;
		C.y = R.y;
	}
	void przesun(double a, double b)
	{
		A.x += a;
		A.y += b;
		B.x += a;
		B.y += b;
		C.x += a;
		C.y += b;
	}
	void obrot_trojkat(double kat, punkt P)
	{
		A.obrot_punkt(kat, P);
		B.obrot_punkt(kat, P);
		C.obrot_punkt(kat, P);
	}
	double obwod()
	{
		double AB, BC, CA;
		AB = odleglosc(A, B);
		BC = odleglosc(B, C);
		CA = odleglosc(C, A);
		return AB + BC + CA;
	}
	double pole()
	{
		double AB, BC, CA;
		AB = odleglosc(A, B);
		BC = odleglosc(B, C);
		CA = odleglosc(C, A);
		double p = (AB + BC + CA) / 2;
		return p;
	}
	void wypisz()
	{
		cout << "A:"; A.wypisz();
		cout << "B:"; B.wypisz();
		cout << "C:"; C.wypisz();
	}
	punkt srodek()
	{
		punkt middle;
		middle.x = (A.x + B.x + C.x) / 3;
		middle.y = (A.y + B.y + C.x) / 3;
		return middle;
	}
	bool czy_w(punkt P)
	{
		double p1, p2, p3, p4;
		trojkat t1, t2, t3;
		t1.A = A; t1.B = B; t1.C = P;
		t2.A = A; t2.B = P; t2.C = C;
		t3.A = P; t3.B = B; t3.C = C;
		p1 = t1.pole();
		p2 = t2.pole();
		p3 = t3.pole();
		p4 = pole();
		if (p1 + p2 + p3 == p4)
			return true;
		else return false;
	}

};




