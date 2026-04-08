#ifndef LRULIST_H
#define LRULIST_H

typedef struct lrunode {
    struct lrunode* next;   //下一节点
    struct lrunode* prev;
    int val;
} LRUNode;

typedef struct {
    LRUNode* head;
    LRUNode* tail;
    int size;
    int MAX;    //存储最大的大小
} LRUList;



/// @brief 判断缓存是否为空
/// @param plist LRUList的地址
/// @return 如果为空返回1 如果不为空返回0
bool isEmptyLRUList(LRUList* plist);

/// @brief 初始化链表,MAX为最大存储量
/// @param plist LRUList的地址
/// @param MAX 缓存的最大值
void initializeLRUList(LRUList* plist, int MAX);


/// @brief 删除最后的缓存
/// @param plist LRUList的地址
/// @return 成功删除返回1  无效删除返回0 空链表返回-1
int delEndNodeInLRUList(LRUList* plist);


/// @brief 删除最新的缓存
/// @param plist LRUList的地址
/// @return 成功删除返回1  无效删除返回0 空链表返回-1
int delStartNodeInLRUList(LRUList* plist);

/// @brief 通过缓存删除缓存
/// @param plist LRUList的地址
/// @param val 要删除的值
/// @return 成功删除返回1  无效删除返回0 空链表返回-1
int delNodeByValInLRUList(LRUList* plist, int val);

/// @brief 通过位置删除缓存
/// @param plist LRUList的地址
/// @param pos 要删除的位置
/// @return 成功删除返回1  无效删除返回0 空链表返回-1
int delNodeByPosInLRUList(LRUList* plist, int pos);

/// @brief 增加新缓存,如果已经存在,等同于查看缓存
/// @param plist LRUList的地址
/// @param val 要增加的值
/// @return 增加成功返回1 如果只是更新返回0 内存分配出错返回-1
int addNewValInLRUList(LRUList* plist, int val);

/// @brief 通过val来查看内容,同时更新内容
/// @param plist LRUList的地址
/// @param val 要查看的值
/// @return 如果找到返回这个节点的地址 如果没找到返回NULL
LRUNode* viewLRUNodeByVal(LRUList* plist, int val);

/// @brief 通过位置pos来查看内容,同时更新内容
/// @param plist LRUList的地址
/// @param pos 要查看的位置
/// @return 如果找到返回这个节点的地址 如果没找到返回NULL
LRUNode* viewLRUNodeByPos(LRUList* plist, int pos);

/// @brief 输出缓存内容
/// @param plist LRUList的地址
void generateLRUList(LRUList* plist);


/// @brief 清空缓存,开始设置的缓存最大值不变
/// @param plist LRUList的地址
void freeLRUList(LRUList* plist);
#endif