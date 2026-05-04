#ifndef OAMAP_MDATA_H
#define OAMAP_MDATA_H
#include <stdbool.h>
#include "../../../base.h"

/// @brief 在OAMap_M中的Entry类型(Entry_M_inOAMap)
typedef struct Entry_M_inOAMap {
    Data_M key;
    Data_M value;
    int state;
    bool isEmpty;
} Entry_M_inOAMap;

/// @brief OAMap_M->采用开放定址法的Map, 可存储任意类型数据
typedef struct OAMap_M {
    Entry_M_inOAMap* arr;
    int mod;
    int len;
    int size;
} OAMap_M;


/// @brief 初始化OAMap_M
/// @param pMap OAMap_M的指针
extern void initMOAMap(OAMap_M* pMap);





/// @brief 释放掉复制来的在OAMap_M中的MVal
/// @param inputData MVal类型指针(Data_M类型)
extern void freeMValInMOAMap(Data_M* inputData);



/// @brief 释放掉复制来的在OAMap_M中的MEntry(Entry_M_inOAMap类型)
/// @param entry MEntry类型(Entry_M_inOAMap类型)
extern void freeMEntryInMOAMap(Entry_M_inOAMap* entry);

/// @brief 释放掉OAMap_M
/// @param pMap OAMap_M的指针
extern void freeMOAMap(OAMap_M* pMap);

/// @brief 插入key和val到OAMap_M类型中去
/// @param pMap OAMap_M的指针
/// @param key MKey(Data_M类型)
/// @param val MVal(Data_M类型)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMKeyAndMValInMOAMap(OAMap_M* pMap, Data_M key, Data_M val);

/// @brief 通过MKey得到复制来的MVal(Data_M类型)
/// @param pMap OAMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MVal, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getCopyMValByMKeyInMOAMap(OAMap_M* pMap, Data_M key);

/// @brief 通过MKey得到MVal(Data_M类型), 可直接修改内部的void* data和void* content内容
/// @param pMap OAMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MVal, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getPtrMValByMKeyInMOAMap(OAMap_M* pMap, Data_M key);


/// @brief 通过MKey得到复制来的MEntry(Entry_M_inOAMap类型)
/// @param pMap OAMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回Entry_M_inOAMap类型数据, 这里是MEntry, 如果没有, 返回空Entry_M_inOAMap类型数据, 通过entry.isEmpty进行查看, 具体查看文档
extern Entry_M_inOAMap getCopyMEntryByKeyInMOAMap(OAMap_M* pMap, Data_M key);


/// @brief 判断Mkey是否在OAMap_M中
/// @param pMap OAMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 如果存在返回true, 否则返回false
extern bool hasKeyInMOAMap(OAMap_M* pMap, Data_M key);


/// @brief 通过MKey删除在OAMap_M中的元素
/// @param pMap OAMap_M的指针
/// @param key MKey(Data_M类型)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delMEntryByMKeyInMOAMap(OAMap_M* pMap, Data_M key);

/// @brief 打印在OAMap_M中的MKey(Data_M类型)
/// @param keyData MKey(Data_M类型)
extern void printMKeyInMOAMap(Data_M keyData);


/// @brief 打印在OAMap_M中的MVal(Data_M类型)
/// @param valData MVal(Data_M类型)
extern void printMValInMOAMap(Data_M valData);

/// @brief 打印在OAMap_M中的MEntry(Entry_M_inOAMap类型)
/// @param entry MEntry(Entry_M_inOAMap类型)
extern void printMEntryInMOAMap(Entry_M_inOAMap entry);

/// @brief 打印OAMap_M中的所有数据
/// @param pMap OAMap_M的指针
extern void printMOAMap(OAMap_M* pMap);
#endif