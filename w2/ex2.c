#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum DataType { CHAR, INTEGER, FLOAT_POINT, DOUBLE_POINT, STRING } DataType ;

typedef union DataValue {
    char v_char;
    int v_int;
    float v_float;
    double v_double;
    char* v_string;
} DataValue;

typedef struct DataNode {
    DataType type;
    DataValue value;
} DataNode;

void setData(DataNode* ptr, void *value, DataType datatype) {
    ptr->type= datatype;//read_some_input(&temp);
    switch(ptr->type) {
        case INTEGER: ptr->value.v_int = *((int*)value); break;
        case FLOAT_POINT: ptr->value.v_float = *((float*)value); break;
        case STRING: ptr->value.v_string = (char*)value; break;
    }   
}

void printDataNode(DataNode* ptr) {
   printf("I am a ");
   switch(ptr->type) {
       case INTEGER: printf("Integer with value %d", ptr->value.v_int); break;
       case FLOAT_POINT: printf("Float with value %f", ptr->value.v_float); break;
       case STRING: printf("String with value %s", ptr->value.v_string); break;
       case DOUBLE_POINT: printf("Double with value %lf", ptr->value.v_double); break;
       case CHAR: printf("Char with value %c", ptr->value.v_char); break;
   }
   printf("\n");
}


int compareDataNode(DataNode *node1, DataNode *node2) {
    switch(node1->type) {
        case CHAR: case INTEGER:
            return node1->value.v_int - node2->value.v_int;
        case FLOAT_POINT:
            return node1->value.v_float - node2->value.v_float;
        case DOUBLE_POINT:
            return node1->value.v_double - node2->value.v_double;
        case STRING:
            return strcmp(node1->value.v_string, node2->value.v_string);
        default:
            return node1->value.v_int - node2->value.v_int;
    }
}

int seqSearchDataList(DataNode *list, int size, void *key, DataType type) {
    for (int i = 0; i < size; ++i) {
        if (list[i].type != type) continue;
        DataNode tmp;
        setData(&tmp, key, type);
        if (compareDataNode(&tmp, list + i) == 0) return i;
    }
    return -1;
}

int main() {
    int size = 5;

    DataNode *list = (DataNode*)malloc(size * sizeof(DataNode));

    char str[] = "Sherly";
    setData(list, str, STRING);

    int one = 1;
    setData(list + 1, &one, INTEGER);

    float zero = 0;
    setData(list + 2, &zero, FLOAT_POINT);

    double zero2 = 0;
    setData(list + 3, &zero2, DOUBLE_POINT);

    char c = '1';
    setData(list + 4, &c, CHAR);

    for (int i = 0; i < size; ++i) {
        printDataNode(list + i);
    }

    float key = 0;
    int found = seqSearchDataList(list, size, &key, FLOAT_POINT);

    printf("\n%s %g type of float in list with index %d\n", found > 0 ? "found" : "not found", key, found);

    return 0;
}