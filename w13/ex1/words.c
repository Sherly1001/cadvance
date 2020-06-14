#include "words.h"

int shercmp(const char *s1, const char *s2) {
    char l1 = 0, l2 = 0;
    while (*s1 && *s2) {
        l1 = tolower(*s1);
        l2 = tolower(*s2);

        if (l1 < l2) return -1;
        else if (l1 > l2) return 1;

        ++s1, ++s2;
    }

    return *s1 ? 1 : *s2 ? -1 : 0;
}

void addSent(list_t **sents, int sent) {
    if (*sents == NULL || (*sents)->sent != sent) {
        list_t *new_s = malloc(sizeof(list_t));

        new_s->sent = sent;
        new_s->next = *sents;

        *sents = new_s;
    }
}

void addWord(words_t **ws, const char *word, int sent) {
    words_t *cur_w = *ws;

    while (cur_w && shercmp(cur_w->word, word)) {
        cur_w = cur_w->next;
    }

    if (cur_w) {
        addSent(&cur_w->sents, sent);
    } else {
        words_t *new_w = malloc(sizeof(words_t));

        int len = strlen(word);
        new_w->word = malloc((len + 1) * sizeof(char));
        strcpy(new_w->word, word);

        new_w->sents = NULL;
        addSent(&new_w->sents, sent);
        new_w->next = *ws;

        *ws = new_w;
    }
}

int scanWord(const char *s) {
    int i = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '\n')) ++i;
    return i;
}

void addWords(words_t **ws, const char *s, int sent) {
    char tmp[30];
    int i;

    while (*s) {
        s += scanWord(s);
        i = 0;
        while (*s && *s != ' ' && *s != '\n') {
            tmp[i] = *s;
            ++i, ++s;
        }
        tmp[i] = '\0';
        if (*tmp) addWord(ws, tmp, sent);
    }
}

void prtWords(words_t *ws) {
    for (words_t *cur_w = ws; cur_w; cur_w = cur_w->next) {
        printf("'%s': ", cur_w->word);
        for (list_t *cur_s = cur_w->sents; cur_s; cur_s = cur_s->next) {
            printf("%d ", cur_s->sent);
        }
        printf("\n");
    }
}

void freeSents(list_t *sents) {
    for (list_t *cur_s = sents, *del_s; cur_s;) {
        del_s = cur_s;
        cur_s = cur_s->next;

        free(del_s);
    }
}

void freeWords(words_t *ws) {
    for (words_t *cur_w = ws, *del_w; cur_w;) {
        del_w = cur_w;
        cur_w = cur_w->next;

        free(del_w->word);
        freeSents(del_w->sents);
        free(del_w);
    }
}
