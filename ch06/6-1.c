#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define debug(fmt, ...) fprintf(stderr, "第%d行: " fmt "\n", __LINE__, __VA_ARGS__)

#define MAXWORD 100
#define NKEYS sizeof(keytab) / sizeof(keytab[0])

struct key{
    char word[100];
    int count;
} keytab[] = {
    "char", 0,
    "int", 0,
    "void", 0
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

//count C keywords
int main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    //debug("%d", keytab[1].count);
    fflush(NULL);
    return 0;
}

//find word int tab[0] ... tab[n - 1]
int binsearch(char *word, struct key keytab[], int n)
{
   
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high)
    {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, keytab[mid].word)) < 0)
            high = mid - 1;
        else if(cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

//get next word or character form input
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    *w = '\0';
    //debug("%s", word);
    return word[0];
}

int flag = 0;
static int storage;
int getch(void)
{
    if (flag)
    {
        flag = 0;
        return storage;
    }
    int c;
    if ((c = getchar()) != EOF)
        return c;
    return -1;
}

void ungetch(int c)
{
    flag = 1;
    storage = c;
}
