#ifndef SLIST_SDATA_H
#define SLIST_SDATA_H
#include <stdbool.h>
#include "../../../base.h"

typedef struct Node_S_inSList Node_S_inSList;

#ifdef NODE_S_IN_SLIST

/// @brief 在SList_S的中的Node_S_inSList节点, 节点的数据类型单一, 是Data_S类型
struct Node_S_inSList {
    struct Node_S_inSList* next;
    Data_S val;
};

#endif

/// @brief SList_S类型, 存储单一类型数据
typedef struct {
    Node_S_inSList* head;
    Node_S_inSList* tail;
    InfoOfData* valInfo;
    int size;
} SList_S;



/**** */
/// @brief 初始化SList_S
/// @param plist SList_S类型的指针
/// @param valInfo InfoOfData类型数据指针
extern void initSSList(SList_S* plist, InfoOfData* valInfo);


/// @brief 释放SVal(Data_S类型)的内容
/// @param plist SList_S的指针
/// @param Val Data_S类型指针
extern void freeSValInSSList(SList_S* plist, Data_S* Val);

/// @brief 通过Data_S类型数据返回SVal的指针(Data_S类型)(可直接修改内部的void* data和void* content内容)
/// @param plist SList_S类型指针
/// @param Val 传入的Data_S类型数据
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getPtrSValBySValInSSList(SList_S* plist, Data_S Val);

/// @brief 通过Pos位置返回Data_S的,注意这里Data_S中的void* data和void* content都是复制的,使用完后记得释放
/// @param plist SList_S类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getCopySValByPosInSSList(SList_S* plist, int pos);


/// @brief 通过位置Pos返回SVal的指针(Data_S类型)(可直接修改内部的void* data和void* content内容)
/// @param plist List类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getPtrSValByPosInSSList(SList_S* plist, int pos);

/// @brief 判断SVal数据是否在SList_S里面
/// @param plist List_M类型指针
/// @param Val 传入的Data_S类型数据
/// @return 有就返回true,没有就false
extern bool hasSValInSSList(SList_S* plist, Data_S Val);



/// @brief 在SList_S链表的尾部插入数据Data_S
/// @param plist SList_S链表指针
/// @param Val 传入的Data_S类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSValAtEndInSSList(SList_S* plist, Data_S Val);


/// @brief 在SList_S链表头部插入数据Data_S
/// @param plist SList_S链表指针
/// @param Val 传入的Data_S类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSValAtStartInSSList(SList_S* plist, Data_S Val);

/// @brief 在SList_S链表Pos位置插入数据Data_S
/// @param plist SList_S链表指针
/// @param Val 传入的Data_S类型数据
/// @param pos 位置的范围在[0, list.size],范围的两端分别代表头插和尾插
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSValAtPosInSSList(SList_S* plist, Data_S Val, int pos);

/// @brief 删除SList_S链表尾节点
/// @param plist SList_S链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delEndNodeInSSList(SList_S* plist);


/// @brief 删除SList_S链表头节点
/// @param plist SList_S链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delStartNodeInSSList(SList_S* plist);

/// @brief 通过SVal(Data_S类型)数据来删除SList_S中的节点
/// @param plist SList_S链表指针
/// @param Val 传入的Data_S类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeBySValInSSList(SList_S* plist, Data_S Val);

/// @brief 通过位置删除SList_S的节点
/// @param plist SList_S链表指针
/// @param pos 要删除的位置(从0开始)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeByPosInSSList(SList_S* plist, int pos);

// /// @brief 反转SList_S链表
// /// @param plist SList_S链表指针
// extern void reverseSSList(SList_S* plist);



/// @brief 打印List_M链表中的Data_S数据(一般为查找类函数返回值)
/// @param plist SList_S链表指针
/// @param Val Data_S类型数据
extern void printSValInSSList(SList_S* plist, Data_S Val);


/// @brief 打印SList_S链表数据
/// @param plist SList_S链表指针
extern void printSSList(SList_S* plist);

/// @brief 清除SList_S链表
/// @param plist SList_S链表指针
extern void freeSSList(SList_S* plist);
#endif

