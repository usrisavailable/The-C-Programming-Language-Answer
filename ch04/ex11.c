#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

#define MAXOP 100   //max size of operand or operator
#define NUMBER '0'  //signal that a number was found

#define MAXVAL 100 //maxinum depth of val stack

int sp = 0; //next free stack position
double val[MAXVAL];

//push f onto value stack
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

//pop and return top value from stack
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getch(void);
void ungetch(int);

//get next character or numeric operand
int getop(char s[])
{
    int i, c;
    static int temp = -1;

    if (temp != -1)
        c = temp;
    if (c == ' ' || temp == -1)
        while ((s[0] = c = getch()) == ' ' || c == '\t')
            ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; //not a number
    i = 0;
    if (isdigit(c))     //collect integer part
        while( isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')   //collect fraction part
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        temp = c;
    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE]; //buffer for ungetch
int bufp = 0;

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

int getop(char []);
void push(double);
double pop(void);

//reverse Polish calculator
int main(int argc, char **argv)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                push((int)pop() % (int)op2);//负数有些不好做
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
