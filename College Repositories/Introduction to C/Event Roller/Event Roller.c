#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    
srand(time(NULL));

int amountOfDice;
int diceType;
int rollTotal;

int randomRoll;

int eventSelect;

printf("How many dice are you rolling\n");
scanf("%d", &amountOfDice);
	   
printf("\nWhat type of dice are you rolling\n");
scanf("%d", &diceType);

printf("\nWhat event are you rolling for\n");
printf("1. Event 1\n");
printf("2. Event 2\n");
printf("3. Event 3\n");
scanf("%d", &eventSelect);




for(int i = 0; i < amountOfDice; i++)
{

    randomRoll = (rand() % diceType) + 1;

    rollTotal = rollTotal + randomRoll;

    printf("d%d number %d rolled a %d\n", diceType,(i + 1), randomRoll);

}

    printf("Your roll total is %d", rollTotal);
    printf("\n");



switch(eventSelect)
{
    case 1:
    printf("\nEvent 1\n"); 
    break;
 
    case 2:
    printf("\nEvent 2\n");  
    break;
 
    case 3:
    printf("\nEvent 3\n"); 
    break;
 
    default:
    printf("\nNot a valid event\n");
    break;

 }
 
 
 
     return 0;
    


}