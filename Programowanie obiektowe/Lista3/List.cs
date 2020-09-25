using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lista
{
    public class Lista<T>
    {
        Lista<T> next;
        Lista<T> prev;
        protected T val;

        bool pustość = true;


        public T Obecny()
        {
            return this.val;
        }

        public void Dodaj_Koniec(T val)
        {
            if (pustość == true) pustość = false;

            if (this.next != null) this.next.Dodaj_Koniec(val);
            else
            {
                this.next = new Lista<T>();
                this.next.val = val;
            }
        }

        public void Dodaj_Początek(T val)
        {
            if (pustość == true) pustość = false;

            if (this.prev != null) this.prev.Dodaj_Początek(val);
            else
            {
                this.prev = new Lista<T>();
                this.prev.val = val;
            }
        }

        public void Usuń_Koniec()
        {
            if (this.next == null) this.prev=null;
            else
            {
                this.next.Usuń_Koniec();
            }
        }

        public void Usuń_Początek()
        {
            if (this.prev == null) this.next = null;
            else
            {
                this.prev.Usuń_Początek();
            }
        }

        public bool Czy_Pusta()
        {
            return pustość;
        }

        public bool Czy_Pusta_V2()
        {
            return ((this.prev == null)&(this.next == null)&(this == null));
        }

        public T Koniec()
        {
            if (this.prev != null) return this.prev.Koniec();
            else return this.val;
        }

        public T Początek()
        {
            if (this.next != null) return this.prev.Początek();
            else return this.val;     
        }





    }
}
