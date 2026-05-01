#ifndef OAMAP_SDATA_H
#define OAMAP_SDATA_H
#include <stdbool.h>
#include "../../../base.h"



/*

    其他采用这种注释

*/


/// @brief 在OAMap_S中的Entry类型(Entry_S_inOAMap)
typedef struct Entry_S_inOAMap {
    Data_S key;
    Data_S val;
    int state;
    bool isEmpty;
} Entry_S_inOAMap;

/// @brief OAMap_S->采用开放定址法的Map, 可存储单一类型数据
typedef struct OAMap_S {
    Entry_S_inOAMap* arr;
    int mod;
    int len;
    int size;
    InfoOfData* keyInfo;
    InfoOfData* valInfo;
} OAMap_S;



/// @brief 初始化OAMap_S
/// @param pMap OAMap_S的指针
/// @param keyInfo key的InfoOfData类型指针
/// @param valInfo val的InfoOfData类型指针
extern void initSOAMap(OAMap_S* pMap, InfoOfData* keyInfo, InfoOfData* valInfo);



/// @brief 释放掉复制来的在OAMap_S中的SVal
/// @param pMap OAMap_S的指针
/// @param inputData SVal类型指针(Data_S类型)
extern void freeSValInSOAMap(OAMap_S* pMap, Data_S* inputData);

/// @brief 释放掉复制来的在OAMap_S中的SEntry(Entry_S_inOAMap类型)
/// @param pMap OAMap_S的指针
/// @param entry SEntry类型(Entry_S_inOAMap类型)
extern void freeSEntryInSOAMap(OAMap_S* pMap, Entry_S_inOAMap* entry);


/// @brief 释放掉OAMap_S
/// @param pMap OAMap_S的指针
extern void freeSOAMap(OAMap_S* pMap);

/// @brief 插入key和val到OAMap_S类型中去
/// @param pMap OAMap_S的指针
/// @param keydata void* keydata
/// @param keycontent void* keycontent
/// @param valdata void* valdata
/// @param valcontent void* valcontent
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSkeyAndSValInSOAMap(OAMap_S* pMap, void* keydata, void* keycontent, void* valdata, void* valcontent);



/// @brief 通过SKey得到复制来的SVal(Data_S类型)
/// @param pMap OAMap_S的指针
/// @param keydata void* keydata
/// @param keycontent void* keycontent
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getCopySValBySkeyInSOAMap(OAMap_S* pMap, void* keydata, void* keycontent);

/// @brief 通过SKey得到SVal(Data_S类型), 可直接修改内部的void* data和void* content内容
/// @param pMap OAMap_S的指针
/// @param keydata void* keydata
/// @param keycontent void* keycontent
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getPtrSValBySKeyInSOAMap(OAMap_S* pMap, void* keydata, void* keycontent);

/// @brief 通过SKey得到复制来的SEntry(Entry_S_inOAMap类型)
/// @param pMap OAMap_S的指针
/// @param keydata void* keydata
/// @param keycontent void* keycontent
/// @return 返回Entry_S_inOAMap类型数据, 这里是SEntry, 如果没有, 返回空Entry_S_inOAMap类型数据, 通过entry.isEmpty进行查看, 具体查看文档
extern Entry_S_inOAMap getCopySEntryByKeyInSOAMap(OAMap_S* pMap, void* keydata, void* keycontent);


/// @brief 判断Skey是否在OAMap_S中
/// @param pMap OAMap_S的指针
/// @param keydata void* keydata
/// @param keycontent void* keycontent
/// @return 如果存在返回true, 否则返回false
extern bool hasSKeyInSOAMap(OAMap_S* pMap, void* keydata, void* keycontent);


/// @brief 通过SKey删除在OAMap_S中的元素
/// @param pMap OAMap_S的指针
/// @param keydata void* keydata
/// @param keycontent void* keycontent
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delSEntryBySKeyInSOAMap(OAMap_S* pMap, void* keydata, void* keycontent);


/// @brief 打印在OAMap_S中的SKey(Data_S类型)
/// @param pMap OAMap_S的指针
/// @param keyData SKey(Data_S类型)
extern void printSKeyInSOAMap(OAMap_S* pMap, Data_S keyData);


/// @brief 打印在OAMap_S中的SVal(Data_S类型)
/// @param pMap OAMap_S的指针
/// @param valData SVal(Data_S类型)
extern void printSValInSOAMap(OAMap_S* pMap, Data_S valData);

/// @brief 打印在OAMap_S中的SEntry(Entry_S_inOAMap类型)
/// @param pMap OAMap_S的指针
/// @param entry SEntry(Entry_S_inOAMap类型)
extern void printSEntryInSOAMap(OAMap_S* pMap, Entry_S_inOAMap entry);

/// @brief 打印OAMap_S中的所有数据
/// @param pMap OAMap_S的指针
extern void printSOAMap(OAMap_S* pMap);



#endif