#include "_single_void_map_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isEmptyList(SingleListInMap* plist);
static void initializeList(SingleListInMap* plist);

//只要是需要两个InfoOfData的函数,直接传入Map类型指针!!!

/////////////////////////////////////////////////////////////////////////////////



//返回空Data
static _SData returnEmptyData() {
    _SData data;
    data.data = NULL;
    data.isEmpty = true;
    data.content = NULL;
    return data;
}

static _SEntryWithList returnEmptyEntry() {
    _SEntryWithList entry;
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

/************** */
void initSMapWithList(_SMapWithList* pMap, InfoOfData* keyInfo, InfoOfData* valInfo) {
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
static CmpResult compareKey(_SData* Data_a, _SData* Data_b, InfoOfData* keyInfo) {
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
void freeDataInSMapWithList(_SData* data, InfoOfData* infoOfKeyOrVal) {
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
void freeEntryInSMapWithList(_SEntryWithList* entry, _SMapWithList* pMap) {
    if (entry->isEmpty) return;
    freeDataInSMapWithList(&(entry->key), pMap->keyInfo);
    freeDataInSMapWithList(&(entry->value), pMap->valInfo);
    entry->isEmpty = true;
}


/************** */
//释放一个链表,包括它里面Data类型数据所指向的内容
static void freeList(SingleListInMap* plist, _SMapWithList* pMap) {
    if (plist->size == 0) {
        return;
    }
    SingleNodeInMap* p = plist->head;
    SingleNodeInMap* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        freeEntryInSMapWithList(&(q->entry), pMap);
        free(q);
    }
    initializeList(plist);
}




/**************** */
void freeSMapWithList(_SMapWithList* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        freeList(&(pMap->arr[i]), pMap);
    }
    free(pMap->arr);
    initSMapWithList(pMap, pMap->keyInfo, pMap->valInfo);
}




///////////////////////////////////////////////////////////////////////////////////////
//链表的构建


static bool isEmptyList(SingleListInMap* plist) {
    return plist->size == 0;
}


/// @brief 初始化链表
/// @param plist 链表指针
static void initializeList(SingleListInMap* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
}


/************* */
static SingleNodeInMap* findNodeByKey(SingleListInMap* plist, _SData key, InfoOfData* keyInfo) {
    if (isEmptyList(plist)) return NULL;
    SingleNodeInMap* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        if (compareKey(&(p->entry.key), &key, keyInfo) == SAME) {
            return p;
        }
    } 
    return NULL;
}

//这个是直接在后面插入的,不会判断key是否已经存在
static int insertEntryInList(SingleListInMap* plist, _SEntryWithList entry) {
    SingleNodeInMap* newNode = (SingleNodeInMap*)malloc(sizeof(SingleNodeInMap));
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



static int delStartNode(SingleListInMap* plist, _SMapWithList* pMap) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    SingleNodeInMap* p = plist->head;
    
    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeEntryInSMapWithList(&(p->entry), pMap);
    free(p);
    plist->size--;
    return Success;

}



static int delEndNode(SingleListInMap* plist, _SMapWithList* pMap) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    SingleNodeInMap* p = plist->tail;
    
    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeEntryInSMapWithList(&(p->entry), pMap);
    free(p);
    plist->size--;
    return Success;
}



static int delNodeByKey(SingleListInMap* plist, _SData key, _SMapWithList* pMap) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    SingleNodeInMap* p = findNodeByKey(plist, key, pMap->keyInfo);
    if (p == NULL) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    if (p == plist->head) return delStartNode(plist, pMap);
    if (p == plist->tail) return delEndNode(plist, pMap);


    p->prev->next = p->next;
    p->next->prev = p->prev;

    freeEntryInSMapWithList(&(p->entry), pMap);
    free(p);
    plist->size--;
    return Success;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
//复制类

//复制Data
static _SData copyData(_SData oldData, InfoOfData* InfoOfKeyOrVal) {

    if (oldData.isEmpty) {
        return returnEmptyData();
    }
    //复制void* data
    _SData newData;

    //copy函数不仅仅只是把指针赋值,还要把整个void* data复制一遍
    newData.data = InfoOfKeyOrVal->oper->copydata(oldData.data, oldData.content);

    if (newData.data == NULL) {
        printf("\nMemory allocation failed\n");
        return returnEmptyData();
    }

    //有content才复制content
    if (InfoOfKeyOrVal->hasContent) {
        newData.content = InfoOfKeyOrVal->oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            printf("\nMemory allocation failed\n");
            InfoOfKeyOrVal->oper->freedata(newData.data, oldData.content);
            return returnEmptyData();
        }
    } else {
        newData.content = NULL;
    }
    newData.isEmpty = false;
    return newData;
}

//复制一个Entry,注意:entry.state自动赋值,必须要自己赋值
static _SEntryWithList copyEntry(_SEntryWithList oldEntry, _SMapWithList* pMap) {
    if (oldEntry.isEmpty) {
        return returnEmptyEntry();
    }
    _SEntryWithList newEntry;
    newEntry.key = copyData(oldEntry.key, pMap->keyInfo);
    if (newEntry.key.isEmpty) {
        return returnEmptyEntry();
    }
    newEntry.value = copyData(oldEntry.value, pMap->valInfo);
    if (newEntry.value.isEmpty) {
        freeDataInSMapWithList(&(newEntry.key), pMap->keyInfo);
        return returnEmptyEntry();
    }
    newEntry.isEmpty = false;
    return newEntry;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//添加keyandval类




//这个函数保证可以添加
static int addEntryFunction(_SMapWithList* pMap, _SData key, _SData value) {
    //hash
    ull index = (pMap->keyInfo->oper->hashdata(key.data, key.content))%pMap->mod;

    SingleNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p) {
        _SData newVal = copyData(value, pMap->valInfo);
        if (newVal.isEmpty) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
        freeDataInSMapWithList(&(p->entry.value), pMap->valInfo);
        p->entry.value = newVal;
        return Success;
    }
    _SEntryWithList oldEntry;
    oldEntry.isEmpty = false;
    oldEntry.key = key;
    oldEntry.value = value;
    
    _SEntryWithList newEntry = copyEntry(oldEntry, pMap);
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
static int addEntryForFreshMap(_SMapWithList* pMap, _SData key, _SData value) {
    ull index = (pMap->keyInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    _SEntryWithList entry;
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


static void freeListForFreshMap(SingleListInMap* plist) {
    if (isEmptyList(plist)) {
        return;
    }
    SingleNodeInMap* p = plist->head;
    SingleNodeInMap* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeList(plist);
}


//重hash
static int freshMap(_SMapWithList* pMap) {
    int newLen = 0;
    if (pMap->len == 0) {
        newLen = 16;    //如果为空,直接给16的空间
    } else {
        newLen = (pMap->len)*2;   //否则扩容两倍
    }

    int newSize = pMap->size;
    int newMod = returnLargestPrime(newLen);
    
    //新创建一个newMap;
    _SMapWithList newMap;
    SingleListInMap* newArray = (SingleListInMap*)malloc(newLen*sizeof(SingleListInMap));
    if (newArray == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    for (int i = 0; i < newLen; i++) {
        //初始化
        initializeList(newArray+i);
    }

    newMap.keyInfo = pMap->keyInfo;
    newMap.valInfo = pMap->valInfo;
    newMap.arr = newArray;
    newMap.len = newLen;
    newMap.mod = newMod;
    newMap.size = 0;    //再添加函数中会自动加,这里设置为0

    for (int i = 0; i < pMap->len; i++) {
        SingleNodeInMap* p = pMap->arr[i].head;
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

static int shrinkMap(_SMapWithList* pMap) {

}

int insertKeyAndValInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent, void* valdata, void* valcontent) {
    //当填充因子大于75%时或者Map为空时自动扩容
    if (4*(pMap->size) >= 3*(pMap->len) || pMap->size == 0) {
        if (freshMap(pMap) == Warning) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
    }
    //原来的stackData函数去除,直接创建
    _SData key = {keydata, keycontent, false};
    _SData val = {valdata, valcontent, false};
    return addEntryFunction(pMap, key, val);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//查找类



//返回的Data数据为新建,用完后记得释放
_SData getCopyValByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyData();
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    _SData key = {keydata, keycontent, false};
    
    SingleNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p == NULL) {
        return returnEmptyData();
    } else {
        _SData newData;
        newData = copyData(p->entry.value, pMap->valInfo);
        if (newData.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newData;
    }
}


_SData getPtrValByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyData();
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    _SData key = {keydata, keycontent, false};
    
    SingleNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p == NULL) {
        return returnEmptyData();
    } else {
        return p->entry.value;
    }
}


_SEntryWithList getCopyEntryByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyEntry();
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    _SData key = {keydata, keycontent, false};
    
    SingleNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p == NULL) {
        return returnEmptyEntry();
    } else {
        _SEntryWithList newEntry;
        newEntry = copyEntry(p->entry, pMap);
        if (newEntry.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newEntry;
    }
}


bool hasKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return false;
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    _SData key = {keydata, keycontent, false};
    SingleNodeInMap* p = findNodeByKey(&(pMap->arr[index]), key, pMap->keyInfo);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//删除类


int delEntryByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return Warning;
    ull index = (pMap->keyInfo->oper->hashdata(keydata, keycontent))%pMap->mod;
    
    _SData key = {keydata, keycontent, false};
    if (delNodeByKey(&(pMap->arr[index]), key, pMap) ==  None) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    pMap->size--;
    return Success;

}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//打印类

void printDataInSMapWithList(_SData data, char* tip, InfoOfData* InfoOfKeyOrVal) {
    if (data.isEmpty) {
        printf("\nData is empty, cannot print\n");
        return;
    }
    printf("[%s:", tip);
    InfoOfKeyOrVal->oper->printdata(data.data, data.content);
    printf("]");
}

void printEntryInSMapWithList(_SEntryWithList entry, _SMapWithList* pMap) {
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

void printSMapWithList(_SMapWithList* pMap) {
    if (pMap->size == 0) {
        printf("\nMap is empty, cannot print\n");
        return;
    }
    int cnt = 0;
    printf("[");
    for (int i = 0; i < pMap->len; i++) {
        SingleNodeInMap* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (cnt != 0) {
                printf(", ");
            }
            printEntryInSMapWithList(p->entry, pMap);
            cnt++;
        }
    }
    printf("]");
}


//////////////////////////////////////////////////////////////////////////////////////////////////








