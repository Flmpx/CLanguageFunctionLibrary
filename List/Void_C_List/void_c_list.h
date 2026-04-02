#ifndef VOID_C_LIST
#define VOID_C_LIST
#include <stdbool.h>

/// @brief 循环链表节点
typedef struct cnode {
    struct cnode* next;
    struct cnode* prev;
    void* data;
    int sizeofdata;
} CNode;

/// @brief 循环链表
typedef struct {
    CNode* head;
    int size;
} CList;


/// @brief 检查链表是否为空
/// @param plist 链表指针
/// @return 链表为空返回1,否则返回0
bool isEmptyCList(CList* plist);

/// @brief 初始化链表,使用前必须初始化
/// @param plist 链表指针
void initializeCList(CList* plist);

/// @brief 比较函数指针类型
typedef int (*Compare)(const void* a, const void* b);


/// @brief 通过data得到当前节点
/// @param plist 链表指针
/// @param data 数据指针
/// @param cmp 自己提供比较函数
/// @return 找到返回节点指针,没找到或者链表为空返回NULL
CNode* findCNodeByData(CList* plist, void* data, Compare cmp);


/// @brief 通过位置返回节点指针
/// @param plist 链表指针
/// @param pos 位置(pos的范围为[0, list.size-1])
/// @return 找到位置节点返回节点指针,没找到,链表为空或者位置不对返回NULL
CNode* findCNodeByPos(CList* plist, int pos);



/// @brief 进行尾插
/// @param plist 链表指针
/// @param data 数据指针
/// @param sizeofdata 数据所占字节数
/// @return 如果节点创建失败返回-1, 如果成功返回1
int insertDataAtEndInCList(CList* plist, void* data, int sizeofdata);

/// @brief 进行头插
/// @param plist 链表指针
/// @param data 数据指针
/// @param sizeofdata 数据所占字节数
/// @return 如果节点创建失败返回-1, 如果成功返回1
int insertDataAtStartInCList(CList* plist, void* data, int sizeofdata);


/// @brief 再指定位置的前面插入新数据
/// @param plist 链表指针
/// @param data 数据指针
/// @param sizeofdata 数据所占字节数
/// @param pos 位置(pos的范围为[0, list.size], 如果pos=0,等于头插,如果pos=list.size,等于尾插)
/// @return 如果位置非法或者节点创建失败,返回-1, 如果成功返回1
int insertDataAtPosInCList(CList* plist, void* data, int sizeofdata, int pos);


/// @brief 删除头节点
/// @param plist 链表指针
/// @return 如果链表为空,返回-1,删除成功返回1
int delStartCNode(CList* plist);

/// @brief 删除尾节点
/// @param plist 链表指针
/// @return 如果链表为空,返回-1,删除成功返回1
int delEndCNode(CList* plist);

/// @brief 通过data删除节点
/// @param plist 链表指针
/// @param data 数据指针
/// @param cmp 自己提供比较函数
/// @return 如果链表为空返回-1, 如果是无效删除(没找到data)返回0, 删除成功返回1
int delCNodeByData(CList* plist, void* data, Compare cmp);


/// @brief 通过pos删除节点
/// @param plist 链表指针
/// @param pos 位置(pos的范围为[0, list.size-1])
/// @return 如果链表为空,位置非法返回-1, 如果没找该位置(不可能)返回0, 删除成功返回1
int delCNodeByPos(CList* plist, int pos);

/// @brief 反转链表
/// @param plist 链表指针
void reverCList(CList* plist);

/// @brief 打印函数指针类型
typedef void (*Print)(const void* a);

/// @brief 从头开始打印链表
/// @param plist 链表指针
/// @param print 自己提供打印函数
void printCListFromStart(CList* plist, Print print);

/// @brief 从任意位置开始打印链表
/// @param plist 链表指针
/// @param print 自己提供打印函数
/// @param pos 位置(pos的范围为[0, list.size-1],如果位置非法,则不打印)
void printCListFromPos(CList* plist, Print print, int pos);

/// @brief 清空链表数据
/// @param plist 链表指针
void freeCList(CList* plist);




#endif