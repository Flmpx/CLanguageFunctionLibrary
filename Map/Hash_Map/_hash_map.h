#ifndef _HASH_MAP_H
#define _HASH_MAP_H
#include <stdbool.h>
#define DEL -1
#define NONE 0
#define EXIST 1
#define NOT_FOUND -1
#define DIFFERENT -1
#define SAME 0

typedef unsigned long long ull;
typedef struct Data Data;


enum info {
    Warning = -1,
    None = 0,
    Success = 1
};


//每个相应的函数应该能够解析相应的字符串
typedef struct {
    char* thingOf_Free;
    char* thingOf_Hash;
    char* thingOf_Compare;
    char* thingOf_Copy;
    char* thingOf_Print;
} Otherthings;




//以下函数都需要自己提供

//释放void* data
typedef void (*_freedata)(void* data, char* thingOf_free);


//对void* data的内容进行hash的函数(hash函数必须返回)
typedef ull (*_hash)(void* data, char* thingOf_Hash);

//对void* data进行比较的函数
typedef int (*_compare)(void* data_a, void* data_b, char* thingOf_Compare);

//对void* data进行复制的函数
typedef void* (*_copy)(void* data, char* thingOf_Copy);

//对Data进行输出的函数
typedef void (*_print)(void* data, char* thingOf_Print);


//创建的这种类型的变量是不允许删除的(把他设置为全局变量),它代表的是某一种类型的相关操作函数
typedef struct Operation {
    _freedata freedata;
    _hash hash;
    _compare cmp;
    _copy copy;
    _print print;
} Operation;


//这是key和val的相关属性
struct Data {
    void* data;
    int type;
    //如果是同一种类型,那他们的操作函数因该都是相同的,所以直接用指针
    Operation* oper;
    Otherthings* others;
    bool isEmpty;
};

typedef struct Entry {
    bool isSingle;
    Data key;
    Data value;
    int state;
} Entry;

typedef struct Map {
    Entry* arr;
    int mod;
    int len;
    int size;
} Map;


#endif