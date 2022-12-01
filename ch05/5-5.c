#include <stdio.h>
#include <stdarg.h>
#include <cstring>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)

char* strncpy(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);
char* strncat(char *s, char *t, int n);

int main(int argc, char **argv)
{
    char s[100] = "hello ";
    char t[100] = "world";
    debug("%d",  strncmp(s, t, 3));
    strncat(s, t, 3);
    debug("%s",  s);
    strncpy(s, t, 3);
    debug("%s",  s);
    return 0;
}

//assume user will input correct arguments
char* strncpy(char *s, char *t, int n)
{
    int lent = strlen(t);
    n = n < lent ? n : lent;
    while(n--)
        *s++ = *t++;
    *s = '\0';
    return s;
}
int strncmp(char *s, char *t, int n)
{
    int lent = strlen(t);
    n = n < lent ? n : lent;
    while(n--)
        if (*s != *t)
            return *s - *t;
        else
            {s++; t++;}
    return 0;
}
char* strncat(char *s, char *t, int n)
{
    int lent = strlen(t);
    int lens = strlen(s);
    s += lens;
    n = n < lent ? n : lent;
    while(n--)
        *s++ = *t++;
    return s;
}
