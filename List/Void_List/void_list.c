#include "void_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static enum info {
    Warning = -1,
    None = 0,
    Success = 1
};


bool isEmptyList(List* plist) {
    return plist->size == 0;
}

void initializeList(List* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
}





Node* findNodeByData(List* plist, void* data, Compare cmp) {
    if (isEmptyList(plist)) return NULL;
    Node* p = plist->head;
    for (; p; p = p->next) {
        if (cmp(p->data, data) == 0) {
            return p;
        }
    }
    return NULL;
}

Node* findNodeByPos(List* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    Node* p = plist->head;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}

/// @brief 创建节点
/// @param data 节点数据指针
/// @param sizeofdata 节点数据所占字节数
/// @return 创建的新节点(data和sizeofdata已经赋值),如果无法创建,返回NULL
static Node* creatNode(void* data, int sizeofdata) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL; 
    void* newData = (void*)malloc(sizeofdata);
    if (newData == NULL) {
        free(newNode);
        return NULL;
    }
    memcpy(newData, data, sizeofdata);
    newNode->data = newData;
    newNode->sizeofdata = sizeofdata;
    return newNode;
}

int insertNodeAtEndInList(List* plist, void* data, int sizeofdata) {
    Node* newNode = creatNode(data, sizeofdata);
    if (newNode == NULL) return Warning; 
    //creatNode函函数已经处理了data的复制了
    newNode->next = NULL;
    newNode->prev = plist->tail;
   
    
    if (plist->size) {
        plist->tail->next = newNode;
        plist->tail = newNode;
    } else {
        plist->head = plist->tail = newNode;
    }
    
    plist->size++;
    return Success;
}


int insertNodeAtStartInList(List* plist, void* data, int sizeofdata) {
    Node* newNode = creatNode(data, sizeofdata);
    if (newNode == NULL) return Warning; 
    
    //creatNode函函数已经处理了data的复制了
    newNode->next = plist->head;
    newNode->prev = NULL;

    if (plist->size) {
        plist->head->prev = newNode;
        plist->head = newNode;
    } else {
        plist->head = plist->tail = newNode;
    }
    
    plist->size++;
    return Success;
}

int insertNodeAtPosInList(List* plist, void* data, int sizeofdata, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertNodeAtStartInList(plist, data, sizeofdata);
    if (pos == plist->size) return insertNodeAtEndInList(plist, data, sizeofdata);

    Node* newNode = creatNode(data, sizeofdata);
    if (newNode == NULL) return Warning; 
    
    Node* p = findNodeByPos(plist, pos);
    
    //creatNode函函数已经处理了data的复制
    newNode->next = p;
    newNode->prev = p->prev;

    p->prev->next = newNode;
    p->prev = newNode;

    plist->size++;
    return Success;
}

int delEndNodeInList(List* plist) {
    if (isEmptyList(plist)) return Warning;

    free(plist->tail->data);

    Node* p = plist->tail;
    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }
    free(p);
    plist->size--;
    return Success;
}
int delStartNodeINList(List* plist) {
    if (isEmptyList(plist)) return Warning;

    free(plist->head->data);

    Node* p = plist->head;
    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }
    free(p);
    plist->size--;
    return Success;
}

int delNodeByData(List* plist, void* data, Compare cmp) {
    if (isEmptyList(plist)) return Warning;
    Node* p = findNodeByData(plist, data, cmp);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeINList(plist);
    if (p == plist->tail) return delEndNodeINList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p->data);
    free(p);
    plist->size--;
    return Success;
}
int delNodeByPos(List* plist, int pos) {
    if (isEmptyList(plist)) return Warning;
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    Node* p = findNodeByPos(plist, pos);
    if (p == plist->head) return delStartNodeINList(plist);
    if (p == plist->tail) return delEndNodeINList(plist);

    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p->data);
    free(p);
    plist->size--;
    return Success;
}

void reverseList(List* plist) {
    if (plist->size < 2) return;
    Node* temp = NULL;
    Node* p = plist->head;
    while (p) {
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;
        
        p = p->prev;
    }
    temp = plist->head;
    plist->head = plist->tail;
    plist->tail = temp;
}


typedef void (*Print)(const void* data);
void printList(List* plist, Print print) {
    Node* p = plist->head;
    for (; p; p = p->next) {
        print(p->data);
    }
    printf("\n");
}



void freeList(List* plist) {
    Node* p = plist->head;
    Node* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q->data);
        free(q);
    }
    initializeList(plist);
}


void sortList(List* plist, Compare cmp) {
    if (plist->size < 2) return;
    Node* p = plist->head;
    // i以及i之前的节点的都是有序区
    for (int i = 0; i < plist->size-1; i++, p = p->next) {
        void* temp_data = p->next->data;
        int temp_sizeofdata = p->next->sizeofdata;
        Node* q = p;
        for (int j = i; j >= 0; j--, q = q->prev) {
            if (cmp(q->data, temp_data) > 0) {
                q->next->data = q->data;
                q->next->sizeofdata = q->sizeofdata;
            } else {
                break;
            }
        }
        if (q) {
            q->next->data = temp_data;
            q->next->sizeofdata = temp_sizeofdata;
        } else {
            plist->head->data = temp_data;
            plist->head->sizeofdata = temp_sizeofdata;
        }
    }
}