#include <stdio.h>
#include <stdlib.h>


int main ()
{


  //Pointers for reading and writing 
  FILE *filePointer;
  FILE *filePointerNP;
  FILE *filePointerE;

// array to store information
  char currentLine[50];

//one more than the amount of lines that will be read
  int lines = 36;

//variable to store information
  int ID;
  char type;
  float HRate;
  float hours;
  float BRate;
  float YComp;
  float Bonus;
  float TComp;
  float EBonus;

//setting the pointers
  filePointer = fopen ("test.txt", "r");
  filePointerNP = fopen ("writeNP.txt", "w");
  filePointerE = fopen ("writeE.txt", "w");

//if statements to see id the files opened correctly
  if (filePointer == NULL)
    {
      fprintf (stderr, "Can't open file %s!\n", "test.txt");

    }

  if (filePointerNP == NULL)
    {
      fprintf (stderr, "Can't open file %s!\n", "writeNP.txt");

    }

  if (filePointerE == NULL)
    {
      fprintf (stderr, "Can't open file %s!\n", "writeE.txt");

    }

//loop used to get and set information
  for (int i = 1; i < lines; i++)
    {
      fscanf (filePointer, "%d", &ID);

	//used to make sure the filepointer will read the char
      fseek (filePointer, 1, SEEK_CUR);
      fscanf (filePointer, "%c", &type);


      fscanf (filePointer, "%f", &HRate);


      fscanf (filePointer, "%f", &hours);


      fscanf (filePointer, "%f", &BRate);


//calculations using the gotten information
      YComp = hours * HRate;
      Bonus = YComp * BRate;
      EBonus = YComp * .1;
      TComp = YComp + Bonus + EBonus;


      printf ("YComp: %f", YComp);
      printf ("Bonus: %f", Bonus);
      printf ("EBonus: %f", EBonus);
      printf ("TComp: %f", TComp);

//if statements used to figure out where the data should be written to
if(type == 'E')
{
  fprintf(filePointerE,"%d",ID);   
  fprintf(filePointerE,"%c    ",type);
  fprintf(filePointerE,"%f ",YComp);
  fprintf(filePointerE,"%f ",Bonus);
  fprintf(filePointerE,"%f ",EBonus);
  fprintf(filePointerE,"%f\n",TComp);   
}

else
{
  fprintf(filePointerNP,"%d",ID);   
  fprintf(filePointerNP,"%c    ",type);
  fprintf(filePointerNP,"%f ",YComp);
  fprintf(filePointerNP,"%f ",Bonus);
  fprintf(filePointerNP,"%f\n",TComp);   
}





    }  


//closing the pointers 
      fclose (filePointer);
      fclose (filePointerNP);
      fclose (filePointerE);

      return 0;
    }
