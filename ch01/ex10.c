#include <stdio.h>

main()
{
    int c;

    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
            putchar('\\t');
        else if (c == '\b')
            putchar('\\b');
        else if (c == '\\')
        {
            putchar('\\');
            putchar('\\');
        }
        else
            putchar(c);
    }
}