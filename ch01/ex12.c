#include <stdio.h>
#include <ctype.h>

#define IN 1
#define OUT 0

int main(int argc, char *argv[])
{
    //统计单词
    //输出每行一个单词
    int nc, nl, nw;
    int state = OUT;
    int c;

    //在Linux中，输入默认暂存到缓冲区，刷新缓冲区才可以得到输出
    while((c = getchar()) != EOF)
    {
        nc++;
        if (c == '\n')
            nl++;
        //关于单个单词的判断很巧妙,但是这部分程序没办法处理文本开头是空白的情况
        if (c == '\n' || c == ' ' || c == '\t')
            state = IN;
        else if (state)
        {
            putchar('\n');
            //printf("\n");
            nw++;
            state = OUT;
        }
        if (isalpha(c))
            putchar(c);
    }

    return 0;
}