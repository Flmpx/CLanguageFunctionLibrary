#include "c_d_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


static enum info {
    Warning = -1,
    None = 0,
    Success = 1
};


void initializeCDList(CDList* plist) {
    plist->head = NULL;
    plist->size = 0;
}

bool isEmptyCDList(CDList* plist) {
    return plist->size == 0 ? true : false;
}


CDNode* findNodeByValInCDList(CDList* plist, int val) {
    int i;
    CDNode* p = plist->head;
    for (i = 0; i < plist->size; i++, p = p->next) {
        if (p->val == val) {
            return p;
        }
    }
    return NULL;
}
CDNode* findNodeByPosInCDList(CDList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    int i;
    CDNode* p = plist->head;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}

int insertValAtEndInCDList(CDList* plist, int val) {
    CDNode* newNode = (CDNode*)malloc(sizeof(CDNode));
    if (newNode == NULL) return Warning;
    newNode->val = val;
    if (plist->size) {
        newNode->next = plist->head;
        newNode->prev = plist->head->prev;
        plist->head->prev->next = newNode;
        plist->head->prev = newNode;
    } else {
        newNode->next = newNode;
        newNode->prev = newNode;
        plist->head = newNode;
    }
    plist->size++;
    return Success;
}
int insertValAtStartInCDList(CDList* plist, int val) {
    CDNode* newNode = (CDNode*)malloc(sizeof(CDNode));
    if (newNode == NULL) return Warning;
    newNode->val = val;

    if (plist->size) {
        newNode->next = plist->head;
        newNode->prev = plist->head->prev;
        plist->head->prev->next = newNode;
        plist->head->prev = newNode;
        plist->head = newNode;
    } else {
        plist->head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    plist->size++;
    return Success;
}
int insertValAtPosInCDList(CDList* plist, int val, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertValAtStartInCDList(plist, val);
    if (pos == plist->size) return insertValAtEndInCDList(plist, val);

    CDNode* newNode = (CDNode*)malloc(sizeof(CDNode));
    if (newNode == NULL) return Warning;
    CDNode* p = findNodeByPosInCDList(plist, pos);
    newNode->val = val;

    newNode->next = p;
    newNode->prev = p->prev;
    p->prev->next = newNode;
    p->prev = newNode;
    plist->size++;
    return Success;
}

int delStartNodeInCDList(CDList* plist) {
    if (isEmptyCDList(plist)) return Warning;
    CDNode* p = plist->head;
    if (plist->size > 1) {
        plist->head->prev->next = plist->head->next;
        plist->head->next->prev = plist->head->prev;
        plist->head = plist->head->next;
    } else {
        plist->head = NULL;
    }
    free(p);
    plist->size--;
    return Success;
}

int delEndNodeInCDList(CDList* plist) {
    if (isEmptyCDList(plist)) return Warning;
    CDNode* p = plist->head->prev;
    if (plist->size > 1) {
        plist->head->prev = plist->head->prev->prev;
        plist->head->prev->next = plist->head;
    } else {
        plist->head = NULL;
    }
    free(p);
    plist->size--;
    return Success;
}

int delNodeByValInCDList(CDList* plist, int val) {
    if (isEmptyCDList(plist)) return Warning;
    CDNode* p = findNodeByValInCDList(plist, val);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeInCDList(plist);
    if (p == plist->head->prev) return delEndNodeInCDList(plist);

    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    plist->size--;
    return Success;
}

int delNodeByPosInCDList(CDList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    if (pos == 0) return delStartNodeInCDList(plist);
    if (pos == plist->size-1) return delEndNodeInCDList(plist);

    CDNode* p = findNodeByPosInCDList(plist, pos);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    plist->size--;
    return Success;
}

void reverseCircleList(CDList* plist) {
    if (plist->size < 2) return;
    CDNode* temp = NULL;
    int i;
    CDNode* p = plist->head;
    for (i = 0; i < plist->size; i++) {
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;

        p = p->prev;    //已经倒置,这里的前即原来的后
    }
    plist->head = plist->head->next;    //已经倒置了,所以原来的最后一个为头节点的下一个
}
void printCDListFromStart(CDList* plist) {
    if (isEmptyCDList(plist)) return;
    int i;
    CDNode* p = plist->head;
    for (i = 0; i < plist->size; i++, p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}
void printCDListFromPos(CDList* plist, int pos) {
    if (isEmptyCDList(plist)) return;
    if ((pos < 0) || (pos >= plist->size)) return;
    int i;
    CDNode* p = findNodeByPosInCDList(plist, pos);
    for (i = 0; i < plist->size; i++, p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}
void freeCDList(CDList* plist) {
    if (isEmptyCDList(plist)) return;
    CDNode* p = plist->head;
    CDNode* q = plist->head->prev;    //可以直接设q = NULL,但是从语义上来说q时p的前一个
    int i;
    for (i = 0; i < plist->size; i++) {
        q = p;
        p  = p->next;
        free(q);
    }
    initializeCDList(plist);
}
