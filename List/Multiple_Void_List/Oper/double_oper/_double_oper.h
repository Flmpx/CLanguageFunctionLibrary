#ifndef _DOUBLE_OPER_H
#define _DOUBLE_OPER_H
#include "../../multiple_void_list.h"
extern void freedata_Double(void* data, void* content);



extern CmpResult cmpdata_Double(void* data_a, void* content_a, void* data_b, void* content_b);


extern void* copydata_Double(void* data, void* content);


extern void* printdata_Double(void* data, void* content);

extern InfoOfData Info_Double;

#endif