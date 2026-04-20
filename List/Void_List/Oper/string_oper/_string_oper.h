#ifndef _STRING_OPER_H
#define _STRING_OPER_H
#define DIFFERENT -1
#define SAME 0
#include "../../void_list.h"



extern void freedata_String(void* data, void* content);




extern int cmpdata_String(void* data_a, void* content_a, void* data_b, void* content_b);



extern void* copydata_String(void* data, void* content);


extern void printdata_String(void* data, void* content);



extern InfoOfData Info_String;

#endif