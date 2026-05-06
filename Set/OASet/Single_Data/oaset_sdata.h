#ifndef OASET_SDATA_H
#define OASET_SDATA_H
#include <stdbool.h>
#include "../../../base.h"

typedef struct Entry_S_inOASet Entry_S_inOASet;

#ifdef ENTRY_S_INOASET

/// @brief 在OASet_S中的Entry类型(Entry_S_inOASet)
typedef struct Entry_S_inOASet {
    Data_S key;
    int state;
    //如果要把内存压缩到极致, 这个属性可以删除, 这里是为了保持与Map有相似之处
    bool isEmpty;
} Entry_S_inOASet;

#endif

/// @brief OASet_S->采用开放定址法的Set, 可存储单一类型数据
typedef struct OASet_S {
    Entry_S_inOASet* arr;
    int mod;
    int len;
    int size;
    InfoOfData* keyInfo;
} OASet_S;



/// @brief 初始化OASet_S
/// @param pSet OASet_S的指针
/// @param keyInfo key的InfoOfData类型指针
extern void initSOASet(OASet_S* pSet, InfoOfData* keyInfo);



/// @brief 释放掉复制来的在OASet_S中的SKey
/// @param pSet OASet_S的指针
/// @param key SKey类型指针(Data_S类型)
extern void freeSKeyInSOASet(OASet_S* pSet, Data_S* key);


/// @brief 释放掉OASet_S
/// @param pSet OASet_S的指针
extern void freeSOASet(OASet_S* pSet);

/// @brief 插入key到OASet_S类型中去
/// @param pSet OASet_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSkeyInSOASet(OASet_S* pSet, Data_S key);



/// @brief 通过SKey得到复制来的SKey(Data_S类型)(你可能会觉得奇怪)
/// @param pSet OASet_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回Data_S类型数据, 这里是SKey, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getCopySKeyBySkeyInSOASet(OASet_S* pSet, Data_S key);



/// @brief 判断Skey是否在OASet_S中
/// @param pSet OASet_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 如果存在返回true, 否则返回false
extern bool hasSKeyInSOASet(OASet_S* pSet, Data_S key);


/// @brief 通过SKey删除在OASet_S中的元素
/// @param pSet OASet_S的指针
/// @param key 传入的key(Data_S类型数据)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delSKeyBySKeyInSOASet(OASet_S* pSet, Data_S key);


/// @brief 打印在OASet_S中的SKey(Data_S类型)
/// @param pSet OASet_S的指针
/// @param key SKey(Data_S类型)
extern void printSKeyInSOASet(OASet_S* pSet, Data_S key);


/// @brief 打印OASet_S中的所有数据
/// @param pSet OASet_S的指针
extern void printSOASet(OASet_S* pSet);



#endif