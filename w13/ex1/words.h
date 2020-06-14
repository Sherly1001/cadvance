#ifndef __words_h__
#define __words_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct list {
    int sent;
    struct list *next;
} list_t;

typedef struct words {
    char *word;
    list_t *sents;
    struct words *next;
} words_t;


int shercmp(const char *s1, const char *s2);
void addSent(list_t **sents, int sent);
void addWord(words_t **ws, const char *word, int sent);
int scanWord(const char *s);
void addWords(words_t **ws, const char *s, int sent);
void prtWords(words_t *ws);
void freeSents(list_t *sents);
void freeWords(words_t *ws);


#endif