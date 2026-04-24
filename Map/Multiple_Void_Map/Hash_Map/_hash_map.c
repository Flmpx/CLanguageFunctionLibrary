#include "_hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum EntryStateInMap {
    DEL_IN_MAP = -1,
    NONE_IN_MAP = 0,
    EXIST_IN_MAP = 1
};






//返回空Data
static Data returnEmptyData() {
    Data data;
    data.data = NULL;
    data.isEmpty = true;
    data.dataInfo = NULL;
    data.content = NULL;
    
    return data;
}

static Entry returnEmptyEntry() {
    Entry entry;
    entry.key = returnEmptyData();
    entry.value = returnEmptyData();
    entry.state = NONE_IN_MAP;
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




/// @brief 比较二者Data类型是否相同
/// @param Data_a a
/// @param Data_b b
/// @param cmp _compare类型的函数
/// @return SAME-->相同 | DIFFERENT-->不同
static CmpResult compareKey(Data* Data_a, Data* Data_b) {
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
void freeData(Data* data) {
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
void freeEntry(Entry* entry) {
    if (entry->isEmpty) return;
    freeData(&(entry->key));
    freeData(&(entry->value));
    entry->isEmpty = true;
}

void freeMap(Map* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[i].state == EXIST_IN_MAP) {
            freeEntry(&(pMap->arr[i]));
        }
    }
    free(pMap->arr);
    initializeMap(pMap);
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
    newData.data = oldData.dataInfo->oper->copydata(oldData.data, oldData.content);

    if (newData.data == NULL) {
        printf("\nMemory allocation failed\n");
        return returnEmptyData();
    }

    newData.dataInfo->hasContent = oldData.dataInfo->hasContent;
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
static InfoOfReturn addEntryFunction(Map* pMap, Data key, Data value) {
    //hash
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    //找到一个NONE或者DEl标记的位置
    while (pMap->arr[index].state != NONE_IN_MAP && pMap->arr[index].state != DEL_IN_MAP) {
        //如果发现是同一个key,则更新数据
        if (compareKey(&(pMap->arr[index].key), &key) == 0) {
            Data newVal = copyData(value);
            if (newVal.isEmpty) {
                printf("\nMemory allocation failed\n");
                return Warning;
            }
            freeData(&(pMap->arr[index].value));
            pMap->arr[index].value = newVal;
            return Success;
        }
        index++;
        index %= pMap->len;
    }

    //使用copyEntry函数进行操作
    Entry oldEntry;
    oldEntry.isEmpty = false;
    oldEntry.key = key;
    oldEntry.value = value;
    pMap->arr[index] = copyEntry(oldEntry);
    
    if (pMap->arr[index].isEmpty) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->arr[index].state = EXIST_IN_MAP;
    pMap->size++;
    return Success;
}




//专门为重哈希做的软拷贝方式添加的Entry
static InfoOfReturn addEntryForFreshMap(Map* pMap, Data key, Data value) {
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    while (pMap->arr[index].state != NONE_IN_MAP) {
        index++;
        index %= pMap->len;
    }
    pMap->arr[index].key = key;
    pMap->arr[index].value = value;
    pMap->arr[index].state = EXIST_IN_MAP;
    pMap->arr[index].isEmpty = false;
    pMap->size++;
    return Success;
}


//重hash
static InfoOfReturn freshMap(Map* pMap) {
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
    Entry* newArray = (Entry*)malloc(newLen*sizeof(Entry));
    if (newArray == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    for (int i = 0; i < newLen; i++) {
        //初始化
        newArray[i].state = NONE_IN_MAP;
        newArray[i].isEmpty = true;
    }

    newMap.arr = newArray;
    newMap.len = newLen;
    newMap.mod = newMod;
    newMap.size = 0;    //再添加函数中会自动加,这里设置为0
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[i].state == EXIST_IN_MAP) {
            addEntryForFreshMap(&newMap, pMap->arr[i].key, pMap->arr[i].value);
        }
    }

    //释放掉原有Entry数组
    free(pMap->arr);

    //给新址
    *pMap = newMap;
    return Success;
}



InfoOfReturn insertEntryInMap(Map* pMap, Data key, Data val) {
    //当填充因子大于75%时自动扩容
    if (4*(pMap->size) >= 3*(pMap->len)) {
        if (freshMap(pMap) == Warning) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
    }
    return addEntryFunction(pMap, key, val);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//查找类


//通过key返回key在Map中的位置
static Position returnIndexByKey(Map* pMap, Data key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return NOT_FOUND;
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[index].state == NONE_IN_MAP) {
            return NOT_FOUND;
        }
        if (pMap->arr[index].state == DEL_IN_MAP) {
            index++;
            index %= (pMap->len);
            continue;
        }

        if (compareKey(&(pMap->arr[index].key), &key) == 0) {
            return index;
        }
        index++;
        index %= (pMap->len);
    }
    return NOT_FOUND;
}


//返回的Data数据为新建,用完后记得释放
Data returnCopyValByKey(Map* pMap, Data key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        printf("\nNot Found\n");
        return returnEmptyData();
    } else {
        Data newData;
        newData = copyData(pMap->arr[index].value);
        if (newData.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newData;
    }
}

Data returnPtrValByKey(Map* pMap, Data key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        printf("\nNot Found\n");
        return returnEmptyData();
    } else {
        return pMap->arr[index].value;
    }
}


Entry returnCopyEntryByKey(Map* pMap, Data key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        return returnEmptyEntry();
    } else {
        Entry newEntry;
        newEntry = copyEntry(pMap->arr[index]);
        if (newEntry.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newEntry;
    }
}


bool hasKeyInMap(Map* pMap, Data key) {
    if (returnIndexByKey(pMap, key) == NOT_FOUND) {
        return false;
    } else {
        return true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//删除类


int delEntryByKey(Map* pMap, Data key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        return None;
    } else {
        freeEntry(&(pMap->arr[index]));
        pMap->arr[index].state = DEL_IN_MAP;
        pMap->size--;
        return Success;
    }
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//整合类

Data stackData(void* data, void* content, int type, InfoOfData* dataInfo) {
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
    data.dataInfo->oper->printdata(data.data, data.content);
    printf("]");
}

void printEntry(Entry entry) {
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

void printMap(Map* pMap) {
    if (pMap->size == 0) {
        printf("\nMap is empty, cannot print\n");
        return;
    }
    int cnt = 0;
    printf("[");
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[i].isEmpty == false) {
            if (cnt != 0) {
                printf(", ");
            }
            printEntry(pMap->arr[i]);
            cnt++;
        }
        
    }
    printf("]");
}


//////////////////////////////////////////////////////////////////////////////////////////////////

