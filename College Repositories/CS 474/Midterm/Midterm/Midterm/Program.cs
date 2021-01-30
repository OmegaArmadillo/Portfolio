using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CS474_Lab_3
{

    class Program
    {


        //size of test array
        private static int SIZE = 100;
        private static int CC = Environment.ProcessorCount;

        public Program() { }  //Constructor
        public static double pi_seq()
        {
            Random r = new Random();
            int nCount = 0;
            double x, y;

            for (int i = 0; i < SIZE; i++)
            {
                x = r.NextDouble();
                y = r.NextDouble();

                if ((x * x + y * y) < 1)
                    nCount++;
            }
            //Console.WriteLine("Pi is {0}", (nCount * 1.0) / SIZE * 4);
            return (nCount * 1.0) / SIZE * 4;
        }

        public static double pi_par()
        {

          
            int nCount = 0;

            int chunkSize = SIZE / CC;

            Parallel.For(0, CC, i => 
            {
                Random r = new Random();
                double x, y;
                
                for (int j = 0; j < chunkSize; j++) 
                {
                   
                    x = r.NextDouble();
                    y = r.NextDouble();

                    Console.WriteLine("{0},{1}", x, y);

                    if ((x * x + y * y) < 1)
                        Interlocked.Add(ref nCount, 1);

                }
                

            });

           
            return (nCount * 1.0) / SIZE * 4; ;  
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Pi is {0}", pi_seq());
            Console.WriteLine("Pi is {0}", pi_par());
            Console.ReadKey();
        }
    }


}
