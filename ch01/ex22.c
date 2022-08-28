#include<stdio.h>
#include<limits.h>
#include<string.h>

#include "debug.h"

#define MAXLINE 1000 
#define MAXLEN INT_MAX
#define END 5   

int getline(char line[], int maxLine);
void copy(char to[], char from[]);
void MultiLine(char line[], int len);

//print the loggest input line
int main(int argc ,char **argv)
{   
    int len; //current line length
    char line[MAXLINE]; //current input line
    char output[MAXLINE];//对于终端输入来说够用

    debug("%d", 11111); //忘记打开vscode的自动保存了
    while ((len = getline(line, MAXLINE)) > 0)
    {
        //按行处理
        //返回的len指向最后一个手动添加的'\0'，很必要，就是这么识别的
        debug("%d", len);
        MultiLine(line, len - 1);
        //printf("%s", output);
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

void MultiLine(char line[], int len)
{
    //每隔END列就要拆一行这样就需要两个计数器
    //一个计数器去记录最后一个非空格的位置
    //一个计数器去记录指标到END的位置
    char output[END + 2]; //留出放'\0'的地方
    int flagi, flagj; //标记最后一个空格处的位置
    int j = 0;
    for (int i = 0; i <= len; i++)
    {
        output[j++] = line[i];
        if (line[i] == ' ' || line[i] == '\t')
            {
                flagj = j;
                flagi = i;
            }
        if (j == END)   
            {
                if (flagj != END + 1)
                {
                    output[flagj] = '\0';
                    i = flagi;
                }
                else
                    output[j + 1] = '\0';
                printf("%s\n", output);
                fflush(stdout);
                debug("%d", j);
                j = 0;
                flagj = END + 1;
            }
    }
    return;
}
