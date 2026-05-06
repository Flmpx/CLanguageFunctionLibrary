#ifndef SLIST_MDATA_H
#define SLIST_MDATA_H
#include "../../../base.h"
#include <stdbool.h>

typedef struct Node_M_inSList Node_M_inSList;



#ifdef NODE_M_IN_SLIST

/// @brief 在SList_M的中的Node_M_inSList节点, 节点的数据任意, 是Data_M类型
struct Node_M_inSList {
    struct Node_M_inSList* next;
    Data_M val;
};
#endif

/// @brief SList_M类型, 可以存储任意类型
typedef struct {
    Node_M_inSList* head;
    Node_M_inSList* tail;
    int size;
} SList_M;


/*** */
/// @brief 初始化SList_M
/// @param plist SList_M类型的指针
extern void initMSList(SList_M* plist);


/// @brief 释放MVal(Data_M类型)的内容
/// @param val MVal类型指针(Data_M类型)
extern void freeMValInMSList(Data_M* val);


/// @brief 通过MVal(Data_M类型)返回MVal的指针(Data_M类型)(可直接修改内部的void* data和void* content内容)
/// @param plist SList_M类型指针
/// @param val 输入的MVal类型(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MVal, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getPtrMValByMValInMSList(SList_M* plist, Data_M val);

/// @brief 通过Pos位置返回MVal(Data_M类型)的,注意这里MVal中的void* data和void* content都是复制的,使用完后记得释放
/// @param plist SList_M类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_M类型数据, 这里是MVal, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getCopyMValByPosInMSList(SList_M* plist, int pos);


/// @brief 通过位置Pos返回MVal的指针(Data_M类型)(可直接修改内部的void* data和void* content内容)
/// @param plist SList_M类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_M类型数据, 这里是MVal, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getPtrMValByPosInMSList(SList_M* plist, int pos);

/// @brief 判断MVal数据是否在SList_M里面
/// @param plist SList_M类型指针
/// @param val Data_M类型数据
/// @return 有就返回true,没有就false
extern bool hasMValInMSList(SList_M* plist, Data_M val);




/// @brief 在SList_M链表的尾部插入节点
/// @param plist SList_M链表指针
/// @param val Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMValAtEndInMSList(SList_M* plist, Data_M val);


/// @brief 在SList_M链表的头部插入节点
/// @param plist SList_M链表指针
/// @param val Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMValAtStartInMSList(SList_M* plist, Data_M val);

/// @brief 在SList_M链表指定位置插入数据
/// @param plist SList_M链表指针
/// @param val Data_M类型数据
/// @param pos 位置的范围在[0, SList_M.size],范围的两端分别代表头插和尾插
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMValAtPosInMSList(SList_M* plist, Data_M val, int pos);

/// @brief 删除SList_M链表头节点
/// @param plist SList_M链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delEndNodeInMSList(SList_M* plist);


/// @brief 删除SList_M链表尾节点
/// @param plist SList_M链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delStartNodeInMSList(SList_M* plist);

/// @brief 通过MVal(Data_M类型)数据来删除SList_M中的节点
/// @param plist SList_M链表指针
/// @param val Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeByMValInMSList(SList_M* plist, Data_M val);

/// @brief 通过位置删除SList_M的节点
/// @param plist SList_M链表指针
/// @param pos 要删除的位置(从0开始)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeByPosInMSList(SList_M* plist, int pos);



// /// @brief 反转SList_M链表
// /// @param plist SList_M链表指针
// extern void reverseMDList(SList_M* plist);



/// @brief 打印SList_M链表中的Data_M数据
/// @param val Data_M类型数据
extern void printMValInMSList(Data_M val);

/// @brief 打印SList_M链表数据
/// @param plist SList_M链表指针
extern void printMSList(SList_M* plist);

/// @brief 清除SList_M链表
/// @param plist SList_M链表指针
extern void freeMSList(SList_M* plist);


#endif


