#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define debug(fmt, ...) fprintf(stderr, "第%d行: " fmt "\n", __LINE__, __VA_ARGS__)

#define MAXWORD 100

struct wordlist
{
    char *data;
    struct wordlist* left;
    struct wordlist* right;
};
/* struct wordlist
{
    char *warray[MAXWORD];
    int count;
}; */

//struct wordlist wordlists[26];
struct wordlist wordlists[26];
FILE* file;
int wordlength;

int getword(char *, int);
void insertword(char *);
void printword(struct wordlist*);
char* strdump(char *);

int main(int argc, char *argv[])
{
    char word[MAXWORD];
    int w;
    file = fopen("6-2.c", "r");
    if (file == NULL)
        debug("%s", "open failed!");

    wordlength = atoi(argv[1]);
    //debug("%d", wordlength);

    while(getword(word, MAXWORD) != EOF)
    {
        //debug("%s", word);
        if (isalpha(word[0]))
        {
            insertword(word);
        }
    }
    printword(wordlists);
    return 0;
}
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    c = fgetc(file);

    while(isspace(c))
        c = fgetc(file);
    *w++ = c;
    if (c == EOF || c == '(')
    {
        *w = '\0';
        return c;
    }
    if (!isalpha(c))
    {
        c = fgetc(file);
        while(!isspace(c) && c != EOF)
        {   
            c = fgetc(file);
            //debug("%c", c);
        }
        *w = '\0';
        //debug("%d", c);
        return c;
    }
    for(;lim >= 0; lim--)
    {
        c = fgetc(file);
        if (isalnum(c))
        {
            *w++ = c;
        }
        else
            break;
    }
    ungetc(c, file);
    *w = '\0';
    return c;
}

char* strdump(char *word)
{
    char *newWord = (char *)malloc(sizeof(word) + 1);
    strcpy(newWord, word);
    return newWord;
}

struct wordlist* inserttree(char *word, struct wordlist *wordlists)
{
    if (!wordlists)
    {
        struct wordlist *tempNode = (struct wordlist *)malloc(sizeof(struct wordlist));
        tempNode->data = strdump(word);
        tempNode->left = NULL;
        tempNode->right = NULL;
        return tempNode;
    }
    if (!wordlists->data)
    {
        wordlists->data = strdump(word);
        wordlists->left = NULL;
        wordlists->right = NULL;
        return wordlists;
    }
    int num = strcmp(wordlists->data, word);
    if (!num)
    {
        return wordlists;
    }
    if (num < 0)
    {
        wordlists->left = inserttree(word, wordlists->left);
    }
    if (num > 0)
    {
        wordlists->right = inserttree(word, wordlists->right);
    }
    return wordlists;
}
void insertword(char *word)
{
    int c = word[0];
    c = tolower(c);
    int num = c - 'a';

    /* int count = wordlists[num].count;
    char *w = (char *)malloc(sizeof(word));
    strcpy(w, word);
    char **warray = wordlists[num].warray;
    warray[count++] = w;
    wordlists[num].count = count; */
    inserttree(word, &wordlists[num]);
    return;
}
static char *wordarray[MAXWORD];
static int num;
void printtree(struct wordlist *treenode)
{

    if (treenode)
    {
        wordarray[num++] = treenode->data; 
    }
    else if (!treenode)
        return;
    printtree(treenode->left);
    printtree(treenode->right);

    return;
}
void sortself()
{
    char *wordarrayNew[MAXWORD];
    int j = 0;
    int i = 0;
    for(i = 0; wordarray[i]; i++)
        if (strlen(wordarray[i]) >= wordlength)
            wordarrayNew[j++] = wordarray[i];
    wordarrayNew[j] = NULL;
    if (!j)
    {
        wordarray[0] = NULL;
        return;
    }
    debug("%d", j);
    char *wordcmp = wordarrayNew[0];
    for(i = 1; wordarrayNew[i]; i++)
        if (strncmp(wordarrayNew[i], wordcmp, wordlength))
            strcpy(wordarrayNew[i], "1");
    debug("%d", i);
    j = 0;
    for(i = 0; wordarrayNew[i]; i++)
        if (strcmp(wordarrayNew[i], "1"))
            wordarray[j++] = wordarrayNew[i];
    wordarray[j] = NULL;
    debug("%d", j);
    if (j == 1)
        wordarray[0] = NULL;
    return;
}
void printword(struct wordlist* wordlists)
{
    int n;
    for(n = 0; n < 26; n++)
    {
        debug("%d%s", n, "----------------");
        /* char **warray = wordlists[n].warray;
        int count = wordlists[n].count;
        while(count--)
        {
            printf("%s ", warray[count]);
        }
        printf("\n"); */
        struct wordlist *tree = &wordlists[n];
        printtree(tree);
        wordarray[num] = NULL;
        sortself();
        for (int i = 0; wordarray[i]; i++)
            printf("%s ", wordarray[i]);
        num = 0;
        printf("\n");
        fflush(NULL);
        debug("%d%s", n, "----------------");
    }
    return;
}

//长度超过设定值的子树
