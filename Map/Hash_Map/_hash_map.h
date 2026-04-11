#ifndef _HASH_MAP_H
#define _HASH_MAP_H
#include <stdbool.h>
#define NULL_IN_OUTER -3
#define EXIST_IN_OUTER -2
#define DEL_IN_MAP -1
#define NONE_IN_MAP 0
#define EXIST_IN_MAP 1
#define NOT_FOUND -1
#define DIFFERENT -1
#define SAME 0

//注:Data和Entry的空不能作为有效的内容,只是为了在出现问题时返回空


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

/// @brief 释放void* data
typedef void (*_freedata)(void* data, char* thingOf_free);


/// @brief 对void* data的内容进行hash的函数(hash函数必须返回ull类型的数据)
typedef ull (*_hash)(void* data, char* thingOf_Hash);

/// @brief 对void* data进行比较的函数
typedef int (*_compare)(void* data_a, void* data_b, char* thingOf_Compare);

/// @brief 对void* data进行复制的函数
typedef void* (*_copy)(void* data, char* thingOf_Copy);

/// @brief 对Data进行输出的函数
typedef void (*_print)(void* data, char* thingOf_Print);


/// @brief 创建的这种类型的变量是不允许删除的(把他设置为全局变量),它代表的是某一种类型的相关操作函数
typedef struct Operation {
    _freedata freedata;
    _hash hash;
    _compare cmp;
    _copy copy;
    _print print;
} Operation;


/// @brief 这是key和val的相关属性
struct Data {
    void* data;
    int type;
    //如果是同一种类型,那他们的操作函数因该都是相同的,所以直接用指针
    Operation* oper;
    Otherthings* others;
    bool isEmpty;
};

/// @brief 哈希表中的一个节点
typedef struct Entry {
    Data key;
    Data value;
    int state;
} Entry;

/// @brief Map
typedef struct Map {
    Entry* arr;
    int mod;
    int len;
    int size;
} Map;


/// @brief 初始化Map
/// @param pMap Mpa类型指针
extern void initializeMap(Map* pMap);

/// @brief 释放掉others的描述性字符串
/// @param others Otherthings类型的指针
extern void freeOthers(Otherthings* others);


/// @brief 释放掉Data数据
/// @param data Data数据类型指针
extern void freeData(Data* data);


/// @brief 释放掉Entry数据
/// @param entry Entry类型指针
extern void freeEntry(Entry* entry);

/// @brief 删除Map;
/// @param pMap Map类型指针
extern void freeMap(Map* pMap);


/// @brief 复制一份Data(描述性字符串会复制一份,但操作函数不会)
/// @param oldData 旧Data数据
/// @return Data数据(返回后的Data一定要检查一下是否为空,若为空,说明内存分配失败或者oldData本来就是空的)
extern Data copyData(Data oldData);

/// @brief 复制一份Entry(描述性字符串会复制一份,但操作函数不会)
/// @param oldEntry 旧Entry数据
/// @return Entry数据
extern Entry copyEntry(Entry oldEntry);

/// @brief 插入新的key和value
/// @param pMap Mpa类型指针
/// @param key key
/// @param val value
/// @return 插入成功返回1
extern int insertEntryInMap(Map* pMap, Data key, Data val);

/// @brief 通过key返回Data
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern Data returnValByKey(Map* pMap, Data key);

/// @brief 判断释放含有该key
/// @param pMap Mpa类型指针
/// @param key key
/// @return 有就返回true,否则false
extern bool hasKeyInMap(Map* pMap, Data key);


/// @brief 通过key删除Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return 没找到返回0,删除成功返回1
extern int delEntryByKey(Map* pMap, Data key);


#endif