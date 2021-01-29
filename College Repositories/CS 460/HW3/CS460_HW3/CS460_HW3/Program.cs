using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace CS460_HW3
{
    class Program
    {
        /** Print the command line usage for this program */
        private static void printUsage()
        {
            Console.WriteLine("Usage is:\n" +
        "\tCS460_HW3 C inputfile outputfile\n\n" +
        "Where:" +
        "  C is the column number to fit to\n" +
        "  inputfile is the input text file \n" +
        "  outputfile is the new output file base name containing the wrapped text.\n" +
        "e.g. CS460_HW3 72 myfile.txt myfile_wrapped.txt");
        }

        public static void Main(string[] args)
        {
            // Column length to wrap to
            int C = 72;
            string inputFileName;
            string outputFilename = "output.txt";
            StreamReader scanner = null;

            // Read the command line arguments ...
            if (args.Length !=3)
            {
                printUsage();
                Environment.Exit(1);
            }
            try
            {
                C = Int32.Parse(args[0]);
                inputFileName = args[1];
                outputFilename = args[2];
                scanner = new StreamReader(inputFileName);
            }
            catch(FileNotFoundException e)
            {
                Console.WriteLine("Could not find the input file.");
                Environment.Exit(1);
            }
            catch(Exception e)
            {
                Console.WriteLine("Something is wrong with the input.");
                printUsage();
                Environment.Exit(1);
            }

            // Read words and their lengths into these vectors
            IQueueInterface<String> words = new LinkedQueue<String>();

            // Read input file into an array and seperates by spaces
            //source
            // https://stackoverflow.com/questions/9740557/reading-a-text-file-word-by-word
            string[] text = scanner.ReadToEnd().Split(' ');

            //puts the array into the queue 
            for(int i = 0; i < text.Length; i++ )
            {
                words.Push(text[i]);
            }

            scanner.Close();

            //start reading
            int spacesRemaining = wrapSimply(words, C, outputFilename);
            Console.WriteLine("Total spaces remaining (Greedy): " + spacesRemaining);
        }

        private static int wrapSimply( IQueueInterface<String> words, int columnLength, String outputFilename)
        {
            StreamWriter writer;

            try
            {
                writer = new StreamWriter(outputFilename);
            }
            catch(FileNotFoundException e)
            {
                Console.WriteLine("Cannot create or open " + outputFilename +
                                  " for writing. Using standard output instead.");
                writer = new StreamWriter("output.txt");
            }

            int col = 1;
            // Running count of spaces left at the end of lines
            int spacesRemiaining = 0;

            while(!words.IsEmpty())
            {
                String str = words.Peek();
                int len = str.Length;

                // See if we need to wrap to the next line
                if (col == 1)
                {
                    writer.Write(str);
                    col += len;
                    words.Pop();
                }
                else if ( (col + len) >= columnLength )
                {
                    // go to the next line
                    writer.Write(Environment.NewLine);
                    spacesRemiaining += (columnLength - col) + 1;
                    col = 1;
                }
                else
                {
                    // Typical case of printing the next word on the same line
                    writer.Write(" ");
                    writer.Write(str);
                    col += (len + 1);
                    words.Pop();
                }
            }

            writer.Write(Environment.NewLine);
            writer.Flush();
            writer.Close();
            return spacesRemiaining;
        } // end wrapSimply
    } // End class Main
}
