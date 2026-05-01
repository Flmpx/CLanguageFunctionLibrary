#ifndef DLIST_SDATA_H
#define DLIST_SDATA_H
#include <stdbool.h>
#include "../../../base.h"

typedef struct Node_S_inDList Node_S_inDList;

#ifdef NODE_S_INDLIST

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


/// @brief 释放SData(Data_S类型)的内容
/// @param plist DList_S的指针
/// @param inputData Data_S类型指针
extern void freeSDataInSDList(DList_S* plist, Data_S* inputData);

/// @brief 通过Data_S类型数据中的void* data和void* content返回SData的指针(Data_S类型)(可直接修改内部的void* data和void* content内容)
/// @param plist DList_S类型指针
/// @param data void* data
/// @param content void* content
/// @return 返回Data_S类型数据, 这里是SData, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getPtrSDataBySDataInSDList(DList_S* plist, void* data, void* content);

/// @brief 通过Pos位置返回Data_S的,注意这里Data_S中的void* data和void* content都是复制的,使用完后记得释放
/// @param plist DList_S类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_S类型数据, 这里是SData, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getCopySDataByPosInSDList(DList_S* plist, int pos);


/// @brief 通过位置Pos返回SData的指针(Data_S类型)(可直接修改内部的void* data和void* content内容)
/// @param plist List类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_S类型数据, 这里是SData, 如果没有, 返回空Data_S类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_S getPtrSDataByPosInSDList(DList_S* plist, int pos);

/// @brief 判断Data_S数据(这里输入的是void* data和void* content)是否在DList_S里面
/// @param plist List_M类型指针
/// @param data void* data
/// @param content void* content
/// @return 有就返回true,没有就false
extern bool hasSDataInSDList(DList_S* plist, void* data, void* content);




/// @brief 在DList_S链表的尾部插入节点(这里输入的是void* data和void* content)
/// @param plist DList_S链表指针
/// @param data void* data
/// @param content void* content
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSDataAtEndInSDList(DList_S* plist, void* data, void* content);


/// @brief 在DList_S链表头部插入节点(这里输入的是void* data和void* content)
/// @param plist DList_S链表指针
/// @param data void* data
/// @param content void* content
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSDataAtStartInSDList(DList_S* plist, void* data, void* content);

/// @brief 在DList_S链表Pos位置插入节点(这里输入的是void* data和void* content)
/// @param plist DList_S链表指针
/// @param data void* data
/// @param content void* content
/// @param pos 位置的范围在[0, list.size],范围的两端分别代表头插和尾插
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertSDataAtPosInSDList(DList_S* plist, void* data, void* content, int pos);

/// @brief 删除DList_S链表尾节点
/// @param plist DList_S链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delEndNodeInSDList(DList_S* plist);


/// @brief 删除DList_S链表头节点
/// @param plist DList_S链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delStartNodeInSDList(DList_S* plist);

/// @brief 通过SData(Data_S类型, 这里输入的是void* data和void* content)数据来删除DList_S中的节点
/// @param plist DList_S链表指针
/// @param data void* data
/// @param content void* content
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeBySDataInSDList(DList_S* plist, void* data, void* content);

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
/// @param inputData Data_S类型数据
extern void printSDataInSDList(DList_S* plist, Data_S inputData);


/// @brief 打印DList_S链表数据
/// @param plist DList_S链表指针
extern void printSDList(DList_S* plist);

/// @brief 清除DList_S链表
/// @param plist DList_S链表指针
extern void freeSDList(DList_S* plist);
#endif

