using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PrimesColl
{
    class Program
    {
        static void Main()
        {
            PrimeCollection pc = new PrimeCollection();

            foreach (int p in pc)
                Console.WriteLine(p);
        }
    }
}