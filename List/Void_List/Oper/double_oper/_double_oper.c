#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "_double_oper.h"

static const char* format_Double = "double%.12edouble"; 


void freedata_Double(void* data, void* content) {
    free(data);
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

static Operation oper_Double = {
    freedata_Double,
    cmpdata_Double,
    copydata_Double,
    printdata_Double,
    NULL,
    NULL
};




InfoOfData Info_Double = {
    &oper_Double,
    false
};