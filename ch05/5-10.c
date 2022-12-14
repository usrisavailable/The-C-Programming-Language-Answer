#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <time.h>
#include <ctype.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAXLINE 1000

static int stack[100];
static int indexxx = 0; //next free position
int pop();
void push(int s);
int getline(char *line, int max);

//find: print lines thatmatch pattern from 1st arg
int main(int argc, char **argv)
{
    char line[MAXLINE];
    int  c;

    /*数组在实际使用过程中都会被转为对应的指针使用
        指针型数组  char *a[]   <--> char **        char型指针
        二位数组    char [][]   <--> char (*)[]     数组型指针
        一维数组    char []     <--> char *         char型指针
    函数原型必须正确，传递的实参也要对应*/

    debug("%d", argc);
    while (--argc > 0 )//&& (*++argv)[0] == '-')
    {
        //这里要搞定操作符的解析
            c = (*++argv)[0];
            int num = 0;
            char *s;
            //debug("%c", c);
            //debug("%d", argc);
            if(isdigit(c))
                c = 'n';
           //debug("%s", argv[0]);
            //终端输入的 * 被识别未其它操作了了，要手动输入 \* 才可以正常识别
            /* if (!strcmp(argv[0], "*"))
                c = '*'; */
            switch (c)
            {
                case '+':
                    num = pop() + pop();
                    push(num);
                    break;
                case '*':
                    num = pop() * pop();
                    push(num);
                    break;
                case 'n':
                    s = argv[0];
                    num = 0;
                    while(*s)
                        num = num * 10 + (*s++ - '0');
                    push(num);
                    break;
                default:
                    printf("option not support %c\n", c);
                    argc = 0;
                    break;
        }
    }

    if (argc > 0)
        printf("Usage: expr 1 2 3\n");
    else
        printf("%d\n", pop());

    //debug("%d", indexxx);
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

void push(int s)
{
    debug("%d",s);
    stack[indexxx] = s;
    indexxx = indexxx + 1;

    return;
}

int pop()
{
    indexxx = indexxx - 1;
    return stack[indexxx];
}
