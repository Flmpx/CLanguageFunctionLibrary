#define GET_LARGESTPRIME
#define ENTRY_STATE_IN_OAMAP
#define DATA_M_OPER
#include "_multiple_void_map_oa.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


static Entry_M_inOAMap getEmptyMEntry() {
    Entry_M_inOAMap entry;
    entry.key = getEmptyMData();
    entry.value = getEmptyMData();
    entry.state = NONE_IN_MAP;
    entry.isEmpty = true;
    return entry;
}



void initMOAMap(OAMap_M* pMap) {
    pMap->arr = NULL;
    pMap->len = pMap->size = 0;
    pMap->mod = 2;
}


///////////////////////////////////////////////////////////////////////////////////
//比较类



//////////////////////////////////////////////////////////////////////////////////////
//释放类


void freeMValInMOAMap(Data_M* inputData) {
    freeMData(inputData);
}


//不会自动给entry的state进行赋值, 自己根据情况进行赋值,这个仅仅只会把Entry中的key和value的data和others(不会释放oper,因为同种类型数据是要共用同一个opertion类型的指针)
void freeMEntryInMOAMap(Entry_M_inOAMap* entry) {
    if (entry->isEmpty) return;
    freeMData(&(entry->key));
    freeMData(&(entry->value));
    entry->isEmpty = true;
}

void freeMOAMap(OAMap_M* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[i].state == EXIST_IN_MAP) {
            freeMEntryInMOAMap(&(pMap->arr[i]));
        }
    }
    free(pMap->arr);
    initMOAMap(pMap);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//复制类

//复制一个Entry,注意:entry.state不是自动赋值,必须要自己赋值
static Entry_M_inOAMap copyMEntry(Entry_M_inOAMap oldEntry) {
    if (oldEntry.isEmpty) {
        return getEmptyMEntry();
    }
    Entry_M_inOAMap newEntry;
    newEntry.key = copyMData(oldEntry.key);
    if (newEntry.key.isEmpty) {
        return getEmptyMEntry();
    }
    newEntry.value = copyMData(oldEntry.value);
    if (newEntry.value.isEmpty) {
        freeMData(&(newEntry.key));
        return getEmptyMEntry();
    }
    newEntry.isEmpty = false;
    return newEntry;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//添加keyandval类




//这个函数保证可以添加
static InfoOfReturn addMEntryFunction(OAMap_M* pMap, Data_M key, Data_M value) {
    //hash
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;

    //用于记录第一次出现的的Del位置, 这么做的原因是即便碰到Del标记也不能直接插入
    int flagFindDel = 0;
    ull firstDelIndex = pMap->len+10;
    //找到一个NONE或者DEl标记的位置
    while (pMap->arr[index].state != NONE_IN_MAP) {
        if (pMap->arr[index].state == DEL_IN_MAP && flagFindDel == 0) {
            firstDelIndex = index;
            flagFindDel = 1;
        }
        //如果发现是同一个key,则更新数据
        if (compareMData(&(pMap->arr[index].key), &key) == SAME) {
            Data_M newVal = copyMData(value);
            if (newVal.isEmpty) {
                printf("\nMemory allocation failed\n");
                return Warning;
            }
            freeMData(&(pMap->arr[index].value));
            pMap->arr[index].value = newVal;
            return Success;
        }
        index++;
        index %= pMap->len;
    }
    //如果之间找到了Del标记, 就在Del位置拆即可
    if (flagFindDel) {
        index = firstDelIndex;
    }
    //使用copyEntry函数进行操作
    Entry_M_inOAMap oldEntry;
    oldEntry.isEmpty = false;
    oldEntry.key = key;
    oldEntry.value = value;
    pMap->arr[index] = copyMEntry(oldEntry);
    
    if (pMap->arr[index].isEmpty) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->arr[index].state = EXIST_IN_MAP;
    pMap->size++;
    return Success;
}




//专门为重哈希做的软拷贝方式添加的Entry
static InfoOfReturn addMEntryForFreshMOAMap(OAMap_M* pMap, Data_M key, Data_M value) {
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
static InfoOfReturn freshMOAMap(OAMap_M* pMap) {
    int newLen = 0;
    if (pMap->len == 0) {
        newLen = 16;    //如果为空,直接给16的空间
    } else {
        newLen = (pMap->len+1)*2;   //否则扩容两倍
    }

    int newSize = pMap->size;
    int newMod = getLargestPrime(newLen);
    
    //新创建一个newMap;
    OAMap_M newMap;
    Entry_M_inOAMap* newArray = (Entry_M_inOAMap*)malloc(newLen*sizeof(Entry_M_inOAMap));
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
            addMEntryForFreshMOAMap(&newMap, pMap->arr[i].key, pMap->arr[i].value);
        }
    }

    //释放掉原有Entry数组
    free(pMap->arr);

    //给新址
    *pMap = newMap;
    return Success;
}



InfoOfReturn insertMKeyAndMValInMOAMap(OAMap_M* pMap, Data_M key, Data_M val) {
    //当填充因子大于75%时自动扩容
    if (4*(pMap->size) >= 3*(pMap->len)) {
        if (freshMOAMap(pMap) == Warning) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
    }
    return addMEntryFunction(pMap, key, val);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//查找类


//通过key返回key在Map中的位置
static Position getIndexByMKey(OAMap_M* pMap, Data_M key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return NOT_FOUND;
    ull index = (key.dataInfo->oper->hashdata(key.data, key.content))%pMap->mod;
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[index].state == NONE_IN_MAP) {
            return NOT_FOUND;
        }
        
        //这个也可以比较为空的情况
        if (compareMData(&(pMap->arr[index].key), &key) == SAME) {
            return index;
        }
        index++;
        index %= (pMap->len);
    }
    return NOT_FOUND;
}


//返回的Data数据为新建,用完后记得释放
Data_M getCopyMValByMKeyInMOAMap(OAMap_M* pMap, Data_M key) {
    int index = getIndexByMKey(pMap, key);
    if (index == NOT_FOUND) {
        printf("\nNot Found\n");
        return getEmptyMData();
    } else {
        Data_M newData;
        newData = copyMData(pMap->arr[index].value);
        if (newData.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newData;
    }
}

Data_M getPtrMValByMKeyInMOAMap(OAMap_M* pMap, Data_M key) {
    int index = getIndexByMKey(pMap, key);
    if (index == NOT_FOUND) {
        printf("\nNot Found\n");
        return getEmptyMData();
    } else {
        return pMap->arr[index].value;
    }
}


Entry_M_inOAMap getCopyMEntryByKeyInMOAMap(OAMap_M* pMap, Data_M key) {
    int index = getIndexByMKey(pMap, key);
    if (index == NOT_FOUND) {
        return getEmptyMEntry();
    } else {
        Entry_M_inOAMap newEntry;
        newEntry = copyMEntry(pMap->arr[index]);
        if (newEntry.isEmpty) {
            printf("\nMemory allocation failed\n");
        }
        return newEntry;
    }
}


bool hasKeyInMOAMap(OAMap_M* pMap, Data_M key) {
    if (getIndexByMKey(pMap, key) == NOT_FOUND) {
        return false;
    } else {
        return true;
    }
}



/////////////////////////////////////////////////////////////////////////////////////////
//删除类


InfoOfReturn delMEntryByMKeyInMOAMap(OAMap_M* pMap, Data_M key) {
    int index = getIndexByMKey(pMap, key);
    if (index == NOT_FOUND) {
        return None;
    } else {
        freeMEntryInMOAMap(&(pMap->arr[index]));
        pMap->arr[index].state = DEL_IN_MAP;
        pMap->size--;
        return Success;
    }
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//整合类

Data_M stackMDataInMOAMap(void* data, void* content, int type, InfoOfData* dataInfo) {
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

void printMKeyInMOAMap(Data_M keyData) {
    if (keyData.isEmpty) {
        printf("\nkey is empty, cannot print\n");
        return;
    }
    printf("[key:");
    keyData.dataInfo->oper->printdata(keyData.data, keyData.content);
    printf("]");
    
}

void printMValInMOAMap(Data_M valData) {
    if (valData.isEmpty) {
        printf("\nval is empty, cannot print\n");
        return;
    }
    printf("[val:");
    valData.dataInfo->oper->printdata(valData.data, valData.content);
    printf("]");

}

void printMEntryInMOAMap(Entry_M_inOAMap entry) {
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

void printMOAMap(OAMap_M* pMap) {
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
            printMEntryInMOAMap(pMap->arr[i]);
            cnt++;
        }
        
    }
    printf("]");
}


//////////////////////////////////////////////////////////////////////////////////////////////////

