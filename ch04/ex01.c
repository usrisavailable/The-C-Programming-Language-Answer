#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

int strindex(char *s, char *t);
int getline(char *s, int lim);

int main(int argc, char **argv)
{
    char s[MAX_LINE];
    char t[MAX_LINE] = "ould";

    while(getline(s, MAX_LINE) > 0)
        {
            if (strindex(s, t) >= 0)
                debug("%s", s);
            fflush(NULL);
        }
    return 0;
}

int getline(char *s, int lim)
{
    int i = 0;
    int c = 0;

    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    //debug("%s", s);
    //fflush(NULL);
    return i;
}

int strindex(char *s, char *t)
{
    int i, j, k;
    for (i = strlen(s) - 1; i >= strlen(t) - 1; i--)
    {
        for (j = i, k = strlen(t) - 1; t[k] != '\0' && t[k] == s[j]; k--, j--)
            {
                // debug("%c %c", t[k], s[j]);
                // fflush(NULL);
            }
        if (k < 0 && t[k] == '\0')
            return i - strlen(t) + 1;
    }
    return -1;
}
