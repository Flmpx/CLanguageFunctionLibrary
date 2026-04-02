#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lrulist.h"


//下一步,构建哈希表,提高查找速度


static enum info {
    Warning = -1,
    None = 0,
    Success = 1
};


bool isEmptyLRUList(LRUList* plist) {
    return plist->size == 0;
}


void initializeLRUList(LRUList* plist, int MAX) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
    plist->MAX = MAX;
}


static LRUNode* findNodeByValInLRUList(LRUList* plist, int val) {
    LRUNode* p = plist->head;
    for (; p; p = p->next) {
        if (p->val == val) {
            return p;
        }
    }
    return NULL;
}

static LRUNode* findNodeByPosInLRUList(LRUList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    int i;
    LRUNode* p = plist->head;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
} 


static void updateViewedLRUNode(LRUList* plist, LRUNode* pnode) {
    if (plist->size == 0) return;
    if (pnode == plist->head) return;
    if (pnode == plist->tail) {
        plist->tail = pnode->prev;
        pnode->prev->next = NULL;
    } else {
        pnode->prev->next = pnode->next;
        pnode->next->prev = pnode->prev;
    }
    pnode->prev = NULL;
    pnode->next = plist->head;
    plist->head->prev = pnode;
    plist->head = pnode;
}

int delEndNodeInLRUList(LRUList* plist) {
    if (isEmptyLRUList(plist)) return Warning;
    LRUNode* p = plist->tail;
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

int delStartNodeInLRUList(LRUList* plist) {
    if (isEmptyLRUList(plist)) return Warning;
    LRUNode* p = plist->head;
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


int delNodeByValInLRUList(LRUList* plist, int val) {
    LRUNode* p = findNodeByValInLRUList(plist, val);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeInLRUList(plist);
    if (p == plist->tail) return delEndNodeInLRUList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    plist->size--;
    return Success;
    
}


int delNodeByPosInLRUList(LRUList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    LRUNode* p = findNodeByPosInLRUList(plist, pos);
    if (p == plist->head) return delStartNodeInLRUList(plist);
    if (p == plist->tail) return delEndNodeInLRUList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    plist->size--;
    return Success;
}


int addNewValInLRUList(LRUList* plist, int val) {

    LRUNode* existing = findNodeByValInLRUList(plist, val);
    if (existing) {
        updateViewedLRUNode(plist, existing);
        return None;
    }

    //若超过最大存储量,则删除最后一个,然后进行添加
    if (plist->size >= plist->MAX) {
        delEndNodeInLRUList(plist);
    }


    LRUNode* newNode = (LRUNode*)malloc(sizeof(LRUNode));
    if (newNode == NULL) return Warning;
    newNode->val = val;
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




LRUNode* viewLRUNodeByVal(LRUList* plist, int val) {
    LRUNode* p = findNodeByValInLRUList(plist, val);
    if (p == NULL) return NULL;
    if (p == plist->head) return p;
    updateViewedLRUNode(plist, p);
    return p;
}

LRUNode* viewLRUNodeByPos(LRUList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    LRUNode* p = findNodeByPosInLRUList(plist, pos);
    if (p == NULL) return NULL;
    if (p == plist->head) return p;
    updateViewedLRUNode(plist, p);
    return p;
}


void generateLRUList(LRUList* plist) {
    LRUNode* p = plist->head;
    for (; p; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");
}

void freeLRUList(LRUList* plist) {
    LRUNode* p = plist->head;
    LRUNode* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeLRUList(plist, plist->MAX);
}

