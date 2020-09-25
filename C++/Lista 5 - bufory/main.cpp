#include "lib.h"
#include <iostream>

using namespace std;

void interL(List L)
{
	char wybor = '1';
	string elem;

	cout << endl;
	cout << "---LISTY---" << endl;
	cout << "1.Dodaj" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Wypisz" << endl;
	cout << "4.Rozmiar" << endl;
	cout << "5.Front" << endl;
	cout << "6.Back" << endl;
	cout << "7.Indeks" << endl;
	cout << "8.Zakoncz" << endl;


	while (wybor != '8')
	{
		wybor = _getch();

		switch (wybor)
		{
		case '1':
			int in1;
			cout << "Podaj indeks: ";
			cin >> in1;
			double wart1;
			cout << "Podaj element: ";
			cin >> wart1;
			L.Add(in1,wart1);
			break;
		case '2':
			int in2;
			cout << "Podaj indeks: ";
			cin >> in2;
			L.Remove(in2);
			break;
		case '3':
			L.WriteAll();
			break;
		case '4':
			cout << L.GetSize() << endl;
			break;
		case '5':
			cout << L.Front() << endl;
			break;
		case '6':
			cout << L.Back() << endl;
			break;
		case '7':
			int in3;
			cout << "Podaj indeks: ";
			cin >> in3;
			cout << L.Indeks(in3) <<endl;
			break;
		default:
			if (wybor != '8')
				cerr << "Bledna komenda";
		}
	}
	wybor = NULL;
};

void interQ(Queue Q)
{
	char wybor = '1';
	string elem;

	cout << endl;
	cout << "---Queue---" << endl;
	cout << "1.++" << endl;
	cout << "2.--" << endl;
	cout << "3.Wypisz" << endl;
	cout << "4.Rozmiar" << endl;
	cout << "5.Zakoncz" << endl;


	while (wybor != '5')
	{
		wybor = _getch();

		switch (wybor)
		{
		case '1':
			double wart1;
			cout << "Podaj element: ";
			cin >> wart1;
			Q+=wart1;
			break;
		case '2':
			--Q;
			break;
		case '3':
			Q.WriteAll();
			break;
		case '4':
			cout << Q.ile() << endl;
			break;
		default:
			if (wybor != '5')
				cerr << "Bledna komenda";
		}
	}
	wybor = NULL;
};

void interS(Stack S)
{
	char wybor = '1';
	string elem;

	cout << endl;
	cout << "---Stack---" << endl;
	cout << "1.++" << endl;
	cout << "2.--" << endl;
	cout << "3.Wypisz" << endl;
	cout << "4.Rozmiar" << endl;
	cout << "5.Zakoncz" << endl;



	while (wybor != '5')
	{
		wybor = _getch();

		switch (wybor)
		{
		case '1':
			double wart1;
			cout << "Podaj element: ";
			cin >> wart1;
			S += wart1;
			break;
		case '2':
			--S;
			break;
		case '3':
			S.WriteAll();
			break;
		case '4':
			cout << S.ile() << endl;
			break;
		default:
			if (wybor != '5')
				cerr << "Bledna komenda";
		}
	}
	wybor = NULL;
};

int main()
{
	List Lita;
	cin >>  Lita;
	Lita.WriteAll();

	List A=Lita;

	std::cout << "------------ LIST ------------\n";
	List MyList;
	interL(MyList);

	std::cout << "\n------------ QUEUE ------------\n";
	Queue MyQueue;
	interQ(MyQueue);


	std::cout << "\n------------ STACK ------------n";
	Stack MyStack;
	interS(MyStack);

}






