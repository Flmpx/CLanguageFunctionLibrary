#include <stdio.h>
#include <stdlib.h>
#include "../_hash_map.h"

void free_Int(void* data, char* thingsOf_free) {
    free(data);
}

ull hash_Int(void* data, char* thingOf_Hash) {
    int n = *(int*)data;
    return (ull)n;
}

int cmp_Int(void* data_a, void* data_b, char* thingOf_Compare) {
    return *(int*)data_a == *(int*)data_b ? SAME : DIFFERENT;
}


void* copy_Int(void* data, char* thingOf_Copy) {
    int* newdata = (int*)malloc(sizeof(int));
    *newdata = *(int*)data;
    return newdata;
}

void print_Int(void* data, char* thingOf_Print) {
    printf("%d", *(int*)data);
}

Operation oper_Int = {
    free_Int,
    hash_Int,
    cmp_Int,
    copy_Int,
    print_Int
};

Otherthings other_Int = {
    "", "", "", "", ""
};


