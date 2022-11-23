#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

void itoa(int n, char s[], int d);
void reverse(char s[], int len);

int main(int argc, char **argv)
{
    char s[MAX_LINE];
    itoa(-65535, s, 5);
    debug("%s", s);
    return 0;
}

void itoa(int n, char s[], int d)
{
    unsigned num;//double is better ,but % is not supprot
    int sign = 1;
    int i = 0;
    if (n < 0)
    {
        num = -n;
        sign = -1;
    }
    else
        num = n;

    do{
        s[i++] = num % 10 + '0';
        num = num / 10;
    }while(num);

    if (sign == -1)
    {
        s[i++] = '-';
    }
    if (i >= d)
        s[i] = '\0';
    else{
        while(d - i)
        {
            s[i++] = ' ';
        }
        s[i] = '\0';
    }
    reverse(s, i);
    return;
}

void reverse(char s[], int len)
{
    int i = 0;
    for (i; i < len / 2; i++)
    {
        int temp;
        temp = s[i];
        s[i] = s[len - i -1];
        s[len - i -1] = temp;
    }
    
    return;
}
