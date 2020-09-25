using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Słowniki
{
    class CustomException : Exception
    {
        public CustomException(string message)
        {

        }

    }
    class Slownik<K, V> where K : IEquatable<K>
    {

        Slownik<K, V> next;
        Slownik<K, V> prev;
        private K klucz;
        private V wartość;

        public void Dodaj(K nowy_klucz, V nowa_wartość)
        {
            if (this.klucz.Equals(nowy_klucz)) wartość = nowa_wartość;
            else
            {
                if (this.next == null)
                {
                    klucz = nowy_klucz;
                    wartość = nowa_wartość;
                    this.next = new Slownik<K, V>();
                }
                else
                {
                    this.next.Dodaj(nowy_klucz, nowa_wartość);
                }
            }
        }


        public void Szukaj(K szukany_klucz)
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
        }


        public void Usuń(K usuwany_klucz)
		
		{
			CustomException niema = new CustomException("Nie ma takiego elementu");
			CustomException jedynak = new CustomException("Jednoelementowy słownik");
			
			if ((this.next==null)&&(!(this.klucz.Equals(usuwany_klucz))) throw(niema);
			
			if ((this.klucz.Equals(usuwany_klucz))&&(this.prev==null)&&(this.next==null)) throw jedynak;
			
            if (this.klucz.Equals(usuwany_klucz))
            {
				if (this.next!=null)
					this.next.prev=this.prev;
				if (this.prev!=null)
					this.prev.next=null;
				else{
					this.prev.next=this.next;
					this.next.prev=this.prev;  }  
            }
            else
            {
                if (this.prev != null)
                    this.prev.Usuń(usuwany_klucz);
                if (this.next != null)
                    this.next.Usuń(usuwany_klucz);
            }
        }











    }
}