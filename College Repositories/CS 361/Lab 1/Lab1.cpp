#include <iostream>
#include <fstream>
#include <chrono>
//#include <unistd.h>
using namespace std;









//Used in the merge sort function to merge the smaller arrays together
void merging(int *currentArray, int start, int end1, int start2, int end2)
{


    //Calculates the size the two current sections of the array
    int firstSize = end1 - start + 1;
    int secondSize =  end2 - start2 + 1;



    //Creating arrays based of off the calculated size
    //int firstHalf[firstSize];
    //int secondHalf[secondSize];
    int* firstHalf = new int[firstSize];
    int* secondHalf = new int[secondSize];



    //Adding the first section of values into the array
    for (int i = 0; i < firstSize; i++)
    {
        firstHalf[i] = currentArray[start + i];
    }



    //Adding the section section of values into the array
    for (int j = 0; j < secondSize; j++)
    {
         secondHalf[j] = currentArray[start2 + j];
    }



    //Used to keep track of the current location in the first half array
    int j = 0;

    //Used to keep track of the current location in the second half array
    int k = 0;


    //Goes through both arrays to add the values back into the current array
    //With lower values going into the array first
    for(int i = start; i < (end2+1); i++)
    {
        //Checks if the current value of the first half is smaller than the second half
        //If it is the value in first half is added otherwise the value in second half is added

        //Code was changed to j-1 and k-1 to be able to get the data for merge 1,000,000 and 10,000,000
        if (firstHalf[j] < secondHalf[k])
        {
            //The loop that checks if j is at the end of the first half
            //if it is not then the value at j is added
            //otherwise it adds the value at k in the second half
            //This makes sure every value is added to the current array and that there are no repeated numbers
            if( j < firstSize)
            {
                currentArray[i] = firstHalf[j];
                j++;
            }
            else
            {
                currentArray[i] = secondHalf[k];
                 k++;
            }

        }
        else
        {
            //The loop that checks if k is at the end of the second half
            //if it is not then the value at k is added
            //otherwise it adds the value at j in the first half
            //This makes sure every value is added to the current array and that there are no repeated numbers
            if(k < secondSize)
            {
                currentArray[i] = secondHalf[k];
                k++;
            }
            else
            {
                currentArray[i] = firstHalf[j];
                j++;
            }


        }


    }


}





//function to merge sort and array
void auxMergeSort(int *currentArray, int start, int end)
{
    // printf("call 1\n");
    //checks if the starting and ending index of the array is the same
    //if it is the array is not sorted because it already is
    //otherwise continue with the sort


    if (start < end)
    {
        //the location of the end of the first half of the array
        int end1 = (end + start)/2;

        //the locations of the start and end of the second half of the array
        int start2 = end1 + 1;
        int end2 = end;

        //repeats the merge sort until the arrays are of size one
        auxMergeSort(currentArray, start, end1);
        auxMergeSort(currentArray, start2, end2);

        //merges the two arrays into one that is ordered
        merging(currentArray, start, end1, start2, end2);
    }
}




//used in the quick sort algorithm to split the array into two parts of lower and higher values
int splitting(int currentArray[],int startIndex, int endIndex, int pivot)
{
  //printf("split 1\n");
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



//Checks if an array is sorted
int arrayCheck(int currentArray[], int currentIndex)
{

    //Checks if the array is of size one because an array of size one is
    //already sorted
    if(currentIndex != (sizeof(currentArray) - 1) )
    {
        //Checks if the next value array is larger than the current value which
        //means the array is not sorted. If that is not the case then it will
        //call the function again and check the next position in the array
        if(currentArray[currentIndex] > currentArray[currentIndex + 1])
        {
            return 0;
        }

        else
        {
            return arrayCheck(currentArray, currentIndex + 1);
        }
    }

    else
    {
        return 1;
    }

}



//Function to check if an array is sorted
void flgIsSorted(int currentArray[])
{

    //Calls a function to check the array which will return a value
    int check = arrayCheck(currentArray, 0);

    //Will tell the user what the result is. if the function returned a 1 it is sorted
    //else the array is not sorted
    if(check == 0)
    {
        printf("not sorted\n");
    }
    else
    {
        printf("is sorted\n");
    }



}






//How to do file input and output
//http://www.cplusplus.com/forum/beginner/78150/

//How to make an array of such a large size
//https://stackoverflow.com/questions/22578879/is-it-possible-to-store-10-million-numbers-in-array

//How to do the nanosecond timing
//https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/
void integerRead()
{

    auto startTime = chrono::steady_clock::now();

    int amount = 1000;

    //Creates a file and opens the data file
	ifstream numberFile;
	numberFile.open ("lab1_data.txt");

    //The array that will hold the values read from the file
    int* numberList = new int[amount];

    //Reads the file into the array
    for(int i = 0; i < amount; i++)
    {
       numberFile >> *(numberList + i);
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

	auxMergeSort(numberList, 0, amount-1);
//    auxQuickSort(numberList, 0, amount - 1);

   printf("array after\n");
    for (int i=(amount - 51); i < amount; i++)
        printf("%d ", numberList[i]);
    printf("\n");




	flgIsSorted(numberList);



    auto endTime = chrono::steady_clock::now();

    long long int totalTime = chrono::duration_cast<chrono::nanoseconds>(endTime-startTime).count();

    printf("Time in Nanoseconds: %llu\n", totalTime);



}










int main()
{


 //   int arrayTest[] = {5,6,9,1,3,2,8,4};
    //int arrayTest[] = {1,2,3,4,5,6,7,8};
/*printf("original\n");
    for (int i=0; i < 8; i++)
        printf("%d ", arrayTest[i]);
    printf("\n");*/

    	integerRead();

	//auxMergeSort(arrayTest, 0, 7);

	//auxQuickSort(arrayTest, 0, 7);

    //printArray(arrayTest, 8);


    //flgIsSorted(arrayTest);
  /*  printf("array after\n");
    for (int i=0; i < 8; i++)
        printf("%d ", arrayTest[i]);
    printf("\n");*/

	return 0;
}
