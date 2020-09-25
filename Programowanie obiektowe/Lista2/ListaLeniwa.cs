using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication
{
    class ListaLeniwa
    {
        public int rozmiar;
        public List<int> L;
        public Random r;

        public ListaLeniwa()
        {
            rozmiar = 0;
            L = new List<int>();
            r = new Random();
        }

        public virtual int kolejna(int n)
        {
            return r.Next();
        }

        public int size()
        {
            return rozmiar;
        }

        public int element(int n)
        {
            if (n < rozmiar) return L[n];
            else
            {
                rozmiar = n;

                if (L.Count == 0) L.Add(0);

                for (int i = L.Count - 1; i < n; i++)
                {
                    L.Add(kolejna(L[i]));
                }

                return L[n];
            }
        }

        public void wypisz_rozmiar()
        {
            Console.WriteLine("Rozmiar listy to " + rozmiar);
        }

        public void wypisz_wszystko()
        {
            for (int a = 1; a <= rozmiar; a++)
            {
                Console.WriteLine(a + "=" + L[a]);
            }
        }



    }

    class Pierwsze : ListaLeniwa
    {
        public bool pierwsza(int n)
        {
            if (n < 2) return false;

            for (int i = 2; i <= Math.Sqrt(n); i++)
            {
                if (n % i == 0) return false;
            }

            return true;
        }

        override public int kolejna(int n)
        {
            n++;
            while (!pierwsza(n)) n++;
            return n;
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {


            Console.WriteLine("TEST:");
            ListaLeniwa lista = new ListaLeniwa();
            Console.WriteLine("Tworzymy nowy element dla i=10: " + lista.element(10));
            lista.wypisz_rozmiar();
            lista.wypisz_wszystko();
            Console.WriteLine();

            Console.WriteLine("TEST v.2 L.PIERWSZE:");
            ListaLeniwa lista2 = new Pierwsze();
            Console.WriteLine("Tworzymy nowy element dla i=15: " + lista2.element(15));
            lista2.wypisz_rozmiar();
            lista2.wypisz_wszystko();
            Console.WriteLine();


            Console.ReadLine();
        }
    }

}
