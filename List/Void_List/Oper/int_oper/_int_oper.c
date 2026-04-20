#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "_int_oper.h"

void freedata_Int(void* data, void* content) {
    free(data);
}


int cmpdata_Int(void* data_a, void* content_a, void* data_b, void* content_b) {
    return *(int*)data_a == *(int*)data_b ? SAME : DIFFERENT;
}


void* copydata_Int(void* data, void* content) {
    int* newdata = (int*)malloc(sizeof(int));
    *newdata = *(int*)data;
    return newdata;
}

void printdata_Int(void* data, void* content) {
    printf("%d", *(int*)data);
}

static Operation oper_Int = {
    freedata_Int,
    cmpdata_Int,
    copydata_Int,
    printdata_Int,
    NULL,
    NULL,
};


InfoOfData Info_Int = {
    &oper_Int,
    false
};
