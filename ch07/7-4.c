#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#define debug(fmt, ...) fprintf(stderr, "line%d: " fmt "\n", __LINE__, __VA_ARGS__)

int minscanf(char *fmt, ...);

int main(int argc, char *argv[])
{
    int ival;
    char *str;

    if (minscanf("%d %s", &ival, &str))
        debug("%d %s", ival, str);
    return 0;
}

int minscanf(char *fmt, ...)
{
    int count = 0;
    va_list ap;
    va_start(ap, fmt);
    char *s = fmt;
    int* ival;
    char **str;

    while(*s){
        while(isspace(*s)) s++;
        if (*s == '%')
            s++;
        else
            return 0;
        switch(*s++){
            case 'd':
                ival = va_arg(ap, int*);
                scanf("%d", ival);
                count++;
                break;
            case 's':
                str = va_arg(ap, char**);
                scanf("%s", *str);
                count++;
                break;
            default:
                break;
        }
    }

    va_end(ap);
    return count;
}

