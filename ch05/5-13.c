#include<stdio.h>
#include<string.h>

#define debug(fmt, ...) fprintf(stderr, "第%d行: " fmt "\n", __LINE__, __VA_ARGS__)

#define MAXLINE 1000
char storage[100000]; //假设就存储10个字符串吧
char *next = storage;

int getline(char s[], int lim);
int main(int argc, char **argv)
{
    char* list[1000];
    char line[1000];
    int num = 0, n = 0;
    int len;

    while((len = getline(line, MAXLINE)) != 0)
    {
        strcpy(next, line);
        list[n++] = next;
        next = next + len + 1;
    }
    
    char *s = argv[1];
    s++;
    while(*s)
    {
        num = num * 10 + (*s - '0');
        s++;
    }
    //debug("%d", num);
    num = num > n ? n : num;
    while(num--)
    {
        debug("%d", num);
        printf("%s", list[--n]);
    }
    return 0;
}

//getline : read a line into s, return length
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')  {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
