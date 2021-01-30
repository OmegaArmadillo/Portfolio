using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CS474_Lab_4
{
    class Program
    {
        const int SIZE = 100;


        static void PiEstimateS()
        {
            //get the width of each section
            double sectionWidth = 1 / (double)SIZE;

            //the estimat for pi
            double estimate = 0;

            //represstns x in th eequation
            double x = 0;

            //go throughthe equaiton
            for(int i = 0; i < SIZE; i++)
            {

                //calcuate hight
                double height = 4 / (1 + (x * x));

                //calculat the area
                double area = height * sectionWidth;

                //add to the esimate
                estimate = estimate + area;

                //increase x
                x = x + sectionWidth;


            }

            Console.WriteLine("The sequential estimate is {0}", estimate);

        }


        static void PiEstimateP()
        {
            //get the width of each section
            double sectionWidth = 1 / (double)SIZE;

            //the estimat for pi
            double estimate = 0;
            
            //the amount of chunks
            int chunkAmount = 10;

            //the size of each chunk
            int chunkSize = SIZE / chunkAmount;

            //go through each chunk
            Parallel.For(0, chunkAmount, f => 
            {
                //calculate the start of the chunk
                int start = f * chunkSize;

                //calculate the end of the chunk
                int end = start + chunkSize;

                //figure out what x should be
                double x = start * sectionWidth;

                //the toatal for that specific chunk
                double chunkEstimate = 0;

                //the lock  for each chunk
                object objLock = new object();

                //go through the chunnk
                for (int i = start; i < end; i++)
                {
                    //calucate height
                    double height = 4 / (1 + (x * x));

                  //  Console.WriteLine("The height is {0}", height);
                   // Console.WriteLine("The width is {0}", i);

                    //calculate the area
                    double area = height * sectionWidth;

                    // Console.WriteLine("The area is {0}", area);

                    //add to the chunks total
                    chunkEstimate = chunkEstimate + area;
                    // Console.WriteLine("The current estimate is {0}", estimate);

                    //increase x
                    x = x + sectionWidth;

                }

                //lock the add to the overall total to make sure it is added correctly
                lock (objLock)
                {
                    estimate = estimate + chunkEstimate;

                }

               



            });
            

            Console.WriteLine("The parallel estimate is {0}", estimate);
            

        }

        static void Main(string[] args)
        {
            Stopwatch stopwatch1 = new Stopwatch();
            Stopwatch stopwatch2 = new Stopwatch();

            stopwatch1.Start();
            PiEstimateS();
            stopwatch1.Stop();
            Console.WriteLine("Sequential Time {0}", stopwatch1.ElapsedMilliseconds);

            stopwatch2.Start();
            PiEstimateP();
            stopwatch2.Stop();
            Console.WriteLine("Parallel Time {0}", stopwatch2.ElapsedMilliseconds);

            Console.ReadLine();
        }
    }
}
