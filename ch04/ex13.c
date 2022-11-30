#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

void itoa(int n, char s[]);
void reverse(char s[], int left, int right);

int main(int argc, char **argv)
{
    char s[MAX_LINE];
    itoa(-65535, s);
    debug("%s", s);
    return 0;
}

void itoa(int n, char s[])
{
    unsigned num;//double is better ,but % is not supprot
    static int i = 0;
    static int sign = 0;
    if (n < 0)
    {
        num = -n;
        sign = 1;
    }
    else
        num = n;

    s[i++] = num % 10 + '0';
    num = num / 10;
    if (num)
        itoa(num, s);
    if (sign)
    {
        s[i++] = '-';
        sign = 0;
    } 
    s[i] = '\0';
    if (s[i] == '\0')
        reverse(s, 0, i - 1);
    return;
}

void reverse(char s[], int left, int right)
{
    if (left >= right)
        return;
        
    int temp;
    temp = s[left];
    s[left] = s[right];
    s[right] = temp;

    reverse(s, ++left, --right);
    
    return;
}
