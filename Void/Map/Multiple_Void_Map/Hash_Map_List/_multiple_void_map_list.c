#include "_multiple_void_map_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isEmptyList(MultiListInMap* plist);
static void initializeList(MultiListInMap* plist);



/////////////////////////////////////////////////////////////////////////////////




//返回空Data
static _MData returnEmptyData() {
    _MData data;
    data.data = NULL;
    data.isEmpty = true;
    data.dataInfo = NULL;
    data.content = NULL;
    
    return data;
}

static _MEntryWithList returnEmptyEntry() {
    _MEntryWithList entry;
    entry.key = returnEmptyData();
    entry.value = returnEmptyData();
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
static int returnLargestPrime(int n) {
    if (n <= 3) return n;
    if (n%2 == 0) n--;
    for (int i = n; ; i-=2) {
        if (isPrime(i)) return i;
    }
    return 2;
}


void initMMapwithList(_MMapWithList* pMap) {
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
static CmpResult compareKey(_MData* Data_a, _MData* Data_b) {
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
void freeDataInMMapWithList(_MData* data) {
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
void freeEntryInMMapWithList(_MEntryWithList* entry) {
    if (entry->isEmpty) return;
    freeDataInMMapWithList(&(entry->key));
    freeDataInMMapWithList(&(entry->value));
    entry->isEmpty = true;
}


//释放一个链表,包括它里面Data类型数据所指向的内容
static void freeList(MultiListInMap* plist) {
    if (plist->size == 0) {
        return;
    }
    MultiNodeInMap* p = plist->head;
    MultiNodeInMap* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        freeEntryInMMapWithList(&(q->entry));
        free(q);
    }
    initializeList(plist);
}



void freeMMapWithList(_MMapWithList* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        freeList(&(pMap->arr[i]));
    }
    free(pMap->arr);
    initMMapwithList(pMap);
}




///////////////////////////////////////////////////////////////////////////////////////
//链表的构建


static bool isEmptyList(MultiListInMap* plist) {
    return plist->size == 0;
}


/// @brief 初始化链表
/// @param plist 链表指针
static void initializeList(MultiListInMap* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
}

static MultiNodeInMap* findNodeByKey(MultiListInMap* plist, _MData key) {
    if (isEmptyList(plist)) return NULL;
    MultiNodeInMap* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        if (compareKey(&(p->entry.key), &key) == SAME) {
            return p;
        }
    } 
    return NULL;
}

//这个是直接在后面插入的,不会判断key是否已经存在
static InfoOfReturn insertEntryInList(MultiListInMap* plist, _MEntryWithList entry) {
    MultiNodeInMap* newNode = (MultiNodeInMap*)malloc(sizeof(MultiNodeInMap));
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

static InfoOfReturn delStartNode(MultiListInMap* plist) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    MultiNodeInMap* p = plist->head;
    
    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeEntryInMMapWithList(&(p->entry));
    free(p);
    plist->size--;
    return Success;

}



static InfoOfReturn delEndNode(MultiListInMap* plist) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    MultiNodeInMap* p = plist->tail;
    
    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeEntryInMMapWithList(&(p->entry));
    free(p);
    plist->size--;
    return Success;
}



static InfoOfReturn delNodeByKey(MultiListInMap* plist, _MData key) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    MultiNodeInMap* p = findNodeByKey(plist, key);
    if (p == NULL) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    if (p == plist->head) return delStartNode(plist);
    if (p == plist->tail) return delEndNode(plist);


    p->prev->next = p->next;
    p->next->prev = p->prev;

    freeEntryInMMapWithList(&(p->entry));
    free(p);
    plist->size--;
    return Success;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
//复制类

//复制Data
static _MData copyData(_MData oldData) {

    if (oldData.isEmpty) {
        return returnEmptyData();
    }
    //复制void* data
    _MData newData;

    //copy函数不仅仅只是把指针赋值,还要把整个void* data赋值一遍
    newData.data = oldData.dataInfo->oper->copydata(oldData.data, oldData.content);

    if (newData.data == NULL) {
        printf("\nMemory allocation failed\n");
        return returnEmptyData();
    }

    newData.dataInfo = oldData.dataInfo;
    //有content才复制content
    if (oldData.dataInfo->hasContent) {
        newData.content = oldData.dataInfo->oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            printf("\nMemory allocation failed\n");
            oldData.dataInfo->oper->freedata(newData.data, oldData.content);
            return returnEmptyData();
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
static _MEntryWithList copyEntry(_MEntryWithList oldEntry) {
    if (oldEntry.isEmpty) {
        return returnEmptyEntry();
    }
    _MEntryWithList newEntry;
    newEntry.key = copyData(oldEntry.key);
    if (newEntry.key.isEmpty) {
        return returnEmptyEntry();
    }
    newEntry.value = copyData(oldEntry.value);
    if (newEntry.value.isEmpty) {
        freeDataInMMapWithList(&(newEntry.key));
        return returnEmptyEntry();
    }
    newEntry.isEmpty = false;
    return newEntry;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//添加keyandval类




//这个函数保证可以添加
static InfoOfReturn addEntryFunction(_MMapWithList* pMap, _MData key, _MData value) {
    //hash
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;

    MultiNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p) {
        _MData newVal = copyData(value);
        if (newVal.isEmpty) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
        freeDataInMMapWithList(&(p->entry.value));
        p->entry.value = newVal;
        return Success;
    }
    _MEntryWithList oldEntry;
    oldEntry.isEmpty = false;
    oldEntry.key = key;
    oldEntry.value = value;
    
    _MEntryWithList newEntry = copyEntry(oldEntry);
    if (newEntry.isEmpty) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    if (insertEntryInList(&(pMap->arr[index]), newEntry) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->size++;
    return Success;
}




//专门为重哈希做的软拷贝方式添加的Entry
static InfoOfReturn addEntryForFreshMap(_MMapWithList* pMap, _MData key, _MData value) {
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    _MEntryWithList entry;
    entry.isEmpty = false;
    entry.key = key;
    entry.value = value;
    if (insertEntryInList(&(pMap->arr[index]), entry) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->size++;
    return Success;
}


static void freeListForFreshMap(MultiListInMap* plist) {
    if (isEmptyList(plist)) {
        return;
    }
    MultiNodeInMap* p = plist->head;
    MultiNodeInMap* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeList(plist);
}


//重hash
static InfoOfReturn freshMap(_MMapWithList* pMap) {
    int newLen = 0;
    if (pMap->len == 0) {
        newLen = 16;    //如果为空,直接给16的空间
    } else {
        newLen = (pMap->len+1)*2;   //否则扩容两倍
    }

    int newSize = pMap->size;
    int newMod = returnLargestPrime(newLen);
    
    //新创建一个newMap;
    _MMapWithList newMap;
    MultiListInMap* newArray = (MultiListInMap*)malloc(newLen*sizeof(MultiListInMap));
    if (newArray == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    for (int i = 0; i < newLen; i++) {
        //初始化
        initializeList(newArray+i);
    }


    newMap.arr = newArray;
    newMap.len = newLen;
    newMap.mod = newMod;
    newMap.size = 0;    //再添加函数中会自动加,这里设置为0

    for (int i = 0; i < pMap->len; i++) {
        MultiNodeInMap* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (addEntryForFreshMap(&newMap, p->entry.key, p->entry.value) == Warning) {
                printf("\nMemory allocation failed\n");
                return Warning;
            }
        }
    }

    for (int i = 0; i < pMap->len; i++) {
        freeListForFreshMap(&(pMap->arr[i]));
    }
    free(pMap->arr);
    *pMap = newMap;
    return Success;
}



InfoOfReturn insertKeyAndValInMMapWithList(_MMapWithList* pMap, _MData key, _MData val) {
    //当填充因子大于75%时或者Map为空时自动扩容
    if (4*(pMap->size) >= 3*(pMap->len) || pMap->size == 0) {
        if (freshMap(pMap) == Warning) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
    }
    return addEntryFunction(pMap, key, val);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//查找类



//返回的Data数据为新建,用完后记得释放
_MData getCopyValByKeyInMMapWithList(_MMapWithList* pMap, _MData key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyData();
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    MultiNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return returnEmptyData();
    } else {
        _MData newData;
        newData = copyData(p->entry.value);
        if (newData.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newData;
    }
}

_MData getPtrValByKeyInMMapWithList(_MMapWithList* pMap, _MData key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyData();
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    MultiNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return returnEmptyData();
    } else {
        return p->entry.value;
    }
}


_MEntryWithList getCopyEntryByKeyInMMapWithList(_MMapWithList* pMap, _MData key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyEntry();
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    MultiNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return returnEmptyEntry();
    } else {
        _MEntryWithList newEntry;
        newEntry = copyEntry(p->entry);
        if (newEntry.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newEntry;
    }
}


bool hasKeyInMMapWithList(_MMapWithList* pMap, _MData key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return false;
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    MultiNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//删除类


InfoOfReturn delEntryByKeyInMMapWithList(_MMapWithList* pMap, _MData key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return Warning;
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    
    if (delNodeByKey(&(pMap->arr[index]), key) == None) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    pMap->size--;
    return Success;
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//整合类

_MData stackDataInMMapWithList(void* data, void* content, int type, InfoOfData* dataInfo) {
    _MData newData;
    newData.data = data;
    newData.isEmpty = false;
    newData.dataInfo = dataInfo;
    newData.content = content;
    newData.type = type;
    return newData;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//打印类

void printDataInMMapWithList(_MData data, char* tip) {
    if (data.isEmpty) {
        printf("\nData is empty, cannot print\n");
        return;
    }
    printf("[%s:", tip);
    data.dataInfo->oper->printdata(data.data, data.content);
    printf("]");
}

void printEntryInMMapWithList(_MEntryWithList entry) {
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

void printMMapWithList(_MMapWithList* pMap) {
    if (pMap->size == 0) {
        printf("\nMap is empty, cannot print\n");
        return;
    }
    int cnt = 0;
    printf("[");
    for (int i = 0; i < pMap->len; i++) {
        MultiNodeInMap* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (cnt != 0) {
                printf(", ");
            }
            printEntryInMMapWithList(p->entry);
            cnt++;
        }
    }
    printf("]");
}


//////////////////////////////////////////////////////////////////////////////////////////////////








