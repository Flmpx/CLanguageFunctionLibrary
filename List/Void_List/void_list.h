#ifndef VOIDLIST_H
#define VOIDLIST_H
#include <stdbool.h>

enum info {
    Warning = -1,
    None = 0,
    Success = 1
};

//以下函数都需要自己提供

/// @brief 释放void* data
typedef void (*_freedata)(void* data, void* content);



/// @brief 对void* data进行比较的函数
typedef int (*_cmpdata)(void* data_a, void* content_a, void* data_b, void* content_b);

/// @brief 对void* data进行复制的函数
typedef void* (*_copydata)(void* data, void* content);

/// @brief 对Data进行输出的函数
typedef void (*_printdata)(void* data, void* content);


/// @brief 按自己的方式释放content
typedef void (*_freecontent)(void* content);


/// @brief 通过按自己的方式解析content内容,然后创建一个完全一样的
typedef void* (*_copycontent)(void* content);


/// @brief 创建的这种类型的变量是不允许删除的(把他设置为全局变量),它代表的是某一种类型的相关操作函数
typedef struct Operation {
    _freedata freedata;
    _cmpdata cmpdata;
    _copydata copydata;
    _printdata printdata;
    _copycontent copycontent;
    _freecontent freecontent;
} Operation;

typedef struct node {
    struct node* prev;
    struct node* next;
    void* data;
    int sizeofdata;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
    Operation* oper;
    bool hasContent;
} List;

/// @brief 判断链表是否为空
/// @param plist 链表指针
/// @return | true:为空 | false:不为空| 
extern bool isEmptyList(List* plist);


/// @brief 初始化链表,使用之前必须初始化
/// @param plist 链表指针
extern void initializeList(List* plist, Operation* oper, bool hasContenet);

typedef int (*Compare)(const void* a, const void* b);

/// @brief 通过data来返回链表节点
/// @param plist 链表指针
/// @param data 数据指针
/// @param cmp 自己提供比较函数,比较函数返回0代表相同
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
extern Node* findNodeByData(List* plist, void* data, Compare cmp);

/// @brief 通过位置返回链表节点
/// @param plist 链表指针
/// @param pos 位置(范围应在[0, list.size-1])
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
extern Node* findNodeByPos(List* plist, int pos);

/// @brief 在链表的尾部插入节点
/// @param plist 链表指针
/// @param data 数据指针
/// @param sizeofdata 节点数据所占字节数
/// @return | -1-->节点创建失败 | 1-->节点创建成功,并成功写入数据 |
extern int insertNodeAtEndInList(List* plist, void* data, int sizeofdata);


/// @brief 在链表的头部插入节点
/// @param plist 链表指针
/// @param data 数据指针
/// @param sizeofdata 节点数据所占字节数
/// @return | -1-->节点创建失败 | 1-->节点创建成功,并成功写入数据 |
extern int insertNodeAtStartInList(List* plist, void* data, int sizeofdata);

/// @brief 
/// @param plist 链表指针
/// @param data 数据指针
/// @param sizeofdata 节点数据所占字节数
/// @param pos 位置的范围在[0, list.size],范围的两端分别代表头插和尾插
/// @return | -1-->节点创建失败或者位置无效 | 1-->节点创建成功,并成功写入数据 |
extern int insertNodeAtPosInList(List* plist, void* data, int sizeofdata, int pos);

/// @brief 删除链表头节点
/// @param plist 链表指针
/// @return 如果链表为空返回-1, 否则返回1
extern int delEndNodeInList(List* plist);


/// @brief 删除链表尾节点
/// @param plist 链表指针
/// @return 如果链表为空返回-1, 否则返回1
int delStartNodeINList(List* plist);

/// @brief 通过data来删除节点
/// @param plist 链表指针
/// @param data 数据指针
/// @param cmp 自己提供比较函数,函数返回0代表数据相同
/// @return 链表为空返回-1, 找不到对应的节点返回0, 删除成功返回1
extern int delNodeByData(List* plist, void* data, Compare cmp);

/// @brief 通过位置删除节点
/// @param plist 链表指针
/// @param pos 要删除的位置
/// @return 如果链表为空或者位置有误返回-1, 删除成功返回1
extern int delNodeByPos(List* plist, int pos);

/// @brief 反转链表
/// @param plist 链表指针
extern void reverseList(List* plist);

/// @brief 打印链表数据
/// @param plist 链表指针
/// @param print 自己提供打印函数
extern void printList(List* plist, Print print);

/// @brief 清除链表
/// @param plist 链表指针
extern void freeList(List* plist);


/// @brief 对链表进行排序
/// @param plist 链表指针
/// @param cmp 自己提供比较函数
extern void sortList(List* plist, Compare cmp);
#endif