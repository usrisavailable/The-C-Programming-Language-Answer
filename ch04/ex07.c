#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

#define BUFSIZE 100
char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0;
int former = 0;

int getch(void);
void ungetch(int);
void ungets(char s[]);  //back a string input
//reverse Polish calculator
int main(int argc, char **argv)
{
    char s[10] = "hello\0";
    int i = 15;
    while(i--)
    {
        //debug("%d", i);
        ungets(s);
        //debug("%d", i);
    }
    debug("%s", buf + former);
    for(i = 0; i != bufp; i++)
    {    
        putchar(buf[i]);
        putchar('\n');
    }
    return 0;
}

void strcopy(char *d, char *s)
{
    int l = strlen(s);
    int i;
    for(i = 0; i < l; i++)
    {
        d[i] = s[i];
        //debug("%d %c", i, d[i]);
    }
    d[i] = '\0';
    return;
}
void ungets(char s[])
{
    int len = strlen(s);

    if (bufp < BUFSIZE && bufp + len < BUFSIZE)
    {
        //debug("%s", buf + bufp);
        strcopy(buf + bufp, s);
        //debug("%d", bufp);
        //debug("%s", buf + bufp);
        former = bufp;
        bufp = bufp + len + 1;
    }
    else
        printf("error: buffer is full\n");

    return;
}
