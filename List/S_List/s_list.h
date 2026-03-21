#ifndef S_LIST_H
#define S_LIST_H

typedef struct snode {
    int val;    //链表的值--->可以自定义其他类型或自定义结构体
    struct snode* next;  //下一节点的地址
} SNode;

typedef struct {
    SNode* head; //链表的头部
    SNode* tail; //链表的尾部
    int size;   //链表的大小
} SList;



//初始化链表
extern void initializeSList(SList* plist);

// 添加新元素到链表的尾部
extern int insertValAtEndInSList(SList* plist, int num);

//添加新元素到链表的头部
extern int insertValAtStartInSList(SList* plist, int num);


//在pos位置和pos-1位置的中间添加节点,0<=pos<=size
//如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
extern int insertValAtPosInSList(SList* plist, int num, int pos);


//找到链表中值为val的节点,如果有多个,返回第一个节点
extern SNode* findNodeByValInSList(SList* plist, int val); 

//通过pos来找到节点
extern SNode* findNodeByPosInSList(SList* plist, int pos);

//通过值来删除节点,如果存在多个节点,删除第一个
extern int delNodeByValInSList(SList* plist, int val);

//删除头节点
int delStartNodeInSList(SList* plist);

//删除尾节点
int delEndNodeInSList(SList* plist);

//通过在链表中的位置来删除节点
extern int delNodeByPosInSList(SList* plist, int pos);

// 打印节点的所有值(只有属性int才可以使用这个函数)
extern void printSList(SList* list); 

//消除链表
extern void freeSList(SList* plist); 


#endif