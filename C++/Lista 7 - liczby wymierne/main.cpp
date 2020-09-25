#include "lib.h"

using namespace std;

void test_errora()
try
{
	wymierna W(1, 0);
}
catch (...)
{
	cout << "Dzielenie przez zero";
}


void main() 
{

	cout << "--Testy v2--" << endl << endl;

	wymierna W0;
	cout << W0.licznik() << endl;
	cout << W0.mianownik() << endl;
	cout << W0.to_str() << endl;
	cout << W0 << endl << endl;

	wymierna W1(5);

	cout << W1.licznik() << endl;
	cout << W1.mianownik() << endl;
	cout << W1.to_str() << endl;
	cout << W1 <<endl << endl;

	cout << "--Testy v2--" << endl << endl;

	wymierna W2(2, -4); // -1/4
	cout << W2.to_str() << endl;
	cout << W2 << endl << endl;

	wymierna W3(2, 18); // 1/9
	cout << W3.to_str() << endl;
	cout << W3 << endl << endl;

	cout << "--Testy_operatorow_bin--" << endl << endl;

	W3 = W3 + W2;
	cout << W3.to_str() << endl;
	cout << W3 << endl << endl;

	W3 = W3 - W2;
	cout << W3.to_str() << endl;
	cout << W3 << endl << endl;

	W3 = W3 * W2;
	cout << W3.to_str() << endl;
	cout << W3 << endl << endl;

	W3 = W3 / W2;
	cout << W3.to_str() << endl;
	cout << W3 << endl << endl;

	cout << "--Testy_operatorow_un--" << endl << endl;

	W3 = -W3;
	cout << W3.to_str() << endl;
	cout << W3 << endl << endl;

	W3 = !W3;
	cout << W3.to_str() << endl;
	cout << W3 << endl << endl;

	wymierna W_k = W3;
	wymierna &W_kk = W3;

	try
	{
		wymierna W(1,0);
	}
	catch (const Dzielenie_przez_0& error)
	{
		cerr << "ERROR" << endl;
		cerr << error.what() << endl;
	}
	catch (const Przekroczenie_zakresu& erro)
	{
		cerr << "ERROR" << endl;
		cerr << erro.what() << endl;
	}
	try
	{
		wymierna W(2147483647);
	}
	catch (const Dzielenie_przez_0& error)
	{
		cerr << "ERROR" << endl;
		cerr << error.what() << endl;
	}
	catch (const Przekroczenie_zakresu& erro)
	{
		cerr << "ERROR" << endl;
		cerr << erro.what() << endl;
	}
	



}


