// cai dat r-b tree
#include "data.h"
#define RED 0
#define BLACK 1

struct node{
	char key[100];  //key tong quat
	PhoneEntry value;
	
	// r-b tree data
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

/* Global, since all function will access them */
struct node *ROOT;
struct node *NILL;

void left_rotate(struct node *x);
void right_rotate(struct node *x);
void tree_print(struct node *x);
void red_black_insert(char * key, PhoneEntry value);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(const char * key);
struct node *tree_minimum(struct node *x);
void red_black_transplant(struct node *u, struct node *v);
void red_black_delete(struct node *z);
void red_black_delete_fixup(struct node *x);