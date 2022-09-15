#include<stdio.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>

#include "debug.h"
long xtoi(char s[]);
int main()
{
    printf("%ld\n", xtoi("0x12"));
    return 0;
}
long xtoi(char s[])
{
    int len = strlen(s);
    int ans = 0;
    int i = 0;

    if (s[1] == 'x' || s[1] == 'X')
        i = 2;
    for (; i < len; i++)
    {
        char c = s[i];
        if(isdigit(c))
            ans = ans * 16 + c - '0';
        else if (isalpha(c))
            ans = ans * 16 + toupper(c) - 'A' + 10;
    }
    return ans;
}