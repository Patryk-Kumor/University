#include "lib.h"

void test(wyrazenie *a)
{
	Zmienna::Zmien("x", 0);
	cout << a->opis() << endl;
	double i = 0.01;
	while(i < 1.01)
	{
		cout << a->oblicz() << endl;
		Zmienna::Zmien("x", i);
		//cout << " - " << Zmienna::Szukaj("x");
		i += 0.01;
	}
}

void main()
{
	cout << "----------------------" << endl;
	cout << "-Liczba/Stala/Zmienna-" << endl;
	cout << "----------------------" << endl << endl;

	wyrazenie *l = new Liczba(2);
	cout << l->oblicz() << endl;
	cout << l->opis() << endl << endl;

	wyrazenie *p = new pi();
	cout << p->oblicz() << endl;
	cout << p->opis() << endl << endl;

	wyrazenie *p1 = new fi();
	cout << p1->oblicz() << endl;
	cout << p1->opis() << endl << endl;

	wyrazenie *p2 = new e();
	cout << p2->oblicz() << endl;
	cout << p2->opis() << endl << endl;



	//--------------------------------------------------------

	cout << "----------------------" << endl;
	cout << "-TEST OPERATOROW 1ARG-" << endl;
	cout << "----------------------" << endl << endl;

	wyrazenie *s = new Sin(new Liczba(30));
	cout << s->oblicz() << endl;
	cout << s->opis() << endl << endl;

	wyrazenie *c = new Cos(new Liczba(45));
	cout << c->oblicz() << endl;
	cout << c->opis() << endl << endl;

	wyrazenie *ex = new Exp(new Liczba(30));
	cout << ex->oblicz() << endl;
	cout << ex->opis() << endl << endl;

	wyrazenie *lo = new Ln(new Liczba(8));
	cout << lo->oblicz() << endl;
	cout << lo->opis() << endl << endl;

	wyrazenie *bez = new Bezwgl(new Liczba(-10));
	cout << bez->oblicz() << endl;
	cout << bez->opis() << endl << endl;

	wyrazenie *prz = new Przeciw(new Liczba(-10));
	cout << prz->oblicz() << endl;
	cout << prz->opis() << endl << endl;

	wyrazenie *odwr = new Odwrot(new Liczba(-10));
	cout << odwr->oblicz() << endl;
	cout << odwr->opis() << endl << endl;

	//--------------------------------------------------------

	cout << "----------------------" << endl ;
	cout << "-TEST OPERATOROW 2ARG-" << endl ;
	cout << "----------------------" << endl << endl;


	wyrazenie *dod = new Dodaj(new Liczba(1), new Liczba(2));
	cout << dod->oblicz() << endl;
	cout << dod->opis() << endl <<endl;

	wyrazenie *od = new Odejmij(new Liczba(1), new Liczba(2));
	cout << od->oblicz() << endl;
	cout << od->opis() << endl << endl;

	wyrazenie *mn = new Mnoz(new Liczba(1), new Liczba(2));
	cout << mn->oblicz() << endl;
	cout << mn->opis() << endl << endl;

	wyrazenie *dz = new Dziel(new Liczba(1), new Liczba(5));
	cout << dz->oblicz() << endl;
	cout << dz->opis() << endl << endl;

	wyrazenie *log2 = new Logarytm(new Liczba(2), new Liczba(8));
	cout << log2->oblicz() << endl;
	cout << log2->opis() << endl << endl;

	wyrazenie *mo = new Modulo(new Liczba(2), new Liczba(8));
	cout << mo->oblicz() << endl;
	cout << mo->opis() << endl << endl;

	wyrazenie *pot = new Potega(new Liczba(2), new Liczba(2));
	cout << pot->oblicz() << endl;
	cout << pot->opis() << endl << endl;

	cout << "---------------------" << endl;
	cout << "------PRZYKLADY------" << endl;
	cout << "---------------------" << endl << endl;

	
	Zmienna::Dodaj("x", 0);
	Zmienna::Dodaj("y", 0);
	Zmienna::Zmien("x", 0);

	wyrazenie *zmiennej = new Zmienna("x");

	wyrazenie *wyrazenie0 = new Odejmij(new pi(),new Dodaj(new Liczba(2),new Mnoz( new Zmienna("x"), new Liczba(7) ) ) );

	wyrazenie *wyrazenie1 = new Dziel(new Mnoz( new Odejmij(new Zmienna("x"), new Liczba(1)) , new Zmienna("x") ), new Liczba(2));

	wyrazenie *wyrazenie2 = new Dziel( new Dodaj(new Liczba(3), new Liczba(5)), new Dodaj(new Liczba(2), new Mnoz(new Zmienna("x"), new Liczba(7)))) ;

	wyrazenie *wyrazenie3 = new Dodaj( new Liczba(2), new Odejmij(new Mnoz(new Zmienna("x"), new Liczba(7)), new Dodaj(new Mnoz(new Zmienna("x"), new Liczba(3)),new Liczba(5))) );

	wyrazenie *wyrazenie5 = new Odejmij(new pi(), new Dodaj(new Liczba(2), new Mnoz(new Zmienna("y"), new Liczba(7))));

	wyrazenie *wyrazenie4 = new Dziel(new Cos(new Mnoz(new Dodaj(new Zmienna("x"), new Liczba(1)), new Zmienna("x"))), new Potega(new e(), new Potega(new Zmienna("x"), new Liczba(2))));

	//-------------------------------------------------------------------------------------------------------------------------//
	/*
	test(zmiennej);
	test(wyrazenie0);
	test(wyrazenie1);
	test(wyrazenie2);
	test(wyrazenie3);
	test(wyrazenie5);
	*/
	Zmienna::Zmien("x", 2);

	wyrazenie *wyrazenienew = new Dodaj(new Liczba(1), new Mnoz(new Liczba(5), new Liczba(2)));


	cout << wyrazenienew->opis() << endl;
	cout << wyrazenienew->oblicz() << endl;


}

