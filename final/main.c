#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jrb.h>

#define clean while (getchar() != '\n');

void menu() {
    printf("\n1. load data from file\n");
    printf("2. run pagerank algorithm one time\n");
    printf("3. run pagerank algorithm m time\n");
    printf("4. show server url and spam bot\n");
    printf("5. shortest path between url id1 and url id2\n");
    printf("6. quit\n\n");
    printf("Your choice: ");
}

int choice(int *c) {
    *c = 0;
    do {
        menu();
        scanf("%d", c);
        clean
    } while (*c < 1 || *c > 6);
}

typedef struct vertice {
    char url[255];
    double rank;
} vertice_t;

typedef struct graph {
    int nV;
    int nE;
    JRB vertices;
    JRB edges;
} graph_t;

// return 1 if already exited
int add_vertice(graph_t g, int id, char *url) {
    JRB node = jrb_find_int(g.vertices, id);
    if (node) {
        return 1;
    }
    vertice_t *v = malloc(sizeof(*v));
    v->rank = 1;
    strcpy(v->url, url);

    jrb_insert_int(g.vertices, id, new_jval_v(v));
    return 0;
}

char *get_name(graph_t g, int id) {
    JRB node = jrb_find_int(g.vertices, id);
    if (node) {
        return jval_v(node->val);
    }
    return NULL;
}

// return 1 if already exited
int add_edge(graph_t g, int id1, int id2) {
    JRB node_1 = jrb_find_int(g.edges, id1);
    if (node_1) {
        JRB node_2 = jrb_find_int(jval_v(node_1->val), id2);
        if (node_2) {
            return 1;
        } else {
            jrb_insert_int(jval_v(node_1->val), id2, new_jval_i(0));
            return 0;
        }
    } else {
        node_1 = make_jrb();
        jrb_insert_int(node_1, id2, new_jval_i(0));
        jrb_insert_int(g.edges, id1, new_jval_v(node_1));
        return 0;
    }
}

void load_from_file(graph_t *g) {
    FILE *f1 = fopen("webpages.txt", "r");
    if (!f1) {
        printf("\nFile webpages.txt doesn't exit\n");
        exit(1);
    }
    FILE *f2 = fopen("pageConnections.txt", "r");
    if (!f2) {
        printf("\nFile pageConnections.txt doesn't exit\n");
        exit(1);
    }

    fscanf(f1, "%d", &g->nV);
    printf("%d\n", g->nV);
    char url[255];
    int id;

    g->vertices = make_jrb();
    g->edges = make_jrb();
    for (int i = 0; i < g->nV; ++i) {
        fscanf(f1, "%s %d", url, &id);
        printf("%s %d\n", url, id);
        add_vertice(*g, id, url);
    }
    printf("\n");
    while (fscanf(f2, " %[^\n]s", url) > 0) {
        // printf("'%s'\n", url);
        sscanf(url, "%d", &id);
        int i = 0, id2 = 0;
        while (url[i] && url[i] != ' ') ++i;
        if (url[i] == ' ') ++i;

        // printf("%d: ", id);
        while (url[i] && url[i] != ' ') {
            if (sscanf(url + i, "%d", &id2) > 0) {
                // printf("%d ", id2);
                while (url[i] && url[i] != ' ') ++i;
                if (url[i] == ' ') ++i;
                // if (url[i] == '\0') printf("\n");

                if (!add_edge(*g, id, id2)) {
                    ++(g->nE);
                }
            } else {
                printf("\n");
                break;
            }
        }
    }

    fclose(f1);
    fclose(f2);

    int min_id = -1;
    int max_id = -1;
    int min_url = INT_MAX;
    int max_url = INT_MIN;

    JRB v1;
    jrb_traverse(v1, g->edges) {
        int count = 0;
        JRB v2, v1_tree = jval_v(v1->val);

        jrb_traverse(v2, v1_tree) {
            ++count;
        }

        if (count > max_url) {
            max_id = jval_i(v1->key);
            max_url = count;
        }
        if (count < min_url) {
            min_id = jval_i(v1->key);
            min_url = count;
        }
    }

    printf("Hot link: id %d url %s\n", max_id, get_name(*g, max_id));
    printf("Bored link: id %d url %s\n", min_id, get_name(*g, min_id));
}

void ranking_one_time(graph_t g) {
    JRB node;
    jrb_traverse(node, g.vertices) {
        int v_i = jval_i(node->key);

        double rank = 0;

        JRB node_i;
        jrb_traverse(node_i, g.edges) {
            JRB node_j, tree_i = jval_v(node_i->val);
            int add = 0, out = 0;
            jrb_traverse(node_j, tree_i) {
                ++out;
                if (v_i == jval_i(node_j->key)) {
                    add = 1;
                }
            }
            if (add) rank += 1 / (double)out;
        }

        printf("%d %s: %lf\n", v_i, get_name(g, v_i), rank);
        vertice_t *v_v = jval_v(node->val);
        v_v->rank = rank;
    }
}

void ranking_m_time(graph_t g) {
    int m = 0;
    printf("\nEnter m: ");
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        printf("time %d\n", i + 1);
        ranking_one_time(g);
        printf("\n");
    }

    printf("Top 3\n");
    int m1 = 0;
    double mm1 = 0;
    JRB node;
    jrb_traverse(node, g.vertices) {
        vertice_t *v = jval_v(node->val);
        if (v->rank > mm1) {
            mm1 = v->rank;
            m1 = jval_i(node->key);
        }
    }

    int m2 = 0;
    double mm2 = 0;
    jrb_traverse(node, g.vertices) {
        if (jval_i(node->key) == m1) continue;
        vertice_t *v = jval_v(node->val);
        if (v->rank > mm2) {
            mm2 = v->rank;
            m2 = jval_i(node->key);
        }
    }

    int m3 = 0;
    double mm3 = 0;
    jrb_traverse(node, g.vertices) {
        if (jval_i(node->key) == m1 || jval_i(node->key) == m2) continue;
        vertice_t *v = jval_v(node->val);
        if (v->rank > mm3) {
            mm3 = v->rank;
            m3 = jval_i(node->key);
        }
    }

    printf("%d %s\n", m1, get_name(g, m1));
    printf("%d %s\n", m2, get_name(g, m2));
    printf("%d %s\n", m3, get_name(g, m3));
}

void spam_bot(graph_t g) {
    JRB node;
    jrb_traverse(node, g.vertices) {
        int v_i = jval_i(node->key);
        int smp = 1;
        JRB node_i;
        jrb_traverse(node_i, g.edges) {
            JRB node_j, tree_i = jval_v(node_i->val);
            int out = 0;
            jrb_traverse(node_j, tree_i) {
                if (jval_i(node_j->key) == v_i) smp = 0;
            }
        }
        if (smp) {
            printf("%d %s is spam bot\n", v_i, get_name(g, v_i));
        }

    }

}

int main() {
    graph_t g;
    int c = 0;

    do {
        choice(&c);

        switch (c) {
          case 1:
            load_from_file(&g);
            break;
          case 2:
            ranking_one_time(g);
            break;
          case 3:
            ranking_m_time(g);
            break;
          case 4:
            spam_bot(g);
            break;
          case 5:
            break;
        }
    } while (c != 6);
}