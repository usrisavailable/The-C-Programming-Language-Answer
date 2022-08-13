#include<stdio.h>
#include<limits.h>
#include<string.h>

#include "debug.h"

#define MAXLINE 1000 //maximum input line length
#define MAXLEN INT_MAX

int getline(char line[], int maxLine);
void copy(char to[], char from[]);

//print the loggest input line
main()
{   
    int len; //current line length
    char line[MAXLINE]; //current input line

    while ((len = getline(line, MAXLINE)) > 0)
    {
        //需要处理换行符,对最后一行的换行符的处理可能是多余的
        int i = len - 1;
        if (line[i] == '\n')
            i--;
        for (; i >= 0; i--)
            if (line[i] == ' ' || line[i] == '\t')
                line[i] = '\0';
            else
                break;
        //debug("%d", i);
        if (i > 0)
        {
            printf("%s", line);
            //debug("%d", strlen(line));
        }
    }

    return 0;
}

//getline : read a line into s, return length
int getline(char s[], int lim)
{
    int c, i;
    //给终止符'\0'留一个空位 这样缓冲区才是正常能被读到的
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')  {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

//copy: copy 'from' into 'to' ; assume to is big enough
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;

    return;
}