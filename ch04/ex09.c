#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

int getch(void);
void ungetch(int);

#define BUFSIZE 100
char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0;

int getch (void)    //get a (possibly pushed-back) character
{
    if (bufp > 0) 
    {
        return buf[--bufp] != EOF? buf[bufp]:getchar();//terminal is a special file
    }
    return getchar();
}
void ungetch(int c)     //push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int main(int argc, char **argv)
{
    
    return 0;
}
