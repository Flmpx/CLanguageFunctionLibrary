#ifndef _SINGLE_VOID_MAP_LIST_H
#define _SINGLE_VOID_MAP_LIST_H
#include <stdbool.h>
#include "../../../_void_base.h"


typedef struct Node_S_inChainMap Node_S_inChainMap;
typedef struct List_S_inChainMap List_S_inChainMap;

/// @brief 哈希表中的一个节点
typedef struct Entry_S_inChainMap {
    Data_S key;
    Data_S value;
    bool isEmpty;
} Entry_S_inChainMap;

#ifdef LIST_AND_NODE_M_IN_CHAINMAP
struct Node_S_inChainMap {
    struct Node_S_inChainMap* next;
    struct Node_S_inChainMap* prev;
    Entry_S_inChainMap entry;
};

struct List_S_inChainMap {
    Node_S_inChainMap* head;
    Node_S_inChainMap* tail;
    int size;
};
#endif



/// @brief ChainMap_S
typedef struct ChainMap_S {
    List_S_inChainMap* arr;
    InfoOfData* keyInfo;
    InfoOfData* valInfo;
    int mod;
    int len;
    int size;
} ChainMap_S;

/// @brief 初始化Map
/// @param pMap Map类型数据指针
/// @param keyInfo key的InfoOfData
/// @param valInfo val的InfoOfData
extern void initSChainMap(ChainMap_S* pMap, InfoOfData* keyInfo, InfoOfData* valInfo);



/// @brief 释放Data类型数据
/// @param data Data类型数据指针
/// @param infoOfKeyOrVal 要释放的Data类型数据的InfoOfData,主要用于释放void* data和void* content
extern void freeSDataInSChainMap(Data_S* data, InfoOfData* infoOfKeyOrVal);

/// @brief 释放Entry类型数据
/// @param entry Entry类型数据指针
/// @param pMap 选择Map类型指针,以确定是那个Map的Entry类型
extern void freeSEntryInSChianMap(Entry_S_inChainMap* entry, ChainMap_S* pMap);

/// @brief 释放Map
/// @param pMap Map类型数据指针
extern void freeSChainMap(ChainMap_S* pMap);


/// @brief 插入key和val到Map中
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content,如果没有输入NULL
/// @param valdata val
/// @param valcontent content, 如果没有输入NULL
/// @return 插入成功返回1, 内存分配失败返回-1
extern InfoOfReturn insertSKeyAndSValInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent, void* valdata, void* valcontent);

/// @brief 通过key返回Data类型数据(会自动创建一份,用完记得释放)
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Data, 如果没有返回空Data, 是否为空Data,使用Data.isEmpty来判断, 建议先使用hasKeyInMap进行判断
extern Data_S getCopySValBySKeyInSChianMap(ChainMap_S* pMap, void* keydata, void* keycontent);


/// @brief 通过key返回Data类型数据(不会创建一份,主要用于修改void* data的内容)
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Data, 如果没有返回空Data, 是否为空Data,使用Data.isEmpty来判断
extern Data_S getPtrSValBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent);

/// @brief 通过key返回Entry类型数据
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果有就返回正常的Entry, 如果没有返回空Entry, 是否为空Entry,使用Entry.isEmpty来判断, 建议先使用hasKeyInMap进行判断
extern Entry_S_inChainMap getCopySEntryBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent);

/// @brief 判断key是否在Map中
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return 如果存在返回true, 否则false
extern bool hasSKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent);

/// @brief 通过key来删除Map中对应的元素
/// @param pMap Map类型指针
/// @param keydata key
/// @param keycontent content, 如果没有输入NULL
/// @return Map为空返回-1, 没找到返回0, 删除成功返回1
extern InfoOfReturn delSEntryBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent);

/// @brief 打印Data类型数据
/// @param data Data类型数据
/// @param tip 提示次,比如[key: ...]
/// @param InfoOfKeyOrVal 当前数据类型的InfoOfData
extern void printSDataInSChainMap(Data_S data, char* tip, InfoOfData* InfoOfKeyOrVal);

/// @brief 打印Entry数据
/// @param entry Entry数据类型
/// @param pMap Map类型指针, 用于判断是哪个Map的Entry
extern void printSEntryInSChainMap(Entry_S_inChainMap entry, ChainMap_S* pMap);

/// @brief 打印整个Map的数据
/// @param pMap Map类型指针
extern void printSChainMap(ChainMap_S* pMap);
#endif