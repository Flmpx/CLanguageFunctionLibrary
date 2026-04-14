#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../_hash_map_list.h"

static const char* format_Double = "double%.12edouble"; 


static const ull mod = 1000000007;
static const ull base = 131;

void freedata_Double(void* data, void* content) {
    free(data);
}


ull hashdata_Double(void* data, void* content) {
    char string[101];
    sprintf(string, format_Double, *(double*)data);
    int len = strlen(string);
    ull result = 0;
    for (int i = 0; i < len; i++) {
        result = (result * base % mod + string[i] + 199)%mod;
    }
    return result;
}

int cmpdata_Double(void* data_a, void* content_a, void* data_b, void* content_b) {
    char string_a[101], string_b[101];
    sprintf(string_a, format_Double, *(double*)data_a);
    sprintf(string_b, format_Double, *(double*)data_b);
    return strcmp(string_a, string_b);
}


void* copydata_Double(void* data, void* content) {
    double* newDouble = (double*)malloc(sizeof(double));
    memcpy(newDouble, (double*)data, sizeof(double));
    return newDouble;
}

void printdata_Double(void* data, void* content) {
    double num = *(double*)data;
    printf("%g", num);
}

Operation oper_Double = {
    freedata_Double,
    hashdata_Double,
    cmpdata_Double,
    copydata_Double,
    printdata_Double,
    NULL,
    NULL
};