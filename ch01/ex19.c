#include<stdio.h>
#include<limits.h>
#include<string.h>

#include "debug.h"

#define MAXLINE 1000 
#define MAXLEN INT_MAX

int getline(char line[], int maxLine);
void copy(char to[], char from[]);
void reverse(char s[], int len);

//print the loggest input line
main()
{   
    int len; //current line length
    char line[MAXLINE]; //current input line

    while ((len = getline(line, MAXLINE)) > 0)
    {
        //终端不会有那么大的长度,文件的话，就难了
        if (line[len - 1] == '\n')
        {
            reverse(line, len - 1);
        }
        else
            reverse(line, len);

        printf("%s", line);
    }

    return 0;
}

//getline : read a line into s, return length
int getline(char s[], int lim)
{
    int c, i;
    //给终止符'\0'留一个空位 这样缓冲区才是正常能被读到的
    //还有就是能避免识别到之前留在缓冲区的字符
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