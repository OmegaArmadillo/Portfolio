#include <iostream>
#include <fstream>
#include <chrono>
#include <unistd.h>

using namespace std;

//how to sort by specific digits
//https://www.geeksforgeeks.org/radix-sort/

//function used to perform a count sort on an array
void countSort(int currentArray[], int arraySize, int currentDigit)
{
    //the array that holds the sorted array
    int* sortedArray = new int[arraySize];

    //the array that keeps track of the values found in the array
    //it is length ten as each space represents 0 - 9 for the possible digit values
    int numberAmount[10] = {0,0,0,0,0,0,0,0,0,0};

    //looks at the digit value of the current spot in the array and adds one to the same location in the counting array
    for (int i = 0; i < arraySize; i++)
    {
        numberAmount[ (currentArray[i]/currentDigit)%10 ] = numberAmount[ (currentArray[i]/currentDigit)%10 ] + 1;
    }

    //adds the value of the current spot in the counting array to value of the next spot in the counting array
    for (int i = 1; i < 10; i++)
    {
         numberAmount[i] = numberAmount[i] + numberAmount[i - 1];
    }


    //adds the value in the current array to the sorted array in the location based off of the counting array
    //then subtracts one from the location in the counting array
    for (int i = arraySize - 1; i >= 0; i--)
    {
        sortedArray[numberAmount[ (currentArray[i]/currentDigit)%10 ] - 1] = currentArray[i];
        numberAmount[ (currentArray[i]/currentDigit)%10 ] = numberAmount[ (currentArray[i]/currentDigit)%10 ] - 1;
    }

    //uses the sorting array to add to rewrite the current array
    for (int i = 0; i < arraySize; i++)
    {
         currentArray[i] = sortedArray[i];
    }

}


//how to sort by specific digits
//https://www.geeksforgeeks.org/radix-sort/

//function that performs a radix sort on an array
void radixSort(int *currentArray, int totalNumbers)
{

    //represents the maximum value in the array to be sorted
    int max = 0;

    //finds the maximum value in the array
    for(int i = 0; i < totalNumbers; i++)
    {

        if( currentArray[i] > max)
        {

            max = currentArray[i];
        }

    }

    //loops a number if times equal the the amount of digits in the max number
    //each run preforms a quick sort on the array but looks at the current digit to tell what digit to look at
    for(int currentDigit = 1; max/currentDigit; currentDigit *= 10)
    {

     /*   printf("original\n");
    for (int i=0; i < totalNumbers; i++)
        printf("%d ", currentArray[i]);
    printf("\n");*/

        countSort(currentArray, totalNumbers, currentDigit);

     /*   printf("after\n");
    for (int i=0; i < totalNumbers; i++)
        printf("%d ", currentArray[i]);
    printf("\n");*/
    }



}




//used in the quick sort algorithm to split the array into two parts of lower and higher values
int splitting(int currentArray[],int startIndex, int endIndex, int pivot)
{

        //Integers to represent the amount of numbers larger and smaller than the pivot
        int smallAmount = 0;
        int largeAmount = 0;


        //The loop that calculates how many numbers are larger and smaller than the pivot
        for (int i = startIndex; i <= endIndex; i++)
        {

            //Makes sure to not check the pivot so it is not counted
            if(i != pivot)
            {
                //The loop that increases the count depending on if the value is
                //higher or lower than the pivot
               if (currentArray[i] < currentArray[pivot])
               {
                   smallAmount++;
               }

               else
               {
                   largeAmount++;
               }
            }

        }


        //Arrays that will hold the numbers that are smaller or larger that the pivot
        int* smaller = new int[smallAmount];
        int* larger = new int[largeAmount];


        //Integers to keep track of the locations in the smaller value
        //and larger value arrays
        int j = 0;
        int k = 0;


        //A similar loop to the last that adds the values to the smaller and larger array
        for (int i = startIndex; i <= endIndex; i++)
        {
            if(i != pivot)
            {
               if (currentArray[i] < currentArray[pivot])
               {
                   smaller[j] = currentArray[i];
                   j++;
               }

               else
               {
                   larger[k] = currentArray[i];
                   k++;
               }
            }



        }

        //Int that keeps track of the value of the pivot so it can be added
        //back later on
        int pivotValue = currentArray[pivot];

        //Int that will be the location of the starting index of the array
        //which is used when adding the numbers back into the array
        int currentLocation = startIndex;


        //The loop that adds all smaller values back into the array.
        for (int i = 0; i < smallAmount; i++)
        {
           currentArray[currentLocation] = smaller[i];
           currentLocation++;


        }


        //Adds the original pivot value back into the array
        currentArray[currentLocation] = pivotValue;

        //Keeps track of where the pivot was placed which will be returned by the function
        //This is so the later function calls will not try to sort this index as it will
        //already be sorted
        int returnPivot = currentLocation;

        //Increasing the index value so the pivot is not replaced
        currentLocation++;

        //Loops that adds the larger values into the array
        for (int i = 0; i < largeAmount; i++)
        {
           currentArray[currentLocation] = larger[i];
           currentLocation++;


        }

    return returnPivot;


}



//function that performs quick sort on an array of values
void auxQuickSort (int currentArray[], int startIndex, int endIndex)
{
   //   printf("call\n");
    //Checks of the start index is not the same as end index because an
    //array of size one is already sorted
    if(startIndex < endIndex)
    {
        //calculates which index will be the pivot for the sort
        int pivot = (endIndex+startIndex) / 2;

        //The end of the first array
        int endIndex1 = pivot - 1;

        //Start of the second array
        int startIndex2 = pivot + 1;

        //printf("\n before: start %d end %d pivot %d start %d end %d \n",startIndex, endIndex1, pivot, startIndex2, endIndex);

        //The unction return the value of the location where the pivot was placed in
        //the array. This is so the sort will not try to sort he value that is already sorted
        pivot = splitting(currentArray, startIndex, endIndex, pivot);

        //These calculate new ends and starts to the sorted value
        //will not be replaced
        endIndex1 = pivot - 1;
        startIndex2 = pivot + 1;

       // printf("\n after: start %d end %d done %d start %d end %d \n",startIndex, endIndex1, pivot, startIndex2, endIndex);

        //Continues sorting the array which will be finished when all functions
        //have the same starting and ending index and thus are sorted
        auxQuickSort(currentArray, startIndex, endIndex1);
        auxQuickSort(currentArray, startIndex2, endIndex);

    }

}






//performs a bucket sort on an array
void bucketSort(int *currentArray, int arraySize)
{

//the bounds for each bucket
//10, 100, 1,000, 10,000, 100,000, 1,000,000 10,000,000 >10,000,000

    //array that holds the size for each bucket
    int bucketSize[8] = {0,0,0,0,0,0,0,0};

    //checks how many numbers fit into the bounds of each bucket
    for(int i = 0; i < arraySize; i++)
    {
            if(currentArray[i] <= 10)
            {
                bucketSize[0]++;
            }
            else if(currentArray[i] <= 100 && currentArray[i] > 10)
            {
                bucketSize[1]++;
            }
            else if(currentArray[i] <= 1000 && currentArray[i] > 100)
            {
                bucketSize[2]++;
            }
            else if(currentArray[i] <= 10000 && currentArray[i] > 1000)
            {
                bucketSize[3]++;
            }
            else if(currentArray[i] <= 100000 && currentArray[i] > 10000)
            {
                bucketSize[4]++;
            }
            else if(currentArray[i] <= 1000000 && currentArray[i] > 100000)
            {
                bucketSize[5]++;
            }
            else if(currentArray[i] <= 10000000 && currentArray[i] > 1000000)
            {
                bucketSize[6]++;
            }
            else
            {
                bucketSize[7]++;
            }

    }



    //creates arrays that represent the buckets based on the calculated size
    int* array0 = new int[bucketSize[0]];
    int* array1 = new int[bucketSize[1]];
    int* array2 = new int[bucketSize[2]];
    int* array3 = new int[bucketSize[3]];
    int* array4 = new int[bucketSize[4]];
    int* array5 = new int[bucketSize[5]];
    int* array6 = new int[bucketSize[6]];
    int* array7 = new int[bucketSize[7]];

    //keep track of the position in each array
    int pos0 = 0;
    int pos1 = 0;
    int pos2 = 0;
    int pos3 = 0;
    int pos4 = 0;
    int pos5 = 0;
    int pos6 = 0;
    int pos7 = 0;


    //adds the values into the buckets based on the buckets bounds
    for(int i = 0; i < arraySize; i++)
    {
            if(currentArray[i] <= 10)
            {
                array0[pos0] = currentArray[i];
                pos0++;
            }
            else if(currentArray[i] <= 100 && currentArray[i] > 10)
            {
                array1[pos1] = currentArray[i];
                pos1++;
            }
            else if(currentArray[i] <= 1000 && currentArray[i] > 100)
            {
                array2[pos2] = currentArray[i];
                pos2++;
            }
            else if(currentArray[i] <= 10000 && currentArray[i] > 1000)
            {
                array3[pos3] = currentArray[i];
                pos3++;
            }
            else if(currentArray[i] <= 100000 && currentArray[i] > 10000)
            {
                array4[pos4] = currentArray[i];
                pos4++;
            }
            else if(currentArray[i] <= 1000000 && currentArray[i] > 100000)
            {
                array5[pos5] = currentArray[i];
                pos5++;
            }
            else if(currentArray[i] <= 10000000 && currentArray[i] > 1000000)
            {
                array6[pos6] = currentArray[i];
                pos6++;
            }
            else
            {
                array7[pos7] = currentArray[i];
                pos7++;
            }

    }



    //quick sort each bucket
    auxQuickSort(array0,0,bucketSize[0]-1);
    auxQuickSort(array1,0,bucketSize[1]-1);
    auxQuickSort(array2,0,bucketSize[2]-1);
    auxQuickSort(array3,0,bucketSize[3]-1);
    auxQuickSort(array4,0,bucketSize[4]-1);
    auxQuickSort(array5,0,bucketSize[5]-1);
    auxQuickSort(array6,0,bucketSize[6]-1);
    auxQuickSort(array7,0,bucketSize[7]-1);



    //keep track of the current position in the array to be sorted
    int currentArrayPos = 0;

    //adds the values of each bucket back into the main array in order
    for(int i = 0; i < bucketSize[0]; i++)
    {
        currentArray[currentArrayPos] = array0[i];
        currentArrayPos++;
    }
    for(int i = 0; i < bucketSize[1]; i++)
    {
        currentArray[currentArrayPos] = array1[i];
        currentArrayPos++;
    }
    for(int i = 0; i < bucketSize[2]; i++)
    {
        currentArray[currentArrayPos] = array2[i];
        currentArrayPos++;
    }
    for(int i = 0; i < bucketSize[3]; i++)
    {
        currentArray[currentArrayPos] = array3[i];
        currentArrayPos++;
    }
    for(int i = 0; i < bucketSize[4]; i++)
    {
        currentArray[currentArrayPos] = array4[i];
        currentArrayPos++;
    }
    for(int i = 0; i < bucketSize[5]; i++)
    {
        currentArray[currentArrayPos] = array5[i];
        currentArrayPos++;
    }
    for(int i = 0; i < bucketSize[6]; i++)
    {
        currentArray[currentArrayPos] = array6[i];
        currentArrayPos++;
    }
    for(int i = 0; i < bucketSize[7]; i++)
    {
        currentArray[currentArrayPos] = array7[i];
        currentArrayPos++;
    }


}








//Checks if an array is sorted
int arrayCheck(int *currentArray, int arraySize)
{

    //represents if the array is sorted
    int isSorted = 1;

    //checks to see if the value ahead of the current position is lower than the current position
    //if it is the isSorted is false and the array is not sorted
    for(int i = 0; i < arraySize - 1; i++)
    {
        if(currentArray[i] > currentArray[i + 1])
        {
            isSorted = 0;
        }
    }

    //tells the user the result of the check
    if(isSorted == 1)
    {
        printf("is sorted\n");
    }
    else
    {
        printf("not sorted\n");
    }
}



//used to help the top ten function
void topTenHelp(int currentArray[], int arraySize, int tenArray[], int currentPlace)
{
    //limits the search to only finding ten values
    if( currentPlace < 10)
    {
        //keeps track of the current max value
        int max = 0;

        //checks every value in the array
        for(int i = 0; i < arraySize; i++)
        {
            //if the current value is the highest number that is not already in the ten largest numbers found
            //that value is made t be the new max
            if( (currentArray[i] > max) && (currentArray[i] < tenArray[currentPlace - 1]) )
            {
                max = currentArray[i];
            }

        }

        //adds that value to the ten largest values
        tenArray[currentPlace] = max;

        //calls the function again to find the other values
        topTenHelp(currentArray, arraySize, tenArray, currentPlace + 1);

    }
}



//finds the ten largest values in an array
void topTen(int currentArray[], int arraySize)
{
    //contains the largest values in the array
    int maxTen[10];

    //keeps track of the max value found in the current check
    int max = 0;


    //finds the largest value in the array
    for(int i = 0; i < arraySize; i++)
    {

        if( currentArray[i] > max)
        {

            max = currentArray[i];
        }

    }

    //sets the first value to be the largest number found
    maxTen[0] = max;

    //calls a function to find the other largest numbers
    topTenHelp(currentArray, arraySize, maxTen, 1);

   printf("top ten\n");
    for (int i=0; i < 10; i++)
        printf("%d ", maxTen[i]);
    printf("\n");
}









//How to do file input and output
//http://www.cplusplus.com/forum/beginner/78150/

//How to make an array of such a large size
//https://stackoverflow.com/questions/22578879/is-it-possible-to-store-10-million-numbers-in-array

//How to do the nanosecond timing
//https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/
void integerRead()
{

    //the amount of values to be read
    int amount = 1000;

    //Creates a file and opens the data file
	ifstream numberFile;
	numberFile.open ("lab3_data.txt");

    //The array that will hold the values read from the file
    int* numberList = new int[amount];

    //Reads the file into the array
    for(int i = 0; i < amount; i++)
    {
       numberFile >> numberList[i];
    }

    //Closes the file pointer
    numberFile.close();



	printf("\n 0. %d",*(numberList));
	printf("\n 1. %d",*(numberList + 1));
	printf("\n 2. %d",*(numberList + 2));
	printf("\n 3. %d",*(numberList + 3));
	printf("\n 4. %d",*(numberList + 4));
	printf("\n 5. %d",*(numberList + 5));
	printf("\n 5. %d",*(numberList + 6));



    //Create and int to test if all numbers where read into the array
	long long int sum = 0;

	//Adds all of the array numbers together and prints the total
    for(int i = 0; i < amount; i++)
    {

     sum = sum + *(numberList + i);

    }
    printf("\n Total: %llu \n",sum);


   radixSort(numberList, amount);


    //starts the timer
    auto startTime = chrono::steady_clock::now();


   // auxQuickSort(numberList, 0, amount - 1);
 //bucketSort(numberList, amount);



      topTen(numberList, amount);


    //stops the timer
   auto endTime = chrono::steady_clock::now();


  //calculates the total time and prints it
    cout << "Time in Milliseconds: " << chrono::duration_cast<chrono::milliseconds>(endTime-startTime).count()
    << endl;
/*
   printf("array after\n");
    for (int i=(amount - 51); i < amount; i++)
        printf("%d ", numberList[i]);
    printf("\n");
*/





//arrayCheck(numberList, amount);

}










int main()
{


  // int arrayTest[] = {561,68,9,123,347,25,87,4};

   int arrayTest[] = {678,196,182,177,169,158,146,131,120,110,100,900,800,700};
   // int arrayTest[] = {1,2,3,4,5,6,7,8};
/*printf("original\n");
    for (int i=0; i < 14; i++)
        printf("%d ", arrayTest[i]);
    printf("\n");*/

    	integerRead();



  //bucketSort(arrayTest,14);

    //radixSort(arrayTest, 14);

   // topTen(arrayTest, 14);

	//insertionSort(arrayTest, 8);

	//auxQuickSort(arrayTest, 0, 13);



//arrayCheck(arrayTest, 14);

    //flgIsSorted(arrayTest);
  /*printf("array after\n");
    for (int i=0; i < 14; i++)
        printf("%d ", arrayTest[i]);
    printf("\n");*/

	return 0;
}
