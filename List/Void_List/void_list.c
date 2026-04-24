#include "void_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static Data copyData(List* plist, Data oldData);
//内部函数使用Data类型,外部使用两个void*
//修改为任意数据类型,这个任意是指整个val都是同一种,但这中可以自定义


//返回空Data
static Data returnEmptyData() {
    Data emptyData;
    emptyData.content = emptyData.data = NULL;
    emptyData.isEmpty = true;
    return emptyData;
}



static bool isEmptyList(List* plist) {
    return plist->size == 0;
}

void initializeList(List* plist, InfoOfData* valInfo) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
    plist->valInfo = valInfo;
    
}




/// @brief 通过data来返回链表节点
/// @param plist 链表指针
/// @param data Data类型数据
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static Node* findNodeByData(List* plist, Data data) {
    if (isEmptyList(plist)) return NULL;
    Node* p = plist->head;
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
static Node* findNodeByPos(List* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    Node* p = plist->head;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}


void freeData(List* plist, Data* inputData) {
    if (inputData->isEmpty) return;

    plist->valInfo->oper->freedata(inputData->data, inputData->content);
    if (plist->valInfo->hasContent) {
        plist->valInfo->oper->freecontent(inputData->content);
    }
    inputData->content = NULL;
    inputData->data = NULL;
    inputData->isEmpty = true;
}


Data returnPtrDataByData(List* plist, void* data, void* content) {
    Data inputData = {data, content, false};
    Node* p = findNodeByData(plist, inputData);
    if (p == NULL) {
        return returnEmptyData();
    } else {
        return p->val;
    }
}


Data returnCopyDataByPos(List* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return returnEmptyData();
    Node* p = NULL;
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
    Data newData = copyData(plist, p->val);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return returnEmptyData();
    }
    return newData;
}

Data returnPtrDataByPos(List* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return returnEmptyData();
    Node* p = NULL;
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

bool hasDataInList(List* plist, void* data, void* content) {
    Data inputData = {data, content, false};
    Node* p = findNodeByData(plist, inputData);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



static Data copyData(List* plist, Data oldData) {
    Data newData;
    newData.data = plist->valInfo->oper->copydata(oldData.data, oldData.content);
    if (newData.data == NULL) {
        return returnEmptyData();
    }
    if (plist->valInfo->hasContent) {
        newData.content = plist->valInfo->oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            plist->valInfo->oper->freedata(newData.data, oldData.content);
            return returnEmptyData();
        }
    }
    newData.isEmpty = oldData.isEmpty;
    return newData;
    
}

//这个创建创建一个Node,并整合数据,data和content会复制
/******************* */
static Node* createNode(List* plist, Data oldData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL; 
    Data newData = copyData(plist, oldData);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return NULL;
    }
    newNode->val = newData;
    return newNode;
}

/*********** */
InfoOfReturn insertDataAtEndInList(List* plist, void* data, void* content) {
    Data oldData = {data, content, false};
    
    //创建节点
    Node* newNode = createNode(plist, oldData);
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


InfoOfReturn insertDataAtStartInList(List* plist, void* data, void* content) {
    Data oldData = {data, content, false};
    
    //创建节点
    Node* newNode = createNode(plist, oldData);
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
InfoOfReturn insertDataAtPosInList(List* plist, void* data, void* content, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertDataAtStartInList(plist, data, content);
    if (pos == plist->size) return insertDataAtEndInList(plist, data, content);

    Data oldData = {data, content, false};
    
    //创建节点
    Node* newNode = createNode(plist, oldData);
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning; 
    }
    
    Node* p = findNodeByPos(plist, pos);
    
    //creatNode函函数已经处理了data, content的复制
    newNode->next = p;
    newNode->prev = p->prev;

    p->prev->next = newNode;
    p->prev = newNode;

    plist->size++;
    return Success;
}

InfoOfReturn delEndNodeInList(List* plist) {
    if (isEmptyList(plist)) return Warning;

    Node* p = plist->tail;
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
InfoOfReturn delStartNodeInList(List* plist) {
    if (isEmptyList(plist)) return Warning;

    Node* p = plist->head;
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

InfoOfReturn delNodeByData(List* plist, void* data, void* content) {
    if (isEmptyList(plist)) return Warning;
    Data inputData = {data, content, false};
    Node* p = findNodeByData(plist, inputData);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeInList(plist);
    if (p == plist->tail) return delEndNodeInList(plist);
    
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
InfoOfReturn delNodeByPos(List* plist, int pos) {
    if (isEmptyList(plist)) return Warning;
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    Node* p = findNodeByPos(plist, pos);
    if (p == plist->head) return delStartNodeInList(plist);
    if (p == plist->tail) return delEndNodeInList(plist);
    
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


void printList(List* plist) {
    Node* p = plist->head;
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



void freeList(List* plist) {
    Node* p = plist->head;
    Node* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        plist->valInfo->oper->freedata(q->val.data, q->val.content);
        if (plist->valInfo->hasContent) {
            plist->valInfo->oper->freecontent(q->val.content);
        }
        free(q);
    }
    initializeList(plist, plist->valInfo);
}


// void sortList(List* plist, Compare cmp) {
//     if (plist->size < 2) return;
//     Node* p = plist->head;
//     // i以及i之前的节点的都是有序区
//     for (int i = 0; i < plist->size-1; i++, p = p->next) {
//         void* temp_data = p->next->data;
//         int temp_sizeofdata = p->next->sizeofdata;
//         Node* q = p;
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