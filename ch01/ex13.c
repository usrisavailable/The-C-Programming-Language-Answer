#include <stdio.h>
#include <ctype.h>

#include "debug.h"

#define IN 1
#define OUT 0

int main()
{
    int c;
    int wordLength[20]; //最长19个字符
    //输出竖形直方图和横形直方图
    //单词长度的出现频率
    int i;
    for (i = 0; i < 20; i++)
    {
        wordLength[i] = 0;
    }

    int state = OUT;
    int len = 0;
    while ((c = getchar()) != EOF)
    {
        if (isalpha(c))
            len++;
        if (c == ' ' || c == '\n')
            state = IN;
        if (state)
        {
            wordLength[len]++;
            len = 0;
            state = OUT;
        }
    }
    
    //创建原始数据的副本
    int copyWordLength[20];
    for(i = 0; i < 20; i++)
    {
        copyWordLength[i] = wordLength[i];
    }

    int maxLen = 0; //最长单词出现的频率
    for (i = 0; i < 20; i++)
    {
        if (maxLen < copyWordLength[i])
            maxLen = copyWordLength[i];
    }

    //解决办法是每次输出一行就可以
    printf("竖形直方图输出\n");
    char str[19] = {' '};
    for(i = maxLen; i > 0; i--)
    {
        int k = 18;
        while(k--)
            str[k] = ' ';

        for (int j = 1; j < 20; j++)
        {
            if (copyWordLength[j] == i)
                {
                    str[j-1] = '*';
                    copyWordLength[j]--;
                }
        }
        printf("%s\n", str);
    }

    printf("\n");

    for(i = 0; i < 20; i++)
    {
        copyWordLength[i] = wordLength[i];
    }
    printf("横形直方图\n");
    for (i = 1; i < 20; i++)
    {
        int j =copyWordLength[i];
        //debug("%d %d", i, j);

        while(j)
        {
            putchar('*');
            j--;
        }
            printf("\n");
    }
    return 0;
}