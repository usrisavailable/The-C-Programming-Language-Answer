#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#define _GUN_SORUCE

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

//get next character or numeric operand
int getop(char s[], char op[], int* index, int len)
{
    int i = *index;
    int j = 0;

    if (i > len)
    {
        return -1;
    }
    while (s[i] == ' ')
        i++;
    if (!isdigit(s[i]))
    {
        *index = ++i;
        return s[i - 1];
    }
    if (isdigit(s[i]))     //collect integer part
        while( isdigit(s[i]) && (op[j++] = s[i++]))
            ;
    if (s[i] == '.' && (op[j++] = '.'))   //collect fraction part
        i++;
    if (isdigit(s[i]))
        while (isdigit(s[i]) && (op[j++] = s[i++]))
            ;
    op[j] = '\0';
    *index = i;
    return NUMBER;
}

int getline(char *s, int lim)
{
    int i = 0;
    int c = 0;

    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    //debug("%s", s);
    //fflush(NULL);
    return i;
}

int main(int argc, char **argv)
{
    int type;
    double op2;
    char s[MAX_LINE];
    char op[MAXOP];
    size_t n;
    int len = getline(s, MAX_LINE);
    int index = 0;

    while ((type = getop(s, op, &index, len)) != EOF)
    {
        debug("%d", index);
        switch (type)
        {
            case NUMBER:
                push(atof(op));
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
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %d\n", type);
                break;
        }
    }

    return 0;
}
