#ifndef _HASH_MAP_H
#define _HASH_MAP_H
#include <stdbool.h>
#define DEL_IN_MAP -1
#define NONE_IN_MAP 0
#define EXIST_IN_MAP 1
#define NOT_FOUND -1
#define DIFFERENT -1
#define SAME 0

//注:Data和Entry的空不能作为有效的内容,只是为了在出现问题时返回空

/*
使用方法:
    1 创建当前类型数据的所有操作函数
    2 把相关函数的指针整合成一个Operation类型的数据
    3 使用stackOthers函数合成描述性信息
    4 使用stackData函数和成Data类型(包括key和val)
    5 插入到散列表中
    6 每次使用玩Map后必须释放掉Map,使用freeMap函数

注: 1 同一中类型的操作函数应该一致
    2 stack函数返回的时自动变量,不可以free
    3 描述信息主要用与操作函数进行操作,操作函数中一般有解析该字符串的功能
      ---- 比如二维动态数组一般写成  2_3 表示2行3列 可用于打印,释放, 复制等
    4 通过key等返回的Entry和Val都是malloc出来的,使用完记得释放,如果无法找到或者无法创建Data或者Entry,会输出提示信息,同时返回空Data或Entry
    5 描述性字符串不可以为NULL,只能为""




*/
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
    bool isEmpty;
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
    Otherthings others;
    bool isEmpty;
};

/// @brief 哈希表中的一个节点
typedef struct Entry {
    Data key;
    Data value;
    int state;
    bool isEmpty;
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


/// @brief 释放掉Data数据
/// @param data Data数据类型指针
extern void freeData(Data* data);


/// @brief 释放掉Entry数据
/// @param entry Entry类型指针
extern void freeEntry(Entry* entry);

/// @brief 删除Map;
/// @param pMap Map类型指针
extern void freeMap(Map* pMap);

/// @brief 插入新的key和value
/// @param pMap Mpa类型指针
/// @param key key
/// @param val value
/// @return 插入成功返回1
extern int insertEntryInMap(Map* pMap, Data key, Data val);

/// @brief 通过key返回Data
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0),除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern Data returnValByKey(Map* pMap, Data key);

/// @brief 通过key返回Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return Entry数据,(如果为空Entry.state == NULL_IN_OUTER)除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern Entry returnEntryByKey(Map* pMap, Data key);


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


/// @brief 将Data的数据整合在一起(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
/// @param data void* data指针
/// @param type 数据类型
/// @param oper 操作函数指针
/// @param others others数据,通过intergrateOthers函数获得
/// @return 返回Data数据(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
extern Data stackData(void* data, int type, Operation* oper, Otherthings others);

/// @brief 将Others的数据整合在一起(注意:这个Otherthings数据里面的不是动态分配的,不可以使用free函数释放)
/// @param thingOf_Free free的描述性字符串
/// @param thingOf_Hash hash的描述性字符串
/// @param thingOf_Compare cmp的描述性字符串
/// @param thingOf_Copy copy的描述性字符串
/// @param thingOf_Print print的描述性字符串
/// @return 返回Otherthings数据(注意:这个Otherthings数据里面的不是动态分配的,不可以使用free函数释放)
extern Otherthings stackOthers(char* thingOf_Free, char* thingOf_Hash, char* thingOf_Compare, char* thingOf_Copy, char* thingOf_Print);
#endif