#ifndef _MULTIPLE_VOID_MAP_OA_H
#define _MULTIPLE_VOID_MAP_OA_H
#include <stdbool.h>
#include "../../../_void_base.h"

/// @brief 哈希表中的一个节点
typedef struct _MEntryWithOA {
    _MData key;
    _MData value;
    int state;
    bool isEmpty;
} _MEntryWithOA;

/// @brief _MMapWithOA
typedef struct _MMapWithOA {
    _MEntryWithOA* arr;
    int mod;
    int len;
    int size;
} _MMapWithOA;


/// @brief 初始化Map
/// @param pMap Mpa类型指针
extern void initMMapWithOA(_MMapWithOA* pMap);


/// @brief 释放掉Data数据
/// @param data Data数据类型指针
extern void freeDataInMMapWithOA(_MData* data);


/// @brief 释放掉Entry数据
/// @param entry Entry类型指针
extern void freeEntryInMMapWithOA(_MEntryWithOA* entry);

/// @brief 删除Map;
/// @param pMap Map类型指针
extern void freeMMapWithOA(_MMapWithOA* pMap);

/// @brief 插入新的key和value
/// @param pMap Mpa类型指针
/// @param key key
/// @param val value
/// @return 插入成功返回1
extern InfoOfReturn insertKeyAndValInMMapWithOA(_MMapWithOA* pMap, _MData key, _MData val);

/// @brief 通过key返回Data(全部内容会复制一遍)
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0),除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern _MData getCopyValByKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);

/// @brief 通过key返回Data(内容不会复制,主要用于修改val)
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0)
extern _MData getPtrValByKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);


/// @brief 通过key返回Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return Entry数据,(如果为空Entry.state == NULL_IN_OUTER)除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern _MEntryWithOA getCopyEntryByKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);


/// @brief 判断释放含有该key
/// @param pMap Mpa类型指针
/// @param key key
/// @return 有就返回true,否则false
extern bool hasKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);


/// @brief 通过key删除Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return 没找到返回0,删除成功返回1
extern InfoOfReturn delEntryByKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);


/// @brief 将Data的数据整合在一起(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
/// @param data void* data指针
/// @param content 描述性信息, void* content
/// @param type 数据类型
/// @param dataInfo InfoOfData类型
/// @return 返回Data数据(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
extern _MData stackDataInMMapWithOA(void* data, void* content, int type, InfoOfData* dataInfo);



/// @brief 打印Data类型数据,包括Key和Val
/// @param data Data类型数据
/// @param tip 提示词,会显示的
extern void printDataInMMapWithOA(_MData data, char* tip);

/// @brief 打印Entry数据,会自动打印Key和val
/// @param entry entry数据
extern void printEntryInMMapWithOA(_MEntryWithOA entry);

/// @brief 打印Map中的所有数据
/// @param pMap Map类型数据指针
extern void printMMapWithOA(_MMapWithOA* pMap);
#endif