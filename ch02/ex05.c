#include<stdio.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>

#include "debug.h"
int any(char [], char []);
int main(int argc, char *argv[])
{
    debug("%s %s", argv[1], argv[2]);
    int pos = any(argv[1], argv[2]);
    if (pos != -1)
        printf("%d\n", pos + 1);
    else
        printf("%d\n", pos);

    return 0;
}
int In(char s[], char c)
{
    int i = 0;
    while(s[i])
    {
        if (c == s[i++])
            return 1;
    }
    return 0;
}
int any(char s1[], char s2[])
{
    int i = 0;
    while(s1[i])
    {
        if (In(s2, s1[i]))
            {
                return i;
            }
        else
            i++;
    }
    return -1;
}