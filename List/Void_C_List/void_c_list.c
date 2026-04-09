#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "void_c_list.h"

static enum info {
    Warning = -1,
    None = 0,
    Success = 1
};


bool isEmptyCList(CList* plist) {
    return plist->size == 0;
}

void initializeCList(CList* plist) {
    plist->head = NULL;
    plist->size = 0;
}


CNode* findCNodeByData(CList* plist, void* data, Compare cmp) {
    if (isEmptyCList(plist)) return NULL;
    CNode* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        if (cmp(p->data, data) == 0) {
            return p;
        }
    }
    return NULL;
}

CNode* findCNodeByPos(CList* plist, int pos) {
    if (isEmptyCList(plist)) return NULL;
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    CNode* p = plist->head;
    if (pos > plist->size/2) {
        int diff = plist->size-pos;
        for (int i = 0; i < diff; i++) {
            p = p->prev;
        }
    } else {
        for (int i = 0; i < pos; i++) {
            p = p->next;
        }
    }
    return p;
}


/// @brief 创建新节点
/// @param data 数据指针
/// @param sizeofdata 数据所占字节数
/// @return 如果创建成功返回节点,如果创建失败返回NULL
CNode* creatCNode(void* data, int sizeofdata) {
    CNode* newCNode = (CNode*)malloc(sizeof(CNode));
    if (newCNode == NULL) return NULL;
    void* newData = (void*)malloc(sizeofdata);
    if (newData == NULL) {
        free(newCNode);
        return NULL;
    }
    memcpy(newData, data, sizeofdata);
    newCNode->data = newData;
    newCNode->sizeofdata = sizeofdata;
    return newCNode;
}

int insertDataAtEndInCList(CList* plist, void* data, int sizeofdata) {
    CNode* newCNode = creatCNode(data, sizeofdata);
    if (newCNode == NULL) return Warning;

    if (plist->size) {
        newCNode->next = plist->head;
        newCNode->prev = plist->head->prev;
        plist->head->prev->next = newCNode;
        plist->head->prev = newCNode;
    } else {
        plist->head = newCNode;
        newCNode->next = newCNode;
        newCNode->prev = newCNode;
    }
    plist->size++;
    return Success;
}




int insertDataAtStartInCList(CList* plist, void* data, int sizeofdata) {
    CNode* newCNode = creatCNode(data, sizeofdata);
    if (newCNode == NULL) return Warning;
    
    if (plist->size) {
        newCNode->next = plist->head;
        newCNode->prev = plist->head->prev;
        plist->head->prev->next = newCNode;
        plist->head->prev = newCNode;
    } else {
        newCNode->next = newCNode;
        newCNode->prev = newCNode;
    }
    plist->head = newCNode;
    plist->size++;
    return Success;
}


int insertDataAtPosInCList(CList* plist, void* data, int sizeofdata, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertDataAtStartInCList(plist, data, sizeofdata);
    if (pos == plist->size) return insertDataAtEndInCList(plist, data, sizeofdata);

    //创建元素
    CNode* newCNode = creatCNode(data, sizeofdata);
    if (newCNode == NULL) return Warning;

    CNode* p = findCNodeByPos(plist, pos);

    newCNode->next = p;
    newCNode->prev = p->prev;
    p->prev->next = newCNode;
    p->prev = newCNode;

    plist->size++;
    return Success;
}


int delStartCNode(CList* plist) {
    if (isEmptyCList(plist)) return Warning;
    
    CNode* p = plist->head;
    if (plist->size > 1) {
        plist->head->prev->next = plist->head->next;
        plist->head->next->prev = plist->head->prev;
        plist->head = plist->head->next;
    } else {
        plist->head = NULL;
    }
    
    free(p->data);
    free(p);
    plist->size--;
    return Success;
}

int delEndCNode(CList* plist) {
    if (isEmptyCList(plist)) return Warning;
    
    CNode* p = plist->head->prev;
    
    if (plist->size > 1) {
        plist->head->prev = plist->head->prev->prev;
        plist->head->prev->next = plist->head;
    } else {
        plist->head = NULL;
    }
    
    free(p->data);
    free(p);
    plist->size--;
    return Success;
}


int delCNodeByData(CList* plist, void* data, Compare cmp) {
    if (isEmptyCList(plist)) return Warning;
    CNode* p = findCNodeByData(plist, data, cmp);
    if (p == NULL) return None;
    
    if (p == plist->head) return delStartCNode(plist);
    if (p == plist->head->prev) return delEndCNode(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p->data);
    free(p);
    plist->size--;
    return Success;
}

int delCNodeByPos(CList* plist, int pos) {
    if (isEmptyCList(plist)) return Warning;
    
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    CNode* p = findCNodeByPos(plist, pos);
    if (p == NULL) return None;
    
    if (p == plist->head) return delStartCNode(plist);
    if (p == plist->head->prev) return delEndCNode(plist);

    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p->data);
    free(p);
    plist->size--;
    return Success;
}


void reverCList(CList* plist) {
    if (plist->size < 2) return;
    CNode* temp = NULL;
    CNode* p = plist->head;
    for (int i = 0; i < plist->size; i++) {
        temp = p->prev;
        p->prev = p->next;
        p->next = temp;

        p = p->prev;
    }

    plist->head = plist->head->next;        //已经倒置了,所以原来的最后一个为头节点的下一个
}



void printCListFromStart(CList* plist, Print print) {
    if (isEmptyCList(plist)) return;
    CNode* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        print(p->data);
    }
    printf("\n");
}

void printCListFromPos(CList* plist, Print print, int pos) {
    if (isEmptyCList(plist)) return;
    if ((pos < 0) || (pos >= plist->size)) return;
    CNode* p = findCNodeByPos(plist, pos);
    
    for (int i = 0; i < plist->size; i++, p = p->next) {
        print(p->data);
    }
    printf("\n");
}

void freeCList(CList* plist) {
    if (isEmptyCList(plist)) return;
    CNode* p = plist->head;
    CNode* q = plist->head->prev;
    for (int i = 0; i < plist->size; i++) {
        q = p;
        p = p->next;
        free(q->data);
        free(q);
    }
    initializeCList(plist);
}