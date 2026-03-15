#include <stdio.h>
#include "./list.h"
#include <stdlib.h>
// 链表的构建,搜索,删除,清除

//初始化链表
void initializeList(List* plist) {
    plist->head = NULL;
    plist->tail = NULL;
    plist->size = 0;
}


// 添加新元素到链表的尾部
int addNumInEnd(List* plist, int num) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return -1;   //如果分配出错,返回-1

    //初始化新得到的节点
    newNode->next = NULL;
    newNode->val = num;
    

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

    return 1;   //正常添加返回1
}

//添加新元素到链表的头部
int addNumInStart(List* plist, int num) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return -1;   //如果分配出错,返回-1

    newNode->next = plist->head;  //将新节点指向原来的头部
    newNode->val = num;   //
    plist->head = newNode;    //再将整个链表的头部设置为p
    
    //如果为空链表,还要同时设置尾部
    if (plist->tail == NULL) {
        plist->tail = newNode;
    }

    plist->size++;  //链表大小++
    return 1;
}

//在pos位置和pos-1位置的中间添加节点,0<=pos<=size
//如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
int addNumInPos(List* plist, int num, int pos) {

    //如果不符合位置范围,返回-1
    if (pos < 0 || pos > plist->size) return -1; // 如果位置小于0,则返回-1代表错误
    
    Node* p = plist->head;  //正在判断是不是这个位置的节点的节点
    Node* q = NULL; //p的前一个节点
    
    //通过循环得到位置对应的节点
    while (p && pos--) {
        q = p;
        p = p->next;
    }
    //创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return -1;   //如果分配出错,返回-1
    newNode->val = num;
    newNode->next = p;  //让这个新节点指向p

    
    if (p == NULL) {
        //如果p为空节点(在pos==size或者链表为空),更新尾节点为newNode
        plist->tail = newNode;
    }

    if (q) {
        //如果上一个节点不为空,那上一个节点指向这个新节点
        q->next = newNode;
    } else {
        //如果前一个节点为空(pos==0或者链表为空),让头节点为newNode
        plist->head = newNode;
    }
    plist->size++;
    return 1;
}

//找到链表中值为val的节点,如果有多个,返回第一个节点
Node* findNodeByVal(List* plist, int val) {
    Node* p = NULL;
    for (p = plist->head; p; p = p->next) {
        if (p->val == val) {
            return p; 
        }
    }
    return NULL;
}

//通过pos来找到节点
Node* findNodeByPos(List* plist, int pos) {
    if (pos < 0 || pos >= plist->size) return NULL; // 如果位置小于0,则返回-1代表错误
    Node* p = plist->head;  //先初始化为头节点
    while (p && pos--) {
        p = p->next;
    }
    return p;
}

//通过值来删除节点,如果存在多个节点,删除第一个
int delNodeByVal(List* plist, int val) {
    
    Node* p = NULL; //正在搜索的节点
    Node* q = NULL; //p的上一个节点

    for (p = plist->head; p; q = p, p = p->next) {
        //如果找到节点的值符合条件
        if (p->val == val) {

            
            if (q) {
                // 如果不是空节点,让上一个节点指向这个节点的下一个节点
                q->next = p->next;
            } else {
                // 如果要删除的节点就是第一个节点,那这个时候的q还是空指针,就让头节点为p的下一个节点
                plist->head = p->next;
            }
            // 如果要删除的节点是最后一个,那我们更新最后的节点
            if (p == plist->tail) {
                plist->tail = q;
            }
            //消除当前节点
            free(p);
            plist->size--;  
            return 1;
        }
    }
    return 0;
}

//通过在链表中的位置来删除节点
int delNodeByPos(List* plist, int pos) {
    //如果不符合位置范围,返回-1
    if (pos < 0 || pos >= plist->size) return -1; // 如果位置小于0,则返回-1代表错误

    Node* p = plist->head;  //搜索的节点p
    Node* q = NULL; //p的前一个节点
    
    //通过循环得到位置对应的节点
    while (p && pos--) {
        q = p;
        p = p->next;
    }
    //这里注意一点,p不可能为空,有范围限制

    if (q) {
        q->next = p->next;
    } else {
        plist->head = p->next;
    }

    if (p == plist->tail) {
        plist->tail = q;
    }

    free(p);
    plist->size--;
    return 1;
}

// 打印节点的所有值(只有属性int才可以使用这个函数)
void printList(List* list) {
    Node* p;
    for (p = list->head; p; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}

//消除链表
void freeList(List* plist) {

    Node* p = plist->head;  //当前节点
    Node* q = NULL; //p的上一个节点
    //只要当前节点非空就执行
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeList(plist);  //初始化
}

