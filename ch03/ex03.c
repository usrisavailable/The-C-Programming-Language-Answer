#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000
void expand(char *s1, char *s2);

int main(int argc , char **argv)
{
    char s1[MAX_LINE];
    strcpy(s1, argv[1]);
    char s2[MAX_LINE];
    //debug("%s", s1);
    expand(s1, s2);
    debug("%s", s2);
    return 0;
}

void expand(char *s1, char *s2)
{
    int lens = strlen(s1);
    int i = 0, j = 0;
    char temp[4];
    int flag = 0;
    
    while(s1[i] == '-')
        s2[j++] = s1[i++];
    for (; i < lens;)
    {
        //read three character
        int r = snprintf(temp, 4, "%s", s1 + i);
        //debug("%s", temp);
        char n = temp[0];
        while(n <= temp[2])
        {
            if (flag)
            {
                flag = 0;
                n++;
                continue;
            }
            s2[j++] = n++;
        }
        i += 3;
        if (i + 1 < lens && s1[i] == '-')
            {
                i--;
                flag = 1;
            }
        else if(s1[i] == '-')
            s2[j++] = '-';
    }
    s2[j] = '\0';
    return ;
}
