#include <stdio.h>
#include <jrb.h>

typedef struct graph {
    JRB vertices;
    int nV;
    int nE;
} graph_t;

graph_t init_graph() {
    graph_t g;
    g.vertices = make_jrb();
    g.nV = 0;
    g.nE = 0;

    return g;
}

// return 1 if alredy in graph
int add_edge(graph_t g, int i, int j, int w) {
    JRB node_i = jrb_find_int(g.vertices, i);
    if (node_i) {
        JRB node_j = jrb_find_int(jval_v(node_i->val), j);
        if (node_j) {
            return 1;
        } else {
            jrb_insert_int(jval_v(node_i->val), j, new_jval_i(w));
            return 0;
        }
    } else {
        JRB node_j = make_jrb();
        jrb_insert_int(node_j, j, new_jval_i(w));

        jrb_insert_int(g.vertices, i, new_jval_v(node_j));
        return 0;
    }
}

// return weight
int get_edge(graph_t g, int i, int j) {
    JRB node_i = jrb_find_int(g.vertices, i);
    if (node_i) {
        JRB node_j = jrb_find_int(jval_v(node_i->val), j);
        if (node_j) {
            return jval_i(node_j->val);
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

void load_from_file(graph_t *g, const char *fn) {
    FILE *f = fopen(fn, "r");
    fscanf(f, "%d %d\n", &g->nV, &g->nE);

    int i, j, w;
    while (fscanf(f, "%d %d %d", &i, &j, &w) > 2) {
        add_edge(*g, i, j, w);
        add_edge(*g, j, i, w);
    }

    fclose(f);
}

void print_matrix(graph_t g) {
    int nv = g.nV;

    printf("%3s ", "");
    for (int i = 0; i < nv; ++i) {
        printf("%3d ", i + 1);
    }
    printf("\n");
    
    for (int i = 1; i <= nv; ++i) {
        printf("%3d ", i);
        for (int j = 1; j <= nv; ++j) {
            int w = get_edge(g, i, j);
            printf("%3d ", w);
        }
        printf("\n");
    }
}

void print_edge_list(graph_t g) {
    JRB node_i;
    jrb_traverse(node_i, g.vertices) {
        printf("%d: ", jval_i(node_i->key));

        JRB node_j, tree_i = jval_v(node_i->val);
        jrb_traverse(node_j, tree_i) {
            printf("%d ", jval_i(node_j->key));
        }
        printf("\n");
    }
}

void jogging_castle(graph_t g){
    JRB node_i; 
    jrb_traverse(node_i, g.vertices) {
        JRB node_j, tree_i = jval_v(node_i->val);
        int check = 0;
        jrb_traverse(node_j, tree_i){
            if(jval_i(node_j->val) >= 50) {
                check = 1;
            } else {
                check = 0;
                break;
            }
        }
        if (check) {
            printf("%d\n", jval_i(node_i->key));
        }
    }
}

void free_graph(graph_t g) {

}

int main() {
    graph_t g = init_graph();

    load_from_file(&g, "input.txt");
    print_matrix(g);

    print_edge_list(g);
    jogging_castle(g);

    free_graph(g);
}