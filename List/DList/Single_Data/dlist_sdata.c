#define NODE_S_INDLIST
#define DATA_S_OPER
#include "dlist_sdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//内部函数使用Data类型,外部使用两个void*
//修改为任意数据类型,这个任意是指整个val都是同一种,但这中可以自定义





static bool isEmptySList(DList_S* plist) {
    return plist->size == 0;
}

void initSDList(DList_S* plist, InfoOfData* valInfo) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
    plist->valInfo = valInfo;
    
}




/// @brief 通过data来返回链表节点
/// @param plist 链表指针
/// @param data Data类型数据
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static Node_S_inDList* getNodeBySData(DList_S* plist, Data_S data) {
    if (isEmptySList(plist)) return NULL;
    Node_S_inDList* p = plist->head;
    for (; p; p = p->next) {
        
        //虽然可直接使用plist中的cmpdata函数, 但为了统一性, 使用统一的compareSData函数
        if (compareSData(p->val, plist->valInfo, data, plist->valInfo) == SAME) {
            return p;
        }
    }
    return NULL;
}


/// @brief 通过位置返回链表节点
/// @param plist 链表指针
/// @param pos 位置(范围应在[0, list.size-1])
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static Node_S_inDList* getNodeByPos(DList_S* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    Node_S_inDList* p = plist->head;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}


void freeSDataInSDList(DList_S* plist, Data_S* inputData) {

    //统一接口
    freeSData(inputData, plist->valInfo);
}


Data_S getPtrSDataBySDataInSDList(DList_S* plist, Data_S inputData) {
    Node_S_inDList* p = getNodeBySData(plist, inputData);
    if (p == NULL) {
        return getEmptySData();
    } else {
        return p->val;
    }
}


Data_S getCopySDataByPosInSDList(DList_S* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return getEmptySData();
    Node_S_inDList* p = NULL;
    if (pos > plist->size/2) {
        p = plist->tail;
        int diff = plist->size - pos - 1;
        for (int i = 0; i < diff; i++) {
            p = p->prev;
        }
    } else {
        p = plist->head;
        for (int i = 0; i < pos; i++) {
            p = p->next;
        }
    }
    Data_S newData = deepCopySData(p->val, plist->valInfo);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return getEmptySData();
    }
    return newData;
}

Data_S getPtrSDataByPosInSDList(DList_S* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return getEmptySData();
    Node_S_inDList* p = NULL;
    if (pos > plist->size/2) {
        p = plist->tail;
        int diff = plist->size - pos - 1;
        for (int i = 0; i < diff; i++) {
            p = p->prev;
        }
    } else {
        p = plist->head;
        for (int i = 0; i < pos; i++) {
            p = p->next;
        }
    }
    return p->val;
}

bool hasSDataInSDList(DList_S* plist, Data_S inputData) {
    Node_S_inDList* p = getNodeBySData(plist, inputData);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



//这个创建创建一个Node,并整合数据,data和content会复制
/******************* */
static Node_S_inDList* createNode(DList_S* plist, Data_S oldData) {
    Node_S_inDList* newNode = (Node_S_inDList*)malloc(sizeof(Node_S_inDList));
    if (newNode == NULL) return NULL; 
    Data_S newData = smartCopySData(oldData, plist->valInfo);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return NULL;
    }
    newNode->val = newData;
    return newNode;
}

/*********** */
InfoOfReturn insertSDataAtEndInSDList(DList_S* plist, Data_S inputData) {
    
    //创建节点
    Node_S_inDList* newNode = createNode(plist, inputData);
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning; 
    }
    //creatNode函函数已经处理了data, content的智能复制了
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


InfoOfReturn insertSDataAtStartInSDList(DList_S* plist, Data_S inputData) {
    
    //创建节点
    Node_S_inDList* newNode = createNode(plist, inputData);
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning; 
    }
    
    //creatNode函函数已经处理了data, content的复制了
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

/************ */
InfoOfReturn insertSDataAtPosInSDList(DList_S* plist, Data_S inputData, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertSDataAtStartInSDList(plist, inputData);
    if (pos == plist->size) return insertSDataAtEndInSDList(plist, inputData);

    
    //创建节点
    Node_S_inDList* newNode = createNode(plist, inputData);
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning; 
    }
    
    Node_S_inDList* p = getNodeByPos(plist, pos);
    
    //creatNode函函数已经处理了data, content的复制
    newNode->next = p;
    newNode->prev = p->prev;

    p->prev->next = newNode;
    p->prev = newNode;

    plist->size++;
    return Success;
}

InfoOfReturn delEndNodeInSDList(DList_S* plist) {
    if (isEmptySList(plist)) return Warning;

    Node_S_inDList* p = plist->tail;

    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }
    freeSData(&(p->val), plist->valInfo);
    free(p);
    plist->size--;
    return Success;
}
InfoOfReturn delStartNodeInSDList(DList_S* plist) {
    if (isEmptySList(plist)) return Warning;

    Node_S_inDList* p = plist->head;

    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeSData(&(p->val), plist->valInfo);
    free(p);
    plist->size--;
    return Success;
}

InfoOfReturn delNodeBySDataInSDList(DList_S* plist, Data_S inputData) {
    if (isEmptySList(plist)) return Warning;
    Node_S_inDList* p = getNodeBySData(plist, inputData);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeInSDList(plist);
    if (p == plist->tail) return delEndNodeInSDList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;

    freeSData(&(p->val), plist->valInfo);
    free(p);
    plist->size--;
    return Success;
}



InfoOfReturn delNodeByPosInSDList(DList_S* plist, int pos) {
    if (isEmptySList(plist)) return Warning;
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    Node_S_inDList* p = getNodeByPos(plist, pos);
    if (p == plist->head) return delStartNodeInSDList(plist);
    if (p == plist->tail) return delEndNodeInSDList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;

    freeSData(&(p->val), plist->valInfo);
    free(p);
    plist->size--;
    return Success;
}

void reverseSDList(DList_S* plist) {
    if (plist->size < 2) return;
    Node_S_inDList* temp = NULL;
    Node_S_inDList* p = plist->head;
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


void printSDataInSDList(DList_S* plist, Data_S inputData) {
    if (inputData.isEmpty) {
        printf("\ndata is empty, cannot print\n");
        return;
    }
    printf("[val:");
    plist->valInfo->oper->printdata(inputData.data, inputData.content);
    printf("]");
}



void printSDList(DList_S* plist) {
    Node_S_inDList* p = plist->head;
    printf("[");
    int cnt = 0;
    for (; p; p = p->next) {
        if (cnt != 0) {
            printf("-->");
        }
        plist->valInfo->oper->printdata(p->val.data, p->val.content);
        cnt++;
    }
    printf("]");
    
}



void freeSDList(DList_S* plist) {
    Node_S_inDList* p = plist->head;
    Node_S_inDList* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        
        freeSData(&(q->val), plist->valInfo);
        free(q);
    }
    initSDList(plist, plist->valInfo);
}

