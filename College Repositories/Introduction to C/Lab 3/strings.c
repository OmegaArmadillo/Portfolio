#include <stdio.h>

int main()
{
	char inputString[20];
	int currentSpace;
	int inputStringLength;
	int i;


    /*Allows for input of a string and gets the length of the string*/	
	printf("Please input a string. ");
	fgets(inputString, 20 , stdin);
	inputStringLength = strlen(inputString);
	
    /*Prints the characters of the string one letter at a time*/	 
	printf("Your string forwards is. " );
    for(currentSpace = 0; inputString[currentSpace] !='\0'; currentSpace++)
	{
        printf("%c",inputString[currentSpace]);
	}

    /*Prints the characters of the string one letter at a time in reverse order*/	
	printf("Your string backwards is. ");	
    for(i = inputStringLength; i >= 0 ; i--)
	{
        printf("%c",inputString[i]);
	}

}