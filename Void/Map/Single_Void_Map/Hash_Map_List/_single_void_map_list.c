#define LIST_AND_NODE_M_IN_CHAINMAP
#include "_single_void_map_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


static bool isEmptySList(List_S_inChainMap* plist);
static void initSList(List_S_inChainMap* plist);

//只要是需要两个InfoOfData的函数,直接传入Map类型指针!!!

/////////////////////////////////////////////////////////////////////////////////



//返回空Data
static Data_S getEmptySData() {
    Data_S data;
    data.data = NULL;
    data.isEmpty = true;
    data.content = NULL;
    return data;
}

static Entry_S_inChainMap getEmptySEntry() {
    Entry_S_inChainMap entry;
    entry.key = getEmptySData();
    entry.value = getEmptySData();
    entry.isEmpty = true;
    return entry;
}


static bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n%2 == 0 || n%3 == 0) return false;
    for (int i = 5; i <= n/i; i+=6) {
        if (n%i == 0 || n%(i+2) == 0) return false;
    }
    return true;
}



/// @brief 返回小于等于n的最大质数
/// @param n n
/// @return 最大质数
static int getLargestPrime(int n) {
    if (n <= 3) return n;
    if (n%2 == 0) n--;
    for (int i = n; ; i-=2) {
        if (isPrime(i)) return i;
    }
    return 2;
}

/************** */
void initSChainMap(ChainMap_S* pMap, InfoOfData* keyInfo, InfoOfData* valInfo) {
    pMap->arr = NULL;
    pMap->len = pMap->size = 0;
    pMap->mod = 2;
    pMap->keyInfo = keyInfo;
    pMap->valInfo = valInfo;
}











///////////////////////////////////////////////////////////////////////////////////
//比较类




/// @brief 比较二者Data类型是否相同
/// @param Data_a a
/// @param Data_b b
/// @param cmp _compare类型的函数
/// @return SAME-->相同 | DIFFERENT-->不同
static CmpResult compareSKey(Data_S* Data_a, Data_S* Data_b, InfoOfData* keyInfo) {
    if (Data_a->isEmpty || Data_b->isEmpty) {
        return DIFFERENT;
    }   
    
    //利用提供的比价函数来进行比较
    if (keyInfo->oper->cmpdata(Data_a->data, Data_a->content, Data_b->data, Data_b->content)) {
        return DIFFERENT;
    }
    return SAME;

}


//////////////////////////////////////////////////////////////////////////////////////
//释放类


/**************** */
//释放Data数据
void freeSDataInSChainMap(Data_S* data, InfoOfData* infoOfKeyOrVal) {
    //为空不释放
    if (data->isEmpty) return;
    //data的释放
    infoOfKeyOrVal->oper->freedata(data->data, data->content);
    //有content时才释放
    if (infoOfKeyOrVal->hasContent) {
        infoOfKeyOrVal->oper->freecontent(data->content);
    }
    
    data->content = NULL;
    data->data = NULL;
    data->isEmpty = true;
}


/************ */
//这个仅仅只会把Entry中的key和value的data和others(不会释放oper,因为同种类型数据是要共用同一个opertion类型的指针)
void freeSEntryInSChianMap(Entry_S_inChainMap* entry, ChainMap_S* pMap) {
    if (entry->isEmpty) return;
    freeSDataInSChainMap(&(entry->key), pMap->keyInfo);
    freeSDataInSChainMap(&(entry->value), pMap->valInfo);
    entry->isEmpty = true;
}


/************** */
//释放一个链表,包括它里面Data类型数据所指向的内容
static void freeSList(List_S_inChainMap* plist, ChainMap_S* pMap) {
    if (plist->size == 0) {
        return;
    }
    Node_S_inChainMap* p = plist->head;
    Node_S_inChainMap* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        freeSEntryInSChianMap(&(q->entry), pMap);
        free(q);
    }
    initSList(plist);
}




/**************** */
void freeSChainMap(ChainMap_S* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        freeSList(&(pMap->arr[i]), pMap);
    }
    free(pMap->arr);
    initSChainMap(pMap, pMap->keyInfo, pMap->valInfo);
}




///////////////////////////////////////////////////////////////////////////////////////
//链表的构建


static bool isEmptySList(List_S_inChainMap* plist) {
    return plist->size == 0;
}


/// @brief 初始化链表
/// @param plist 链表指针
static void initSList(List_S_inChainMap* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
}


/************* */
static Node_S_inChainMap* getNodeBySKey(List_S_inChainMap* plist, Data_S key, InfoOfData* keyInfo) {
    if (isEmptySList(plist)) return NULL;
    Node_S_inChainMap* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        if (compareSKey(&(p->entry.key), &key, keyInfo) == SAME) {
            return p;
        }
    } 
    return NULL;
}

//这个是直接在后面插入的,不会判断key是否已经存在
static int insertSEntryInSList(List_S_inChainMap* plist, Entry_S_inChainMap entry) {
    Node_S_inChainMap* newNode = (Node_S_inChainMap*)malloc(sizeof(Node_S_inChainMap));
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



static int delStartNode(List_S_inChainMap* plist, ChainMap_S* pMap) {
    if (isEmptySList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_S_inChainMap* p = plist->head;
    
    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeSEntryInSChianMap(&(p->entry), pMap);
    free(p);
    plist->size--;
    return Success;

}



static int delEndNode(List_S_inChainMap* plist, ChainMap_S* pMap) {
    if (isEmptySList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_S_inChainMap* p = plist->tail;
    
    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeSEntryInSChianMap(&(p->entry), pMap);
    free(p);
    plist->size--;
    return Success;
}



static int delNodeBySKey(List_S_inChainMap* plist, Data_S key, ChainMap_S* pMap) {
    if (isEmptySList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_S_inChainMap* p = getNodeBySKey(plist, key, pMap->keyInfo);
    if (p == NULL) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    if (p == plist->head) return delStartNode(plist, pMap);
    if (p == plist->tail) return delEndNode(plist, pMap);


    p->prev->next = p->next;
    p->next->prev = p->prev;

    freeSEntryInSChianMap(&(p->entry), pMap);
    free(p);
    plist->size--;
    return Success;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
//复制类

//复制Data
static Data_S copySData(Data_S oldData, InfoOfData* InfoOfKeyOrVal) {

    if (oldData.isEmpty) {
        return getEmptySData();
    }
    //复制void* data
    Data_S newData;

    //copy函数不仅仅只是把指针赋值,还要把整个void* data复制一遍
    newData.data = InfoOfKeyOrVal->oper->copydata(oldData.data, oldData.content);

    if (newData.data == NULL) {
        printf("\nMemory allocation failed\n");
        return getEmptySData();
    }

    //有content才复制content
    if (InfoOfKeyOrVal->hasContent) {
        newData.content = InfoOfKeyOrVal->oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            printf("\nMemory allocation failed\n");
            InfoOfKeyOrVal->oper->freedata(newData.data, oldData.content);
            return getEmptySData();
        }
    } else {
        newData.content = NULL;
    }
    newData.isEmpty = false;
    return newData;
}

//复制一个Entry,注意:entry.state自动赋值,必须要自己赋值
static Entry_S_inChainMap copySEntry(Entry_S_inChainMap oldEntry, ChainMap_S* pMap) {
    if (oldEntry.isEmpty) {
        return getEmptySEntry();
    }
    Entry_S_inChainMap newEntry;
    newEntry.key = copySData(oldEntry.key, pMap->keyInfo);
    if (newEntry.key.isEmpty) {
        return getEmptySEntry();
    }
    newEntry.value = copySData(oldEntry.value, pMap->valInfo);
    if (newEntry.value.isEmpty) {
        freeSDataInSChainMap(&(newEntry.key), pMap->keyInfo);
        return getEmptySEntry();
    }
    newEntry.isEmpty = false;
    return newEntry;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//添加keyandval类




//这个函数保证可以添加
static int addSEntryFunction(ChainMap_S* pMap, Data_S key, Data_S value) {
    //hash
    ull index = (pMap->keyInfo->oper->hashdata(key.data, key.content))%pMap->mod;

    Node_S_inChainMap* p = getNodeBySKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p) {
        Data_S newVal = copySData(value, pMap->valInfo);
        if (newVal.isEmpty) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
        freeSDataInSChainMap(&(p->entry.value), pMap->valInfo);
        p->entry.value = newVal;
        return Success;
    }
    Entry_S_inChainMap oldEntry;
    oldEntry.isEmpty = false;
    oldEntry.key = key;
    oldEntry.value = value;
    
    Entry_S_inChainMap newEntry = copySEntry(oldEntry, pMap);
    if (newEntry.isEmpty) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    if (insertSEntryInSList(&(pMap->arr[index]), newEntry) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->size++;
    return Success;
}




//专门为重哈希做的软拷贝方式添加的Entry
static int addSEntryForFreshSChainMap(ChainMap_S* pMap, Data_S key, Data_S value) {
    ull index = (pMap->keyInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    Entry_S_inChainMap entry;
    entry.isEmpty = false;
    entry.key = key;
    entry.value = value;
    if (insertSEntryInSList(&(pMap->arr[index]), entry) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->size++;
    return Success;
}


//专门做的一个软删除的freeList
static void freeSListForFreshSChainMap(List_S_inChainMap* plist) {
    if (isEmptySList(plist)) {
        return;
    }
    Node_S_inChainMap* p = plist->head;
    Node_S_inChainMap* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initSList(plist);
}


//重hash
static int freshSChainMap(ChainMap_S* pMap) {
    int newLen = 0;
    if (pMap->len == 0) {
        newLen = 16;    //如果为空,直接给16的空间
    } else {
        newLen = (pMap->len)*2;   //否则扩容两倍
    }

    int newSize = pMap->size;
    int newMod = getLargestPrime(newLen);
    
    //新创建一个newMap;
    ChainMap_S newMap;
    List_S_inChainMap* newArray = (List_S_inChainMap*)malloc(newLen*sizeof(List_S_inChainMap));
    if (newArray == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    for (int i = 0; i < newLen; i++) {
        //初始化
        initSList(newArray+i);
    }

    newMap.keyInfo = pMap->keyInfo;
    newMap.valInfo = pMap->valInfo;
    newMap.arr = newArray;
    newMap.len = newLen;
    newMap.mod = newMod;
    newMap.size = 0;    //再添加函数中会自动加,这里设置为0

    for (int i = 0; i < pMap->len; i++) {
        Node_S_inChainMap* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (addSEntryForFreshSChainMap(&newMap, p->entry.key, p->entry.value) == Warning) {
                printf("\nMemory allocation failed\n");
                return Warning;
            }
        }
    }

    for (int i = 0; i < pMap->len; i++) {
        freeSListForFreshSChainMap(&(pMap->arr[i]));
    }
    free(pMap->arr);
    *pMap = newMap;

    return Success;
}

static int shrinkSChainMap(ChainMap_S* pMap) {

}

int insertSKeyAndSValInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent, void* valdata, void* valcontent) {
    //当填充因子大于75%时或者Map为空时自动扩容
    if (4*(pMap->size) >= 3*(pMap->len) || pMap->size == 0) {
        if (freshSChainMap(pMap) == Warning) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
    }
    //原来的stackData函数去除,直接创建
    Data_S key = {keydata, keycontent, false};
    Data_S val = {valdata, valcontent, false};
    return addSEntryFunction(pMap, key, val);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//查找类



//返回的Data数据为新建,用完后记得释放
Data_S getCopySValBySKeyInSChianMap(ChainMap_S* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return getEmptySData();
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    Data_S key = {keydata, keycontent, false};
    
    Node_S_inChainMap* p = getNodeBySKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p == NULL) {
        return getEmptySData();
    } else {
        Data_S newData;
        newData = copySData(p->entry.value, pMap->valInfo);
        if (newData.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newData;
    }
}


Data_S getPtrSValBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return getEmptySData();
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    Data_S key = {keydata, keycontent, false};
    
    Node_S_inChainMap* p = getNodeBySKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p == NULL) {
        return getEmptySData();
    } else {
        return p->entry.value;
    }
}


Entry_S_inChainMap getCopySEntryBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return getEmptySEntry();
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    Data_S key = {keydata, keycontent, false};
    
    Node_S_inChainMap* p = getNodeBySKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p == NULL) {
        return getEmptySEntry();
    } else {
        Entry_S_inChainMap newEntry;
        newEntry = copySEntry(p->entry, pMap);
        if (newEntry.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newEntry;
    }
}


bool hasSKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return false;
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    Data_S key = {keydata, keycontent, false};
    Node_S_inChainMap* p = getNodeBySKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//删除类


int delSEntryBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return Warning;
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    Data_S key = {keydata, keycontent, false};
    if (delNodeBySKey(&(pMap->arr[index]), key, pMap) ==  None) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    pMap->size--;
    return Success;

}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//打印类

void printSDataInSChainMap(Data_S data, char* tip, InfoOfData* InfoOfKeyOrVal) {
    if (data.isEmpty) {
        printf("\nData is empty, cannot print\n");
        return;
    }
    printf("[%s:", tip);
    InfoOfKeyOrVal->oper->printdata(data.data, data.content);
    printf("]");
}

void printSEntryInSChainMap(Entry_S_inChainMap entry, ChainMap_S* pMap) {
    if (entry.isEmpty) {
        printf("\nEntry is empty, cannot print\n");
        return;
    }
    //key
    printf("[key:");
    pMap->keyInfo->oper->printdata(entry.key.data, entry.key.content);
    
    //value
    printf(", value:");
    pMap->valInfo->oper->printdata(entry.value.data, entry.value.content);
    printf("]");
}

void printSChainMap(ChainMap_S* pMap) {
    if (pMap->size == 0) {
        printf("\nMap is empty, cannot print\n");
        return;
    }
    int cnt = 0;
    printf("[");
    for (int i = 0; i < pMap->len; i++) {
        Node_S_inChainMap* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (cnt != 0) {
                printf(", ");
            }
            printSEntryInSChainMap(p->entry, pMap);
            cnt++;
        }
    }
    printf("]");
}


//////////////////////////////////////////////////////////////////////////////////////////////////








