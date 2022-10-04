#include<stdio.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>

#include "debug.h"

int nbits(int x);
int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y);
int main(int argc, char *argv[])
{
    unsigned int x = setbits(123, 3, 3, 11);
    printf("%x\n", 123);
    printf("%x\n", 11);
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
int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y)
{
    int lenx = nbits(x);
    int leny = nbits(y);
    if (n > leny || p + n > lenx)
        debug("%s", "bad agguments");

    unsigned int temp = ~(~0 << n); //构造n位全1
    y = y & temp; //获取y的后n位
    unsigned int afterx = ~(~0 << (lenx - p - n));
    //这里是可以用’|‘的，会保留想要的
    x = x >> (lenx - p);
    x = x << n;
    x = x | y;
    x = x << (lenx - p - n);
    x = x | afterx;
    return x;
}
