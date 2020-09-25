using System;
using System.Collections;

namespace PrimesColl
{
    public class Pierwsze : IEnumerator
    {
        private int obecny;

        private bool CzyPierwsza(int n)
        {
            if (n < 2) return false;

            for (int i = 2; i < n - 1; i++)
            {
                if (n % i == 0) return false;
            }

            return true;
        }

        public object Current
        {
            get // Tu ważne
            {
                return obecny;
            }
        }

        public bool MoveNext() //IEnumerator
        {
            obecny++;
            while (!CzyPierwsza(obecny)) obecny++;
            return obecny < int.MaxValue;
        }

        public void Reset() //IEnumerator
        {
            obecny = 1;
        }


    }


    class PrimeCollection : IEnumerable
    {
        public IEnumerator GetEnumerator()
        {
            return new Pierwsze();
        }
    }
}