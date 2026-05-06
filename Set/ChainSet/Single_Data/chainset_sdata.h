#ifndef CHAINSET_SDATA_H
#define CHAINSET_SDATA_H
#include <stdbool.h>
#include "../../../base.h"


typedef struct Node_S_inChainSet Node_S_inChainSet;
typedef struct List_S_inChainSet List_S_inChainSet;



#ifdef ENTRY_S_INCHAINSET

/// @brief 在ChainSet_S中的Entry类型(Entry_S_inChainSet)
typedef struct Entry_S_inChainSet {
    Data_S key;
    bool isEmpty;
} Entry_S_inChainSet;

#endif

#ifdef NODE_S_INCHAINSET

/// @brief 在ChainSet_S中的链表节点(Node_S_inChainSet类型)
struct Node_S_inChainSet {
    struct Node_S_inChainSet* next;
    struct Node_S_inChainSet* prev;
    Entry_S_inChainSet entry;
};

#endif

#ifdef LIST_S_INCHAINSET

/// @brief 在ChainSet_S中的链表(Node_S_inChainSet类型)
struct List_S_inChainSet {
    Node_S_inChainSet* head;
    Node_S_inChainSet* tail;
    int size;
};
#endif



/// @brief ChainSet_S->采用链表法的Set, 可存储单一类型数据
typedef struct ChainSet_S {
    List_S_inChainSet* arr;
    InfoOfData* keyInfo;
    int mod;
    int len;
    int size;
} ChainSet_S;

/// @brief 初始化ChainSet_S
/// @param pSet ChainSet_S的指针
/// @param keyInfo key的InfoOfData类型指针
extern void initSChainSet(ChainSet_S* pSet, InfoOfData* keyInfo);






/// @brief 释放掉复制来的在ChainSet_S中的SKey
/// @param pSet ChainKey_S的指针
/// @param key MKey类型指针(Data_S类型)
extern void freeSKeyInSChainSet(ChainSet_S* pSet, Data_S* key);


/// @brief 释放掉ChainSet_S
/// @param pSet ChainSet_S的指针
extern void freeSChainSet(ChainSet_S* pSet);


/// @brief 插入key到ChainSet_S类型中去
/// @param pSet ChainSet_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSKeyInSChainSet(ChainSet_S* pSet, Data_S key);

/// @brief 通过SKey得到复制来的SKey(Data_S类型)(你可能会感到奇怪)
/// @param pSet ChainSet_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回Data_S类型数据, 这里是SKey, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getCopySKeyBySKeyInSChianSet(ChainSet_S* pSet, Data_S key);


/// @brief 判断Skey是否在ChainSet_S中
/// @param pSet ChainSet_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 如果存在返回true, 否则false
extern bool hasSKeyInSChainSet(ChainSet_S* pSet, Data_S key);

/// @brief 通过SKey删除在ChainSet_S中的元素
/// @param pSet ChainSet_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delSKeyBySKeyInSChainSet(ChainSet_S* pSet, Data_S key);



/// @brief 打印在ChainSet_S中的SKey(Data_S类型)
/// @param pSet ChainSet_S的指针
/// @param key SKey(Data_S类型)
extern void printSKeyInSChainSet(ChainSet_S* pSet, Data_S key);



/// @brief 打印ChainSet_S中的所有数据
/// @param pSet ChainSet_S的指针
extern void printSChainSet(ChainSet_S* pSet);
#endif