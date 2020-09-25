#include "lib.h"
wymierna::wymierna()
{
	this->licz = 0;
	this->mian = 1;
}
wymierna::wymierna(int n_licznik, int n_mianownik) throw(Dzielenie_przez_0, Przekroczenie_zakresu)
{	
	if (n_mianownik == 0)
	{
		throw Dzielenie_przez_0();
	}

	if ((n_licznik >= 2147483647) || (n_mianownik >= 2147483647))
	{
		throw Przekroczenie_zakresu();
	}

	int NWD = this->nwd(n_licznik, n_mianownik);

		if (n_licznik*n_mianownik >= 0)
		{
			this->licz = abs(n_licznik) / NWD;
			this->mian = abs(n_mianownik) / NWD;
		}
		else
		{
			this->licz = -abs(n_licznik / NWD);
			this->mian = abs(n_mianownik / NWD);
		}
	

}
int wymierna::nwd(int a, int b)
{
	a = abs(a);
	b = abs(b);
	while (a != b)
	{
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return a; 
}


int wymierna::licznik() 
{
	return this->licz;
}
int wymierna::mianownik()
{
	return this->mian;
}

string wymierna::to_str()
{
	string a = to_string(licz);
	string b = to_string(mian);
	return (a+"/"+b) ;
}


wymierna operator+(const wymierna &x, const wymierna &y)
{	
	int l = x.licz*y.mian + y.licz*x.mian;
	int m = x.mian*y.mian;

	return wymierna(l,m);
}
wymierna operator-(const wymierna &x, const wymierna &y)
{
	int l = x.licz*y.mian - y.licz*x.mian;
	int m = x.mian*y.mian;

	return wymierna(l, m);
}
wymierna operator*(const wymierna &x, const wymierna &y)
{
	int l = x.licz*y.licz;
	int m = x.mian*y.mian;

	return wymierna(l, m);
}
wymierna operator/(const wymierna &x, const wymierna &y)
{
	int l = x.licz*y.mian;
	int m = x.mian*y.licz;

	return wymierna(l, m);
}


wymierna::operator int const()
{
	return licz / mian;
}

wymierna wymierna::operator- ()
{
	return wymierna(this->licz, -this->mian);
}
wymierna wymierna::operator! ()
{
	return wymierna(this->mian, this->licz);
}

