#include <stdio.h>
#include "_string_oper.h"
#include "../../_hash_map_list.h"
#include <string.h>
#include <stdlib.h>

static ull mod = 1000000007;
static ull base = 131;

void freedata_String(void* data, void* content) {
    free(data);
}


ull hashdata_String(void* data, void* content) {
    const char* string = (char*)data;
    ull result = 0;
    int len = strlen(string);
    for (int i = 0; i < len; i++) {
        result = (result * base % mod + string[i] + 199)%mod;
    }
    return result;
}

int cmpdata_String(void* data_a, void* content_a, void* data_b, void* content_b) {
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
    printf("%s", (char*)data);
}

Operation oper_String = {
    freedata_String,
    hashdata_String,
    cmpdata_String,
    copydata_String,
    printdata_String,
    NULL,
    NULL
};



