#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

#define MAXOP 100   //max size of operand or operator
#define NUMBER '0'  //signal that a number was found

#define MAXVAL 100 //maxinum depth of val stack

/*************************************************
    stack operation
**************************************************/
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

double top()
{
    if (sp > 0)
        return val[sp - 1];
    else
    {
        printf("error: stack empty!\n");
        return 0.0;
    }
}

void duptop()
{
    double temp = top();
    if (temp)
        push(top());
    return;
}

void swaptop()
{
    double t1 = pop();
    double t2 = pop();
    if (t1 && t2)
    {
        push(t1);
        push(t2);
    }
    return;

}

void clearstack()
{
    sp = 0;
    return;
}
/*******************************************************************
    end
********************************************************************/

/*******************************************************************
    获取操作数和操作符
********************************************************************/
int getch(void);
void ungetch(int);

//get next character or numeric operand
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isalnum(c) && c != '.')
        return c; //not a number
    i = 0;
            ;
    //数字部分
    if (isdigit(c))     //collect integer part
        while( isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')   //collect fraction part
        while (isdigit(s[++i] = c = getch()))
            ;
    //sin
    if (isalpha(c))
    {
        while( isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return 's';
    }
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
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

/*******************************************************************
    end
********************************************************************/

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
                //swaptop();
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
            case 's':
                push(sin(pop()));
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
