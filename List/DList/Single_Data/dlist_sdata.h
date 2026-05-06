#ifndef DLIST_SDATA_H
#define DLIST_SDATA_H
#include <stdbool.h>
#include "../../../base.h"

typedef struct Node_S_inDList Node_S_inDList;

#ifdef NODE_S_IN_DLIST

/// @brief 在DList_S的中的Node_S_inDList节点, 节点的数据类型单一, 是Data_S类型
struct Node_S_inDList {
    struct Node_S_inDList* prev;
    struct Node_S_inDList* next;
    Data_S val;
};

#endif

/// @brief DList_S类型, 存储单一类型数据
typedef struct {
    Node_S_inDList* head;
    Node_S_inDList* tail;
    InfoOfData* valInfo;
    int size;
} DList_S;



/**** */
/// @brief 初始化DList_S
/// @param plist DList_S类型的指针
/// @param valInfo InfoOfData类型数据指针
extern void initSDList(DList_S* plist, InfoOfData* valInfo);


/// @brief 释放SVal(Data_S类型)的内容
/// @param plist DList_S的指针
/// @param val Data_S类型指针
extern void freeSValInSDList(DList_S* plist, Data_S* val);

/// @brief 通过Data_S类型数据返回SVal的指针(Data_S类型)(可直接修改内部的void* data和void* content内容)
/// @param plist DList_S类型指针
/// @param val 传入的Data_S类型数据
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getPtrSValBySValInSDList(DList_S* plist, Data_S val);

/// @brief 通过Pos位置返回Data_S的,注意这里Data_S中的void* data和void* content都是复制的,使用完后记得释放
/// @param plist DList_S类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getCopySValByPosInSDList(DList_S* plist, int pos);


/// @brief 通过位置Pos返回SVal的指针(Data_S类型)(可直接修改内部的void* data和void* content内容)
/// @param plist List类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_S类型数据, 这里是SVal, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getPtrSValByPosInSDList(DList_S* plist, int pos);

/// @brief 判断Data_S数据是否在DList_S里面
/// @param plist List_M类型指针
/// @param val 传入的Data_S类型数据
/// @return 有就返回true,没有就false
extern bool hasSValInSDList(DList_S* plist, Data_S val);



/// @brief 在DList_S链表的尾部插入数据Data_S
/// @param plist DList_S链表指针
/// @param val 传入的Data_S类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSValAtEndInSDList(DList_S* plist, Data_S val);


/// @brief 在DList_S链表头部插入数据Data_S
/// @param plist DList_S链表指针
/// @param val 传入的Data_S类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSValAtStartInSDList(DList_S* plist, Data_S val);

/// @brief 在DList_S链表Pos位置插入数据Data_S
/// @param plist DList_S链表指针
/// @param val 传入的Data_S类型数据
/// @param pos 位置的范围在[0, list.size],范围的两端分别代表头插和尾插
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSValAtPosInSDList(DList_S* plist, Data_S val, int pos);

/// @brief 删除DList_S链表尾节点
/// @param plist DList_S链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delEndNodeInSDList(DList_S* plist);


/// @brief 删除DList_S链表头节点
/// @param plist DList_S链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delStartNodeInSDList(DList_S* plist);

/// @brief 通过SVal(Data_S类型)数据来删除DList_S中的节点
/// @param plist DList_S链表指针
/// @param val 传入的Data_S类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeBySValInSDList(DList_S* plist, Data_S val);

/// @brief 通过位置删除DList_S的节点
/// @param plist DList_S链表指针
/// @param pos 要删除的位置(从0开始)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeByPosInSDList(DList_S* plist, int pos);

/// @brief 反转DList_S链表
/// @param plist DList_S链表指针
extern void reverseSDList(DList_S* plist);



/// @brief 打印List_M链表中的Data_S数据(一般为查找类函数返回值)
/// @param plist DList_S链表指针
/// @param val Data_S类型数据
extern void printSValInSDList(DList_S* plist, Data_S val);


/// @brief 打印DList_S链表数据
/// @param plist DList_S链表指针
extern void printSDList(DList_S* plist);

/// @brief 清除DList_S链表
/// @param plist DList_S链表指针
extern void freeSDList(DList_S* plist);
#endif

