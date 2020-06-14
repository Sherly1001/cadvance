#include "words.h"
#include "sher_pqueue.h"

typedef struct data {
    words_t *w1, *w2;
    list_t *sents;
} data_t;

void *pq_copy_data(void *data) {
    data_t *new = malloc(sizeof(data_t));
    new->w1 = ((data_t*)data)->w1;
    new->w2 = ((data_t*)data)->w2;
    return new;
}

void pq_free_data(void *data) {
    freeSents(((data_t*)data)->sents);
    free(data);
}

void load_ws(words_t **ws, const char *fn) {
    FILE *f = fopen(fn, "r");
    if (!f) {
        printf("Can't open file '%s'\n", fn);
        return;
    }

    char s[1000];

    for (int r = 0, c = 0;;) {
        if ((r = fscanf(f, "%[^.,!?\"\n]s", s)) > 0) {
            addWords(ws, s, ++c);
        } else if (r == 0) {
            fseek(f, 1, SEEK_CUR);
        } else {
            break;
        }
        fseek(f, 1, SEEK_CUR);
    }

    fclose(f);
}

list_t *commonSents(words_t *w1, words_t *w2) {
    list_t *sents = NULL;

    for (list_t *sent1 = w1->sents, *sent2 = w2->sents; sent1 && sent2;) {
        if (sent1->sent == sent2->sent) {
            addSent(&sents, sent1->sent);
            sent1 = sent1->next;
            sent2 = sent2->next;
        } else if (sent1->sent > sent2->sent) {
            sent1 = sent1->next;
        } else {
            sent2 = sent2->next;
        }
    }

    return sents;
}

void pairWords(words_t *ws) {
    pqueue_t q = {0};

    for (words_t *cur_i = ws; cur_i; cur_i = cur_i->next) {
        for (words_t *cur_j = cur_i->next; cur_j; cur_j = cur_j->next) {
            list_t *sents = commonSents(cur_i, cur_j);

            int priority = 0;
            for (list_t *cur_s = sents; cur_s; cur_s = cur_s->next) ++priority;

            if (priority > 1) {
                data_t *data = pq_enqueue(&q, &(data_t){cur_i, cur_j, NULL}, priority);
                data->sents = sents;
            } else {
                freeSents(sents);
            }
        }
    }

    while (q.first) {
        data_t *data = pq_dequeue(&q);
        printf("'%s', '%s': ", data->w1->word, data->w2->word);
        for (list_t *cur_i = data->sents; cur_i; cur_i = cur_i->next) {
            printf("%d ", cur_i->sent);
        }
        printf("\n");

        pq_free_data(data);
    }
}

int main() {
    words_t *ws = NULL;

    load_ws(&ws, "ex1.txt");
    prtWords(ws);

    printf("\n===== Pair words =====\n");

    pairWords(ws);

    freeWords(ws);
}