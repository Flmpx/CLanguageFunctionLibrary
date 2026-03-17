#include <stdio.h>
#include <stdlib.h>
#include <list.h>


//初始化链表
void initializeList(List* plist) {
    plist->head = NULL;
    plist->tail = NULL;
    plist->size = 0;
}

//通过val来找到节点,并返回节点,如果没找到,返回NULL
Node* findNodeByVal(List* plist, int val) {
    Node* p = plist->head;
    for (; p; p = p->next) {
        if (p->val == val) {
            return p;
        }
    }
    return NULL;
}


//通过位置来返回节点,如果没有,返回NULL,其中0 <= pos < size
Node* findNodeByPos(List* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    Node* p = plist->head;

    //循环找到位置为pos的节点
    int i;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }

    return p;
}



//在链表的尾部插入新元素
int insertNodeAtEnd(List* plist, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
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
int insertNodeAtStart(List* plist, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
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
int insertNodeAtPos(List* plist, int val, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;

    // 如果为特殊情况,直接调用其他函数
    if (pos == 0) return insertNodeAtStart(plist, val);
    if (pos == plist->size) return insertNodeAtEnd(plist, val);

    //调用函数找到在pos位置的节点
    Node* p = findNodeByPos(plist, pos);


    Node* newNode = (Node*)malloc(sizeof(Node));
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
int delStartNode(List* plist) {
    if (plist->size == 0) return Warning;
    Node* p = plist->head;  //让p指向头节点
    
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
int delEndNode(List* plist) {
    if (plist->size == 0) return Warning;
    Node* p = plist->tail;  //让p指向尾节点
    
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
int delNodeByVal(List* plist, int val) {

    Node* p = findNodeByVal(plist, val);

    if (p == NULL) return None;

    //特殊情况调用其他函数
    if (p == plist->head) return delStartNode(plist);
    if (p == plist->tail) return delEndNode(plist);

    p->prev->next = p->next;
    p->next->prev = p->prev;

    free(p);
    plist->size--;
    return Success;
}

//删除pos位置的节点
int delNodeByPos(List* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return Warning;

    //特殊情况,调用函数
    if (pos == 0) return delStartNode(plist);
    if (pos == plist->size-1) return delEndNode(plist);

    Node* p = findNodeByPos(plist, pos);

    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    plist->size--;
    return Success;

}

//反转整个链表
void reverseList(List* plist) {
    if (plist->size < 2) return;
    Node* p = plist->head;
    Node* temp = NULL;
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
void printList(List* plist) {
    Node* p = plist->head;
    for (; p; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}

//清除链表
void freeList(List* plist) {
    Node* p = plist->head;
    Node* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeList(plist);
}
