#include <stdio.h>

main()
{
    int c;
    int flag = 0;

    //换行会刷新缓冲区
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            flag = 1;
            continue;
        }
        else
        {
            if (flag)
            {
                putchar(' ');
                flag = 0;
            }
            putchar(c);
        }
    }

    printf("\n");
}