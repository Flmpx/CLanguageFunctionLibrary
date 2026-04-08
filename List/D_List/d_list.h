#ifndef D_LIST_H
#define D_LIST_H



//节点
typedef struct dnode {
    struct dnode* prev;
    int val;
    struct dnode* next;
} DNode;

//双向链表
typedef struct {
    DNode* head;
    DNode* tail;
    int size;
} DList;

//初始化链表
extern void initializeDList(DList* plist);

//通过val来找到节点,并返回节点,如果没找到,返回NULL
extern DNode* findNodeByValInDList(DList* plist, int val);


//通过位置来返回节点,如果没有,返回NULL,其中0 <= pos < size
extern DNode* findNodeByPosInDList(DList* plist, int pos);

//在链表的尾部插入新元素
extern int insertNodeAtEndInDList(DList* plist, int val);

//在链表的头部插入新元素
extern int insertNodeAtStartInDList(DList* plist, int val);

//在pos位置和pos-1位置的中间添加节点,0<=pos<=size
//如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
extern int insertNodeAtPosInDList(DList* plist, int val, int pos);

//删除头节点
extern int delStartNodeInDList(DList* plist);

//删除尾节点
extern int delEndNodeInDList(DList* plist);

//通过val来删除节点,如果有多个,删除第一个
extern int delNodeByValInDList(DList* plist, int val);

//删除pos位置的节点
extern int delNodeByPosInDList(DList* plist, int pos);

//反转整个链表
extern void reverseDList(DList* plist);

//打印链表的val
extern void printDList(DList* plist);

//清除链表
extern void freeDList(DList* plist);

#endif