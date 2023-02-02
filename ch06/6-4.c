#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define debug(fmt, ...) fprintf(stderr, "line%d: " fmt "\n", __LINE__, __VA_ARGS__)

//#define NULL (void *)(0)

#define MAXWORD 100
#define MAXLEN 1000

//单词所在行列表
struct lineslist
{
    int value;  //保存行号
    struct lineslist *next; //以链表的形式存储
};
//单词列表
struct wordlist
{
    char *data; //保存所有单词
    struct wordlist* left;  //下一个单词
    struct wordlist* right;  //下一个单词
    struct lineslist *lineslists;    //单词附加的行号列表
};

struct newwordlist {
    char *data;
    int frequency;
    struct newwordlist *next;
};

FILE* file;

int getword(char *, int, char *, int *);
void printword(struct wordlist*);
struct wordlist* strdump(char *, int);
int FindPreposition(char *word, char **wp);
struct wordlist* inserttree(char *word, int line, struct wordlist *wordlists);

int main(int argc, char *argv[])
{
    char word[MAXWORD];
    char line[MAXLEN];
    char *fileName = argv[1];
    file = fopen(fileName, "r");
    char *preposition[] = {"the", "and", "a", "an", "NULL"};
    struct wordlist *wordlists = 0;
    int lines = 0;

    if (file == NULL)
        debug("%s", "open failed!");

    while(fgets(line, MAXWORD, file) != NULL)
    {
        lines++;
        int lineLength = 0;
        while (getword(word, MAXWORD, line, &lineLength))
            if (!FindPreposition(word, preposition))
                wordlists = inserttree(word, lines, wordlists);
    }
    printword(wordlists);
    return 0;
}
int getword(char *word, int lim, char *line, int *len)
{
    int character;
    int nextCh = *len;
    char *wordCopy = word;

    character = line[nextCh++];

    while(isspace(character))
        character = line[nextCh++];
    *wordCopy++ = character;
    *wordCopy = '\0';
    if (character == '\0')
        return 0;
    
    for(;lim >= 0; lim--)
    {
        character = line[nextCh++];
        if (character == ',' || character == '.' || isspace(character))
            break;
        *wordCopy++ = character;
    }
    *wordCopy = '\0';
    *len = nextCh;
    return nextCh;
}

struct wordlist* strdump(char *word, int line)
{
    struct wordlist *newWord = (struct wordlist*)malloc(sizeof(struct wordlist) + 1);
    newWord->data = (char *)malloc(sizeof(word) + 1);
    newWord->left = NULL;
    newWord->right = NULL;
    newWord->lineslists = (struct lineslist *)malloc(sizeof(struct lineslist) + 1);
    newWord->lineslists->value = line;
    newWord->lineslists->next = NULL;
    strcpy(newWord->data, word);
    return newWord;
}

struct wordlist* inserttree(char *word, int line, struct wordlist *wordlists)
{
    if (!wordlists)
    {
        struct wordlist *tempNode = strdump(word, line);
        return tempNode;
    }

    int num = strcmp(wordlists->data, word);
    if (!num)
    {
        struct lineslist *tempNode = (struct lineslist *)malloc(sizeof(struct lineslist) + 1);
        //debug("%s %d", wordlists->data, line);
        tempNode->value = line;
        tempNode->next = NULL;
        tempNode->next = wordlists->lineslists->next;
        wordlists->lineslists->next = tempNode;
    }
    if (num < 0)
    {
        wordlists->left = inserttree(word, line, wordlists->left);
    }
    if (num > 0)
    {
        wordlists->right = inserttree(word, line, wordlists->right);
    }
    return wordlists;
}

void printtree(struct wordlist *treenode, struct newwordlist** newwordlists)
{
    if (treenode)
    {
        struct newwordlist * newWord = (struct newwordlist *)malloc(sizeof(struct newwordlist) + 1);
        newWord->data = treenode->data;
        struct lineslist * tempNode = treenode->lineslists;
        int count = 0;
        while(tempNode)
        {
            count++;
            tempNode = tempNode->next;
        }
        newWord->frequency = count;
        newWord->next = NULL;
        struct newwordlist *tempWordlist = (*newwordlists)->next;
        struct newwordlist *tempPreWordlist = *newwordlists;
        while(tempWordlist)
        {
            if (count < tempWordlist->frequency)
                {tempPreWordlist = tempWordlist; tempWordlist = tempWordlist->next;}
            else
                break;
        }
        newWord->next = tempWordlist;
        tempPreWordlist->next = newWord;
    }
    else if (!treenode)
        return;
    printtree(treenode->left, newwordlists);
    printtree(treenode->right, newwordlists);

    return;
}

void printword(struct wordlist* wordlists)
{
    struct newwordlist *newWord = (struct newwordlist *)malloc(sizeof(struct newwordlist) + 1);
    newWord->frequency = 0;
    newWord->next = NULL;
    printtree(wordlists, &newWord);
    struct newwordlist *word = newWord->next;
    while(word)
        {debug("%d %s", word->frequency, word->data);   word = word->next;}
    return;
}

int FindPreposition(char *word, char **wp)
{
    char **temp = wp;
    while(*temp != "NULL")
        if(!strcmp(word, *temp++))
            return 1;
    return 0;
}
