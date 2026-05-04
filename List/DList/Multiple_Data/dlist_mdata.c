#define NODE_M_INDLIST
#define DATA_M_OPER
#include "dlist_mdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//内部函数使用Data类型,外部使用两个void*
//修改为任意数据类型,这个任意是指整个val都是同一种,但这中可以自定义






static bool isEmptyMList(DList_M* plist) {
    return plist->size == 0;
}

void initMDList(DList_M* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;    
}


//////////////////////////////////////////////////////////////////////////////////






/// @brief 通过data来返回链表节点
/// @param plist 链表指针
/// @param data Data类型数据
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static Node_M_inDList* getNodeByMData(DList_M* plist, Data_M data) {
    if (isEmptyMList(plist)) return NULL;
    Node_M_inDList* p = plist->head;
    for (; p; p = p->next) {
        if (compareMData(p->val, data) == SAME) {
            return p;
        }
    }
    return NULL;
}


/// @brief 通过位置返回链表节点
/// @param plist 链表指针
/// @param pos 位置(范围应在[0, list.size-1])
/// @return 若存在节点,返回节点, 如果位置无效,返回NULL
static Node_M_inDList* getNodeByPos(DList_M* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return NULL;
    Node_M_inDList* p = plist->head;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    return p;
}

Data_M getPtrMDataByMDataInMDList(DList_M* plist, Data_M inputData) {
    Node_M_inDList* p = getNodeByMData(plist, inputData);
    if (p == NULL) {
        return getEmptyMData();
    } else {
        return p->val;
    }
}


Data_M getCopyMDataByPosInMDList(DList_M* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return getEmptyMData();
    Node_M_inDList* p = NULL;
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
    //返回的一定是深拷贝的Data
    Data_M newData = deepCopyMData(p->val);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return getEmptyMData();
    }
    return newData;
}

Data_M getPtrMDataByPosInMDList(DList_M* plist, int pos) {
    if ((pos < 0) || (pos >= plist->size)) return getEmptyMData();
    Node_M_inDList* p = NULL;
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

bool hasMDataInMDList(DList_M* plist, Data_M inputData) {
    Node_M_inDList* p = getNodeByMData(plist, inputData);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



void freeMDataInMDList(Data_M* inputData) {
    //freeMData只能内部使用, 使用freeMDataInMList作为外部接口
    freeMData(inputData);
}



//这个创建创建一个Node,并整合数据,data和content会复制
/******************* */
static Node_M_inDList* createNode(Data_M oldData) {
    Node_M_inDList* newNode = (Node_M_inDList*)malloc(sizeof(Node_M_inDList));
    if (newNode == NULL) return NULL; 
    Data_M newData = smartCopyMData(oldData);
    if (newData.isEmpty) {
        printf("\nMemory allocation failed\n");
        return NULL;
    }
    newNode->val = newData;
    return newNode;
}

/*********** */
InfoOfReturn insertMDataAtEndInMDList(DList_M* plist, Data_M inputData) {
    
    //创建节点
    Node_M_inDList* newNode = createNode(inputData);
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


InfoOfReturn insertMDataAtStartInMDList(DList_M* plist, Data_M inputData) {
    
    //创建节点
    Node_M_inDList* newNode = createNode(inputData);
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
InfoOfReturn insertMDataAtPosInMDList(DList_M* plist, Data_M inputData, int pos) {
    if ((pos < 0) || (pos > plist->size)) return Warning;
    if (pos == 0) return insertMDataAtStartInMDList(plist, inputData);
    if (pos == plist->size) return insertMDataAtEndInMDList(plist, inputData);

    
    
    //创建节点
    Node_M_inDList* newNode = createNode(inputData);
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning; 
    }
    
    Node_M_inDList* p = getNodeByPos(plist, pos);
    
    //creatNode函函数已经处理了data, content的复制
    newNode->next = p;
    newNode->prev = p->prev;

    p->prev->next = newNode;
    p->prev = newNode;

    plist->size++;
    return Success;
}

InfoOfReturn delEndNodeInMDList(DList_M* plist) {
    if (isEmptyMList(plist)) return Warning;

    Node_M_inDList* p = plist->tail;

    
    //释放掉Data_M内存
    freeMData(&(p->val));

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


InfoOfReturn delStartNodeInMDList(DList_M* plist) {
    if (isEmptyMList(plist)) return Warning;

    Node_M_inDList* p = plist->head;
    
    freeMData(&(p->val));

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

InfoOfReturn delNodeByMDataInMDList(DList_M* plist, Data_M inputData) {
    if (isEmptyMList(plist)) return Warning;

    Node_M_inDList* p = getNodeByMData(plist, inputData);
    if (p == NULL) return None;
    if (p == plist->head) return delStartNodeInMDList(plist);
    if (p == plist->tail) return delEndNodeInMDList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;


    freeMData(&(p->val));

    free(p);
    plist->size--;
    return Success;
}
InfoOfReturn delNodeByPosInMDList(DList_M* plist, int pos) {
    if (isEmptyMList(plist)) return Warning;
    if ((pos < 0) || (pos >= plist->size)) return Warning;
    Node_M_inDList* p = getNodeByPos(plist, pos);
    if (p == plist->head) return delStartNodeInMDList(plist);
    if (p == plist->tail) return delEndNodeInMDList(plist);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;


    freeMData(&(p->val));
    free(p);
    plist->size--;
    return Success;
}

void reverseMDList(DList_M* plist) {
    if (plist->size < 2) return;
    Node_M_inDList* temp = NULL;
    Node_M_inDList* p = plist->head;
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



void printSDataInMDList(Data_M inputData) {
    if (inputData.isEmpty) {
        printf("\ndata is empty, cannot print\n");
        return;
    }
    printf("[val:");
    inputData.dataInfo->oper->printdata(inputData.data, inputData.content);
    printf("]");
}

void printMDList(DList_M* plist) {
    Node_M_inDList* p = plist->head;
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



void freeMDList(DList_M* plist) {
    Node_M_inDList* p = plist->head;
    Node_M_inDList* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        freeMData(&(q->val));
        free(q);
    }
    initMDList(plist);
}

