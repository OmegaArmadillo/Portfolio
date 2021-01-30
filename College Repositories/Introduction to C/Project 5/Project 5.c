
#include <stdio.h>
#include <stdlib.h>



void readArray(int amount, FILE *file, int (*pointer)[amount])
{
    
   for(int i = 0; i < amount; i++)
    {
	
	    for(int j = 0; j < amount; j++)
	    {
		
		    fscanf (file, "%d", (*(pointer + i) + j)   );
		
	    }
	
	
    }
 
    
}




void printArray(int amount, int (*pointer)[amount])
{



    for(int i = 0; i < amount; i++)
    {

	    for(int j = 0; j < amount; j++)
	    {
		
		printf ("%d ", *(*(pointer + i) + j) );
		
	    }


	    printf ("\n");

    }
    

		printf ("\n");
    
}




void addArray(int amount, int (*pointerA)[amount], int (*pointerB)[amount])
{


    for(int i = 0; i < amount; i++)
    {

	    for(int j = 0; j < amount; j++)
	    {
		
		    *(*(pointerB + i) + j) =  *(*(pointerA + i) + j) + *(*(pointerA + i) + j); 
	
	    }
	
    }
    
    
}




void divideArray(int amount, int (*pointerA)[amount], int (*pointerB)[amount])
{


    for(int i = 0; i < amount; i++)
    {

	    for(int j = 0; j < amount; j++)
	    {
		
		    *(*(pointerB + i) + j) =  *(*(pointerB + i) + j)  /  *(*(pointerA + i) + j); 
		
	    }
	
    }
    
    
}




void multiplyArray(int amount, int (*pointerB)[amount])
{


    for(int i = 0; i < amount; i++)
    {

    	for(int j = 0; j < amount; j++)
	    {
		
		    *(*(pointerB + i) + j) =  *(*(pointerB + i) + j)  *  *(*(pointerB + i) + j); 
		
		
	    }
	
    }
    
}




void makeSpace()
{
    
   		printf ("\n"); 
}




int main ()
{

//arrays used
int firstArrayA[3][3];
int firstArrayB[3][3];

int secondArrayA[4][4];
int secondArrayB[4][4];

int thirdArrayA[5][5];
int thirdArrayB[5][5];


//pointers for the different arrays
int *firstArrayAPointer;
int *secondArrayAPointer;
int *thirdArrayAPointer;

int *firstArrayBPointer;
int *secondArrayBPointer;
int *thirdArrayBPointer;

//setting the array pointers
firstArrayAPointer = firstArrayA;
secondArrayAPointer = secondArrayA;
thirdArrayAPointer = thirdArrayA;

firstArrayBPointer = firstArrayB;
secondArrayBPointer = secondArrayB;
thirdArrayBPointer = thirdArrayB;


//setting file pointers
FILE *firstArrayReader;
FILE *secondArrayReader;
FILE *thirdArrayReader;

//setting the file pointers
firstArrayReader = fopen ("arrayOne.txt", "r");
secondArrayReader = fopen ("arrayTwo.txt", "r");
thirdArrayReader = fopen ("arrayThree.txt", "r");




 //if statements to see id the files opened correctly
  if (firstArrayReader == NULL)
    {
      fprintf (stderr, "Can't find the file %s.\n", "arrayOne.txt");

    }

  if (secondArrayReader == NULL)
    {
      fprintf (stderr, "Can't find the file %s.\n", "arrayTwo.txt");

    }

  if (thirdArrayReader == NULL)
    {
      fprintf (stderr, "Can't find the file %s.\n", "arrayThree.txt");

    }



//repeating functions to read, calculate and print the arrays

readArray(3, firstArrayReader, firstArrayAPointer);


printArray(3,firstArrayAPointer);


addArray(3, firstArrayAPointer, firstArrayBPointer);
printArray(3,firstArrayBPointer);


multiplyArray(3,firstArrayBPointer);
printArray(3,firstArrayBPointer);


divideArray(3, firstArrayAPointer, firstArrayBPointer);
printArray(3,firstArrayBPointer);


makeSpace();



readArray(4, secondArrayReader, secondArrayAPointer);

printArray(4,secondArrayAPointer);


addArray(4, secondArrayAPointer, secondArrayBPointer);
printArray(4, secondArrayBPointer);


multiplyArray(4,secondArrayBPointer);
printArray(4, secondArrayBPointer);


divideArray(4, secondArrayAPointer, secondArrayBPointer);
printArray(4, secondArrayBPointer);

makeSpace();



readArray(5, thirdArrayReader, thirdArrayAPointer);


printArray(5,thirdArrayAPointer);


addArray(5, thirdArrayAPointer, thirdArrayBPointer);
printArray(5, thirdArrayBPointer);


multiplyArray(5,thirdArrayBPointer);
printArray(5, thirdArrayBPointer);


divideArray(5, thirdArrayAPointer, thirdArrayBPointer);
printArray(5, thirdArrayBPointer);

makeSpace();
}