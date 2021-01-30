#include <stdio.h>


int main()
{

    float height;
    float weight;
    int age;
    int i;

    /*The loop that allows the program to be repeatable*/	
for(i = 1; i > 0; i++)
{
	/*Input the values and store them for later use*/
	printf("Please input your height in inches. ");
	scanf("%f", &height);

	printf("Please input your weight in pounds. ");
	scanf("%f", &weight);	
	 
	printf("Please input your age in years. ");
	scanf("%d", &age);

    /*Calling the functions calculate the values needed*/	
    float calculateHatSize(float weightI,float heightI);
    float calculateJacketSize(float heightI,float weightI,int ageI);
    float calculateWaistSize(float weightI,int ageI);
    
	/*Printing the values for the user*/	
    printf("Your hat size in inches is. ");
    printf("%f",calculateHatSize(weight,height));
    printf("\n");

    printf("Your jacket size in inches is. ");
    printf("%f",calculateJacketSize(height,weight,age));
    printf("\n");

    printf("Your waist size in inches is. ");    
    printf("%f",calculateWaistSize(weight,age));
    printf("\n");
}
    
    return 0;
}

    /*Function to calculate hat size*/
float calculateHatSize(float weightI,float heightI)
{
   float hatSize;
   hatSize = (weightI/heightI)*2.9;
   
   return hatSize;
}

    /*Function to calculate jacket size*/
float calculateJacketSize(float heightI,float weightI,int ageI)
{
    float jacketSize;
    int remain;
    remain = (ageI-30)/10;
    jacketSize = (heightI * weightI)/288 + .125 * remain; 
    
    return jacketSize;
}

    /*Function to calculate waist size*/
float calculateWaistSize(float weightI, int ageI)
{
    float waistSize;
    int remain;
    remain = (ageI-28)/2;
    waistSize = weightI/5.7 +  .1*remain;
    
    return waistSize;
}