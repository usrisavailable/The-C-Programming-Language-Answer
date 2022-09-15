#include<stdio.h>
#include<limits.h>

#include "debug.h"

int main()
{
    //signed char
    printf("the minimum signed char %d", SCHAR_MIN);
    printf("the maximum signed char %d", SCHAR_MAX);

    //unsigned char
    printf("the minimum unsigned char %d", 0);
    printf("the maximum unsigned char %d", UCHAR_MAX);

    //signed short int
    printf("the minimum signed short int %d", SHRT_MIN);
    printf("the maximum signed short int %d", SHRT_MAX);

    //unsigned short int
    printf("the minimum unsigned short int %d\n", 0);
    printf("the maximum unsigned short int %d\n", USHRT_MAX);

    //signed int
    printf("the minimum signed int %d\n", INT_MIN);
    printf("the maximum signed int %d\n", INT_MAX);

    //unsigned int
    printf("the minimum unsigned int %d\n", 0);
    printf("the maximum unsigned int %u\n", UINT_MAX);
    return 0;
}