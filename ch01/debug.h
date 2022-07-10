#include <stdio.h>
#include <stdarg.h>

//扩张成宏的形式
#define debug(fmt, ...) fprintf(stderr, "第%d行: " fmt "\n", __LINE__, __VA_ARGS__)

/* void debug(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    printf("第%d行: ", va_arg(args, int));
    fmt++;
    while(*fmt != '\0')
    {
        if ('d' == *fmt)
        {
            int i = va_arg(args, int);
            printf("%d ", i);
        }
        else if ('f' == *fmt)
        {
            double f = va_arg(args, double);
            printf("%f ", f);
        }
        else if ('s' == *fmt)
        {
            char *str = va_arg(args, char*);
            printf("%s ", str);
        }
        fmt++;
    }
    printf("\n");
    va_end(args);
    return;
} */