#ifndef LIST_H
#define LIST_H


enum info {
    Warning = -1,
    None = 0,
    Success = 1
};

typedef struct node {
    int val;    //链表的值--->可以自定义其他类型或自定义结构体
    struct node* next;  //下一节点的地址
} Node;

typedef struct {
    Node* head; //链表的头部
    Node* tail; //链表的尾部
    int size;   //链表的大小
} List;



//初始化链表
extern void initializeList(List* plist);

// 添加新元素到链表的尾部
extern int insertValAtEnd(List* plist, int num);

//添加新元素到链表的头部
extern int insertValAtStart(List* plist, int num);


//在pos位置和pos-1位置的中间添加节点,0<=pos<=size
//如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
extern int insertValAtPos(List* plist, int num, int pos);


//找到链表中值为val的节点,如果有多个,返回第一个节点
extern Node* findNodeByVal(List* plist, int val); 

//通过pos来找到节点
extern Node* findNodeByPos(List* plist, int pos);

//通过值来删除节点,如果存在多个节点,删除第一个
extern int delNodeByVal(List* plist, int val);

//删除头节点
int delStartNode(List* plist);

//删除尾节点
int delEndNode(List* plist);

//通过在链表中的位置来删除节点
extern int delNodeByPos(List* plist, int pos);

// 打印节点的所有值(只有属性int才可以使用这个函数)
extern void printList(List* list); 

//消除链表
extern void freeList(List* plist); 


#endif