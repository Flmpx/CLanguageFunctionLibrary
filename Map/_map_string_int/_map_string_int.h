#ifndef _MAP_STRING_INT_H
#define _MAP_STRING_INT_H
#include <stdbool.h>
#define NOT_FOUND -1
#define DIFFERENT -1
#define SAME 0
typedef unsigned long long ull;


enum info {
    Warning = -1,
    None = 0,
    Success = 1
};

typedef struct Entry {
    char* key;
    int val;
    bool isEmpty;
} Entry;


typedef struct Node {
    struct Node* prev;
    struct Node* next;
    Entry entry;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} List;

typedef struct Map {
    List* arr;
    int size;
    int len;
    int mod;
} Map;

/// @brief 初始化Map
/// @param pMap Map类型数据指针
extern void initializeMap(Map* pMap);


/// @brief 将字符串key和整形val插入到Map中
/// @param pMap Map类型数据指针
/// @param key 字符串key
/// @param val 整形val
/// @return 插入成功返回1 | 内存分配失败返回-1
extern int insertKeyAndValInMap(Map* pMap, char* key, int val);


/// @brief 判断key是否在Map
/// @param pMap Map类型指针
/// @param key string_key
/// @return 有--> true | 没--> false
extern bool hasKeyInMap(Map* pMap, char* key);

/// @brief 通过key返回val
/// @param pMap Map类型数据指针
/// @param key string_key
/// @return int类型数据val(其中-1代表没找到)
extern int returnValByKey(Map* pMap, char* key);



/// @brief 通过key返回Entry()
/// @param pMap Map类型数据指针
/// @param key string_key
/// @return 返回Entry类型数据, 如果没找到,Entry.isEmpty = true
extern Entry returnEntryByKey(Map* pMap, char* key);




/// @brief 通过key来删除
/// @param pMap Map类型数据指针
/// @param key string_key
/// @return 若没找到返回0, Map为空返回-1, 删除成功返回1
extern int delEntryByKey(Map* pMap, char* key);

/// @brief 打印Entry类型数据
/// @param entry Entry类型数据
extern void printEntry(Entry entry);

/// @brief 打印Map所有数据
/// @param pMap Map类型数据指针
extern void printMap(Map* pMap);


/// @brief 清空Map
/// @param pMap Map类型数据指针
extern void freeMap(Map* pMap);

/// @brief 清空Entry
/// @param entry Entry类型数据
extern void freeEntry(Entry entry);


#endif