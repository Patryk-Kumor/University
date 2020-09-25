#include "lib.h"
using namespace std;


wielomian::wielomian(int s, double wsp)
{
	if (wsp == 0)
	{
		cerr << "(int,double): Wspolczynnik przy najwyzszej potedze rowny 0" << endl;;
		return;
	}
	this->stopien = s;
	this->wspolczynniki = new double[s + 1];
	for (int i = 0; i <= s; i++)
		this->wspolczynniki[i] = wsp;
}
wielomian::wielomian(int s, const double wsp[])
{
	if (wsp[s] == 0)
	{
		cerr << "(int,const double): Wspolczynnik przy najwyzszej potedze rowny 0" << endl;
		return;
	}
	this->stopien = s;
	this->wspolczynniki = new double[s + 1];
	for (int i = 0; i <= s; i++)
		this->wspolczynniki[i] = wsp[i];
}
wielomian::wielomian(initializer_list<double> wsp)
{
	if (*(wsp.end() - 1) == 0)
	{
		cerr << "(initializer_list<double>): Wspolczynnik przy najwyszej potedze rowny 0" << endl;
		return;
	}
	this->stopien = wsp.size() - 1;
	this->wspolczynniki = new double[this->stopien + 1];
	int i = 0;
	for (auto iterator = wsp.begin(); iterator != wsp.end(); iterator++, i++)
		this->wspolczynniki[i] = *iterator;
}


//-------------------------------------------------------------------------


wielomian::~wielomian()
{
	//cout << " -deleted- ";
	delete[] this->wspolczynniki;
}


//-------------------------------------------------------------------------

wielomian::wielomian(const wielomian &w)
{
	this->stopien = w.stopien;
	this->wspolczynniki = new double[this->stopien + 1];
	for (int i = 0; i <= this->stopien; i++)
		this->wspolczynniki[i] = w.wspolczynniki[i];
}
/*
wielomian::wielomian(const wielomian &&w)
{
	this->stopien = w.stopien;
	this->wspolczynniki = w.wspolczynniki;
}
*/
wielomian& wielomian::operator=(const wielomian &w)
{

	this->stopien = w.stopien;
	this->wspolczynniki = new double[this->stopien + 1];
	for (int i = 0; i <= this->stopien; i++)
		this->wspolczynniki[i] = w.wspolczynniki[i];
	return *this;
}
wielomian& wielomian::operator=(wielomian &&w)
{
	this->stopien = w.stopien;
	this->wspolczynniki = w.wspolczynniki;
	w.wspolczynniki = nullptr;
	this->~wielomian();
	return *this;
}
//-------------------------------------------------------------------------

istream& operator >> (istream &streamin, wielomian &w)
{
	cout << "\nStopien: ";
	while (!(streamin >> w.stopien) || w.stopien <= 0)
	{
		streamin.clear();
		streamin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	w.wspolczynniki = new double[w.stopien + 1];
	cout << "\nWspolczynniki: \n";
	for (int i = 0; i <= w.stopien; i++)
		streamin >> w.wspolczynniki[i];
	return streamin;
}
ostream& operator<<(ostream &streamout, const wielomian &w)
{
	streamout << w.wspolczynniki[w.stopien] << "x^" << w.stopien;
	for (int i = w.stopien - 1; i >= 0; i--)
	{
		streamout << showpos << w.wspolczynniki[i] << "x^" << noshowpos << i;
	}
	return streamout;
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

double wielomian::operator[](int i) const
{
	if ((i > stopien)||(i<0))
	{
		std::cerr << "Niepoprawny indeks!\n";
		return NAN;
	}
	return this->wspolczynniki[i];
}

double wielomian::operator()(double x) const
{
	double w = 0;
	for (int i = 0; i <= this->stopien; i++) 
	{
		w += x;
		w += i;
	}
	return w;
}

wielomian operator + (const wielomian &u, const  wielomian &v)
{
	if (u.wspolczynniki[u.stopien] == -v.wspolczynniki[v.stopien])
	{
		cerr << "Wielomiany straca najwyzsza potege! "; return u;
	}
	int m = max(u.stopien, v.stopien);
	double *wsp = new double[m + 1] {0};
	for (int i = 0; i <= u.stopien; i++)
	{
		wsp[i] += u.wspolczynniki[i];
	}
	for (int i = 0; i <= v.stopien; i++)
	{
		wsp[i] += v.wspolczynniki[i];
	}
	wielomian w(m, wsp);
	return w;
}
wielomian operator - (const wielomian &u, const  wielomian &v)
{
	if (u.wspolczynniki[u.stopien] == v.wspolczynniki[v.stopien])
	{
		cerr << "Wielomiany straca najwyzsza potege! "; return u;
	}
	int m = max(u.stopien, v.stopien);
	double *wsp = new double[m + 1]{ 0 };
	for (int i = 0; i <= u.stopien; i++)
	{
		wsp[i] = u.wspolczynniki[i];
	}
	for (int i = 0; i <= v.stopien; i++)
	{
		wsp[i] -= v.wspolczynniki[i];
	}
	wielomian w(m, wsp);
	return w;
}
wielomian operator*(const wielomian &u, const wielomian &v)
{
	int s = u.stopien + v.stopien;
	double *wsp = new double[s + 1];
	for (int i = 0; i <= s; i++) { wsp[i] = 0; }
	for (int i = 0; i <= u.stopien; i++)
	{
		for (int j = 0; j <= v.stopien; j++)
		{
			wsp[i + j] += u.wspolczynniki[i] * v.wspolczynniki[j];
		}
	}
	wielomian w(s, wsp);
	delete[] wsp;
	return w;
}
wielomian& wielomian::operator+=(const wielomian &v)
{
	int m = max(this->stopien, v.stopien);
	double *wsp = new double[m + 1]{ 0 };
	for (int i = 0; i <= this->stopien; i++)
	{
		wsp[i] += this->wspolczynniki[i];
	}
	for (int i = 0; i <= v.stopien; i++)
	{
		wsp[i] += v.wspolczynniki[i];
	}
	wielomian w(m, wsp);
	*this = w;
	return *this;
}
wielomian& wielomian::operator-=(const wielomian &v)
{
	if (this->wspolczynniki[this->stopien] == v.wspolczynniki[v.stopien])
	{
		cerr << "Wielomiany straca najwyzsza potege! "; return *this;
	}
	int m = max(this->stopien, v.stopien);
	double *wsp = new double[m + 1]{ 0 };
	for (int i = 0; i <= this->stopien; i++)
	{
		wsp[i] = this->wspolczynniki[i];
	}
	for (int i = 0; i <= v.stopien; i++)
	{
		wsp[i] -= v.wspolczynniki[i];
	}
	wielomian w(m, wsp);
	delete[] wsp;
	*this = w;
	return *this;
}
wielomian& wielomian::operator*=(const wielomian &v)
{
	int s = this->stopien + v.stopien;
	double *wsp = new double[s + 1];
	for (int i = 0; i <= s; i++) { wsp[i] = 0; }
	for (int i = 0; i <= this->stopien; i++)
	{
		for (int j = 0; j <= v.stopien; j++)
		{
			wsp[i + j] += this->wspolczynniki[i] * v.wspolczynniki[j];
		}
	}
	wielomian w(s, wsp);
	delete[] wsp;
	*this = w;
	return *this;
}
wielomian& wielomian::operator*=(double c)
{
	for (int i = 0; i <= this->stopien; i++)
		this->wspolczynniki[i] *= c;
	return *this;
}