#ifndef _MULTIPLE_VOID_MAP_LIST_H
#define _MULTIPLE_VOID_MAP_LIST_H
#include <stdbool.h>
#include "../../../_void_base.h"

/// @brief 哈希表中的一个节点
typedef struct _MEntryWithList {
    _MData key;
    _MData value;
    bool isEmpty;
} _MEntryWithList;


typedef struct MultiNodeInMap {
    struct MultiNodeInMap* next;
    struct MultiNodeInMap* prev;
    _MEntryWithList entry;
} MultiNodeInMap;

typedef struct {
    MultiNodeInMap* head;
    MultiNodeInMap* tail;
    int size;
} MultiListInMap;

/// @brief _MMapWithList
typedef struct _MMapWithList {
    MultiListInMap* arr;
    int mod;
    int len;
    int size;
} _MMapWithList;


/// @brief 初始化Map
/// @param pMap Mpa类型指针
extern void initMMapwithList(_MMapWithList* pMap);


/// @brief 释放掉Data数据
/// @param data Data数据类型指针
extern void freeDataInMMapWithList(_MData* data);


/// @brief 释放掉Entry数据
/// @param entry Entry类型指针
extern void freeEntryInMMapWithList(_MEntryWithList* entry);

/// @brief 删除Map;
/// @param pMap Map类型指针
extern void freeMMapWithList(_MMapWithList* pMap);

/// @brief 插入新的key和value
/// @param pMap Mpa类型指针
/// @param key key
/// @param val value
/// @return 插入成功返回1
extern InfoOfReturn insertKeyAndValInMMapWithList(_MMapWithList* pMap, _MData key, _MData val);

/// @brief 通过key返回Data(会全部复制)
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0),除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern _MData getCopyValByKeyInMMapWithList(_MMapWithList* pMap, _MData key);

/// @brief 通过key返回Data(不会复制,主要用于修改val)
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0)
extern _MData getPtrValByKeyInMMapWithList(_MMapWithList* pMap, _MData key);

/// @brief 通过key返回Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return Entry数据,(如果为空Entry.state == NULL_IN_OUTER)除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern _MEntryWithList getCopyEntryByKeyInMMapWithList(_MMapWithList* pMap, _MData key);


/// @brief 判断释放含有该key
/// @param pMap Mpa类型指针
/// @param key key
/// @return 有就返回true,否则false
extern bool hasKeyInMMapWithList(_MMapWithList* pMap, _MData key);


/// @brief 通过key删除Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return 没找到返回0,删除成功返回1
extern InfoOfReturn delEntryByKeyInMMapWithList(_MMapWithList* pMap, _MData key);


/// @brief 将Data的数据整合在一起(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
/// @param data void* data指针
/// @param content 描述性信息, void* content
/// @param type 数据类型
/// @param dataInfo InfoOfData类型
/// @return 返回Data数据(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
extern _MData stackDataInMMapWithList(void* data, void* content, int type, InfoOfData* dataInfo);



/// @brief 打印Data类型数据,包括Key和Val
/// @param data Data类型数据
/// @param tip 提示词,会显示的
extern void printDataInMMapWithList(_MData data, char* tip);

/// @brief 打印Entry数据,会自动打印Key和val
/// @param entry entry数据
extern void printEntryInMMapWithList(_MEntryWithList entry);

/// @brief 打印Map中的所有数据
/// @param pMap Map类型数据指针
extern void printMMapWithList(_MMapWithList* pMap);
#endif