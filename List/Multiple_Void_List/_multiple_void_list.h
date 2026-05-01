#ifndef _MULTIPLE_VOID_LIST_H
#define _MULTIPLE_VOID_LIST_H
#include "../../_void_base.h"
#include <stdbool.h>

typedef struct Node_M_inList Node_M_inList;



#ifdef NODE_M_INLIST

/// @brief 在List_M的中的Node_M_inList节点, 节点的数据任意, 是Data_M类型
struct Node_M_inList {
    struct Node_M_inList* prev;
    struct Node_M_inList* next;
    Data_M val;
};
#endif

/// @brief List_M类型, 可以存储任意类型
typedef struct {
    Node_M_inList* head;
    Node_M_inList* tail;
    int size;
} List_M;


/*** */
/// @brief 初始化List_M
/// @param plist List_M类型的指针
extern void initMList(List_M* plist);


/// @brief 释放MData(Data_M类型)的内容
/// @param inputData MData类型指针(Data_M类型)
extern void freeMDataInMList(Data_M* inputData);


/// @brief 通过MData(Data_M类型)返回MData的指针(Data_M类型)(可直接修改内部的void* data和void* content内容)
/// @param plist List_M类型指针
/// @param inputData 输入的MData类型(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MData, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getPtrMDataBySDataInMList(List_M* plist, Data_M inputData);

/// @brief 通过Pos位置返回MData(Data_M类型)的,注意这里MData中的void* data和void* content都是复制的,使用完后记得释放
/// @param plist List_M类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_M类型数据, 这里是MData, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getCopyMDataByPosInMList(List_M* plist, int pos);


/// @brief 通过位置Pos返回MData的指针(Data_M类型)(可直接修改内部的void* data和void* content内容)
/// @param plist List_M类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_M类型数据, 这里是MData, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getPtrMDataByPosInMList(List_M* plist, int pos);

/// @brief 判断Data_M数据是否在List_M里面
/// @param plist List_M类型指针
/// @param inputData Data_M类型数据
/// @return 有就返回true,没有就false
extern bool hasMDataInMList(List_M* plist, Data_M inputData);




/// @brief 在List_M链表的尾部插入节点
/// @param plist List_M链表指针
/// @param inputData Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMDataAtEndInMList(List_M* plist, Data_M inputData);


/// @brief 在List_M链表的头部插入节点
/// @param plist List_M链表指针
/// @param inputData Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMDataAtStartInMList(List_M* plist, Data_M inputData);

/// @brief 在List_M链表指定位置插入数据
/// @param plist List_M链表指针
/// @param inputData Data_M类型数据
/// @param pos 位置的范围在[0, List_M.size],范围的两端分别代表头插和尾插
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMDataAtPosInMList(List_M* plist, Data_M inputData, int pos);

/// @brief 删除List_M链表头节点
/// @param plist List_M链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delEndNodeInMList(List_M* plist);


/// @brief 删除List_M链表尾节点
/// @param plist List_M链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delStartNodeInMList(List_M* plist);

/// @brief 通过MData(Data_M类型)数据来删除List_M中的节点
/// @param plist List_M链表指针
/// @param inputData Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeByMDataInMList(List_M* plist, Data_M inputData);

/// @brief 通过位置删除List_M的节点
/// @param plist List_M链表指针
/// @param pos 要删除的位置(从0开始)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeByPosInMList(List_M* plist, int pos);


/// @brief 将Data_M的数据整合在一起(注意:这个Data_M数据里面的不是动态分配的,不可以使用freeMData一类函数释放)
/// @param data void* data指针
/// @param content 描述性信息, void* content
/// @param type 数据标签, 不要使用-1
/// @param dataInfo InfoOfData类型指针
/// @return 返回Data_M数据(注意:这个Data_M数据里面的不是动态分配的,不可以使用freeMData一类函数释放)
extern Data_M stackMDataInMList(void* data, void* content, int type, InfoOfData* dataInfo);


/// @brief 反转List_M链表
/// @param plist List_M链表指针
extern void reverseMList(List_M* plist);



/// @brief 打印List_M链表中的Data_M数据
/// @param inputData Data_M类型数据
extern void printSDataInMList(Data_M inputData);

/// @brief 打印List_M链表数据
/// @param plist List_M链表指针
extern void printMList(List_M* plist);

/// @brief 清除List_M链表
/// @param plist List_M链表指针
extern void freeMList(List_M* plist);


#endif


