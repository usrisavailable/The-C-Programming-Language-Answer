#include<stdio.h>
#include<limits.h>

#include "debug.h"

//应该没理解错题意，可以分段传输
#define MAXLINE 1000 //maximum input line length
#define MAXLEN INT_MAX

int count = INT_MAX;

int getline(char line[], int maxLine);
void copy(char to[], char from[]);

//print the loggest input line
main()
{   
    debug("%d", MAXLINE);
    debug("%d", INT_MAX);
    int len; //current line length
    int max; //maximum length seen so far
    char line[MAXLINE]; //current input line
    //char longest[MAXLINE];  //longest line saved here 

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0)
    {
        
        count -= len;
        printf("%s", line);
        if (len < 999 || count < 0)
            break;
    }

    return 0;
}

//getline : read a line into s, return length
int getline(char s[], int lim)
{
    int c, i;
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