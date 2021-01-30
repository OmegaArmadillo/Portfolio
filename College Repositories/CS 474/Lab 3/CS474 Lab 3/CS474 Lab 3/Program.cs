using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

namespace CS474_Lab_3
{
    class Program
    {
        const int SIZE = 1000;


        // sequential example modified from https://www.geeksforgeeks.org/sieve-of-eratosthenes/
        public static void SequentialSOE()
        {

            //holds wether numbers are prime
            byte[] allNumbers = new byte[SIZE];

            //set all numbers as being prime
            for (int i = 0; i < SIZE; i++)
            {
                allNumbers[i] = 1;
            }


            //celing of the sqrt of size
            int sizeCeiling = ((int)Math.Sqrt(SIZE)) + 1;

            //go through all numbers up to the ceiling
            for (int i = 2; i < sizeCeiling; i++)
            {
               //if the current number is a prime
                if (allNumbers[i] == 1)
                {
                   //got through all multiples and set them to not be prime
                    for (int j = i * i; j < SIZE; j = j + i)
                    {
                        allNumbers[j] = 0;
                    }
                        
                }
            }

            //holds the total number of primes
            int primeTotal = 0;

           //calculate the total number of primes
            for (int i = 2; i < SIZE; i++)
            {
                if (allNumbers[i] == 1)
                    primeTotal++;
            }

            Console.WriteLine("S Prime Total {0}", primeTotal);

        }






        public static void ParallelSoE ()
        {

           

            //repersesnts each number
            byte[] allNumbers = new byte[SIZE];

            //fill all of the array with 1
            Parallel.For(0, SIZE, i =>
            {
                allNumbers[i] = 1;

            });

            //the ceiling of the square root of size
            int sizeCeiling = ((int)Math.Sqrt(SIZE)) + 1;


            //calculate how big a chunk should be
            int chunkSize = ((sizeCeiling) / 16) + 1;


            //go through the amount of chunks
            Parallel.For(0, 16, m =>
            {

                //calculate the start and end of each chunk
                int start = (m * chunkSize)+2;
                int end = (m * chunkSize) + chunkSize+2;
                

               //Console.WriteLine("se {0},{1}", start, end);

                //go through each chunk
                for(int k = start; k<end; k++)
                {
                    
                    //checks if the current number is a prime
                    if (allNumbers[k] == 1)
                    {

                        //sets all non prime numbers that are a multiple of the current prime to 0        
                        for (int j = k * k; j < SIZE; j = j + k)
                        {
                            allNumbers[j] = 0;
                        }


                    }




                }



            });

            

            //total number of prime numbers in the array
            int primeTotal = 0;

            //find the numbers that are prime and add to the total
            Parallel.For(2, SIZE, i =>
            {

                if (allNumbers[i] == 1)
                    Interlocked.Add(ref primeTotal, 1);

            });
          
            Console.WriteLine("P Prime Total {0}", primeTotal);
        }


        static void Main(string[] args)
        {
            Stopwatch sequentialTime = new Stopwatch();

            Stopwatch parallelTime = new Stopwatch();



            sequentialTime.Start();
            SequentialSOE();
            sequentialTime.Stop();
            Console.WriteLine("Sequential Time {0}", sequentialTime.ElapsedMilliseconds);


            
            parallelTime.Start();
            ParallelSoE();
            parallelTime.Stop();
            Console.WriteLine("Parallel Time Chunk {0}", parallelTime.ElapsedMilliseconds);
           


            
        }
    }
}
