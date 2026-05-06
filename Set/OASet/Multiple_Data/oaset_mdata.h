#ifndef OASET_MDATA_H
#define OASET_MDATA_H
#include <stdbool.h>
#include "../../../base.h"

typedef struct Entry_M_inOASet Entry_M_inOASet;

#ifdef ENTRY_M_INOASET


/// @brief 在OASet_M中的Entry类型(Entry_M_inOASet)
typedef struct Entry_M_inOASet {
    Data_M key;
    int state;
    bool isEmpty;
} Entry_M_inOASet;

#endif

/// @brief OASet_M->采用开放定址法的Set, 可存储任意类型数据
typedef struct OASet_M {
    Entry_M_inOASet* arr;
    int mod;
    int len;
    int size;
} OASet_M;


/// @brief 初始化OASet_M
/// @param pSet OASet_M的指针
extern void initMOASet(OASet_M* pSet);





/// @brief 释放掉复制来的在OASet_M中的MKey
/// @param key MKey类型指针(Data_M*类型)
extern void freeMKeyInMOASet(Data_M* key);



/// @brief 释放掉OASet_M
/// @param pSet OASet_M的指针
extern void freeMOASet(OASet_M* pSet);

/// @brief 插入key到OASet_M类型中去
/// @param pSet OASet_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMKeyInMOASet(OASet_M* pSet, Data_M key);

/// @brief 通过MKey得到复制来的MKey(Data_M类型)(你可能会觉得奇怪)
/// @param pSet OASet_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MKey, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getCopyMKeyByMKeyInMOASet(OASet_M* pSet, Data_M key);



/// @brief 判断Mkey是否在OASet_M中
/// @param pSet OASet_M的指针
/// @param key MKey(Data_M类型)
/// @return 如果存在返回true, 否则返回false
extern bool hasMKeyInMOASet(OASet_M* pSet, Data_M key);


/// @brief 通过MKey删除在OASet_M中的元素
/// @param pSet OASet_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delMKeyByMKeyInMOASet(OASet_M* pSet, Data_M key);

/// @brief 打印在OASet_M中的MKey(Data_M类型)
/// @param key MKey(Data_M类型)
extern void printMKeyInMOASet(Data_M key);


/// @brief 打印OASet_M中的所有数据
/// @param pSet OASet_M的指针
extern void printMOASet(OASet_M* pSet);
#endif