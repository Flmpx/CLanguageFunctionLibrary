#ifndef _HASH_MAP_LIST_H
#define _HASH_MAP_LIST_H
#include <stdbool.h>
#define NOT_FOUND -1
#define DIFFERENT -1
#define SAME 0

//注:Data和Entry的空不能作为有效的内容,只是为了在出现问题时返回空

/*
使用方法:
    1 创建当前类型数据的所有操作函数
    2 把相关函数的指针整合成一个Operation类型的数据
    3 将这个Operation类型的指针和是否有content数据存入一个InfoOfData类型数据种
    4 初始化Map时会让写入InfoOfData类型的数据,按需写,注意这是直接写死了这个Map的key和val的类型
    4 插入到散列表中
    5 每次使用完Map后必须释放掉Map,使用freeMap函数

注: 1 同一中类型的操作函数应该一致
    3 通过key等返回的Entry和Val(Data类型)都是malloc出来的,使用完记得释放,如果无法找到或者无法创建Data或者Entry,会输出提示信息,同时返回空Data或Entry
    4 content内容一般为结构体,比如二维动态数组content的应该为,注意要是指针
                        typedef struct {
                            int row;
                            int col;
                        } MetriArray;





*/

typedef unsigned long long ull;
typedef struct Data Data;


enum info {
    Warning = -1,
    None = 0,
    Success = 1
};

//以下函数都需要自己提供

/// @brief 释放void* data
typedef void (*_freedata)(void* data, void* content);


/// @brief 对void* data的内容进行hash的函数(hash函数必须返回ull类型的数据)
typedef ull (*_hashdata)(void* data, void* content);

/// @brief 对void* data进行比较的函数
typedef int (*_cmpdata)(void* data_a, void* content_a, void* data_b, void* content_b);

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


/// @brief 这是key和val的相关属性
struct Data {
    void* data;
    void* content;  //用于描述data数据的特点的
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

typedef struct InfoOfData {
    //如果是同一种类型,那他们的操作函数因该都是相同的,所以直接用指针
    Operation* oper;
    bool hasContent;
} InfoOfData;


/// @brief Map
typedef struct Map {
    List* arr;
    InfoOfData keyInfo;
    InfoOfData valInfo;
    int mod;
    int len;
    int size;
} Map;

/// @brief 初始化Map
/// @param pMap Map类型数据指针
/// @param keyInfo key的InfoOfData
/// @param valInfo val的InfoOfData
extern void initializeMap(Map* pMap, InfoOfData keyInfo, InfoOfData valInfo);


/// @brief 释放Data类型数据
/// @param data Data类型数据指针
/// @param infoOfKeyOrVal 要释放的Data类型数据的InfoOfData,主要用于释放void* data和void* content
extern void freeData(Data* data, InfoOfData infoOfKeyOrVal);

/// @brief 释放Entry类型数据
/// @param entry Entry类型数据指针
/// @param pMap 选择Map类型指针,以确定是那个Map的Entry类型
extern void freeEntry(Entry* entry, Map* pMap);

/// @brief 释放Map
/// @param pMap Map类型数据指针
extern void freeMap(Map* pMap);


/// @brief 插入key和val到Map中
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content,如果没有输入NULL
/// @param valdata val
/// @param valcontent content, 如果没有输入NULL
/// @return 插入成功返回1, 内存分配失败返回-1
extern int insertKeyAndValInMap(Map* pMap, void* keydata, void* keycontent, void* valdata, void* valcontent);

/// @brief 通过key返回Data类型数据(会自动创建一份,用完记得释放)
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Data, 如果没有返回空Data, 是否为空Data,使用Data.isEmpty来判断, 建议先使用hasKeyInMap进行判断
extern Data returnCopyValByKey(Map* pMap, void* keydata, void* keycontent);


/// @brief 通过key返回Data类型数据(不会创建一份,主要用于修改void* data的内容)
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Data, 如果没有返回空Data, 是否为空Data,使用Data.isEmpty来判断
extern Data returnPtrValByKey(Map* pMap, void* keydata, void* keycontent);

/// @brief 通过key返回Entry类型数据
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Entry, 如果没有返回空Entry, 是否为空Entry,使用Entry.isEmpty来判断, 建议先使用hasKeyInMap进行判断
extern Entry returnCopyEntryByKey(Map* pMap, void* keydata, void* keycontent);

/// @brief 判断key是否在Map中
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果存在返回true, 否则false
extern bool hasKeyInMap(Map* pMap, void* keydata, void* keycontent);

/// @brief 通过key来删除Map中对应的元素
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return Map为空返回-1, 没找到返回0, 删除成功返回1
extern int delEntryByKey(Map* pMap, void* keydata, void* keycontent);

/// @brief 打印Data类型数据
/// @param data Data类型数据
/// @param tip 提示次,比如[key: ...]
/// @param InfoOfKeyOrVal 当前数据类型的InfoOfData
extern void printData(Data data, char* tip, InfoOfData InfoOfKeyOrVal);

/// @brief 打印Entry数据
/// @param entry Entry数据类型
/// @param pMap Map类型指针, 用于判断是哪个Map的Entry
extern void printEntry(Entry entry, Map* pMap);

/// @brief 打印整个Map的数据
/// @param pMap Map类型指针
extern void printMap(Map* pMap);
#endif