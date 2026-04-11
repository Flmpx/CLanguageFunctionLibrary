#ifndef _INT_OPER_H
#define _INT_OPER_H
#include "../_hash_map.h"
extern void free_Int(void* data, char* thingsOf_free);


extern ull hash_Int(void* data, char* thingOf_Hash);


extern int cmp_Int(void* data_a, void* data_b, char* thingOf_Compare);

extern void* copy_Int(void* data, char* thingOf_Copy);

extern void print_Int(void* data, char* thingOf_Print);


extern Operation oper_Int;

extern Otherthings other_Int;


#endif