#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#define debug(fmt, ...) fprintf(stderr, "line%d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAXLINE 1096

int diff(FILE *fd1, FILE *fd2, char **s1, char **s2);

int main(int argc, char *argv[])
{
    FILE *fd1 = fopen(argv[1], "r");
    FILE *fd2 = fopen(argv[2], "r");

    if (!fd1 || !fd2)
        fprintf(stderr, "open failed\n");

    char *str1, *str2;
    if (diff(fd1, fd2, &str1, &str2))
        debug("%s %s", str1, str2);
    else
        debug("%s", "the same file");
    return 0;
}

int diff(FILE *fd1, FILE *fd2, char **s1, char **s2)
{
    char *tempStr1 = (char *)malloc(MAXLINE);
    char *tempStr2 = (char *)malloc(MAXLINE);

    while (fgets(tempStr1, MAXLINE, fd1) && fgets(tempStr2, MAXLINE, fd2)){
        if (strcmp(tempStr1, tempStr2) != 0)
            {
                *s1 = tempStr1; *s2 = tempStr2; return 1;
            }
    }

    if (feof(fd1) && feof(fd2))
        return 0;
    if (feof(fd1))
    {*s1 = NULL; fgets(tempStr2, MAXLINE, fd2); *s2 = tempStr2; return 1;}
    if (feof(fd2))
    {*s2 = NULL; fgets(tempStr1, MAXLINE, fd1); *s1 = tempStr1; return 1;}
    
}
