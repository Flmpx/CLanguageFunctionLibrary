#ifndef _SINGLE_VOID_MAP_LIST_H
#define _SINGLE_VOID_MAP_LIST_H
#include <stdbool.h>
#include "../../../_void_base.h"

/// @brief 哈希表中的一个节点
typedef struct _SEntryWithList {
    _SData key;
    _SData value;
    bool isEmpty;
} _SEntryWithList;


typedef struct SingleNodeInMap {
    struct SingleNodeInMap* next;
    struct SingleNodeInMap* prev;
    _SEntryWithList entry;
} SingleNodeInMap;

typedef struct {
    SingleNodeInMap* head;
    SingleNodeInMap* tail;
    int size;
} SingleListInMap;




/// @brief _SMapWithList
typedef struct _SMapWithList {
    SingleListInMap* arr;
    InfoOfData* keyInfo;
    InfoOfData* valInfo;
    int mod;
    int len;
    int size;
} _SMapWithList;

/// @brief 初始化Map
/// @param pMap Map类型数据指针
/// @param keyInfo key的InfoOfData
/// @param valInfo val的InfoOfData
extern void initSMapWithList(_SMapWithList* pMap, InfoOfData* keyInfo, InfoOfData* valInfo);


/// @brief 释放Data类型数据
/// @param data Data类型数据指针
/// @param infoOfKeyOrVal 要释放的Data类型数据的InfoOfData,主要用于释放void* data和void* content
extern void freeDataInSMapWithList(_SData* data, InfoOfData* infoOfKeyOrVal);

/// @brief 释放Entry类型数据
/// @param entry Entry类型数据指针
/// @param pMap 选择Map类型指针,以确定是那个Map的Entry类型
extern void freeEntryInSMapWithList(_SEntryWithList* entry, _SMapWithList* pMap);

/// @brief 释放Map
/// @param pMap Map类型数据指针
extern void freeSMapWithList(_SMapWithList* pMap);


/// @brief 插入key和val到Map中
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content,如果没有输入NULL
/// @param valdata val
/// @param valcontent content, 如果没有输入NULL
/// @return 插入成功返回1, 内存分配失败返回-1
extern InfoOfReturn insertKeyAndValInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent, void* valdata, void* valcontent);

/// @brief 通过key返回Data类型数据(会自动创建一份,用完记得释放)
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Data, 如果没有返回空Data, 是否为空Data,使用Data.isEmpty来判断, 建议先使用hasKeyInMap进行判断
extern _SData getCopyValByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);


/// @brief 通过key返回Data类型数据(不会创建一份,主要用于修改void* data的内容)
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Data, 如果没有返回空Data, 是否为空Data,使用Data.isEmpty来判断
extern _SData getPtrValByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);

/// @brief 通过key返回Entry类型数据
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Entry, 如果没有返回空Entry, 是否为空Entry,使用Entry.isEmpty来判断, 建议先使用hasKeyInMap进行判断
extern _SEntryWithList getCopyEntryByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);

/// @brief 判断key是否在Map中
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果存在返回true, 否则false
extern bool hasKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);

/// @brief 通过key来删除Map中对应的元素
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return Map为空返回-1, 没找到返回0, 删除成功返回1
extern InfoOfReturn delEntryByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);

/// @brief 打印Data类型数据
/// @param data Data类型数据
/// @param tip 提示次,比如[key: ...]
/// @param InfoOfKeyOrVal 当前数据类型的InfoOfData
extern void printDataInSMapWithList(_SData data, char* tip, InfoOfData* InfoOfKeyOrVal);

/// @brief 打印Entry数据
/// @param entry Entry数据类型
/// @param pMap Map类型指针, 用于判断是哪个Map的Entry
extern void printEntryInSMapWithList(_SEntryWithList entry, _SMapWithList* pMap);

/// @brief 打印整个Map的数据
/// @param pMap Map类型指针
extern void printSMapWithList(_SMapWithList* pMap);
#endif