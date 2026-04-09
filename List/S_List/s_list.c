#include <stdio.h>
#include "s_list.h"
#include <stdlib.h>
// 链表的构建,搜索,删除,清除

enum info {
    Warning = -1,
    None = 0,
    Success = 1
};

//初始化链表
void initializeSList(SList* plist) {
    plist->head = NULL;
    plist->tail = NULL;
    plist->size = 0;
}


// 添加新元素到链表的尾部
int insertValAtEndInSList(SList* plist, int val) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    if (newNode == NULL) return Warning;   //如果分配出错,返回-1

    //初始化新得到的节点
    newNode->next = NULL;
    newNode->val = val;
    

    if (plist->head) {
        //如果不是空链表,将这个节点接到链表的尾部
        plist->tail->next = newNode;
    } else {
        // 如果为空链表,让头部为这个节点
        plist->head = newNode;
    }

    //不论是不是空链表,都要更新链表的尾部
    plist->tail = newNode;

    //链表大小++
    plist->size++;

    return Success;   //正常添加返回1
}

//添加新元素到链表的头部
int insertValAtStartInSList(SList* plist, int val) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    if (newNode == NULL) return Warning;   //如果分配出错,返回-1

    newNode->next = plist->head;  //将新节点指向原来的头部
    newNode->val = val;   //
    
    //如果为空链表,还要同时设置尾部
    if (plist->tail == NULL) {
        plist->tail = newNode;
        
    }
    plist->head = newNode;    //再将整个链表的头部设置为p

    plist->size++;  //链表大小++
    return Success;
}

//在pos位置和pos-1位置的中间添加节点,0<=pos<=size
//如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
int insertValAtPosInSList(SList* plist, int val, int pos) {

    //如果不符合位置范围,返回-1
    if (pos < 0 || pos > plist->size) return Warning; // 如果位置小于0,则返回-1代表错误
    
    //如果为在结尾或头添加,直接调用函数
    if (pos == 0) return insertValAtStartInSList(plist, val);
    if (pos == plist->size) return insertValAtEndInSList(plist, val);

    SNode* p = plist->head;  //正在判断是不是这个位置的节点的节点
    SNode* q = NULL; //p的前一个节点
    
    //通过循环得到位置对应的节点及前一个节点
    
    int i;
    for (i = 0; i < pos; i++) {
        q = p;
        p = p->next;
    }
    //创建新节点
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    if (newNode == NULL) return -1;   //如果分配出错,返回-1

    newNode->val = val;
    newNode->next = p;  //让这个新节点指向p
    q->next = newNode;
    
    
    
    plist->size++;
    return Success;
}

//找到链表中值为val的节点,如果有多个,返回第一个节点
SNode* findNodeByValInSList(SList* plist, int val) {
    SNode* p = NULL;
    for (p = plist->head; p; p = p->next) {
        if (p->val == val) {
            return p; 
        }
    }
    return NULL;
}

//通过pos来找到节点
SNode* findNodeByPosInSList(SList* plist, int pos) {
    if (pos < 0 || pos >= plist->size) return NULL; // 如果位置小于0,则返回-1代表错误
    SNode* p = plist->head;  //先初始化为头节点
    
    int i;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}


//删除头节点
int delStartNodeInSList(SList* plist) {
    if (plist->size == 0) return Warning;
    SNode* p = plist->head;

    if (plist->size > 1) {
        //
        plist->head = plist->head->next;
    } else {
        //如果只有一个节点,直接清空
        plist->head = plist->tail = NULL;
    }
    plist->size--;
    free(p);
    return Success;
}

//删除尾节点
int delEndNodeInSList(SList* plist) {
    if (plist->size == 0) return Warning;
    //找到最后一个节点及前一个节点
    SNode* p = plist->head;
    SNode* q = NULL;
    int i;
    for (i = 0; i < plist->size-1; i++) {
        q = p;
        p = p->next;
    }


    if (plist->size > 1) {
        q->next = NULL;
        plist->tail = q;
    } else {
        //如果只有一个节点,直接全部清空
        plist->head = plist->tail = NULL;
    }

    free(p);
    return Success;

}


//通过值来删除节点,如果存在多个节点,删除第一个
int delNodeByValInSList(SList* plist, int val) {
    
    SNode* p = plist->head; //正在搜索的节点
    SNode* q = NULL; //p的上一个节点

    for (; p; q = p, p = p->next) {
        //如果找到节点的值符合条件
        if (p->val == val) {

            if (p == plist->head) return delStartNodeInSList(plist);
            if (p == plist->tail) return delEndNodeInSList(plist);

            q->next = p->next;
            free(p);
            plist->size--;
            return Success;
        }
    }
    return None;
}

//通过在链表中的位置来删除节点
int delNodeByPosInSList(SList* plist, int pos) {
    //如果不符合位置范围,返回-1
    if (pos < 0 || pos >= plist->size) return Warning; // 如果位置小于0,则返回-1代表错误

    SNode* p = plist->head;  //搜索的节点p
    SNode* q = NULL; //p的前一个节点
    
    int i;
    for (i = 0; i < pos; i++) {
        q = p;
        p = p->next;
    }

    if (p == plist->head) return delStartNodeInSList(plist);
    if (p == plist->tail) return delEndNodeInSList(plist);

    q->next = p->next;
    free(p);
    plist->size--;
    return Success;
}

// 打印节点的所有值(只有属性int才可以使用这个函数)
void printSList(SList* list) {
    SNode* p;
    for (p = list->head; p; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}

//消除链表
void freeSList(SList* plist) {

    SNode* p = plist->head;  //当前节点
    SNode* q = NULL; //p的上一个节点
    //只要当前节点非空就执行
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeSList(plist);  //初始化
}

