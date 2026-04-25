#ifndef _MULTIPLE_VOID_LIST_H
#define _MULTIPLE_VOID_LIST_H
#include "../../_void_base.h"
#include <stdbool.h>


typedef struct node {
    struct node* prev;
    struct node* next;
    _MData val;
} MultiNodeInList;



typedef struct {
    MultiNodeInList* head;
    MultiNodeInList* tail;
    int size;
} _MList;

/// @brief 初始化List
/// @param plist List类型的指针
extern void initMList(_MList* plist);


/// @brief 释放Data的内容
/// @param inputData Data类型指针
extern void freeDataInMList(_MData* inputData);


/// @brief 通过Data类型返回Data(主要用于改变List中的这个数据)
/// @param plist List类型指针
/// @param inputData Data数据
/// @return 如果找到,就返回Data类型, 这里的Ptr主要是Data数据里面的void* data和void* content
extern _MData getPtrDataByDataInMList(_MList* plist, _MData inputData);

/// @brief 通过Pos位置返回Data的,注意这里Data中的data和content都是复制的,使用完后记得释放
/// @param plist List类型指针
/// @param pos 位置
/// @return 如果找到,返回Data,反之,返回空Data
extern _MData getCopyDataByPosInMList(_MList* plist, int pos);


/// @brief 通过Pos位置返回Data的,返回的是List中Data,说明可以通过这样修改数据
/// @param plist List类型指针
/// @param pos 位置
/// @return 如果找到,返回Data,反之,返回空Data
extern _MData getPtrDataByPosInMList(_MList* plist, int pos);

/// @brief 判断数据是否在里面
/// @param plist List类型指针
/// @param inputData Data类型数据
/// @return 有就返回true,没有就false
extern bool hasDataInMList(_MList* plist, _MData inputData);




/// @brief 在链表的尾部插入节点
/// @param plist 链表指针
/// @param inputData Data类型数据
/// @return | -1-->节点创建失败 | 1-->节点创建成功,并成功写入数据 |
extern InfoOfReturn insertDataAtEndInMList(_MList* plist, _MData inputData);


/// @brief 在链表的头部插入节点
/// @param plist 链表指针
/// @param inputData Data类型数据
/// @return | -1-->节点创建失败 | 1-->节点创建成功,并成功写入数据 |
extern InfoOfReturn insertDataAtStartInMList(_MList* plist, _MData inputData);

/// @brief 在指定位置插入数据
/// @param plist 链表指针
/// @param inputData Data类型数据
/// @param pos 位置的范围在[0, list.size],范围的两端分别代表头插和尾插
/// @return | -1-->节点创建失败或者位置无效 | 1-->节点创建成功,并成功写入数据 |
extern InfoOfReturn insertDataAtPosInMList(_MList* plist, _MData inputData, int pos);

/// @brief 删除链表头节点
/// @param plist 链表指针
/// @return 如果链表为空返回-1, 否则返回1
extern InfoOfReturn delEndNodeInMList(_MList* plist);


/// @brief 删除链表尾节点
/// @param plist 链表指针
/// @return 如果链表为空返回-1, 否则返回1
extern InfoOfReturn delStartNodeInMList(_MList* plist);

/// @brief 通过data来删除节点
/// @param plist 链表指针
/// @param inputData Data类型数据
/// @return 链表为空返回-1, 找不到对应的节点返回0, 删除成功返回1
extern InfoOfReturn delNodeByDataInMList(_MList* plist, _MData inputData);

/// @brief 通过位置删除节点
/// @param plist 链表指针
/// @param pos 要删除的位置
/// @return 如果链表为空或者位置有误返回-1, 删除成功返回1
extern InfoOfReturn delNodeByPosInMList(_MList* plist, int pos);


/// @brief 整合数据(不会复制,只是整合)
/// @param data void* data
/// @param content void* content
/// @param type 数据标签,尽量不要使用-1
/// @param dataInfo InfoOfData类型数
/// @return 整合好的Data数据
extern _MData stackDataInMList(void* data, void* content, int type, InfoOfData* dataInfo);


/// @brief 反转链表
/// @param plist 链表指针
extern void reverseMList(_MList* plist);

/// @brief 打印链表数据
/// @param plist 链表指针
extern void printMList(_MList* plist);

/// @brief 清除链表
/// @param plist 链表指针
extern void freeMList(_MList* plist);


#endif


