#ifndef LIST_H
#define LIST_H

enum info {
    Warning = -1,   //错误返回,pos范围不对,内存分配出错
    None = 0,   //相当于没操作,比如删除val,但val不存在
    Success = 1 //操作成功
};

//节点
typedef struct node {
    struct node* prev;
    int val;
    struct node* next;
} Node;

//双向链表
typedef struct {
    Node* head;
    Node* tail;
    int size;
} List;

//初始化链表
extern void initializeList(List* plist);

//通过val来找到节点,并返回节点,如果没找到,返回NULL
extern Node* findNodeByVal(List* plist, int val);


//通过位置来返回节点,如果没有,返回NULL,其中0 <= pos < size
extern Node* findNodeByPos(List* plist, int pos);

//在链表的尾部插入新元素
extern int insertNodeAtEnd(List* plist, int val);

//在链表的头部插入新元素
extern int insertNodeAtStart(List* plist, int val);

//在pos位置和pos-1位置的中间添加节点,0<=pos<=size
//如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
extern int insertNodeAtPos(List* plist, int val, int pos);

//删除头节点
extern int delStartNode(List* plist);

//删除尾节点
extern int delEndNode(List* plist);

//通过val来删除节点,如果有多个,删除第一个
extern int delNodeByVal(List* plist, int val);

//删除pos位置的节点
extern int delNodeByPos(List* plist, int pos);

//反转整个链表
extern void reverseList(List* plist);

//打印链表的val
extern void printList(List* plist);

//清除链表
extern void freeList(List* plist);

#endif