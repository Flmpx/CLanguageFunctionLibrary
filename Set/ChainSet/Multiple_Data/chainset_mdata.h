#ifndef CHAINSET_MDATA_H
#define CHAINSET_MDATA_H
#include <stdbool.h>
#include "../../../base.h"

typedef struct Node_M_inChainSet Node_M_inChainSet;
typedef struct List_M_inChainSet List_M_inChainSet;

#ifdef ENTRY_M_INCHAINSET

/// @brief 在ChainSet_M中的Entry类型(Entry_M_inChainSet)
typedef struct Entry_M_inChainSet {
    Data_M key;
    bool isEmpty;
} Entry_M_inChainSet;

#endif

#ifdef NODE_M_INCHAINSET

/// @brief 在ChainSet中的链表节点, Node_M_inChainSet类型
struct Node_M_inChainSet {
    struct Node_M_inChainSet* next;
    struct Node_M_inChainSet* prev;
    Entry_M_inChainSet entry;
};

#endif

#ifdef LIST_M_INCHAINSET

/// @brief 在ChainSet中的链表, List_M_inChainSet
struct List_M_inChainSet {
    Node_M_inChainSet* head;
    Node_M_inChainSet* tail;
    int size;
};

#endif

/// @brief ChainSet_M->采用链表法的Set, 可存储任意类型数据
typedef struct ChainSet_M {
    List_M_inChainSet* arr;
    int mod;
    int len;
    int size;
} ChainSet_M;


/// @brief 初始化ChainSet_M
/// @param pSet ChainSet_M的指针
extern void initMChainSet(ChainSet_M* pSet);



/// @brief 释放掉复制来的在ChainSet_M中的MKey
/// @param key MKey类型指针(Data_M*类型)
extern void freeMKeyInMChainSet(Data_M* key);

/// @brief 释放掉ChainSet_M
/// @param pSet ChainSet_M的指针
extern void freeMChainSet(ChainSet_M* pSet);

/// @brief 插入key到ChainSet_M类型中去
/// @param pSet ChainSet_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMKeyInMChainSet(ChainSet_M* pSet, Data_M key);

/// @brief 通过MKey得到复制来的MKey(Data_M类型)(你可能会觉得奇怪)
/// @param pSet ChainSet_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MKey, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getCopyMKeyByMKeyInMChainSet(ChainSet_M* pSet, Data_M key);


/// @brief 判断Mkey是否在ChainSet_M中
/// @param pSet ChainSet_M的指针
/// @param key MKey(Data_M类型)
/// @return 如果存在返回true, 否则返回false
extern bool hasMKeyInMChainSet(ChainSet_M* pSet, Data_M key);


/// @brief 通过MKey删除在ChainSet_M中的元素
/// @param pSet ChainSet_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delMKeyByMKeyInMChainSet(ChainSet_M* pSet, Data_M key);




/// @brief 打印在ChainSet_M中的MKey(Data_M类型)
/// @param key MKey(Data_M类型)
extern void printMKeyInMChainSet(Data_M key);


/// @brief 打印ChainSet_M中的所有数据
/// @param pSet ChainSet_M的指针
extern void printMChainSet(ChainSet_M* pSet);
#endif