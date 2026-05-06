#ifndef CHAINMAP_SDATA_H
#define CHAINMAP_SDATA_H
#include <stdbool.h>
#include "../../../base.h"

typedef struct Node_S_inChainMap Node_S_inChainMap;
typedef struct List_S_inChainMap List_S_inChainMap;

/// @brief 在ChainMap_S中的Entry类型(Entry_S_inChainMap)
typedef struct Entry_S_inChainMap {
    Data_S key;
    Data_S value;
    bool isEmpty;
} Entry_S_inChainMap;

#ifdef NODE_S_INCHAINMAP

/// @brief 在ChainMap_S中的链表节点(Node_S_inChainMap类型)
struct Node_S_inChainMap {
    struct Node_S_inChainMap* next;
    struct Node_S_inChainMap* prev;
    Entry_S_inChainMap entry;
};
#endif

#ifdef LIST_S_INCHAINMAP

/// @brief 在ChainMap_S中的链表(Node_S_inChainMap类型)
struct List_S_inChainMap {
    Node_S_inChainMap* head;
    Node_S_inChainMap* tail;
    int size;
};
#endif



/// @brief ChainMap_S->采用链表法的Map, 可存储单一类型数据
typedef struct ChainMap_S {
    List_S_inChainMap* arr;
    InfoOfData* keyInfo;
    InfoOfData* valInfo;
    int mod;
    int len;
    int size;
} ChainMap_S;

/// @brief 初始化ChainMap_S
/// @param pMap ChainMap_S的指针
/// @param keyInfo key的InfoOfData类型指针
/// @param valInfo val的InfoOfData类型指针
extern void initSChainMap(ChainMap_S* pMap, InfoOfData* keyInfo, InfoOfData* valInfo);






/// @brief 释放掉复制来的在ChainMap_S中的SVal
/// @param pMap ChainMap_S的指针
/// @param val MVal类型指针(Data_S类型)
extern void freeSValInSChainMap(ChainMap_S* pMap, Data_S* val);

/// @brief 释放掉复制来的在ChainMap_S中的SEntry(Entry_S_inChainMap类型)
/// @param pMap ChainMap_S的指针
/// @param entry SEntry类型(Entry_S_inChainMap类型)
extern void freeSEntryInSChainMap(ChainMap_S* pMap, Entry_S_inChainMap* entry);

/// @brief 释放掉ChainMap_S
/// @param pMap ChainMap_S的指针
extern void freeSChainMap(ChainMap_S* pMap);


/// @brief 插入key和val到ChainMap_S类型中去
/// @param pMap ChainMap_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @param val 传入的val(Data_S类型数据)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSKeyAndSValInSChainMap(ChainMap_S* pMap, Data_S key, Data_S val);

/// @brief 通过SKey得到复制来的SVal(Data_S类型)
/// @param pMap ChainMap_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getCopySValBySKeyInSChianMap(ChainMap_S* pMap, Data_S key);


/// @brief 通过SKey得到SVal(Data_S类型), 可直接修改内部的void* data和void* content内容
/// @param pMap ChainMap_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getPtrSValBySKeyInSChainMap(ChainMap_S* pMap, Data_S key);

/// @brief 通过SKey得到复制来的SEntry(Entry_S_inChainMap类型)
/// @param pMap ChainMap_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回Entry_S_inChainMap类型数据, 这里是SEntry, 如果没有, 返回空Entry_S_inChainMap类型数据, 通过entry.isEmpty进行查看, 具体查看文档
extern Entry_S_inChainMap getCopySEntryBySKeyInSChainMap(ChainMap_S* pMap, Data_S key);

/// @brief 判断Skey是否在ChainMap_S中
/// @param pMap ChainMap_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 如果存在返回true, 否则false
extern bool hasSKeyInSChainMap(ChainMap_S* pMap, Data_S key);

/// @brief 通过SKey删除在ChainMap_S中的元素
/// @param pMap ChainMap_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delSEntryBySKeyInSChainMap(ChainMap_S* pMap, Data_S key);



/// @brief 打印在ChainMap_S中的SKey(Data_S类型)
/// @param pMap ChainMap_S的指针
/// @param key SKey(Data_S类型)
extern void printSKeyInSChainMap(ChainMap_S* pMap, Data_S key);

/// @brief 打印在ChainMap_S中的SVal(Data_S类型)
/// @param pMap ChainMap_S的指针
/// @param val SVal(Data_S类型)
extern void printSValInSChainMap(ChainMap_S* pMap, Data_S val);

/// @brief 打印在ChainMap_S中的SEntry(Entry_S_inChainMap类型)
/// @param pMap ChainMap_S的指针
/// @param entry SEntry(Entry_S_inChainMap类型)
extern void printSEntryInSChainMap(ChainMap_S* pMap, Entry_S_inChainMap entry);




/// @brief 打印ChainMap_S中的所有数据
/// @param pMap ChainMap_S的指针
extern void printSChainMap(ChainMap_S* pMap);
#endif