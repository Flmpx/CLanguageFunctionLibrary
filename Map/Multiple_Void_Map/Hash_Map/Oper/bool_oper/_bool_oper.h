#ifndef _BOOL_OPER_H
#define _BOOL_OPER_H
#include "../../_hash_map.h"

/*
    注意:布尔类型一般做val,而不是key
*/


extern void freedata_Bool(void* data, void* content);


extern ull hashdata_Bool(void* data, void* content);


extern int cmpdata_Bool(void* data_a, void* content_a, void* data_b, void* content_b);


extern void* copydata_Bool(void* data, void* content);

extern void printdata_Bool(void* data, void* content);


extern Operation oper_Bool;

#endif