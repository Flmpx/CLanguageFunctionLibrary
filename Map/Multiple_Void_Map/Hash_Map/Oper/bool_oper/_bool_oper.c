#include <stdio.h>
#include <stdlib.h>
#include "_bool_oper.h"


void freedata_Bool(void* data, void* content) {
    free(data);
}

ull hashdata_Bool(void* data, void* content) {
    bool num = *(bool*)data;
    return num == true ? 99ull : 100ull;
}

CmpResult cmpdata_Bool(void* data_a, void* content_a, void* data_b, void* content_b) {
    bool num_a = *(bool*)data_a;
    bool num_b = *(bool*)data_b;
    return num_a == num_b ? SAME : DIFFERENT;
}

void* copydata_Bool(void* data, void* content) {
    bool* newNum = (bool*)malloc(sizeof(bool));
    *newNum = *(bool*)data;
    return newNum;
}

void printdata_Bool(void* data, void* content) {
    printf("%s", *(bool*)data == true ? "True" : "False");
}

static Operation oper_Bool = {
    freedata_Bool, 
    hashdata_Bool,
    cmpdata_Bool,
    copydata_Bool,
    printdata_Bool,
    NULL,
    NULL
};


InfoOfData Info_Bool = {
    &oper_Bool,
    false
};


