#ifndef _INT_OPER_H
#define _INT_OPER_H
#include "../../_multiple_void_hash_map_list.h"
extern void freedata_Int(void* data, void* content);


extern ull hashdata_Int(void* data, void* content);


extern int cmpdata_Int(void* data_a, void* content_a, void* data_b, void* content_b);

extern void* copydata_Int(void* data, void* content);

extern void printdata_Int(void* data, void* content);


extern InfoOfData Info_Int;


#endif