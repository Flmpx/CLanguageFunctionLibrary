#include "_hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

Operation emptyOperation = {
    NULL, NULL, NULL, NULL, NULL
};

Otherthings emptyOtherthings = {
    NULL, NULL, NULL, NULL, NULL
};




static bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n%2 == 0 || n%3 == 0) return false;
    for (int i = 5; i <= n/i; i+=6) {
        if (n%i == 0 || n%(i+2) == 0) return false;
    }
    return true;
}

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




static int compareString(char* string_a, char* string_b) {
    if (string_a == string_b) return SAME;
    if (string_a == NULL || string_b == NULL) return DIFFERENT;
    return strcmp(string_a, string_b) == 0 ? SAME : DIFFERENT;
}

static int compareOthers(Otherthings* other_a, Otherthings* other_b) {
    int result = 0;
    result += compareString(other_a->thingOf_Compare, other_b->thingOf_Compare);
    if (result) return DIFFERENT;
    result += compareString(other_a->thingOf_Copy, other_b->thingOf_Copy);
    if (result) return DIFFERENT;
    result += compareString(other_a->thingOf_Free, other_b->thingOf_Free);
    if (result) return DIFFERENT;
    result += compareString(other_a->thingOf_Hash, other_b->thingOf_Hash);
    if (result) return DIFFERENT;
    result += compareString(other_a->thingOf_Print, other_b->thingOf_Print);
    if (result) return DIFFERENT;
    return SAME;
}

//这个函数通过判断函数指针是否相同来判断函数是否相同
static int compareOperation(Operation* oper_b, Operation* oper_a) {
    int result = 0;
    result += (oper_a->freedata == oper_b->freedata);
    result += (oper_a->cmp == oper_b->cmp);
    result += (oper_a->copy == oper_b->copy);
    result += (oper_a->hash == oper_b->hash);
    result += (oper_a->print == oper_b->print);

    return result == 5 ? SAME : DIFFERENT;
}

//这个Compare函数
static int compareData(Data* Data_a, Data* Data_b, _compare cmp) {
    if (Data_a->type != Data_b->type) {
        return DIFFERENT;
    }
    if (compareOperation(Data_a->oper, Data_b->oper)) {
        printf("\nType is the same but operation is different! Please check!\n");
        return DIFFERENT;
    }

    if (compareOthers(Data_a->others, Data_b->others)) {
        return DIFFERENT;
    }
    if (cmp(Data_a->data, Data_b->data, Data_a->others->thingOf_Compare)) {
        return DIFFERENT;
    }
    return SAME;

}


static void freeOthers(Otherthings* others) {
    free(others->thingOf_Compare);
    free(others->thingOf_Copy);
    free(others->thingOf_Free);
    free(others->thingOf_Hash);
    free(others->thingOf_Print);
    free(others);
}

void freeData(Data* data) {
    if (data->isEmpty) return;
    data->oper->freedata(data->data, data->others->thingOf_Free);
    freeOthers(data->others);
    data->data = NULL;
    data->oper = &emptyOperation;
    data->others = &emptyOtherthings;
    data->type = -1;
    data->isEmpty = true;
}

//这个仅仅只会把Entry中的key和value的data和others(不会释放oper,因为同种类型数据是要共用同一个opertion类型的指针)
void freeEntry(Entry* entry) {
    freeData(&(entry->key));
    freeData(&(entry->value));
}

void freeMap(Map* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[i].state == 1) {
            freeEntry(&(pMap->arr[i]));
        }
    }
    free(pMap->arr);
    initializeMap(pMap);
}





static char* copyString(char* oldString) {
    if (oldString == NULL) return NULL;
    int len = strlen(oldString);
    char* newString = (char*)malloc((len+1)*sizeof(char));
    strcpy(newString, oldString);
    return newString;
}

static Otherthings* copyOtherthings(Otherthings* oldOtherthings) {
    Otherthings* newThing = (Otherthings*)malloc(sizeof(Otherthings));
    newThing->thingOf_Compare = copyString(oldOtherthings->thingOf_Compare);
    newThing->thingOf_Copy = copyString(oldOtherthings->thingOf_Copy);
    newThing->thingOf_Free = copyString(oldOtherthings->thingOf_Free);
    newThing->thingOf_Hash = copyString(oldOtherthings->thingOf_Hash);
    newThing->thingOf_Print = copyString(oldOtherthings->thingOf_Print);
    return newThing;
}

Data copyData(Data oldData) {
    //复制void* data
    Data newData;

    //copy函数不仅仅只是把指针赋值,还要把整个void* data赋值一遍
    newData.data = oldData.oper->copy(oldData.data, oldData.others->thingOf_Copy);

    newData.type = oldData.type;

    //提供的相应操作函数因该是全局的
    newData.oper = oldData.oper;
    //由于输入的字符串信息可能是静态区的,所以需要完全复制
    newData.others = copyOtherthings(oldData.others);
    newData.isEmpty = false;
    return newData;
}

Entry copyEntry(Entry oldEntry) {
    Entry newEntry;
    newEntry.key = copyData(oldEntry.key);
    newEntry.value = copyData(oldEntry.value);
    newEntry.isSingle = true;
    newEntry.state = EXIST;
    return newEntry;
}


//这个函数保证可以添加
static int addEntryFunction(Map* pMap, Data key, Data value) {
    ull index = (key.oper->hash(key.data, key.others->thingOf_Hash))%pMap->mod;
    while (pMap->arr[index].state != NONE && pMap->arr[index].state != DEL) {
        if (compareData(&(pMap->arr[index].key), &key, key.oper->cmp) == 0) {
            freeData(&(pMap->arr[index].value));
            pMap->arr[index].value = copyData(value);
            return Success;
        }
        index++;
        index %= pMap->len;
    }
    pMap->arr[index].key = copyData(key);
    pMap->arr[index].value = copyData(value);
    pMap->arr[index].state = EXIST;
    pMap->arr[index].isSingle = false;
    pMap->size++;
    return Success;
}


static int addEntryForFreshMap(Map* pMap, Data key, Data value) {
    ull index = (key.oper->hash(key.data, key.others->thingOf_Hash))%pMap->mod;
    while (pMap->arr[index].state != NONE) {
        index++;
        index %= pMap->len;
    }
    pMap->arr[index].key = key;
    pMap->arr[index].value = value;
    pMap->arr[index].state = EXIST;
    pMap->arr[index].isSingle = false;
    pMap->size++;
    return Success;
}

static int freshMap(Map* pMap) {
    int newLen = 0;
    if (pMap->len == 0) {
        newLen = 16;
    } else {
        newLen = (pMap->len+1)*2;
    }
    int newSize = pMap->size;
    int newMod = returnLargestPrime(newLen);
    
    Map newMap;
    Entry* newArray = (Entry*)malloc(newLen*sizeof(Entry));
    for (int i = 0; i < newLen; i++) {
        newArray[i].state = NONE;
    }

    newMap.arr = newArray;
    newMap.len = newLen;
    newMap.mod = newMod;
    newMap.size = 0;
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[i].state == 1) {
            addEntryForFreshMap(&newMap, pMap->arr[i].key, pMap->arr[i].value);
        }
    }
    free(pMap->arr);
    *pMap = newMap;
    return Success;
}


int insertEntryInMap(Map* pMap, Data key, Data val) {
    if (4*(pMap->size) >= 3*(pMap->len)) {
        freshMap(pMap);
    }
    addEntryFunction(pMap, key, val);
    return Success;
}


Data returnEmptyData() {
    Data data;
    data.data = NULL;
    data.isEmpty = true;
    data.type = -1;
    data.oper = &emptyOperation;
    data.others = &emptyOtherthings;
    return data;
}


static int returnIndexByKey(Map* pMap, Data key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return NOT_FOUND;
    ull index = (key.oper->hash(key.data, key.others->thingOf_Hash))%pMap->mod;
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[index].state == NONE) {
            return NOT_FOUND;
        }
        if (pMap->arr[index].state == DEL) {
            index++;
            index %= (pMap->len);
            continue;
        }

        if (compareData(&(pMap->arr[index].key), &key, key.oper->cmp) == 0) {
            return index;
        }
        index++;
        index %= (pMap->len);
    }
    return NOT_FOUND;
}


//返回的Data数据为新建,用完后记得释放
Data returnValByKey(Map* pMap, Data key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        return returnEmptyData();
    } else {
        return copyData(pMap->arr[index].value);
    }
}


bool hasKeyInMap(Map* pMap, Data key) {
    if (returnIndexByKey(pMap, key) == NOT_FOUND) {
        return false;
    } else {
        return true;
    }
}

int delEntryByKey(Map* pMap, Data key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        return None;
    } else {
        freeEntry(&(pMap->arr[index]));
        pMap->arr[index].state = DEL;
        pMap->size--;
        return Success;
    }
}