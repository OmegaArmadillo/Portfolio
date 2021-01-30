using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CS474_Lab2
{
    class Program
    {


        static void Main(string[] args)
        {
            Stopwatch stopwatch1 = new Stopwatch();
            Stopwatch stopwatch2 = new Stopwatch();
            
            //how many numbers are generated
            const int SIZE = 20000000;

            //the list of numbers
            int[] list = new int[SIZE];

            //the randomizer
            var rand = new Random();

            //generate the list of numbers
            for(int i = 0; i < SIZE; i++)
            {
                list[i] = rand.Next();
               //Console.WriteLine("{0}", list[i]);
            }





           //run the algorithms and record/display their times
            stopwatch1.Start();
            SequenialMax(SIZE, list);
            stopwatch1.Stop();
            Console.WriteLine("Sequential: {0}", stopwatch1.ElapsedMilliseconds);

            stopwatch2.Start();
            ParallelMax(SIZE,list, Environment.ProcessorCount);
           // Console.WriteLine("PC: {0}", Environment.ProcessorCount);
            stopwatch2.Stop();
            Console.WriteLine("Parallel: {0}", stopwatch2.ElapsedMilliseconds);    
            
            Console.ReadLine();
        }



        static void SequenialMax(int SIZE, int[] list)
        {
            //stores the highest number
            int nMax = 0;

            //go through the list and replace nMax if a new highest number is found
            for (int i = 0; i < SIZE; i++)
            {
                if (list[i] > nMax)
                {
                    nMax = list[i];
                }
            }


            Console.WriteLine("Sequential List Max: {0}", nMax);

        }

      

        static void ParallelMax(int SIZE, int[] list, int chunkAmount)
        {
            //the size of each chunk
            int chunkSize = SIZE / chunkAmount;

            //the highest value of the entire list
            int nMax = 0;
           
            //go through each chunk in parallel
            Parallel.For(0, chunkAmount, i =>
            {
                //the temp to hold the highest value of each chunk
                int temp = 0;

                //the lock for the checking and replacing at the end
                object objLock = new object();

                //go through the chunk and find the highest value in the chunk
                for (int j = i * chunkSize; j < (i * chunkSize) + chunkSize; j++)
                    {
                        if (list[j] > temp)
                        {

                            temp = list[j];
                            
                        }
                    }

                //put a lock on replacing the highest value in the list so it won't accidently replace the highest value 
                lock (objLock) 
                {
                    if (temp > nMax)
                    {

                        nMax = temp;

                    }

                }


            }
            );


            Console.WriteLine("Parallel List Max: {0}", nMax);

        }

        


    }

}
