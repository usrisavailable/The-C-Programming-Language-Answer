#include<stdio.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>

#include "debug.h"

int nbits(int x);
int rightrot(unsigned int x, unsigned int n);
int main(int argc, char *argv[])
{
    unsigned int x = rightrot(123u, 3u);
    printf("%x\n", 123);
    printf("%x\n", x);

    return 0;
}

int nbits(unsigned int x)
{
    int len = 0;
    while (x)
    {
        len++;
        x = x >> 1;
    }
    return len;
}
int rightrot(unsigned int x, unsigned int n)
{
    int lenx = nbits(x);
    if (n > lenx)
        printf("%s\n", "bad argument");
    
    unsigned int tail = x & ~(~0 << (n));
    x = x >> n;
    tail = tail << (32 - n);
    x = x | tail;
    return x;
}
