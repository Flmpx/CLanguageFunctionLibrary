#ifndef _MULTIPLE_VOID_MAP_OA_H
#define _MULTIPLE_VOID_MAP_OA_H
#include <stdbool.h>
#include "../../../_void_base.h"

/// @brief 哈希表中的一个节点
typedef struct Entry_M_inOAMap {
    Data_M key;
    Data_M value;
    int state;
    bool isEmpty;
} Entry_M_inOAMap;

/// @brief OAMap_M
typedef struct OAMap_M {
    Entry_M_inOAMap* arr;
    int mod;
    int len;
    int size;
} OAMap_M;


/// @brief 初始化Map
/// @param pMap Mpa类型指针
extern void initMOAMap(OAMap_M* pMap);


/**** */
/// @brief 释放掉Data数据
/// @param data Data数据类型指针
extern void freeMDataInMOAMap(Data_M* data);


/// @brief 释放掉Entry数据
/// @param entry Entry类型指针
extern void freeMEntryInMOAMap(Entry_M_inOAMap* entry);

/// @brief 删除Map;
/// @param pMap Map类型指针
extern void freeMOAMap(OAMap_M* pMap);

/// @brief 插入新的key和value
/// @param pMap Mpa类型指针
/// @param key key
/// @param val value
/// @return 插入成功返回1
extern InfoOfReturn insertMKeyAndMValInMOAMap(OAMap_M* pMap, Data_M key, Data_M val);

/// @brief 通过key返回Data(全部内容会复制一遍)
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0),除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern Data_M getCopyMValByMKeyInMOAMap(OAMap_M* pMap, Data_M key);

/// @brief 通过key返回Data(内容不会复制,主要用于修改val)
/// @param pMap Mpa类型指针
/// @param key key
/// @return Data数据,(如果为空,Data.isEmpty==0)
extern Data_M getPtrMValByMKeyInMOAMap(OAMap_M* pMap, Data_M key);


/// @brief 通过key返回Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return Entry数据,(如果为空Entry.state == NULL_IN_OUTER)除了操作函数不是复制的一份,其他的都是复制的,使用完后记得释放
extern Entry_M_inOAMap getCopyMEntryByKeyInMOAMap(OAMap_M* pMap, Data_M key);


/// @brief 判断释放含有该key
/// @param pMap Mpa类型指针
/// @param key key
/// @return 有就返回true,否则false
extern bool hasKeyInMOAMap(OAMap_M* pMap, Data_M key);


/// @brief 通过key删除Entry
/// @param pMap Mpa类型指针
/// @param key key
/// @return 没找到返回0,删除成功返回1
extern InfoOfReturn delMEntryByMKeyInMOAMap(OAMap_M* pMap, Data_M key);


/// @brief 将Data的数据整合在一起(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
/// @param data void* data指针
/// @param content 描述性信息, void* content
/// @param type 数据类型
/// @param dataInfo InfoOfData类型
/// @return 返回Data数据(注意:这个Data数据里面的不是动态分配的,不可以使用freeData函数释放)
extern Data_M stackMDataInMOAMap(void* data, void* content, int type, InfoOfData* dataInfo);



/// @brief 打印Data类型数据,包括Key和Val
/// @param data Data类型数据
/// @param tip 提示词,会显示的
extern void printMDataInMOAMap(Data_M data, char* tip);

/// @brief 打印Entry数据,会自动打印Key和val
/// @param entry entry数据
extern void printMEntryInMOAMap(Entry_M_inOAMap entry);

/// @brief 打印Map中的所有数据
/// @param pMap Map类型数据指针
extern void printMOAMap(OAMap_M* pMap);
#endif