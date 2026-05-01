#ifndef DLIST_MDATA_H
#define DLIST_MDATA_H
#include "../../../base.h"
#include <stdbool.h>

typedef struct Node_M_inDList Node_M_inDList;



#ifdef NODE_M_INDLIST

/// @brief 在DList_M的中的Node_M_inDList节点, 节点的数据任意, 是Data_M类型
struct Node_M_inDList {
    struct Node_M_inDList* prev;
    struct Node_M_inDList* next;
    Data_M val;
};
#endif

/// @brief DList_M类型, 可以存储任意类型
typedef struct {
    Node_M_inDList* head;
    Node_M_inDList* tail;
    int size;
} DList_M;


/*** */
/// @brief 初始化DList_M
/// @param plist DList_M类型的指针
extern void initMList(DList_M* plist);


/// @brief 释放MData(Data_M类型)的内容
/// @param inputData MData类型指针(Data_M类型)
extern void freeMDataInMList(Data_M* inputData);


/// @brief 通过MData(Data_M类型)返回MData的指针(Data_M类型)(可直接修改内部的void* data和void* content内容)
/// @param plist DList_M类型指针
/// @param inputData 输入的MData类型(Data_M类型)
/// @return 返回Data_M类型数据, 这里是MData, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getPtrMDataBySDataInMList(DList_M* plist, Data_M inputData);

/// @brief 通过Pos位置返回MData(Data_M类型)的,注意这里MData中的void* data和void* content都是复制的,使用完后记得释放
/// @param plist DList_M类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_M类型数据, 这里是MData, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getCopyMDataByPosInMList(DList_M* plist, int pos);


/// @brief 通过位置Pos返回MData的指针(Data_M类型)(可直接修改内部的void* data和void* content内容)
/// @param plist DList_M类型指针
/// @param pos 位置(从0开始)
/// @return 返回Data_M类型数据, 这里是MData, 如果没有, 返回空Data_M类型数据, 通过Data.isEmpty进行查看, 具体查看文档
extern Data_M getPtrMDataByPosInMList(DList_M* plist, int pos);

/// @brief 判断Data_M数据是否在DList_M里面
/// @param plist DList_M类型指针
/// @param inputData Data_M类型数据
/// @return 有就返回true,没有就false
extern bool hasMDataInMList(DList_M* plist, Data_M inputData);




/// @brief 在DList_M链表的尾部插入节点
/// @param plist DList_M链表指针
/// @param inputData Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMDataAtEndInMList(DList_M* plist, Data_M inputData);


/// @brief 在DList_M链表的头部插入节点
/// @param plist DList_M链表指针
/// @param inputData Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMDataAtStartInMList(DList_M* plist, Data_M inputData);

/// @brief 在DList_M链表指定位置插入数据
/// @param plist DList_M链表指针
/// @param inputData Data_M类型数据
/// @param pos 位置的范围在[0, DList_M.size],范围的两端分别代表头插和尾插
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn insertMDataAtPosInMList(DList_M* plist, Data_M inputData, int pos);

/// @brief 删除DList_M链表头节点
/// @param plist DList_M链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delEndNodeInMList(DList_M* plist);


/// @brief 删除DList_M链表尾节点
/// @param plist DList_M链表指针
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delStartNodeInMList(DList_M* plist);

/// @brief 通过MData(Data_M类型)数据来删除DList_M中的节点
/// @param plist DList_M链表指针
/// @param inputData Data_M类型数据
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeByMDataInMList(DList_M* plist, Data_M inputData);

/// @brief 通过位置删除DList_M的节点
/// @param plist DList_M链表指针
/// @param pos 要删除的位置(从0开始)
/// @return 返回InfoOfRetrun中的枚举类型, 具体查看文档
extern InfoOfReturn delNodeByPosInMList(DList_M* plist, int pos);


/// @brief 将Data_M的数据整合在一起(注意:这个Data_M数据里面的不是动态分配的,不可以使用freeMData一类函数释放)
/// @param data void* data指针
/// @param content 描述性信息, void* content
/// @param type 数据标签, 不要使用-1
/// @param dataInfo InfoOfData类型指针
/// @return 返回Data_M数据(注意:这个Data_M数据里面的不是动态分配的,不可以使用freeMData一类函数释放)
extern Data_M stackMDataInMList(void* data, void* content, int type, InfoOfData* dataInfo);


/// @brief 反转DList_M链表
/// @param plist DList_M链表指针
extern void reverseMList(DList_M* plist);



/// @brief 打印DList_M链表中的Data_M数据
/// @param inputData Data_M类型数据
extern void printSDataInMList(Data_M inputData);

/// @brief 打印DList_M链表数据
/// @param plist DList_M链表指针
extern void printMList(DList_M* plist);

/// @brief 清除DList_M链表
/// @param plist DList_M链表指针
extern void freeMList(DList_M* plist);


#endif


