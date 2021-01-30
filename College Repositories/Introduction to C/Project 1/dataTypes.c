#include <stdio.h>

int main()
{
	
	// Assigning value to the variables
    char charExample = 'c';
    unsigned char unCharExample= 'c';
    short shortExample = 32767;
    unsigned short unShortExample = 65535;
    int intExample = 2147438647;
    unsigned int unIntExample = 4294967295;
    long longExample = 2147438647;
    unsigned long unLongExample = 4294967295;
    long long longLongExample = 9223372036854775807;
    unsigned long long unlongLongExample = 18446744073709551615;
    float floatExample = 3.14159;
    double doubleExample = 3.14159265359;
    long double longDoubleExample = 3.14159265359358979323;
    
 
	// Printing the variables 
    printf("Examples of the data types are.\n");
    printf("\n");
    printf("char %c\n", charExample);
    printf("unsigned char %d\n", unCharExample);    
    printf("short %d\n", shortExample);
    printf("unsigned short %d\n", unShortExample);
    printf("int %d\n", intExample);
    printf("unsigned int %d\n", unIntExample);
    printf("long %ld\n", longExample);
    printf("unsigned long %ld\n", unLongExample);
    printf("long long %ld\n", longLongExample);
    printf("unsigned long long %ld\n", unlongLongExample);
    printf("float %f\n", floatExample);
    printf("double %lf\n", doubleExample);
    printf("long double %Lf\n", longDoubleExample);    
    
	return 0;