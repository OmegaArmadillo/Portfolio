#include <stdio.h>

int main()
{
	int amountOfPeople;
	int maximumCapacity;
	int amountUntilMaximum;
	
	printf("How many people will be attending this meeting? ");
	scanf("%d", &amountOfPeople);

	printf("What is the maximum capacity of the room you will be meeting in? ");
	scanf("%d", &maximumCapacity);

    if(amountOfPeople <= maximumCapacity)
    {
	    amountUntilMaximum = maximumCapacity - amountOfPeople;
	    printf("You meet the fire regulation and can hold the meeting.\n");
    	printf("You can invite this many more people before you reach the maximum capacity. %d", amountUntilMaximum) ;
    }	

    if(amountOfPeople > maximumCapacity)
    {
	    amountUntilMaximum = amountOfPeople - maximumCapacity;
	    printf("You do not meet the fire regulation and cannot hold the meeting.\n");
	    printf("You must uninvite this many people before you meet the fire regulations. %d", amountUntilMaximum);
    }


}