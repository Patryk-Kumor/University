using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Stream
{
    class IntStream
    {
        public int prev;

        public IntStream()
        {
            reset();
        }

        public virtual int next()
        {
            if (prev == int.MaxValue) return -1;
            prev++;
            return prev;
        }

        public bool eos()
        {
            return (prev == int.MaxValue);
        }

        virtual public void reset()
        {
            prev = -1;
        }


    }

    class PrimesStream : IntStream
    {


        override public int next()
        {
            prev++;
            if (prev == int.MaxValue) return 1;
            while (!pierwsza(prev)) prev++;
            return prev;
        }

        public bool pierwsza(int n)
        {
            if (n < 2) return false;
            for (int i = 2; i <= Math.Sqrt(n); i++)
            {
                if (n % i == 0) return false;
            }

            return true;
        }

        override public void reset()
        {
            prev = 1;
        }


    }

    class RandomStream : IntStream
    {
        Random r = new Random();

        public override int next()
        {
            return r.Next(-int.MaxValue,int.MaxValue);
        }


    }

    class Program
    {
        static void Main()
        {

            IntStream stream = new IntStream();
            Console.WriteLine("TEST");
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(stream.next());
                Console.WriteLine(stream.eos());
            }



            PrimesStream stream2 = new PrimesStream();
            Console.WriteLine();
            Console.WriteLine("TEST PRIMES");
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(stream2.next());
                Console.WriteLine(stream2.eos());
            }

            RandomStream stream3 = new RandomStream();
            Console.WriteLine();
            Console.WriteLine("TEST RANDOM");
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(stream3.next());
                Console.WriteLine(stream3.eos());
            }

            Console.Read();

        }

    }

}
