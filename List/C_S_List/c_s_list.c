#include "c_s_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static enum info {
    Warning = -1,
    None = 0,
    Success = 1
};

//判断循环单链表是不是空链表
bool isEmptyCSList(CSList* plist) {
    return plist->size == 0 ? true : false;
}


void initializeCSList(CSList* plist) {
    plist->size = 0;
    plist->tail = NULL;
}

int insertValAtEndInCSList(CSList* plist, int val) {
    CSNode* newNode = (CSNode*)malloc(sizeof(CSNode));
    if (newNode == NULL) return Warning;
    newNode->val = val;

    if (plist->size) {
        newNode->next = plist->tail->next; //为头节点
        plist->tail->next = newNode;
        plist->tail = newNode;
    } else {
        plist->tail = newNode;
        newNode->next = newNode;
    }
    plist->size++;
    return Success;
}

int insertValAtStartInCSList(CSList* plist, int val) {
    CSNode* newNode = (CSNode*)malloc(sizeof(CSNode));
    if (newNode == NULL) return Warning;
    newNode->val = val;
    if (plist->size) {
        newNode->next = plist->tail->next;
        plist->tail->next = newNode;
    } else {
        plist->tail = newNode;
        newNode->next = newNode;
    }
    plist->size++;
    return Success;
} 

int insertValAtPosInCSList(CSList* plist, int val, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertValAtStartInCSList(plist, val);
    if (pos == plist->size) return insertValAtEndInCSList(plist, val);

    CSNode* p = plist->tail->next;    //头节点
    CSNode* q = plist->tail; //p的前一个节点
    int i;
    for (i = 0; i < pos; i++) {
        q = p;
        p = p->next;
    }
    CSNode* newNode = (CSNode*)malloc(sizeof(CSNode));
    if (newNode == NULL) return Warning;
    newNode->val = val;
    newNode->next = p;
    q->next = newNode;
    plist->size++;
    return Success;
}

CSNode* findNodeByValInCSList(CSList* plist, int val) {
    if (isEmptyCSList(plist)) return NULL;
    CSNode* p = plist->tail->next;
    
    int i;
    for (i = 0; i < plist->size; i++, p = p->next) {
        if (p->val == val) {
            return p;
        }
    }
    return NULL;
}
CSNode* findNodeByPosInCSList(CSList* plist, int pos) {
    if (isEmptyCSList(plist)) return NULL;
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    CSNode* p = plist->tail->next;
    int i;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}

int delStartNodeInCSList(CSList* plist) {
    if (isEmptyCSList(plist)) return Warning;
    CSNode* p = plist->tail->next;
    if (plist->size > 1) {
        plist->tail->next = plist->tail->next->next;
    } else {
        plist->tail = NULL;
    }
    free(p);
    plist->size--;
    return Success;
}

int delEndNodeInCSList(CSList* plist) {
    if (isEmptyCSList(plist)) return Warning;
    CSNode* p = plist->tail->next;
    CSNode* q = plist->tail; //p的前一个节点
    
    int i;
    for (i = 0; i < plist->size-1; i++) {
        q = p;
        p = p->next;
    }
    
    if (plist->size > 1) {
        q->next = p->next;
        plist->tail = q;
    } else {
        plist->tail = NULL;
    }
    free(p);
    plist->size--;
    return Success;
    
}
int delNodeByValInCSList(CSList* plist, int val) {
    if (isEmptyCSList(plist)) return Warning;
    
    CSNode* p = plist->tail->next;
    CSNode* q = plist->tail;
    
    int i;
    for (i = 0; i < plist->size; i++, p = p->next) {
        if (p->val == val) {
            if (p == plist->tail) return delEndNodeInCSList(plist);
            if (p == plist->tail->next) return delStartNodeInCSList(plist);
        
            q->next = p->next;
            free(p);
            plist->size--;
            return Success;
        }
    }
    return None;
}

int delNodeByPosInCSList(CSList* plist, int pos) {
    if (isEmptyCSList(plist)) return Warning;
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    if (pos == 0) return delStartNodeInCSList(plist);
    if (pos == plist->size-1) return delEndNodeInCSList(plist);
    
    CSNode* p = plist->tail->next;
    CSNode* q = plist->tail;
    
    int i;
    for (i = 0; i < pos; i++) {
        q = p;
        p = p->next;
    }
    q->next = p->next;
    free(p);
    plist->size--;
    return Success;
}

void printCSListFromStart(CSList* plist) {
    if (isEmptyCSList(plist)) return;
    CSNode* p = plist->tail->next;
    int i;
    for (i = 0; i < plist->size; i++, p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}

void printCSListFromPos(CSList* plist, int pos) {
    if (isEmptyCSList(plist)) return;
    if ((pos < 0) || (pos >= plist->size)) return;
    if (pos == 0) {
        printCSListFromStart(plist);
        return;
    }
    CSNode* p = findNodeByPosInCSList(plist, pos);
    int i;
    for (i = 0; i < plist->size; i++, p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}
void freeCSList(CSList* plist) {
    if (isEmptyCSList(plist)) return;
    CSNode* p = plist->tail->next;
    CSNode* q = plist->tail;
    int i;
    for (i = 0; i < plist->size; i++) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeCSList(plist);
}