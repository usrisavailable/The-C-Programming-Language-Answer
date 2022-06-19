#include <stdio.h>

main()
{
    int count = 0;
    int c;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
            ++count;
    }

    printf("total number is %d\n", count);
}