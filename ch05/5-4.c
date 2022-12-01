#include <stdio.h>
#include <stdarg.h>
#include <cstring>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)

int strend(char *s, char *t);

int main(int argc, char **argv)
{
    char s[100] = "hellohello0";
    char t[100] = "llo";
    strend(s, t);
    debug("%d",  strend(s, t));
    return 0;
}

int strend(char *s, char *t)
{
    int lens = strlen(s);
    int lent = strlen(t);
    if (s < t)
        return -1;
    s += (lens - lent);

    while((*s++ == *t++) && *s)
        ;
    if (!*s)
        return 0;
    return -1;
}
