#include <stdio.h>
#include "_string_oper.h"
#include <string.h>
#include <stdlib.h>


void freedata_String(void* data, void* content) {
    free(data);
}



CmpResult cmpdata_String(void* data_a, void* content_a, void* data_b, void* content_b) {
    const char* string_a = (char*)data_a;
    const char* string_b = (char*)data_b;
    return strcmp(string_a, string_b);
}

void* copydata_String(void* data, void* content) {
    const char* string = (char*)data;
    int len = strlen(string);
    char* newString = (char*)malloc((len+1)*sizeof(char));
    strcpy(newString, string);
    return newString;
}

void printdata_String(void* data, void* content) {
    printf("\"%s\"", (char*)data);
}

static Operation oper_String = {
    freedata_String,
    cmpdata_String,
    copydata_String,
    printdata_String,
    NULL,
    NULL
};


InfoOfData Info_String = {
    &oper_String,
    false
};


