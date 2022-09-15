#include<stdio.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>

#include "debug.h"
void squeeze(char [], char []);
int main(int argc, char *argv[])
{
    debug("%s %s", argv[1], argv[2]);
    squeeze(argv[1], argv[2]);
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
void squeeze(char s1[], char s2[])
{
    int i = 0;
    int j = 0;
    while(s1[i])
    {
        if (!In(s2, s1[i]))
            {
                debug("%d", s1[i]);
                s1[j++] = s1[i++];
            }
        else
            i++;
    }
    s1[j] = '\0';
    printf("%s\n", s1);
}