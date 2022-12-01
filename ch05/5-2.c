#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)


#define BUFSIZE 100
char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0;

double getfloat(double *);
int getch(void);
void ungetch(int);

int main(int argc, char **argv)
{
    double n;
    getfloat(&n);
    debug("%f", n);
    return 0;
}

int getch (void)    //get a (possibly pushed-back) character
{
    return (bufp > 0) ? buf[--bufp] :getchar();//terminal is a special file
}
void ungetch(int c)     //push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

double getfloat(double *pn)
{
    int c, sign;

    while (isspace(c = getch()))    //skip white sapce
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);     //it is not a number
        return 0.0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())  
        *pn = 10 * *pn + (c - '0');
    if (c == '.')
        c = getch();
    int t = 1;
    for (; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0');
        t *= 10;
    }
    debug("%f", *pn);
    *pn /= t;
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c; 

}
