#include "multiple_void_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static Data copyData(Data oldData);
//内部函数使用Data类型,外部使用两个void*
//修改为任意数据类型,这个任意是指整个val都是同一种,但这中可以自定义



//返回空Data
static Data returnEmptyData() {
    Data emptyData;
    emptyData.content = emptyData.data = NULL;
    emptyData.isEmpty = true;
    emptyData.type = NOT_FOUND;
    emptyData.valInfo = NULL;
    return emptyData;
}



static bool isEmptyList(List* plist) {
    return plist->size == 0;
}

void initializeList(List* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;    
}


//////////////////////////////////////////////////////////////////////////////////



static CmpResult compareData(Data Data_a, Data Data_b) {
    if (Data_a.isEmpty || Data_b.isEmpty) {
        return DIFFERENT;
    }
    if (Data_a.type != Data_b.type) {
        return DIFFERENT;
    }
    if (Data_a.valInfo != Data_b.valInfo) {
        //类型相同但数据自带的操作函数及信息不同,说明有问题
        printf("\nType is the same but operation is different! Please check!\n");
        return DIFFERENT;
    }
    _cmpdata cmp;
    cmp = Data_a.valInfo->oper->cmpdata;
    if (cmp(Data_a.data, Data_a.content, Data_b.data, Data_b.content) == DIFFERENT) {
        return DIFFERENT;
    }
    return SAME;
}




/// @brief 通过data来返回链表节点
/// @param plist 链表指针
/// @param data Data类型数据
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static Node* findNodeByData(List* plist, Data data) {
    if (isEmptyList(plist)) return NULL;
    Node* p = plist->head;
    for (; p; p = p->next) {
        if (compareData(p->val, data) == SAME) {
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

Data returnPtrDataByData(List* plist, Data inputData) {
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
    Data newData = copyData(p->val);
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

bool hasDataInList(List* plist, Data inputData) {
    Node* p = findNodeByData(plist, inputData);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



void freeData(Data* inputData) {
    if (inputData->isEmpty) return;

    inputData->valInfo->oper->freedata(inputData->data, inputData->content);
    
    if (inputData->valInfo->hasContent) {
        inputData->valInfo->oper->freecontent(inputData->content);
    }
    inputData->content = NULL;
    inputData->data = NULL;

    inputData->isEmpty = true;
    inputData->valInfo = NULL;
    inputData->type = NOT_FOUND;

}



static Data copyData(Data oldData) {
    Data newData;
    newData.data = oldData.valInfo->oper->copydata(oldData.data, oldData.content);
    if (newData.data == NULL) {
        return returnEmptyData();
    }
    if (oldData.valInfo->hasContent) {
        newData.content = oldData.valInfo->oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            oldData.valInfo->oper->freedata(newData.data, oldData.content);
            return returnEmptyData();
        }
    }
    newData.valInfo = oldData.valInfo;
    newData.type = oldData.type;
    newData.isEmpty = oldData.isEmpty;
    return newData;
    
}

//这个创建创建一个Node,并整合数据,data和content会复制
/******************* */
static Node* createNode(Data oldData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL; 
    Data newData = copyData(oldData);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return NULL;
    }
    newNode->val = newData;
    return newNode;
}

/*********** */
InfoOfReturn insertDataAtEndInList(List* plist, Data inputData) {
    
    //创建节点
    Node* newNode = createNode(inputData);
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


InfoOfReturn insertDataAtStartInList(List* plist, Data inputData) {
    
    //创建节点
    Node* newNode = createNode(inputData);
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
InfoOfReturn insertDataAtPosInList(List* plist, Data inputData, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertDataAtStartInList(plist, inputData);
    if (pos == plist->size) return insertDataAtEndInList(plist, inputData);

    
    
    //创建节点
    Node* newNode = createNode(inputData);
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
    p->val.valInfo->oper->freedata(p->val.data, p->val.content);
    if (p->val.valInfo->hasContent) {
        p->val.valInfo->oper->freecontent(p->val.content);
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
    p->val.valInfo->oper->freedata(p->val.data, p->val.content);
    if (p->val.valInfo->hasContent) {
        p->val.valInfo->oper->freecontent(p->val.content);
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

InfoOfReturn delNodeByData(List* plist, Data inputData) {
    if (isEmptyList(plist)) return Warning;

    Node* p = findNodeByData(plist, inputData);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeInList(plist);
    if (p == plist->tail) return delEndNodeInList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;

    p->val.valInfo->oper->freedata(p->val.data, p->val.content);
    if (p->val.valInfo->hasContent) {
        p->val.valInfo->oper->freecontent(p->val.content);
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

    p->val.valInfo->oper->freedata(p->val.data, p->val.content);
    if (p->val.valInfo->hasContent) {
        p->val.valInfo->oper->freecontent(p->val.content);
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


Data stackData(void* data, void* content, int type, InfoOfData* valInfo) {
    Data newData;
    newData.data = data;
    newData.type = type;
    newData.isEmpty = false;
    newData.valInfo = valInfo;
    newData.content = content;
    return newData;
}

void printList(List* plist) {
    Node* p = plist->head;
    printf("[");
    int cnt = 0;
    for (; p; p = p->next) {
        if (cnt != 0) {
            printf("-->");
        }
        p->val.valInfo->oper->printdata(p->val.data, p->val.content);
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
        q->val.valInfo->oper->freedata(q->val.data, q->val.content);
        if (q->val.valInfo->hasContent) {
            q->val.valInfo->oper->freecontent(q->val.content);
        }
        free(q);
    }
    initializeList(plist);
}

