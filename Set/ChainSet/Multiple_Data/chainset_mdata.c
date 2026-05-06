#define ENTRY_M_INCHAINSET
#define NODE_M_INCHAINSET
#define LIST_M_INCHAINSET

#define GET_LARGESTPRIME

#define DATA_M_OPER

#include "chainset_mdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isEmptyMList(List_M_inChainSet* plist);
static void initMList(List_M_inChainSet* plist);



/////////////////////////////////////////////////////////////////////////////////



void initMChainSet(ChainSet_M* pSet) {
    pSet->arr = NULL;
    pSet->len = pSet->size = 0;
    pSet->mod = 2;
}











///////////////////////////////////////////////////////////////////////////////////
//比较类







//////////////////////////////////////////////////////////////////////////////////////
//释放类

//对外接口


void freeMKeyInMChainSet(Data_M* key) {
    freeMData(key);
}



//这个仅仅只会把Entry中的key的data和content(不会释放oper,因为同种类型数据是要共用同一个opertion类型的指针)
static void freeMEntry(Entry_M_inChainSet* entry) {
    if (entry->isEmpty) return;
    freeMData(&(entry->key));
    entry->isEmpty = true;
}


//释放一个链表,包括它里面Data类型数据所指向的内容
static void freeMList(List_M_inChainSet* plist) {
    if (plist->size == 0) {
        return;
    }
    Node_M_inChainSet* p = plist->head;
    Node_M_inChainSet* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        freeMEntry(&(q->entry));
        free(q);
    }
    initMList(plist);
}



void freeMChainSet(ChainSet_M* pSet) {
    for (int i = 0; i < pSet->len; i++) {
        freeMList(&(pSet->arr[i]));
    }
    free(pSet->arr);
    initMChainSet(pSet);
}




///////////////////////////////////////////////////////////////////////////////////////
//链表的构建


static bool isEmptyMList(List_M_inChainSet* plist) {
    return plist->size == 0;
}


/// @brief 初始化链表
/// @param plist 链表指针
static void initMList(List_M_inChainSet* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
}

static Node_M_inChainSet* getNodeByMKey(List_M_inChainSet* plist, Data_M key) {
    if (isEmptyMList(plist)) return NULL;
    Node_M_inChainSet* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        if (compareMData(p->entry.key, key) == SAME) {
            return p;
        }
    } 
    return NULL;
}

//这个是直接在后面插入的,不会判断key是否已经存在
static InfoOfReturn insertMEntryInMList(List_M_inChainSet* plist, Entry_M_inChainSet entry) {
    Node_M_inChainSet* newNode = (Node_M_inChainSet*)malloc(sizeof(Node_M_inChainSet));
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    newNode->entry = entry;
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

static InfoOfReturn delStartNode(List_M_inChainSet* plist) {
    if (isEmptyMList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_M_inChainSet* p = plist->head;
    
    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeMEntry(&(p->entry));
    free(p);
    plist->size--;
    return Success;

}



static InfoOfReturn delEndNode(List_M_inChainSet* plist) {
    if (isEmptyMList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_M_inChainSet* p = plist->tail;
    
    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeMEntry(&(p->entry));
    free(p);
    plist->size--;
    return Success;
}



static InfoOfReturn delNodeByMKey(List_M_inChainSet* plist, Data_M key) {
    if (isEmptyMList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_M_inChainSet* p = getNodeByMKey(plist, key);
    if (p == NULL) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    if (p == plist->head) return delStartNode(plist);
    if (p == plist->tail) return delEndNode(plist);


    p->prev->next = p->next;
    p->next->prev = p->prev;

    freeMEntry(&(p->entry));
    free(p);
    plist->size--;
    return Success;
}




///////////////////////////////////////////////////////////////////////////////////////////////////
//添加key类




//这个函数保证可以添加
static InfoOfReturn addMEntryFunction(ChainSet_M* pSet, Data_M key) {
    //hash
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pSet->mod;

    //在插入之前先进行一次查找
    Node_M_inChainSet* p = getNodeByMKey(&(pSet->arr[index]), key);
    if (p) {
        return None;
    }

    Entry_M_inChainSet newEntry;
    newEntry.isEmpty = false;
    newEntry.key = deepCopyMData(key);
    if (newEntry.key.isEmpty) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    if (insertMEntryInMList(&(pSet->arr[index]), newEntry) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pSet->size++;
    return Success;
}




//专门为重哈希做的软拷贝方式添加的Entry
static InfoOfReturn addMEntryForFreshMChainSet(ChainSet_M* pSet, Data_M key) {
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pSet->mod;
    Entry_M_inChainSet entry;
    entry.isEmpty = false;
    entry.key = key;
    if (insertMEntryInMList(&(pSet->arr[index]), entry) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pSet->size++;
    return Success;
}


static void freeMListForFreshMChainSet(List_M_inChainSet* plist) {
    if (isEmptyMList(plist)) {
        return;
    }
    Node_M_inChainSet* p = plist->head;
    Node_M_inChainSet* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initMList(plist);
}


//重hash
static InfoOfReturn freshMChainSet(ChainSet_M* pSet) {
    int newLen = 0;

    //无论如何都要保证len至少为16
    if (pSet->len == 0) {
        newLen = 16;
    } else if (4*(pSet->size) >= 3*(pSet->len)) {
        newLen = pSet->len*2;
    } else if (4*(pSet->size) <= pSet->len && pSet->len >= 32) {
        //至少要保证缩容之后len至少为16
        newLen = pSet->len/2;
    } else {
        return None;
    }

    int newSize = pSet->size;
    int newMod = getLargestPrime(newLen);
    
    //新创建一个newSet;
    ChainSet_M newSet;
    List_M_inChainSet* newArray = (List_M_inChainSet*)malloc(newLen*sizeof(List_M_inChainSet));
    if (newArray == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    for (int i = 0; i < newLen; i++) {
        //初始化
        initMList(newArray+i);
    }


    newSet.arr = newArray;
    newSet.len = newLen;
    newSet.mod = newMod;
    newSet.size = 0;    //再添加函数中会自动加,这里设置为0

    for (int i = 0; i < pSet->len; i++) {
        Node_M_inChainSet* p = pSet->arr[i].head;
        
        /*
            将这个循环改为用p来进行判断
        */
        for (int j = 0; j < pSet->arr[i].size; j++, p = p->next) {
            if (addMEntryForFreshMChainSet(&newSet, p->entry.key) == Warning) {
                printf("\nMemory allocation failed\n");
                return Warning;
            }
        }
    }

    for (int i = 0; i < pSet->len; i++) {
        freeMListForFreshMChainSet(&(pSet->arr[i]));
    }
    free(pSet->arr);
    *pSet = newSet;
    return Success;
}





InfoOfReturn insertMKeyInMChainSet(ChainSet_M* pSet, Data_M key) {
    
    //在插入之前进行freshSet
    //当填充因子大于75%时或者Set为空时自动扩容
    freshMChainSet(pSet);
    return addMEntryFunction(pSet, key);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//查找类



//返回的Data数据为新建,用完后记得释放
Data_M getCopyMKeyByMKeyInMChainSet(ChainSet_M* pSet, Data_M key) {
    if (pSet->len == 0 || pSet->size == 0 || pSet->arr == NULL) return getEmptyMData();
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pSet->mod;
    
    Node_M_inChainSet* p = getNodeByMKey(&(pSet->arr[index]), key);
    if (p == NULL) {
        return getEmptyMData();
    } else {
        Data_M newData;
        newData = deepCopyMData(p->entry.key);
        if (newData.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newData;
    }
}



bool hasMKeyInMChainSet(ChainSet_M* pSet, Data_M key) {
    if (pSet->len == 0 || pSet->size == 0 || pSet->arr == NULL) return false;
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pSet->mod;
    
    Node_M_inChainSet* p = getNodeByMKey(&(pSet->arr[index]), key);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//删除类


InfoOfReturn delMKeyByMKeyInMChainSet(ChainSet_M* pSet, Data_M key) {
    if (pSet->len == 0 || pSet->size == 0 || pSet->arr == NULL) return Warning;
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pSet->mod;
    
    if (delNodeByMKey(&(pSet->arr[index]), key) == None) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    pSet->size--;
    //删除后进行重hash
    freshMChainSet(pSet);
    return Success;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//打印类


void printMKeyInMChainSet(Data_M key) {
    if (key.isEmpty) {
        printf("\nkey is empty, cannot print\n");
        return;
    }
    printf("[key:");
    key.dataInfo->oper->printdata(key.data, key.content);
    printf("]");
}

void printMChainSet(ChainSet_M* pSet) {
    if (pSet->size == 0) {
        printf("\nSet is empty, cannot print\n");
        return;
    }
    int cnt = 0;
    printf("[");
    for (int i = 0; i < pSet->len; i++) {
        Node_M_inChainSet* p = pSet->arr[i].head;
        for (int j = 0; j < pSet->arr[i].size; j++, p = p->next) {
            if (cnt != 0) {
                printf(", ");
            }
            printMKeyInMChainSet(p->entry.key);
            cnt++;
        }
    }
    printf("]");
}


//////////////////////////////////////////////////////////////////////////////////////////////////








