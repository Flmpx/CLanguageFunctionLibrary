#define NODE_S_INLIST
#include "_single_void_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static Data_S copySData(List_S* plist, Data_S oldData);
//内部函数使用Data类型,外部使用两个void*
//修改为任意数据类型,这个任意是指整个val都是同一种,但这中可以自定义


//返回空Data
static Data_S getEmptySData() {
    Data_S emptyData;
    emptyData.content = emptyData.data = NULL;
    emptyData.isEmpty = true;
    return emptyData;
}



static bool isEmptySList(List_S* plist) {
    return plist->size == 0;
}

void initSList(List_S* plist, InfoOfData* valInfo) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
    plist->valInfo = valInfo;
    
}




/// @brief 通过data来返回链表节点
/// @param plist 链表指针
/// @param data Data类型数据
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static Node_S_inList* getNodeBySData(List_S* plist, Data_S data) {
    if (isEmptySList(plist)) return NULL;
    Node_S_inList* p = plist->head;
    for (; p; p = p->next) {
        if (plist->valInfo->oper->cmpdata(p->val.data, p->val.content, data.data, data.content) == SAME) {
            return p;
        }
    }
    return NULL;
}


/// @brief 通过位置返回链表节点
/// @param plist 链表指针
/// @param pos 位置(范围应在[0, list.size-1])
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static Node_S_inList* getNodeByPos(List_S* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    Node_S_inList* p = plist->head;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}


void freeSDataInSList(List_S* plist, Data_S* inputData) {
    if (inputData->isEmpty) return;

    plist->valInfo->oper->freedata(inputData->data, inputData->content);
    if (plist->valInfo->hasContent) {
        plist->valInfo->oper->freecontent(inputData->content);
    }
    inputData->content = NULL;
    inputData->data = NULL;
    inputData->isEmpty = true;
}


Data_S getPtrSDataByMDataInSList(List_S* plist, void* data, void* content) {
    Data_S inputData = {data, content, false};
    Node_S_inList* p = getNodeBySData(plist, inputData);
    if (p == NULL) {
        return getEmptySData();
    } else {
        return p->val;
    }
}


Data_S getCopySDataByPosInSList(List_S* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return getEmptySData();
    Node_S_inList* p = NULL;
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
    Data_S newData = copySData(plist, p->val);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return getEmptySData();
    }
    return newData;
}

Data_S getPtrSDataByPosInSList(List_S* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return getEmptySData();
    Node_S_inList* p = NULL;
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

bool hasSDataInSList(List_S* plist, void* data, void* content) {
    Data_S inputData = {data, content, false};
    Node_S_inList* p = getNodeBySData(plist, inputData);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



static Data_S copySData(List_S* plist, Data_S oldData) {
    Data_S newData;
    newData.data = plist->valInfo->oper->copydata(oldData.data, oldData.content);
    if (newData.data == NULL) {
        return getEmptySData();
    }
    if (plist->valInfo->hasContent) {
        newData.content = plist->valInfo->oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            plist->valInfo->oper->freedata(newData.data, oldData.content);
            return getEmptySData();
        }
    }
    newData.isEmpty = oldData.isEmpty;
    return newData;
    
}

//这个创建创建一个Node,并整合数据,data和content会复制
/******************* */
static Node_S_inList* createNode(List_S* plist, Data_S oldData) {
    Node_S_inList* newNode = (Node_S_inList*)malloc(sizeof(Node_S_inList));
    if (newNode == NULL) return NULL; 
    Data_S newData = copySData(plist, oldData);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return NULL;
    }
    newNode->val = newData;
    return newNode;
}

/*********** */
InfoOfReturn insertSDataAtEndInSList(List_S* plist, void* data, void* content) {
    Data_S oldData = {data, content, false};
    
    //创建节点
    Node_S_inList* newNode = createNode(plist, oldData);
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning; 
    }
    //creatNode函函数已经处理了data, content的复制了
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


InfoOfReturn insertSDataAtStartInSList(List_S* plist, void* data, void* content) {
    Data_S oldData = {data, content, false};
    
    //创建节点
    Node_S_inList* newNode = createNode(plist, oldData);
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
InfoOfReturn insertSDataAtPosInSList(List_S* plist, void* data, void* content, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertSDataAtStartInSList(plist, data, content);
    if (pos == plist->size) return insertSDataAtEndInSList(plist, data, content);

    Data_S oldData = {data, content, false};
    
    //创建节点
    Node_S_inList* newNode = createNode(plist, oldData);
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning; 
    }
    
    Node_S_inList* p = getNodeByPos(plist, pos);
    
    //creatNode函函数已经处理了data, content的复制
    newNode->next = p;
    newNode->prev = p->prev;

    p->prev->next = newNode;
    p->prev = newNode;

    plist->size++;
    return Success;
}

InfoOfReturn delEndNodeInSList(List_S* plist) {
    if (isEmptySList(plist)) return Warning;

    Node_S_inList* p = plist->tail;
    plist->valInfo->oper->freedata(p->val.data, p->val.content);
    if (plist->valInfo->hasContent) {
        plist->valInfo->oper->freecontent(p->val.content);
    }

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
InfoOfReturn delStartNodeInSList(List_S* plist) {
    if (isEmptySList(plist)) return Warning;

    Node_S_inList* p = plist->head;
    plist->valInfo->oper->freedata(p->val.data, p->val.content);
    if (plist->valInfo->hasContent) {
        plist->valInfo->oper->freecontent(p->val.content);
    }

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

InfoOfReturn delNodeBySDataInSList(List_S* plist, void* data, void* content) {
    if (isEmptySList(plist)) return Warning;
    Data_S inputData = {data, content, false};
    Node_S_inList* p = getNodeBySData(plist, inputData);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeInSList(plist);
    if (p == plist->tail) return delEndNodeInSList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;

    plist->valInfo->oper->freedata(p->val.data, p->val.content);
    if (plist->valInfo->hasContent) {
        plist->valInfo->oper->freecontent(p->val.content);
    }
    free(p);
    plist->size--;
    return Success;
}
InfoOfReturn delNodeByPosInSList(List_S* plist, int pos) {
    if (isEmptySList(plist)) return Warning;
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    Node_S_inList* p = getNodeByPos(plist, pos);
    if (p == plist->head) return delStartNodeInSList(plist);
    if (p == plist->tail) return delEndNodeInSList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;

    plist->valInfo->oper->freedata(p->val.data, p->val.content);
    if (plist->valInfo->hasContent) {
        plist->valInfo->oper->freecontent(p->val.content);
    }
    free(p);
    plist->size--;
    return Success;
}

void reverseSList(List_S* plist) {
    if (plist->size < 2) return;
    Node_S_inList* temp = NULL;
    Node_S_inList* p = plist->head;
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


void printSList(List_S* plist) {
    Node_S_inList* p = plist->head;
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



void freeSList(List_S* plist) {
    Node_S_inList* p = plist->head;
    Node_S_inList* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        plist->valInfo->oper->freedata(q->val.data, q->val.content);
        if (plist->valInfo->hasContent) {
            plist->valInfo->oper->freecontent(q->val.content);
        }
        free(q);
    }
    initSList(plist, plist->valInfo);
}


// void sortList(List_S* plist, Compare cmp) {
//     if (plist->size < 2) return;
//     Node_S_inList* p = plist->head;
//     // i以及i之前的节点的都是有序区
//     for (int i = 0; i < plist->size-1; i++, p = p->next) {
//         void* temp_data = p->next->data;
//         int temp_sizeofdata = p->next->sizeofdata;
//         Node_S_inList* q = p;
//         for (int j = i; j >= 0; j--, q = q->prev) {
//             if (cmp(q->data, temp_data) > 0) {
//                 q->next->data = q->data;
//                 q->next->sizeofdata = q->sizeofdata;
//             } else {
//                 break;
//             }
//         }
//         if (q) {
//             q->next->data = temp_data;
//             q->next->sizeofdata = temp_sizeofdata;
//         } else {
//             plist->head->data = temp_data;
//             plist->head->sizeofdata = temp_sizeofdata;
//         }
//     }
// }