#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//function for guessing the int value
void guessInt(int number)
{
   for(int i = 0; i < 4; i++)
   {
      int guess;
      
       printf("\nGuess a number between and inluding 1 and 10\n");
	   scanf("%d", &guess);
	   
	   if(guess > number)
	   {
       printf("Your guess is too high\n");
       printf("You have this many guesses left: %d\n",(3-i));
	   }
	   
	   if(guess < number)
	   {
       printf("Your guess is too low\n");
       printf("You have this many guesses left: %d\n",(3-i));	       
	   }
	   
	   if(guess == number)
	   {
       printf("You have guessed correctly\n");
	   i=3;
	   }
       
   }
       printf("The value was %d ", number);    
}




//function for guessing the float value
void guessFloat(float number)
{
    number = number * 10000;
    int changeFloat = number;
    printf("\n%d\n",changeFloat);
    number = (float)changeFloat/10000;

    
   for(int i = 0; i < 4; i++)
   {
      float guess;
      
       printf("\nGuess a number between 0 and 1\n");
	   scanf("%f", &guess);
	   
	   if(guess > number)
	   {
       printf("Your guess is too high\n");
       printf("You have this many guesses left: %d\n",(3-i));
	   }
	   
	   if(guess < number)
	   {
       printf("Your guess is too low\n");
       printf("You have this many guesses left: %d\n",(3-i));	       
	   }
	   
	   if(guess == number)
	   {
       printf("You have guessed correctly\n");
	   i=3;
	   }
       
   }
       printf("The value was %f ", number);    
}


//function for guessing the long value
void guessLong(long number, long number2)
{
    
    float floatNumber2 = number2 / 100000;
    float floatTotal = number + number2;
    number = floatTotal * 100000;

    
    if(number < 0)
    {
    number = number * -1;    
        
    }
    
   for(int i = 0; i < 4; i++)
   {
      long guess;
      
       printf("\nGuess a number between 1 and 10\n");
	   scanf("%ld", &guess);
	   
	   if(guess > number)
	   {
       printf("Your guess is too high\n");
       printf("You have this many guesses left: %d\n",(3-i));
	   }
	   
	   if(guess < number)
	   {
       printf("Your guess is too low\n");
       printf("You have this many guesses left: %d\n",(3-i));	       
	   }
	   
	   if(guess == number)
	   {
       printf("You have guessed correctly\n");
	   i=3;
	   }
       
   }
       printf("The value was %ld ", number);    
}









int main()
{
	//variables used for selection and randomization
    int choice;
    int randomInt;
    float randomFloat;
    long randomLong1;
    long randomLong2;
 
	//asking the user for a selection 
	printf("What data type do you want to guess?\n");
	printf("1. Int\n");
	printf("2. Float\n");
	printf("3. Long\n");
	printf("To select a data type enter the number next to your choice.\n");
	scanf("%d", &choice);  
	
	
	//used to seed the rand function
	srand(time(NULL));
		
  
	//switch statement used to determine what data type will be randomized and guessed
    switch(choice)
    {
        case 1:
	    printf("You selected an int\n");
	    randomInt = 1 + rand()%10;
	    guessInt(randomInt);
        break;
        
        case 2:
	    printf("You selected a float\n");
	    randomFloat =(float)rand()/(float)(RAND_MAX)  ;
	    guessFloat(randomFloat);	    
        break;
	    
        case 3:
	    printf("You selected a long\n");
	    randomLong1 = rand()%20000;
	    randomLong2 = rand()%20000;	   
	    guessLong(randomLong1,randomLong2);
	    break;
	    
	    default:
	    printf("You have entered an incorrect value");	    
    }
    


    return 0;
}
