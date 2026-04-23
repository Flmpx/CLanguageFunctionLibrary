#ifndef MULTIPLE_VOID_LIST_H
#define MULTIPLE_VOID_LIST_H
#define NOT_FOUND -1
#define DIFFERENT -1
#define SAME 0


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

typedef struct InfoOfData {
    Operation* oper;
    bool hasContent;
} InfoOfData;

typedef struct Data {
    void* data;
    void* content;
    InfoOfData valInfo;
    int type;
    bool isEmpty;
} Data;


typedef struct node {
    struct node* prev;
    struct node* next;
    Data val;
} Node;



typedef struct {
    Node* head;
    Node* tail;
    int size;
} List;

/// @brief 初始化List
/// @param plist List类型的指针
extern void initializeList(List* plist);


/// @brief 通过Data类型返回Data(主要用于改变List中的这个数据)
/// @param plist List类型指针
/// @param inputData Data数据
/// @return 如果找到,就返回Data类型, 这里的Ptr主要是Data数据里面的void* data和void* content
extern Data returnPtrDataByData(List* plist, Data inputData);

/// @brief 通过Pos位置返回Data的,注意这里Data中的data和content都是复制的,使用完后记得释放
/// @param plist List类型指针
/// @param pos 位置
/// @return 如果找到,返回Data,反之,返回空Data
extern Data returnCopyDataByPos(List* plist, int pos);


/// @brief 通过Pos位置返回Data的,返回的是List中Data,说明可以通过这样修改数据
/// @param plist List类型指针
/// @param pos 位置
/// @return 如果找到,返回Data,反之,返回空Data
extern Data returnPtrDataByPos(List* plist, int pos);

/// @brief 判断数据是否在里面
/// @param plist List类型指针
/// @param inputData Data类型数据
/// @return 有就返回true,没有就false
extern bool hasDataInList(List* plist, Data inputData);




/// @brief 在链表的尾部插入节点
/// @param plist 链表指针
/// @param inputData Data类型数据
/// @return | -1-->节点创建失败 | 1-->节点创建成功,并成功写入数据 |
extern int insertDataAtEndInList(List* plist, Data inputData);


/// @brief 在链表的头部插入节点
/// @param plist 链表指针
/// @param inputData Data类型数据
/// @return | -1-->节点创建失败 | 1-->节点创建成功,并成功写入数据 |
extern int insertDataAtStartInList(List* plist, Data inputData);

/// @brief 在指定位置插入数据
/// @param plist 链表指针
/// @param inputData Data类型数据
/// @param pos 位置的范围在[0, list.size],范围的两端分别代表头插和尾插
/// @return | -1-->节点创建失败或者位置无效 | 1-->节点创建成功,并成功写入数据 |
extern int insertDataAtPosInList(List* plist, Data inputData, int pos);

/// @brief 删除链表头节点
/// @param plist 链表指针
/// @return 如果链表为空返回-1, 否则返回1
extern int delEndNodeInList(List* plist);


/// @brief 删除链表尾节点
/// @param plist 链表指针
/// @return 如果链表为空返回-1, 否则返回1
int delStartNodeInList(List* plist);

/// @brief 通过data来删除节点
/// @param plist 链表指针
/// @param inputData Data类型数据
/// @return 链表为空返回-1, 找不到对应的节点返回0, 删除成功返回1
extern int delNodeByData(List* plist, Data inputData);

/// @brief 通过位置删除节点
/// @param plist 链表指针
/// @param pos 要删除的位置
/// @return 如果链表为空或者位置有误返回-1, 删除成功返回1
extern int delNodeByPos(List* plist, int pos);


/// @brief 整合数据(不会复制,只是整合)
/// @param data void* data
/// @param content void* content
/// @param type 数据标签,尽量不要使用-1
/// @param valInfo InfoOfData类型数
/// @return 整合好的Data数据
extern Data stackData(void* data, void* content, int type, InfoOfData valInfo);


/// @brief 反转链表
/// @param plist 链表指针
extern void reverseList(List* plist);

/// @brief 打印链表数据
/// @param plist 链表指针
extern void printList(List* plist);

/// @brief 清除链表
/// @param plist 链表指针
extern void freeList(List* plist);


#endif


