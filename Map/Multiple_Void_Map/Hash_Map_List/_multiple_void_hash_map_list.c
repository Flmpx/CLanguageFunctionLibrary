#include "_multiple_void_hash_map_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool isEmptyList(List* plist);
static void initializeList(List* plist);



/////////////////////////////////////////////////////////////////////////////////


/// @brief 空oper,代表一种错误状态
static Operation emptyOperation = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

static InfoOfData returnEmptyInfo() {
    InfoOfData info;
    info.hasContent = false;
    info.oper = NULL;
    return info;
}

//返回空Data
static Data returnEmptyData() {
    Data data;
    data.data = NULL;
    data.isEmpty = true;
    data.dataInfo = returnEmptyInfo();
    data.content = NULL;
    
    return data;
}

static Entry returnEmptyEntry() {
    Entry entry;
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


void initializeMap(Map* pMap) {
    pMap->arr = NULL;
    pMap->len = pMap->size = 0;
    pMap->mod = 2;
}











///////////////////////////////////////////////////////////////////////////////////
//比较类

//这个函数通过判断函数指针是否相同来判断函数是否相同
static int compareOper(Operation* oper_b, Operation* oper_a) {
    return oper_a == oper_b ? SAME : DIFFERENT;
    
}




/// @brief 比较二者Data类型是否相同
/// @param Data_a a
/// @param Data_b b
/// @param cmp _compare类型的函数
/// @return SAME-->相同 | DIFFERENT-->不同
static int compareKey(Data* Data_a, Data* Data_b) {
    if (Data_a->isEmpty || Data_b->isEmpty) {
        return DIFFERENT;
    }
    if (Data_a->type != Data_b->type) {
        return DIFFERENT;
    }
    if (compareOper(Data_a->dataInfo.oper, Data_b->dataInfo.oper) == DIFFERENT) {
        //类型相同带操作函数不同,说明有问题
        printf("\nType is the same but operation is different! Please check!\n");
        return DIFFERENT;
    }
    
    _cmpdata cmp;
    cmp = Data_a->dataInfo.oper->cmpdata;    //能走到这一步,说明二者的比较函数相同
    if (cmp(Data_a->data, Data_a->content, Data_b->data, Data_b->content) == DIFFERENT) {
        return DIFFERENT;
    }
    return SAME;

}


//////////////////////////////////////////////////////////////////////////////////////
//释放类

//释放Data数据
void freeData(Data* data) {
    //为空不释放
    if (data->isEmpty) return;
    //data的释放
    data->dataInfo.oper->freedata(data->data, data->content);
    //有content时才释放
    if (data->dataInfo.hasContent) {
        data->dataInfo.oper->freecontent(data->content);
    }

    data->content = NULL;
    data->data = NULL;

    data->dataInfo.oper = &emptyOperation;
    data->type = NOT_FOUND;
    data->isEmpty = true;
}

//这个仅仅只会把Entry中的key和value的data和others(不会释放oper,因为同种类型数据是要共用同一个opertion类型的指针)
void freeEntry(Entry* entry) {
    if (entry->isEmpty) return;
    freeData(&(entry->key));
    freeData(&(entry->value));
    entry->isEmpty = true;
}


//释放一个链表,包括它里面Data类型数据所指向的内容
static void freeList(List* plist) {
    if (plist->size == 0) {
        return;
    }
    Node* p = plist->head;
    Node* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        freeEntry(&(q->entry));
        free(q);
    }
    initializeList(plist);
}



void freeMap(Map* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        freeList(&(pMap->arr[i]));
    }
    free(pMap->arr);
    initializeMap(pMap);
}




///////////////////////////////////////////////////////////////////////////////////////
//链表的构建


static bool isEmptyList(List* plist) {
    return plist->size == 0;
}


/// @brief 初始化链表
/// @param plist 链表指针
static void initializeList(List* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
}

static Node* findNodeByKey(List* plist, Data key) {
    if (isEmptyList(plist)) return NULL;
    Node* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        if (compareKey(&(p->entry.key), &key) == SAME) {
            return p;
        }
    } 
    return NULL;
}

//这个是直接在后面插入的,不会判断key是否已经存在
static int insertEntryInList(List* plist, Entry entry) {
    Node* newNode = (Node*)malloc(sizeof(Node));
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

static int delStartNode(List* plist) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node* p = plist->head;
    
    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeEntry(&(p->entry));
    free(p);
    plist->size--;
    return Success;

}



static int delEndNode(List* plist) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node* p = plist->tail;
    
    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }

    freeEntry(&(p->entry));
    free(p);
    plist->size--;
    return Success;
}



static int delNodeByKey(List* plist, Data key) {
    if (isEmptyList(plist)) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    Node* p = findNodeByKey(plist, key);
    if (p == NULL) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    if (p == plist->head) return delStartNode(plist);
    if (p == plist->tail) return delEndNode(plist);


    p->prev->next = p->next;
    p->next->prev = p->prev;

    freeEntry(&(p->entry));
    free(p);
    plist->size--;
    return Success;
}







///////////////////////////////////////////////////////////////////////////////////////////////////
//复制类

//复制Data
static Data copyData(Data oldData) {

    if (oldData.isEmpty) {
        return returnEmptyData();
    }
    //复制void* data
    Data newData;

    //copy函数不仅仅只是把指针赋值,还要把整个void* data赋值一遍
    newData.data = oldData.dataInfo.oper->copydata(oldData.data, oldData.content);

    if (newData.data == NULL) {
        printf("\nMemory allocation failed\n");
        return returnEmptyData();
    }

    newData.dataInfo.hasContent = oldData.dataInfo.hasContent;
    //有content才复制content
    if (oldData.dataInfo.hasContent) {
        newData.content = oldData.dataInfo.oper->copycontent(oldData.content);
        if (newData.content == NULL) {
            printf("\nMemory allocation failed\n");
            oldData.dataInfo.oper->freedata(newData.data, oldData.content);
            return returnEmptyData();
        }
    } else {
        newData.content = NULL;
    }
    newData.type = oldData.type;

    //提供的相应操作函数因该是全局的
    newData.dataInfo.oper = oldData.dataInfo.oper;
    newData.isEmpty = false;
    return newData;
}

//复制一个Entry,注意:entry.state自动赋值,必须要自己赋值
static Entry copyEntry(Entry oldEntry) {
    if (oldEntry.isEmpty) {
        return returnEmptyEntry();
    }
    Entry newEntry;
    newEntry.key = copyData(oldEntry.key);
    if (newEntry.key.isEmpty) {
        return returnEmptyEntry();
    }
    newEntry.value = copyData(oldEntry.value);
    if (newEntry.value.isEmpty) {
        freeData(&(newEntry.key));
        return returnEmptyEntry();
    }
    newEntry.isEmpty = false;
    return newEntry;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//添加keyandval类




//这个函数保证可以添加
static int addEntryFunction(Map* pMap, Data key, Data value) {
    //hash
    ull index = (key.dataInfo.oper->hashdata(key.data, key.content))%pMap->mod;

    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p) {
        Data newVal = copyData(value);
        if (newVal.isEmpty) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
        freeData(&(p->entry.value));
        p->entry.value = newVal;
        return Success;
    }
    Entry oldEntry;
    oldEntry.isEmpty = false;
    oldEntry.key = key;
    oldEntry.value = value;
    
    Entry newEntry = copyEntry(oldEntry);
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
static int addEntryForFreshMap(Map* pMap, Data key, Data value) {
    ull index = (key.dataInfo.oper->hashdata(key.data, key.content))%pMap->mod;
    Entry entry;
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


static void freeListForFreshMap(List* plist) {
    if (isEmptyList(plist)) {
        return;
    }
    Node* p = plist->head;
    Node* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeList(plist);
}


//重hash
static int freshMap(Map* pMap) {
    int newLen = 0;
    if (pMap->len == 0) {
        newLen = 16;    //如果为空,直接给16的空间
    } else {
        newLen = (pMap->len+1)*2;   //否则扩容两倍
    }

    int newSize = pMap->size;
    int newMod = returnLargestPrime(newLen);
    
    //新创建一个newMap;
    Map newMap;
    List* newArray = (List*)malloc(newLen*sizeof(List));
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
        Node* p = pMap->arr[i].head;
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



int insertKeyAndValInMap(Map* pMap, Data key, Data val) {
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
Data returnCopyValByKey(Map* pMap, Data key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyData();
    ull index = (key.dataInfo.oper->hashdata(key.data, key.content))%pMap->mod;
    
    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return returnEmptyData();
    } else {
        Data newData;
        newData = copyData(p->entry.value);
        if (newData.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newData;
    }
}

Data returnPtrValByKey(Map* pMap, Data key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyData();
    ull index = (key.dataInfo.oper->hashdata(key.data, key.content))%pMap->mod;
    
    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return returnEmptyData();
    } else {
        return p->entry.value;
    }
}


Entry returnCopyEntryByKey(Map* pMap, Data key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return returnEmptyEntry();
    ull index = (key.dataInfo.oper->hashdata(key.data, key.content))%pMap->mod;
    
    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return returnEmptyEntry();
    } else {
        Entry newEntry;
        newEntry = copyEntry(p->entry);
        if (newEntry.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newEntry;
    }
}


bool hasKeyInMap(Map* pMap, Data key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return false;
    ull index = (key.dataInfo.oper->hashdata(key.data, key.content))%pMap->mod;
    
    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return false;
    } else {
        return true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//删除类


int delEntryByKey(Map* pMap, Data key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return Warning;
    ull index = (key.dataInfo.oper->hashdata(key.data, key.content))%pMap->mod;
    
    if (delNodeByKey(&(pMap->arr[index]), key) == None) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    pMap->size--;
    return Success;
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//整合类

Data stackData(void* data, void* content, int type, InfoOfData dataInfo) {
    Data newData;
    newData.data = data;
    newData.isEmpty = false;
    newData.dataInfo = dataInfo;
    newData.content = content;
    newData.type = type;
    return newData;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//打印类

void printData(Data data, char* tip) {
    if (data.isEmpty) {
        printf("\nData is empty, cannot print\n");
        return;
    }
    printf("[%s:", tip);
    data.dataInfo.oper->printdata(data.data, data.content);
    printf("]");
}

void printEntry(Entry entry) {
    if (entry.isEmpty) {
        printf("\nEntry is empty, cannot print\n");
        return;
    }
    //key
    printf("[key:");
    entry.key.dataInfo.oper->printdata(entry.key.data, entry.key.content);
    
    //value
    printf(", value:");
    entry.value.dataInfo.oper->printdata(entry.value.data, entry.value.content);
    printf("]");
}

void printMap(Map* pMap) {
    if (pMap->size == 0) {
        printf("\nMap is empty, cannot print\n");
        return;
    }
    int cnt = 0;
    printf("[");
    for (int i = 0; i < pMap->len; i++) {
        Node* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (cnt != 0) {
                printf(", ");
            }
            printEntry(p->entry);
            cnt++;
        }
    }
    printf("]");
}


//////////////////////////////////////////////////////////////////////////////////////////////////








