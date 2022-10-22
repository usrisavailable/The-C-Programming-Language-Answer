#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

void escape(char *s, char *t);
void notescape(char *s, char *t);

int main(int argc, char **argv)
{
    char s[MAX_LINE];
    char t[MAX_LINE];
    FILE *file = fopen("ex02.c", "r");
    
    fread(t, 5, 20, file);
    escape(s, t);
    debug("%s", s);
    debug("%s", "\\n"); //three character but '\n' is one character
    notescape(s, t);
    debug("%s", s);
    return 0;
}

void escape(char *s, char *t)
{
    int lent = strlen(t);
    int i, j = 0;

    for(i = 0; i < lent; i++)
    {
        switch(t[i])
        {
            case '\t':
                s[j++] = '\\';
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            default:
                s[j++] = t[i];
        }
    }
    s[j] = '\0';

    return;
}

void notescape(char *s, char *t)
{
    int lent = strlen(t);
    int i, j = 0;

    for(i = 0; i < lent; i++)
    {
        switch(t[i])
        {
            case '\\':
                if (t[i + 1] == '\\' && t[i + 2] == 't')
                    s[j++] = '\t';
                if (t[i + 1] == '\\' && t[i + 2] == 'n')
                    s[j++] = '\n';
                t += 2;
                break;
            default:
                s[j++] = t[i];
        }
    }
    s[j] = '\0';

    return;
}
