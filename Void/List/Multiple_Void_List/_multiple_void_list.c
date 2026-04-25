#include "_multiple_void_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static _MData copyData(_MData oldData);
//内部函数使用Data类型,外部使用两个void*
//修改为任意数据类型,这个任意是指整个val都是同一种,但这中可以自定义



//返回空Data
static _MData returnEmptyData() {
    _MData emptyData;
    emptyData.content = emptyData.data = NULL;
    emptyData.isEmpty = true;
    emptyData.type = NOT_FOUND;
    emptyData.dataInfo = NULL;
    return emptyData;
}



static bool isEmptyList(_MList* plist) {
    return plist->size == 0;
}

void initMList(_MList* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;    
}


//////////////////////////////////////////////////////////////////////////////////



static CmpResult compareData(_MData Data_a, _MData Data_b) {
    if (Data_a.isEmpty || Data_b.isEmpty) {
        return DIFFERENT;
    }
    if (Data_a.type != Data_b.type) {
        return DIFFERENT;
    }
    if (Data_a.dataInfo != Data_b.dataInfo) {
        //类型相同但数据自带的操作函数及信息不同,说明有问题
        printf("\nType is the same but operation is different! Please check!\n");
        return DIFFERENT;
    }
    _cmpdata cmp;
    cmp = Data_a.dataInfo->oper->cmpdata;
    if (cmp(Data_a.data, Data_a.content, Data_b.data, Data_b.content) == DIFFERENT) {
        return DIFFERENT;
    }
    return SAME;
}




/// @brief 通过data来返回链表节点
/// @param plist 链表指针
/// @param data Data类型数据
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static MultiNodeInList* findNodeByData(_MList* plist, _MData data) {
    if (isEmptyList(plist)) return NULL;
    MultiNodeInList* p = plist->head;
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
static MultiNodeInList* findNodeByPos(_MList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    MultiNodeInList* p = plist->head;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}

_MData getPtrDataByDataInMList(_MList* plist, _MData inputData) {
    MultiNodeInList* p = findNodeByData(plist, inputData);
    if (p == NULL) {
        return returnEmptyData();
    } else {
        return p->val;
    }
}


_MData getCopyDataByPosInMList(_MList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return returnEmptyData();
    MultiNodeInList* p = NULL;
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
    _MData newData = copyData(p->val);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return returnEmptyData();
    }
    return newData;
}

_MData getPtrDataByPosInMList(_MList* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return returnEmptyData();
    MultiNodeInList* p = NULL;
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

bool hasDataInMList(_MList* plist, _MData inputData) {
    MultiNodeInList* p = findNodeByData(plist, inputData);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



void freeDataInMList(_MData* inputData) {
    if (inputData->isEmpty) return;

    inputData->dataInfo->oper->freedata(inputData->data, inputData->content);
    
    if (inputData->dataInfo->hasContent) {
        inputData->dataInfo->oper->freecontent(inputData->content);
    }
    inputData->content = NULL;
    inputData->data = NULL;

    inputData->isEmpty = true;
    inputData->dataInfo = NULL;
    inputData->type = NOT_FOUND;

}



static _MData copyData(_MData oldData) {
    _MData newData;
    newData.data = oldData.dataInfo->oper->copydata(oldData.data, oldData.content);
    if (newData.data == NULL) {
        return returnEmptyData();
    }
    if (oldData.dataInfo->hasContent) {
        newData.content = oldData.dataInfo->oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            oldData.dataInfo->oper->freedata(newData.data, oldData.content);
            return returnEmptyData();
        }
    }
    newData.dataInfo = oldData.dataInfo;
    newData.type = oldData.type;
    newData.isEmpty = oldData.isEmpty;
    return newData;
    
}

//这个创建创建一个Node,并整合数据,data和content会复制
/******************* */
static MultiNodeInList* createNode(_MData oldData) {
    MultiNodeInList* newNode = (MultiNodeInList*)malloc(sizeof(MultiNodeInList));
    if (newNode == NULL) return NULL; 
    _MData newData = copyData(oldData);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return NULL;
    }
    newNode->val = newData;
    return newNode;
}

/*********** */
InfoOfReturn insertDataAtEndInMList(_MList* plist, _MData inputData) {
    
    //创建节点
    MultiNodeInList* newNode = createNode(inputData);
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


InfoOfReturn insertDataAtStartInMList(_MList* plist, _MData inputData) {
    
    //创建节点
    MultiNodeInList* newNode = createNode(inputData);
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
InfoOfReturn insertDataAtPosInMList(_MList* plist, _MData inputData, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertDataAtStartInMList(plist, inputData);
    if (pos == plist->size) return insertDataAtEndInMList(plist, inputData);

    
    
    //创建节点
    MultiNodeInList* newNode = createNode(inputData);
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning; 
    }
    
    MultiNodeInList* p = findNodeByPos(plist, pos);
    
    //creatNode函函数已经处理了data, content的复制
    newNode->next = p;
    newNode->prev = p->prev;

    p->prev->next = newNode;
    p->prev = newNode;

    plist->size++;
    return Success;
}

InfoOfReturn delEndNodeInMList(_MList* plist) {
    if (isEmptyList(plist)) return Warning;

    MultiNodeInList* p = plist->tail;
    p->val.dataInfo->oper->freedata(p->val.data, p->val.content);
    if (p->val.dataInfo->hasContent) {
        p->val.dataInfo->oper->freecontent(p->val.content);
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
InfoOfReturn delStartNodeInMList(_MList* plist) {
    if (isEmptyList(plist)) return Warning;

    MultiNodeInList* p = plist->head;
    p->val.dataInfo->oper->freedata(p->val.data, p->val.content);
    if (p->val.dataInfo->hasContent) {
        p->val.dataInfo->oper->freecontent(p->val.content);
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

InfoOfReturn delNodeByDataInMList(_MList* plist, _MData inputData) {
    if (isEmptyList(plist)) return Warning;

    MultiNodeInList* p = findNodeByData(plist, inputData);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeInMList(plist);
    if (p == plist->tail) return delEndNodeInMList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;

    p->val.dataInfo->oper->freedata(p->val.data, p->val.content);
    if (p->val.dataInfo->hasContent) {
        p->val.dataInfo->oper->freecontent(p->val.content);
    }
    free(p);
    plist->size--;
    return Success;
}
InfoOfReturn delNodeByPosInMList(_MList* plist, int pos) {
    if (isEmptyList(plist)) return Warning;
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    MultiNodeInList* p = findNodeByPos(plist, pos);
    if (p == plist->head) return delStartNodeInMList(plist);
    if (p == plist->tail) return delEndNodeInMList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;

    p->val.dataInfo->oper->freedata(p->val.data, p->val.content);
    if (p->val.dataInfo->hasContent) {
        p->val.dataInfo->oper->freecontent(p->val.content);
    }
    free(p);
    plist->size--;
    return Success;
}

void reverseMList(_MList* plist) {
    if (plist->size < 2) return;
    MultiNodeInList* temp = NULL;
    MultiNodeInList* p = plist->head;
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


_MData stackDataInMList(void* data, void* content, int type, InfoOfData* dataInfo) {
    _MData newData;
    newData.data = data;
    newData.type = type;
    newData.isEmpty = false;
    newData.dataInfo = dataInfo;
    newData.content = content;
    return newData;
}

void printMList(_MList* plist) {
    MultiNodeInList* p = plist->head;
    printf("[");
    int cnt = 0;
    for (; p; p = p->next) {
        if (cnt != 0) {
            printf("-->");
        }
        p->val.dataInfo->oper->printdata(p->val.data, p->val.content);
        cnt++;
    }
    printf("]");
    
}



void freeMList(_MList* plist) {
    MultiNodeInList* p = plist->head;
    MultiNodeInList* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        q->val.dataInfo->oper->freedata(q->val.data, q->val.content);
        if (q->val.dataInfo->hasContent) {
            q->val.dataInfo->oper->freecontent(q->val.content);
        }
        free(q);
    }
    initMList(plist);
}

