#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define debug(fmt, ...) fprintf(stderr, "line%d: " fmt "\n", __LINE__, __VA_ARGS__)

struct nlist {
    struct nlist *next; //next entry in chain
    char *name;     //defined name
    char *defn;     //replacement text
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];     //pointer table

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

//lookup: look for s in hashtab
struct nlist* lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;      //found
    
    return NULL;        //not found
}

char *strdup(char *s)
{
    char *tempStr = (char *)malloc(sizeof(s) + 1);
    if (tempStr)
        return NULL;
    return strcpy(tempStr, s);
}

//install:  put (name, defn) in hashtab
struct nlist* install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL){
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *) np->defn);        //free previous defn
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name)
{
    struct nlist *np, *prenp;

    if ((np = lookup(name)) == NULL)
        printf("%s\n", "undef failed, name not found");
    else{
        struct nlist *np, *prenp;

        for (np = prenp = hashtab[hash(s)]; np != NULL; prenp = np, np = np->next)
            if (strcmp(s, np->name) == 0)
                break;
    
        free((void *)np->name);
        free((void *)np->defn);
        prenp->next = np->next;
    }
}
int main(int argc, char *argv[])
{
    return 0;
}
