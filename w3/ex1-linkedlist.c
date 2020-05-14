#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define scan(...) scanf(__VA_ARGS__); \
                  while(getchar() != '\n');

typedef struct PhoneEntry {
    char name[50];
    long phone;
} PhoneEntry;

typedef struct PhoneBook {
    PhoneEntry val;
    struct PhoneBook *next;
} PhoneBook;

typedef struct PhoneList {
    PhoneBook *first, *last;
    long size;
} PhoneList;

void init(PhoneList *pl) {
    pl->first = pl->last = 0;
    pl->size = 0;
}

int exited(PhoneList *pl, const char *name) {
    if (!pl) return 0;
    for (PhoneBook *i = pl->first; i; i = i->next) {
        if (!strcmp(i->val.name, name)) return 1;
    }
    return 0;
}

void add(PhoneList *pl, const char *name, long phone) {
    if (exited(pl, name)) return;
    if (pl->first) {
        pl->last->next = malloc(sizeof(PhoneBook));
        pl->last = pl->last->next;
    } else {
        pl->first = pl->last = malloc(sizeof(PhoneBook));
    }
    pl->last->val.phone = phone;
    strcpy(pl->last->val.name, name);
    pl->last->next = NULL;
    pl->size += 1;
}

void addMore(PhoneList *pl) {
    char name[80] = "";
    long phone = 0;
    do {
        printf("Name: ");
        scan("%[^\n]s", name);
        printf("Phone: ");
        scan("%ld", &phone);
        add(pl, name, phone);
        printf("\nMore?\n1. yes\n0. no\n");
        int c = 0;
        scan("%d", &c);
        if (!c) break;
    } while (1);
}

void freeList(PhoneList *pl) {
    PhoneBook *tmp = pl->first;
    while (tmp) {
        PhoneBook *f = tmp;
        tmp = tmp->next;
        free(f);
    }
    pl->first = pl->last = NULL;
    pl->size = 0;
}

void load(PhoneList *pl, const char *fn) {
    FILE *f = fopen(fn, "r");
    if (!f) {
        printf("Can't open file %s\n", fn);
        return;
    }
    char line[100];
    char name[80] = "";
    long phone = 0, size = 0;
    fscanf(f, "%ld\n", &size);
    while (size) {
        fgets(line, 99, f);
        int i = 0;
        while (i < 99 & line[i] != '|') ++i;
        line[i] = 0;
        sscanf(line + i + 1, "%ld", &phone);
        add(pl, line, phone);
        --size;
    }
    fclose(f);
}

void save(PhoneList *pl) {
    FILE *f = fopen("contacts.txt", "w");
    fprintf(f, "%ld\n", pl->size);
    for (PhoneBook *i = pl->first; i; i = i->next) {
        fprintf(f, "%s|%ld\n", i->val.name, i->val.phone);
    }
    fclose(f);
}

void cpLower(char *s1, const char *s2) {
    int i = 0;
    for (; s2[i]; ++i) s1[i] = tolower(s2[i]);
    s1[i] = '\0';
}

PhoneBook *find(PhoneList *pl, const char *name) {
    char iname1[50] = "", iname2[50] = "";
    for (PhoneBook *i = pl->first; i; i = i->next) {
        cpLower(iname1, i->val.name);
        cpLower(iname2, name);
        char *found = strstr(iname1, iname2);
        if (found) return i;
    }
    return NULL;
}

void prt(PhoneList *pl) {
    for (PhoneBook *i = pl->first; i; i = i->next) {
        printf("%s|%ld\n", i->val.name, i->val.phone);
    }
    printf("\n");
}
int main() {
    PhoneList pl = {0};
    // addMore(&pl);
    load(&pl, "contacts.txt");
    prt(&pl);

    char ln[] = "tien dung";
    PhoneBook *found = find(&pl, ln);
    if (found) printf("%s has phone number is: %ld\n", ln, found->val.phone);
    else printf("%s don's have in this phone list\n", ln);
    save(&pl);
    freeList(&pl);
    return 0;
}