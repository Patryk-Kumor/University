using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Interfejs_Słownik
{
    interface Słowniczek<K,V>:  IEnumerable
    {
        void Dodaj(K klucz, V wartość);

        V Szukaj(K klucz);

        void Usuń(K klucz);
    }


    class Słownik<K, V> : Słowniczek<K, V>, IEnumerable where K : IEquatable<K>
{

        Słownik<K, V> next;
        Słownik<K, V> prev;
        private K klucz;
        private V wartość;
        int Length;
	private int obecny=1;


        public void Dodaj(K nowy_klucz, V nowa_wartość)
        {
            if (this.klucz.Equals(nowy_klucz)) wartość = nowa_wartość;
            else
            {
                if (this.next == null)
                {
                    klucz = nowy_klucz;
                    wartość = nowa_wartość;
                    this.next = new Słownik<K, V>();
                    Length++;
                }
                else
                {
                    this.next.Dodaj(nowy_klucz, nowa_wartość);
                }
            }
        }


        public V Szukaj(K szukany_klucz)
        {
            if (this.next == null)
            {
                Console.WriteLine("Nie znaleziono");
            }
            else
            {
                if (this.klucz.Equals(szukany_klucz))
                {
                    Console.Write("Znaleziono");
                    Console.Write(this.wartość);
                }
                else
                {
                    this.next.Szukaj(szukany_klucz);
                }
            }

            return wartość;
        }


        public void Usuń(K usuwany_klucz)
        {
            if ((this.next == null) && (!(this.klucz.Equals(usuwany_klucz)))) throw new Exception("Error nr=1");
            if ((this.klucz.Equals(usuwany_klucz)) && (this.prev == null) && (this.next == null)) throw new Exception("Error nr=2");
            if (this.klucz.Equals(usuwany_klucz))
            {
                if (this.next != null)
                {
                    this.next.prev = this.prev;
                    Length--;
                }
                if (this.prev != null)
                {
                    this.prev.next = null;
                    Length--;
                }
                else
                {
                    this.prev.next = this.next;
                    this.next.prev = this.prev;
                    Length--;
                }
            }
            else
            {
                if (this.prev != null)
                    this.prev.Usuń(usuwany_klucz);
                if (this.next != null)
                    this.next.Usuń(usuwany_klucz);
            }
        }

        public override string ToString()
        {
            return base.ToString() + ":<" + klucz.ToString() + "-" + wartość.ToString() + ">";
        }

        public int Długość()
        {
            return Length;
        }

	

	
}

    class Słowa : IEnumerator
    {
	private int obecny=1;
        public IEnumerable GetEnumerator()
        {
            return new Słownik<K,V>();
        }
	public object Current
        {
            get {return obecny;}
        }
	public bool MoveNext() //IEnumerator
	{
            obecny++;
        }
        public void Reset() //IEnumerator
        {
            obecny=1;
        }

    }
    



    public class Program
    {
        public static void Main()
        {
		Słownik<string,string> S = new Słownik<string,string>(); 
		S.Dodaj("smok","skyrim");           
		foreach (string K in S)
                Console.WriteLine(K);
        }
    }
}
