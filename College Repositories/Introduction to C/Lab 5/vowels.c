#include <stdio.h>

int main()
{

char userInput[50];
char *charPointer;
char *initialCharPointer;
charPointer = userInput;
initialCharPointer = userInput;
int inputStringLength;

printf("Please input a sentence. ");
fgets(userInput, 50, stdin);
inputStringLength = strlen(userInput);

void vowelChecker(char *startPointer, int stringLength);
void consonantChecker(char *startPointer, int stringLength);


vowelChecker(charPointer, inputStringLength);
consonantChecker(charPointer, inputStringLength);



    return 0;
}







void vowelChecker(char *startPointer, int stringLength)
{



printf("Vowels in the sentence. ");
for(int i = 0; i < stringLength - 1; i ++)
{

if( *startPointer =='a' ||  *startPointer =='e' || *startPointer =='i' || *startPointer =='o'  || *startPointer =='u')
{
printf("%c", *startPointer);    
    
}

startPointer = startPointer + 1;
    
}

}


void consonantChecker(char *startPointer, int stringLength)
{


printf("\nEveryother letter in the sentence. ");
for(int i = 0; i < stringLength - 1; i ++)
{

if( *startPointer !='a' &&  *startPointer !='e' && *startPointer !='i' && *startPointer !='o'  && *startPointer !='u' && *startPointer !=' ')
{
printf("%c", *startPointer);    
    
}

startPointer = startPointer + 1;
    
}


}
