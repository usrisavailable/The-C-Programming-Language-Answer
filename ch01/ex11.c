#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    //统计单词
    int nc, nl, nw;
    int state = OUT;
    int c;

    while((c = getchar()) != EOF)
    {
        nc++;
        if (c == '\n')
            nl++;
        //关于单个单词的判断很巧妙,但是这部分程序没办法处理文本开头是空白的情况
        if (nc == '\n' || nc == ' ' || nc == '\t')
            state = IN;
        else if (state)
        {
            nw++;
            state = OUT;
        }
    }

    return 0;
}