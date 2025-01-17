#include "lib.h"

double odleglosc(punkt P, punkt Q)
{
	return sqrt(pow((Q.x - P.x), 2) + pow((Q.y - P.y), 2));
}

bool czy_prostopadle(odcinek M, odcinek N)
{
	double wspol_M = (M.B.y - M.A.y) / (M.B.x - M.A.x);
	double wspol_N = (N.B.y - N.A.y) / (N.B.x - N.A.x);
	if (wspol_N*wspol_M == -1) return true;
	else return false;
}

bool czy_rownolegle(odcinek M, odcinek N)
{
	double wspol_M = (M.B.y - M.A.y) / (M.B.x - M.A.x);
	double wspol_N = (N.B.y - N.A.y) / (N.B.x - N.A.x);
	if (wspol_N == wspol_M) return true;
	else return false;
}

string przeciecie(odcinek M, odcinek N)
{
	double wspol_M = (M.B.y - M.A.y) / (M.B.x - M.A.x);
	double wspol_N = (N.B.y - N.A.y) / (N.B.x - N.A.x);
	if (wspol_N == wspol_M)
		throw string("Nie ma przeciecia");
	else
	{
		return string("ma");
	}

}

bool czy_rozlaczne(trojkat t1, trojkat t2)
{
	if ((t1.czy_w(t2.A) == false) && (t1.czy_w(t2.B) == false) && (t1.czy_w(t2.C) == false) && (t2.czy_w(t1.A) == false) && (t2.czy_w(t1.B) == false) && (t2.czy_w(t1.C) == false))return true;
	else
		return false;
}

bool czy_zawiera(trojkat t1, trojkat t2)
{
	double p1, p2;
	p1 = t1.pole();
	p2 = t2.pole();
	if (p1 >= p2)
	{
		if (t1.czy_w(t2.A) == true && t1.czy_w(t2.B) == true && t1.czy_w(t2.C) == true) return true;
	}
	else
	{
		if (t2.czy_w(t1.A) == true && t2.czy_w(t1.B) == true && t2.czy_w(t1.C) == true) return true;
	}
	return false;
}





int main(int x)
{
	double a; double b; double c; punkt Y;

	
	cout << "	KLASA - PUNKT " << endl;
	cout << "Definiujemy nowy punkt: "; punkt X; X.wypisz(); cout << endl;
	cout << "Podaj nowe wspolrzedne dla punktu:\na="; cin >> a; cout << "b="; cin >> b; punkt X2 = X;
	cout << "Podaj wspolrzednprzesuniecia:\na="; cin >> a; cout << "b="; cin >> b;
	cout << "Przesuwamy o wektor [" << a << "," << b << "]: "; X.przesun(a, b); X.wypisz(); cout << endl;
	cout << "Zmieniamy wsporzedne punktu na (" << a << "," << b << "): "; X.nadpisz(a, b); X.wypisz(); cout << endl;
	cout << "Podaj kat obrotu wzgledem jakiegos punktu\nkat="; cin >> a; cout << "-pierwsza wspolrzedna punktu="; cin >> b;  cout << "-druga wspolrzedna punktu="; cin >> c; Y.nadpisz(b, c);
	cout << "Nowe wspolrzedne: "; X.obrot_punkt(a, Y); X.wypisz(); cout << endl;
	cout << "Ich odleglosc: " << odleglosc(X,Y); cout << endl << endl << endl;


	cout << "	KLASA - ODCINEK " << endl;
	punkt P; punkt Q; P.nadpisz(1, 2); Q.nadpisz(2, 4);
	cout << "Definiujemy nowy odcinek: "; odcinek Odc; Odc.wypisz(); cout << endl;
	cout << "Zmieniamy wsp.: P(1, 2); Q(2, 4): "; Odc.nadpisz(P, Q); Odc.wypisz(); cout << endl; odcinek Z = Odc;
	cout << "Dlugosc: " << Odc.lenght(); cout << endl;
	cout << "Srodek: "; Odc.srodek().wypisz(); cout << endl;
	cout << "Przesuniecie o [1,2]: "; Odc.przesun(1,2); Odc.wypisz(); cout << endl;
	cout << "Obrot o 45rad wobec (2,4): "; Odc.obrot_odcinek(45,Q); Odc.wypisz(); cout << endl;
	cout << "Czy P(1,2) lezy na odcinku? "; cout <<Odc.czy_lezy(P); cout << endl;
	cout << "Odcinek bazowy Z: "; Z.wypisz(); cout << endl;
	cout << "Czy prostopadle? " << czy_prostopadle(Odc, Z); cout << endl;
	cout << "Czy rownolegle? " << czy_rownolegle(Odc, Z); cout << endl << endl << endl;	
	cout << "Punkt wspolny?: " << przeciecie(Z,Odc) << endl << endl;



	cout << "	KLASA - TROJKAT " << endl;
	cout << "A=(0,0),B=(0,3),C=(3,3)"; punkt A1; punkt B1; B1.nadpisz(0, 3); punkt C1; C1.nadpisz(3, 3); cout << endl; punkt R; R.nadpisz(0, 1);
	cout << "Tworzymy nowy trojkat:"; trojkat T; T.nadpisz(A1, B1, C1); cout << endl; punkt E; E.nadpisz(1, 0.5);
	trojkat T2 = T;
	cout << "Czy E(12,1) jest w trojkacie? " << T.czy_w(E); cout << endl;
	cout << "Jego pole: " << T.pole(); cout << endl;
	cout << "Jego obwod: " << T.obwod(); cout << endl;
	cout << "Jego srodek: "; T.srodek().wypisz(); cout << endl;
	cout << "Przesuniecie o [1,2]: "; T.przesun(1, 2); T.wypisz(); cout << endl;
	cout << "Obrot o 45rad (1,1): "; T.obrot_trojkat(45,E); T.wypisz(); cout << endl;
	cout << "Czy T2 zawiera sie w T:" << czy_zawiera(T, T2) << endl;
	cout << "Czy T2 rozloczne wobec T: " << czy_rozlaczne(T, T2) << endl;




	cout << endl;



};
