#include <stdio.h>
#include <stdlib.h>

typedef struct struct_t {
    int i;
    float f;
    char c;
} struct_t;

typedef union union_t {
    int i;
    float f;
    char c;
} union_t;

int main() {
    struct_t str;
    union_t uni;

    printf("\nunion declare like struct\n");
    printf("is a set of multiple type too\n");

    printf("\nSize of struct: %ld bytes\n", sizeof(str));
    printf("Size of union: %ld bytes\n", sizeof(uni));

    printf("\nSee above union's size is the max size of element in union\nand struct's size is the sum of elements's size\n");

    str.i = 1;
    str.f = 2.3;
    str.c = '4';

    printf("\nsturct's integer value: %d\n", str.i);
    printf("sturct's float value: %f\n", str.f);
    printf("sturct's char value: %c\n\n", str.c);

    uni.i = 1;
    uni.f = 2.3;
    uni.c = '4';

    printf("union's integer value: %d\n", uni.i);
    printf("union's float value: %f\n", uni.f);
    printf("union's char value: %c\n", uni.c);

    printf("\nThe value of union's now is wrong, why?\n");
    printf("Because of the structure of union\n");

    printf("\nIn the memories, structure of struct sound be like that:\n");
    printf("| ---- | ---- | - |      (each `-` is one byte)\n");
    printf("  ^int   ^float ^char\n");

    printf("\nBut union is:\n");
    printf("| ---- |\n");
    printf("  ^int\n");
    printf("  ^float\n");
    printf("  ^char\n");

    printf("\nSee, all the pointer of union element point to the start of union,\n"
           "not like struct, they have the sequence\n");
    printf("That is the reason why only the last seted element has correct value\n");

    printf("\nBut now, I'm going to use union like this:\n");

    uni.i = 1;
    printf("union's integer value: %d\n", uni.i);

    uni.f = 2.3;
    printf("union's float value: %f\n", uni.f);

    uni.c = '4';
    printf("union's char value: %c\n", uni.c);

    printf("\nSee, the values now are corrected\n");
    return 0;
}