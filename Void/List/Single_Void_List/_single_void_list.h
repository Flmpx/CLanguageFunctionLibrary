#ifndef _SINGLE_VOID_LIST_H
#define _SINGLE_VOID_LIST_H
#include <stdbool.h>
#include "../../_void_base.h"



typedef struct SingleNodeInList {
    struct SingleNodeInList* prev;
    struct SingleNodeInList* next;
    _SData val;
} SingleNodeInList;


typedef struct {
    SingleNodeInList* head;
    SingleNodeInList* tail;
    InfoOfData* valInfo;
    int size;
} _SList;




/// @brief 初始化List
/// @param plist List类型的指针
/// @param valInfo InfoOfData类型数据
extern void initSList(_SList* plist, InfoOfData* valInfo);


/// @brief 释放Data类型数据
/// @param plist List的指针
/// @param inputData Data类型指针
extern void freeDataInSList(_SList* plist, _SData* inputData);

/// @brief 通过Data类型返回Data(主要用于改变List中的这个数据)
/// @param plist List类型指针
/// @param data void* data
/// @param content void* content
/// @return 如果找到,就返回Data类型, 这里的Ptr主要是Data数据里面的void* data和void* content
extern _SData getPtrDataByDataInSList(_SList* plist, void* data, void* content);

/// @brief 通过Pos位置返回Data的,注意这里Data中的data和content都是复制的,使用完后记得释放
/// @param plist List类型指针
/// @param pos 位置
/// @return 如果找到,返回Data,反之,返回空Data
extern _SData getCopyDataByPosInSList(_SList* plist, int pos);


/// @brief 通过Pos位置返回Data的,返回的是List中Data,说明可以通过这样修改数据
/// @param plist List类型指针
/// @param pos 位置
/// @return 如果找到,返回Data,反之,返回空Data
extern _SData getPtrDataByPosInSList(_SList* plist, int pos);

/// @brief 判断数据是否在里面
/// @param plist List类型指针
/// @param data void* data
/// @param content void* content
/// @return 有就返回true,没有就false
extern bool hasDataInSList(_SList* plist, void* data, void* content);




/// @brief 在链表的尾部插入节点
/// @param plist 链表指针
/// @param data void* data
/// @param content void* content
/// @return | -1-->节点创建失败 | 1-->节点创建成功,并成功写入数据 |
extern InfoOfReturn insertDataAtEndInSList(_SList* plist, void* data, void* content);


/// @brief 在链表的头部插入节点
/// @param plist 链表指针
/// @param data void* data
/// @param content void* content
/// @return | -1-->节点创建失败 | 1-->节点创建成功,并成功写入数据 |
extern InfoOfReturn insertDataAtStartInSList(_SList* plist, void* data, void* content);

/// @brief 在指定位置插入数据
/// @param plist 链表指针
/// @param data void* data
/// @param content void* content
/// @param pos 位置的范围在[0, list.size],范围的两端分别代表头插和尾插
/// @return | -1-->节点创建失败或者位置无效 | 1-->节点创建成功,并成功写入数据 |
extern InfoOfReturn insertDataAtPosInSList(_SList* plist, void* data, void* content, int pos);

/// @brief 删除链表头节点
/// @param plist 链表指针
/// @return 如果链表为空返回-1, 否则返回1
extern InfoOfReturn delEndNodeInSList(_SList* plist);


/// @brief 删除链表尾节点
/// @param plist 链表指针
/// @return 如果链表为空返回-1, 否则返回1
extern InfoOfReturn delStartNodeInSList(_SList* plist);

/// @brief 通过data来删除节点
/// @param plist 链表指针
/// @param data void* data
/// @param content void* content
/// @return 链表为空返回-1, 找不到对应的节点返回0, 删除成功返回1
extern InfoOfReturn delNodeByDataInSList(_SList* plist, void* data, void* content);

/// @brief 通过位置删除节点
/// @param plist 链表指针
/// @param pos 要删除的位置
/// @return 如果链表为空或者位置有误返回-1, 删除成功返回1
extern InfoOfReturn delNodeByPosInSList(_SList* plist, int pos);

/// @brief 反转链表
/// @param plist 链表指针
extern void reverseSList(_SList* plist);

/// @brief 打印链表数据
/// @param plist 链表指针
extern void printSList(_SList* plist);

/// @brief 清除链表
/// @param plist 链表指针
extern void freeSList(_SList* plist);
#endif


// /// @brief 对链表进行排序
// /// @param plist 链表指针
// /// @param cmp 自己提供比较函数
// extern void sortList(_SList* plist, Compare cmp);