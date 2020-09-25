#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <typeinfo>       // operator typeid
#include <exception>  
#include <list>
#include <cstdlib>
#include <climits>

using namespace std;


class Wyjatek_wymierny : public exception
	{
	private:
		string blad;
	public:
		Wyjatek_wymierny() { blad = "Wyjatek wymierny!"; }
		Wyjatek_wymierny(string str) { blad = str; }
		const char* what() { return blad.c_str(); }
	};
class Przekroczenie_zakresu : public Wyjatek_wymierny
	{
	private:
		string blad;
	public:
		Przekroczenie_zakresu() { blad = "Przekroczony zakres!"; }
		Przekroczenie_zakresu(string str) { blad = str; }
		virtual const char* what() const noexcept override { return "Przekroczenie zakresu!"; }
};
class Dzielenie_przez_0 : public Wyjatek_wymierny
{
private:
	string blad;
public:
	Dzielenie_przez_0() { blad = "Dzielenie przez zero!"; }
	Dzielenie_przez_0(string str) { blad = str; }
	//const char* what() { return blad.c_str(); }
	virtual const char* what() const noexcept override { return "Dzielenie przez zero!"; }
};


class wymierna
{


public:
	int licz, mian;
	wymierna();
	wymierna(int n_licznik, int n_mianownik = 1) throw(Dzielenie_przez_0, Przekroczenie_zakresu);
	int nwd(int a, int b);
	int licznik();
	int mianownik();

	string to_str();

	friend ostream &operator<<(ostream &os, wymierna const &w)
	{
		double wynik = double(w.licz) / double(w.mian);
		os << wynik;
		return os;
	};

	explicit operator int const();

	friend wymierna operator+ (const wymierna &x, const wymierna &y);
	friend wymierna operator- (const wymierna &x, const wymierna &y);
	friend wymierna operator* (const wymierna &x, const wymierna &y);
	friend wymierna operator/ (const wymierna &x, const wymierna &y);

	wymierna operator- ();
	wymierna operator! ();
};
