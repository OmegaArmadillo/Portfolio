using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS474_Lab1
{
    class Program
    {
        static long fib(int n)
        {
            if (n <= 1)
                return n;
            return fib(n-1) + fib(n-2);
        }
        static void Main(string[] args)
        {
            Stopwatch stopwatch = new Stopwatch();
            Console.Clear();
            stopwatch.Start();
            Parallel.For(0, 35, i =>
            {
                Console.WriteLine("Fib {0}: {1}", i, fib(i));
            });
            Console.WriteLine("Outside: Hello World");
            stopwatch.Stop();
            Console.WriteLine("Testing loop time in milliseconds: {0}", stopwatch.ElapsedMilliseconds);

            Console.ReadLine();
        }
    }
}
