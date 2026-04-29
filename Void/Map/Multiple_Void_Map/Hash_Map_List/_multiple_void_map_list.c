#define LIST_AND_NODE_M_INCHAINMAP
#include "_multiple_void_map_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isEmptyMList(List_M_inChainMap* plist);
static void initMList(List_M_inChainMap* plist);



/////////////////////////////////////////////////////////////////////////////////




//返回空Data
static Data_M getEmptyMData() {
    Data_M data;
    data.data = NULL;
    data.isEmpty = true;
    data.dataInfo = NULL;
    data.content = NULL;
    
    return data;
}

static Entry_M_inChainMap getEmptyMEntry() {
    Entry_M_inChainMap entry;
    entry.key = getEmptyMData();
    entry.value = getEmptyMData();
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


void initMChainMap(ChainMap_M* pMap) {
    pMap->arr = NULL;
    pMap->len = pMap->size = 0;
    pMap->mod = 2;
}











///////////////////////////////////////////////////////////////////////////////////
//比较类





/// @brief 比较二者Data类型是否相同
/// @param Data_a a
/// @param Data_b b
/// @param cmp _compare类型的函数
/// @return SAME-->相同 | DIFFERENT-->不同
static CmpResult compareMKey(Data_M* Data_a, Data_M* Data_b) {
    if (Data_a->isEmpty || Data_b->isEmpty) {
        return DIFFERENT;
    }
    if (Data_a->type != Data_b->type) {
        return DIFFERENT;
    }
    if (Data_a->dataInfo != Data_b->dataInfo) {
        //类型相同但数据自带的操作函数及信息不同,说明有问题
        printf("\nType is the same but operation is different! Please check!\n");
        return DIFFERENT;
    }
    
    _cmpdata cmp;
    cmp = Data_a->dataInfo->oper->cmpdata;    //能走到这一步,说明二者的比较函数相同
    if (cmp(Data_a->data, Data_a->content, Data_b->data, Data_b->content) == DIFFERENT) {
        return DIFFERENT;
    }
    return SAME;

}


//////////////////////////////////////////////////////////////////////////////////////
//释放类

//释放Data数据
void freeMDataInMChainMap(Data_M* data) {
    //为空不释放
    if (data->isEmpty) return;
    //data的释放
    data->dataInfo->oper->freedata(data->data, data->content);
    //有content时才释放
    if (data->dataInfo->hasContent) {
        data->dataInfo->oper->freecontent(data->content);
    }

    data->content = NULL;
    data->data = NULL;

    data->dataInfo = NULL;
    data->type = NOT_FOUND;
    data->isEmpty = true;
}

//这个仅仅只会把Entry中的key和value的data和others(不会释放oper,因为同种类型数据是要共用同一个opertion类型的指针)
void freeMEntryInMChainMap(Entry_M_inChainMap* entry) {
    if (entry->isEmpty) return;
    freeMDataInMChainMap(&(entry->key));
    freeMDataInMChainMap(&(entry->value));
    entry->isEmpty = true;
}


//释放一个链表,包括它里面Data类型数据所指向的内容
static void freeMList(List_M_inChainMap* plist) {
    if (plist->size == 0) {
        return;
    }
    Node_M_inChainMap* p = plist->head;
    Node_M_inChainMap* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        freeMEntryInMChainMap(&(q->entry));
        free(q);
    }
    initMList(plist);
}



void freeMChainMap(ChainMap_M* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        freeMList(&(pMap->arr[i]));
    }
    free(pMap->arr);
    initMChainMap(pMap);
}




///////////////////////////////////////////////////////////////////////////////////////
//链表的构建


static bool isEmptyMList(List_M_inChainMap* plist) {
    return plist->size == 0;
}


/// @brief 初始化链表
/// @param plist 链表指针
static void initMList(List_M_inChainMap* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
}

static Node_M_inChainMap* getNodeByMKey(List_M_inChainMap* plist, Data_M key) {
    if (isEmptyMList(plist)) return NULL;
    Node_M_inChainMap* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        if (compareMKey(&(p->entry.key), &key) == SAME) {
            return p;
        }
    } 
    return NULL;
}

//这个是直接在后面插入的,不会判断key是否已经存在
static InfoOfReturn insertMEntryInMList(List_M_inChainMap* plist, Entry_M_inChainMap entry) {
    Node_M_inChainMap* newNode = (Node_M_inChainMap*)malloc(sizeof(Node_M_inChainMap));
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

static InfoOfReturn delStartNode(List_M_inChainMap* plist) {
    if (isEmptyMList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_M_inChainMap* p = plist->head;
    
    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeMEntryInMChainMap(&(p->entry));
    free(p);
    plist->size--;
    return Success;

}



static InfoOfReturn delEndNode(List_M_inChainMap* plist) {
    if (isEmptyMList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_M_inChainMap* p = plist->tail;
    
    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeMEntryInMChainMap(&(p->entry));
    free(p);
    plist->size--;
    return Success;
}



static InfoOfReturn delNodeByMKey(List_M_inChainMap* plist, Data_M key) {
    if (isEmptyMList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node_M_inChainMap* p = getNodeByMKey(plist, key);
    if (p == NULL) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    if (p == plist->head) return delStartNode(plist);
    if (p == plist->tail) return delEndNode(plist);


    p->prev->next = p->next;
    p->next->prev = p->prev;

    freeMEntryInMChainMap(&(p->entry));
    free(p);
    plist->size--;
    return Success;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
//复制类

//复制Data
static Data_M copyMData(Data_M oldData) {

    if (oldData.isEmpty) {
        return getEmptyMData();
    }
    //复制void* data
    Data_M newData;

    //copy函数不仅仅只是把指针赋值,还要把整个void* data赋值一遍
    newData.data = oldData.dataInfo->oper->copydata(oldData.data, oldData.content);

    if (newData.data == NULL) {
        printf("\nMemory allocation failed\n");
        return getEmptyMData();
    }

    newData.dataInfo = oldData.dataInfo;
    //有content才复制content
    if (oldData.dataInfo->hasContent) {
        newData.content = oldData.dataInfo->oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            printf("\nMemory allocation failed\n");
            oldData.dataInfo->oper->freedata(newData.data, oldData.content);
            return getEmptyMData();
        }
    } else {
        newData.content = NULL;
    }
    newData.type = oldData.type;

    //提供的相应操作函数因该是全局的
    newData.dataInfo->oper = oldData.dataInfo->oper;
    newData.isEmpty = false;
    return newData;
}

//复制一个Entry,注意:entry.state自动赋值,必须要自己赋值
static Entry_M_inChainMap copyMEntry(Entry_M_inChainMap oldEntry) {
    if (oldEntry.isEmpty) {
        return getEmptyMEntry();
    }
    Entry_M_inChainMap newEntry;
    newEntry.key = copyMData(oldEntry.key);
    if (newEntry.key.isEmpty) {
        return getEmptyMEntry();
    }
    newEntry.value = copyMData(oldEntry.value);
    if (newEntry.value.isEmpty) {
        freeMDataInMChainMap(&(newEntry.key));
        return getEmptyMEntry();
    }
    newEntry.isEmpty = false;
    return newEntry;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//添加keyandval类




//这个函数保证可以添加
static InfoOfReturn addMEntryFunction(ChainMap_M* pMap, Data_M key, Data_M value) {
    //hash
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;

    //在插入之前先进行一次查找
    Node_M_inChainMap* p = getNodeByMKey(&(pMap->arr[index]), key);
    if (p) {
        Data_M newVal = copyMData(value);
        if (newVal.isEmpty) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
        freeMDataInMChainMap(&(p->entry.value));
        p->entry.value = newVal;
        return Success;
    }
    Entry_M_inChainMap oldEntry;
    oldEntry.isEmpty = false;
    oldEntry.key = key;
    oldEntry.value = value;
    
    Entry_M_inChainMap newEntry = copyMEntry(oldEntry);
    if (newEntry.isEmpty) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    if (insertMEntryInMList(&(pMap->arr[index]), newEntry) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->size++;
    return Success;
}




//专门为重哈希做的软拷贝方式添加的Entry
static InfoOfReturn addMEntryForFreshMChainMap(ChainMap_M* pMap, Data_M key, Data_M value) {
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    Entry_M_inChainMap entry;
    entry.isEmpty = false;
    entry.key = key;
    entry.value = value;
    if (insertMEntryInMList(&(pMap->arr[index]), entry) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->size++;
    return Success;
}


static void freeMListForFreshMChainMap(List_M_inChainMap* plist) {
    if (isEmptyMList(plist)) {
        return;
    }
    Node_M_inChainMap* p = plist->head;
    Node_M_inChainMap* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initMList(plist);
}


//重hash
static InfoOfReturn freshMChainMap(ChainMap_M* pMap) {
    int newLen = 0;
    if (pMap->len == 0) {
        newLen = 16;    //如果为空,直接给16的空间
    } else {
        newLen = (pMap->len+1)*2;   //否则扩容两倍
    }

    int newSize = pMap->size;
    int newMod = getLargestPrime(newLen);
    
    //新创建一个newMap;
    ChainMap_M newMap;
    List_M_inChainMap* newArray = (List_M_inChainMap*)malloc(newLen*sizeof(List_M_inChainMap));
    if (newArray == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    for (int i = 0; i < newLen; i++) {
        //初始化
        initMList(newArray+i);
    }


    newMap.arr = newArray;
    newMap.len = newLen;
    newMap.mod = newMod;
    newMap.size = 0;    //再添加函数中会自动加,这里设置为0

    for (int i = 0; i < pMap->len; i++) {
        Node_M_inChainMap* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (addMEntryForFreshMChainMap(&newMap, p->entry.key, p->entry.value) == Warning) {
                printf("\nMemory allocation failed\n");
                return Warning;
            }
        }
    }

    for (int i = 0; i < pMap->len; i++) {
        freeMListForFreshMChainMap(&(pMap->arr[i]));
    }
    free(pMap->arr);
    *pMap = newMap;
    return Success;
}



InfoOfReturn insertMKeyAndMValInMChainMap(ChainMap_M* pMap, Data_M key, Data_M val) {
    //当填充因子大于75%时或者Map为空时自动扩容
    if (4*(pMap->size) >= 3*(pMap->len) || pMap->size == 0) {
        if (freshMChainMap(pMap) == Warning) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
    }
    return addMEntryFunction(pMap, key, val);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//查找类



//返回的Data数据为新建,用完后记得释放
Data_M getCopyMValByMKeyInMChainMap(ChainMap_M* pMap, Data_M key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return getEmptyMData();
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    Node_M_inChainMap* p = getNodeByMKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return getEmptyMData();
    } else {
        Data_M newData;
        newData = copyMData(p->entry.value);
        if (newData.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newData;
    }
}

Data_M getPtrMValByMKeyInMChainMap(ChainMap_M* pMap, Data_M key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return getEmptyMData();
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    Node_M_inChainMap* p = getNodeByMKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return getEmptyMData();
    } else {
        return p->entry.value;
    }
}


Entry_M_inChainMap getCopyMEntryByMKeyInMChainMap(ChainMap_M* pMap, Data_M key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return getEmptyMEntry();
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    Node_M_inChainMap* p = getNodeByMKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return getEmptyMEntry();
    } else {
        Entry_M_inChainMap newEntry;
        newEntry = copyMEntry(p->entry);
        if (newEntry.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newEntry;
    }
}


bool hasMKeyInMChainMap(ChainMap_M* pMap, Data_M key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return false;
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    Node_M_inChainMap* p = getNodeByMKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//删除类


InfoOfReturn delMEntryByMKeyInMChainMap(ChainMap_M* pMap, Data_M key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return Warning;
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    if (delNodeByMKey(&(pMap->arr[index]), key) == None) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    pMap->size--;
    return Success;
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//整合类

Data_M stackMDataInMChainMap(void* data, void* content, int type, InfoOfData* dataInfo) {
    Data_M newData;
    newData.data = data;
    newData.isEmpty = false;
    newData.dataInfo = dataInfo;
    newData.content = content;
    newData.type = type;
    return newData;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//打印类

void printMDataInMChainMap(Data_M data, char* tip) {
    if (data.isEmpty) {
        printf("\nData is empty, cannot print\n");
        return;
    }
    printf("[%s:", tip);
    data.dataInfo->oper->printdata(data.data, data.content);
    printf("]");
}

void printMEntryInMChainMap(Entry_M_inChainMap entry) {
    if (entry.isEmpty) {
        printf("\nEntry is empty, cannot print\n");
        return;
    }
    //key
    printf("[key:");
    entry.key.dataInfo->oper->printdata(entry.key.data, entry.key.content);
    
    //value
    printf(", value:");
    entry.value.dataInfo->oper->printdata(entry.value.data, entry.value.content);
    printf("]");
}

void printMChainMap(ChainMap_M* pMap) {
    if (pMap->size == 0) {
        printf("\nMap is empty, cannot print\n");
        return;
    }
    int cnt = 0;
    printf("[");
    for (int i = 0; i < pMap->len; i++) {
        Node_M_inChainMap* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (cnt != 0) {
                printf(", ");
            }
            printMEntryInMChainMap(p->entry);
            cnt++;
        }
    }
    printf("]");
}


//////////////////////////////////////////////////////////////////////////////////////////////////








