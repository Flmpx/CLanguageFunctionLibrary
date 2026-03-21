#include <stdio.h>
#include <stdlib.h>
#include "d_list.h"


static enum info {
    Warning = -1,   //错误返回,pos范围不对,内存分配出错
    None = 0,   //相当于没操作,比如删除val,但val不存在
    Success = 1 //操作成功
};
//初始化链表
void initializeDList(DList* plist) {
    plist->head = NULL;
    plist->tail = NULL;
    plist->size = 0;
}

//通过val来找到节点,并返回节点,如果没找到,返回NULL
DNode* findNodeByValInDList(DList* plist, int val) {
    DNode* p = plist->head;
    for (; p; p = p->next) {
        if (p->val == val) {
            return p;
        }
    }
    return NULL;
}


//通过位置来返回节点,如果没有,返回NULL,其中0 <= pos < size
DNode* findNodeByPosInDList(DList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    DNode* p = plist->head;

    //循环找到位置为pos的节点
    int i;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }

    return p;
}



//在链表的尾部插入新元素
int insertNodeAtEndInDList(DList* plist, int val) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) return Warning;

    // 初始化这个新节点
    newNode->next = NULL;
    newNode->prev = plist->tail;    
    newNode->val = val;

    if (plist->size > 0) {
        //非空链表
        plist->tail->next = newNode;
    } else {
        //空链表
        plist->head = newNode;
    }
    plist->tail = newNode;  //更改尾节点
    plist->size++;
    return Success;
}

//在链表的头部插入新元素
int insertNodeAtStartInDList(DList* plist, int val) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) return Warning;

    // 初始化这个节点
    newNode->next = plist->head;
    newNode->prev = NULL;
    newNode->val = val;

    if (plist->size > 0) {
        //非空链表
        plist->head->prev = newNode;
    } else {
        //空链表
        plist->tail = newNode;
    }
    
    plist->head = newNode;  //更改头节点
    plist->size++;
    return Success;
}


//在pos位置和pos-1位置的中间添加节点,0<=pos<=size
//如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
int insertNodeAtPosInDList(DList* plist, int val, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;

    // 如果为特殊情况,直接调用其他函数
    if (pos == 0) return insertNodeAtStartInDList(plist, val);
    if (pos == plist->size) return insertNodeAtEndInDList(plist, val);

    //调用函数找到在pos位置的节点
    DNode* p = findNodeByPosInDList(plist, pos);


    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) return Warning;


    newNode->val = val;
    newNode->next = p;
    newNode->prev = p->prev;
    p->prev->next = newNode;
    p->prev = newNode;

    plist->size++;
    return Success;
}


//删除头节点
int delStartNodeInDList(DList* plist) {
    if (plist->size == 0) return Warning;
    DNode* p = plist->head;  //让p指向头节点
    
    if (plist->size == 1) {
        //如果数目只有一个,那直接清空
        plist->head = plist->tail = NULL;
    } else {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    }
    free(p);
    plist->size--;
    return Success;
}

//删除尾节点
int delEndNodeInDList(DList* plist) {
    if (plist->size == 0) return Warning;
    DNode* p = plist->tail;  //让p指向尾节点
    
    if (plist->size == 1) {
        //数目为1,直接清空
        plist->head = plist->tail = NULL;
    } else {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    }
    free(p);
    plist->size--;
    return Success;
}

//通过val来删除节点,如果有多个,删除第一个
int delNodeByValInDList(DList* plist, int val) {

    DNode* p = findNodeByValInDList(plist, val);

    if (p == NULL) return None;

    //特殊情况调用其他函数
    if (p == plist->head) return delStartNodeInDList(plist);
    if (p == plist->tail) return delEndNodeInDList(plist);

    p->prev->next = p->next;
    p->next->prev = p->prev;

    free(p);
    plist->size--;
    return Success;
}

//删除pos位置的节点
int delNodeByPosInDList(DList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return Warning;

    //特殊情况,调用函数
    if (pos == 0) return delStartNodeInDList(plist);
    if (pos == plist->size-1) return delEndNodeInDList(plist);

    DNode* p = findNodeByPosInDList(plist, pos);

    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    plist->size--;
    return Success;

}

//反转整个链表
void reverseDList(DList* plist) {
    if (plist->size < 2) return;
    DNode* p = plist->head;
    DNode* temp = NULL;
    while (p) {
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;
        p = p->prev;    //由于已经倒转,现在的前一个指向原来的后一个
    }

    //交换头和尾
    temp = plist->head;
    plist->head = plist->tail;
    plist->tail = temp;
}

//打印链表的val
void printDList(DList* plist) {
    DNode* p = plist->head;
    for (; p; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}

//清除链表
void freeDList(DList* plist) {
    DNode* p = plist->head;
    DNode* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeDList(plist);
}
