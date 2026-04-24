#ifndef _MULTIPLE_VOID_HASH_MAP_LIST_H
#define _MULTIPLE_VOID_HASH_MAP_LIST_H
#include <stdbool.h>
#define NOT_FOUND -1
typedef enum cmpresult {
    SAME = 0,
    DIFFERENT = 1,
} CmpResult;



typedef enum info {
    Warning = -1,
    None = 0,
    Success = 1
} InfoOfReturn;

//注:Data和Entry的空不能作为有效的内容,只是为了在出现问题时返回空

/*
使用方法:
    1 创建当前类型数据的所有操作函数
    2 把相关函数的指针整合成一个Operation类型的数据
    3 使用stackData函数和成Data类型(包括key和val)
    4 插入到散列表中
    5 每次使用完Map后必须释放掉Map,使用freeMap函数

注: 1 同一中类型的操作函数应该一致
    2 stackData函数返回的时自动变量,不可以free
    3 通过key等返回的Entry和Val都是malloc出来的,使用完记得释放,如果无法找到或者无法创建Data或者Entry,会输出提示信息,同时返回空Data或Entry
    4 content内容一般为结构体,比如二维动态数组content的应该为,注意要是指针
                        typedef struct {
                            int row;
                            int col;
                        } MetriArray;





*/

typedef unsigned long long ull;
typedef struct Data Data;




//以下函数都需要自己提供

/// @brief 释放void* data
typedef void (*_freedata)(void* data, void* content);


/// @brief 对void* data的内容进行hash的函数(hash函数必须返回ull类型的数据)
typedef ull (*_hashdata)(void* data, void* content);

/// @brief 对void* data进行比较的函数
typedef CmpResult (*_cmpdata)(void* data_a, void* content_a, void* data_b, void* content_b);

/// @brief 对void* data进行复制的函数
typedef void* (*_copydata)(void* data, void* content);

/// @brief 对Data进行输出的函数
typedef void (*_printdata)(void* data, void* content);


/// @brief 按自己的方式释放content
typedef void (*_freecontent)(void* content);


/// @brief 通过按自己的方式解析content内容,然后创建一个完全一样的
typedef void* (*_copycontent)(void* content);


/// @brief 创建的这种类型的变量是不允许删除的(把他设置为全局变量),它代表的是某一种类型的相关操作函数
typedef struct Operation {
    _freedata freedata;
    _hashdata hashdata;
    _cmpdata cmpdata;
    _copydata copydata;
    _printdata printdata;
    _copycontent copycontent;
    _freecontent freecontent;
} Operation;



typedef struct InfoOfData {
    //如果是同一种类型,那他们的操作函数因该都是相同的,所以直接用指针
    Operation* oper;
    bool hasContent;
} InfoOfData;

/// @brief 这是key和val的相关属性
struct Data {
    void* data;
    void* content;  //用于描述data数据的特点的
    InfoOfData* dataInfo;
    int type;
    bool isEmpty;
};

/// @brief 哈希表中的一个节点
typedef struct Entry {
    Data key;
    Data value;
    bool isEmpty;
} Entry;


typedef struct Node {
    struct Node* next;
    struct Node* prev;
    Entry entry;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} List;

/// @brief Map
typedef struct Map {
    List* arr;
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
extern InfoOfReturn insertKeyAndValInMap(Map* pMap, Data key, Data val);

/// @brief 通过key返回Data(会全部复制)
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0),除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern Data returnCopyValByKey(Map* pMap, Data key);

/// @brief 通过key返回Data(不会复制,主要用于修改val)
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0)
extern Data returnPtrValByKey(Map* pMap, Data key);

/// @brief 通过key返回Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return Entry数据,(如果为空Entry.state == NULL_IN_OUTER)除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern Entry returnCopyEntryByKey(Map* pMap, Data key);


/// @brief 判断释放含有该key
/// @param pMap Mpa类型指针
/// @param key key
/// @return 有就返回true,否则false
extern bool hasKeyInMap(Map* pMap, Data key);


/// @brief 通过key删除Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return 没找到返回0,删除成功返回1
extern InfoOfReturn delEntryByKey(Map* pMap, Data key);


/// @brief 将Data的数据整合在一起(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
/// @param data void* data指针
/// @param content 描述性信息, void* content
/// @param type 数据类型
/// @param dataInfo InfoOfData类型
/// @return 返回Data数据(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
extern Data stackData(void* data, void* content, int type, InfoOfData* dataInfo);



/// @brief 打印Data类型数据,包括Key和Val
/// @param data Data类型数据
/// @param tip 提示词,会显示的
extern void printData(Data data, char* tip);

/// @brief 打印Entry数据,会自动打印Key和val
/// @param entry entry数据
extern void printEntry(Entry entry);

/// @brief 打印Map中的所有数据
/// @param pMap Map类型数据指针
extern void printMap(Map* pMap);
#endif