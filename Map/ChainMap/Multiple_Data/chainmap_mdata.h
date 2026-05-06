#ifndef CHAINMAP_MDATA_H
#define CHAINMAP_MDATA_H
#include <stdbool.h>
#include "../../../base.h"

typedef struct Node_M_inChainMap Node_M_inChainMap;
typedef struct List_M_inChainMap List_M_inChainMap;



/// @brief 在ChainMap_M中的Entry类型(Entry_M_inChainMap)
typedef struct Entry_M_inChainMap {
    Data_M key;
    Data_M value;
    bool isEmpty;
} Entry_M_inChainMap;



#ifdef NODE_M_INCHAINMAP

/// @brief 在ChainMap中的链表节点, Node_M_inChainMap类型
struct Node_M_inChainMap {
    struct Node_M_inChainMap* next;
    struct Node_M_inChainMap* prev;
    Entry_M_inChainMap entry;
};

#endif


#ifdef LIST_M_INCHAINMAP

/// @brief 在ChainMap中的链表, List_M_inChainMap
struct List_M_inChainMap {
    Node_M_inChainMap* head;
    Node_M_inChainMap* tail;
    int size;
};

#endif

/// @brief ChainMap_M->采用链表法的Map, 可存储任意类型数据
typedef struct ChainMap_M {
    List_M_inChainMap* arr;
    int mod;
    int len;
    int size;
} ChainMap_M;


/// @brief 初始化ChainMap_M
/// @param pMap ChainMap_M的指针
extern void initMChainMap(ChainMap_M* pMap);




/// @brief 释放掉复制来的在ChainMap_M中的MVal
/// @param val MVal类型指针(Data_M类型)
extern void freeMValInMChainMap(Data_M* val);

/// @brief 释放掉复制来的在ChainMap_M中的MEntry(Entry_M_inChainMap类型)
/// @param entry MEntry类型(Entry_M_inChainMap类型)
extern void freeMEntryInMChainMap(Entry_M_inChainMap* entry);

/// @brief 释放掉ChainMap_M
/// @param pMap ChainMap_M的指针
extern void freeMChainMap(ChainMap_M* pMap);

/// @brief 插入key和val到ChainMap_M类型中去
/// @param pMap ChainMap_M的指针
/// @param key MKey(Data_M类型)
/// @param val MVal(Data_M类型)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMKeyAndMValInMChainMap(ChainMap_M* pMap, Data_M key, Data_M val);

/// @brief 通过MKey得到复制来的MVal(Data_M类型)
/// @param pMap ChainMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MVal, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getCopyMValByMKeyInMChainMap(ChainMap_M* pMap, Data_M key);

/// @brief 通过MKey得到MVal(Data_M类型), 可直接修改内部的void* data和void* content内容
/// @param pMap ChainMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MVal, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getPtrMValByMKeyInMChainMap(ChainMap_M* pMap, Data_M key);

/// @brief 通过MKey得到复制来的MEntry(Entry_M_inChainMap类型)
/// @param pMap ChainMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回Entry_M_inChainMap类型数据, 这里是MEntry, 如果没有, 返回空Entry_M_inChainMap类型数据, 通过entry.isEmpty进行查看, 具体查看文档
extern Entry_M_inChainMap getCopyMEntryByMKeyInMChainMap(ChainMap_M* pMap, Data_M key);


/// @brief 判断Mkey是否在ChainMap_M中
/// @param pMap ChainMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 如果存在返回true, 否则返回false
extern bool hasMKeyInMChainMap(ChainMap_M* pMap, Data_M key);


/// @brief 通过MKey删除在ChainMap_M中的元素
/// @param pMap ChainMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delMEntryByMKeyInMChainMap(ChainMap_M* pMap, Data_M key);




/// @brief 打印在ChainMap_M中的MKey(Data_M类型)
/// @param key MKey(Data_M类型)
extern void printMKeyInMChainMap(Data_M key);



/// @brief 打印在ChainMap_M中的MVal(Data_M类型)
/// @param val MVal(Data_M类型)
extern void printMValInMChainMap(Data_M val);

/// @brief 打印在ChainMap_M中的MEntry(Entry_M_inChainMap类型)
/// @param entry MEntry(Entry_M_inChainMap类型)
extern void printMEntryInMChainMap(Entry_M_inChainMap entry);

/// @brief 打印ChainMap_M中的所有数据
/// @param pMap ChainMap_M的指针
extern void printMChainMap(ChainMap_M* pMap);
#endif