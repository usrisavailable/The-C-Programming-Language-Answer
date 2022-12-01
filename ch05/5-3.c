#include <stdio.h>
#include <stdarg.h>
#include <cstring>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)

char* strcat(char *d, char *s);

int main(int argc, char **argv)
{
    char d[100] = "hello ";
    char s[100] = "world";
    strcat(d, s);
    debug("%s", d);
    return 0;
}

char* strcat(char *d, char *s)
{
    int len = strlen(d);
    d += len;
    while((*d++ = *s++))
        ;
    return d;
}
