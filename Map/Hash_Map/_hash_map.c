#include "_hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/// @brief 空oper,代表一种错误状态
static Operation emptyOperation = {
    NULL, NULL, NULL, NULL, NULL
};


/// @brief 空others,代表一种错误状态
static Otherthings emptyOtherthings = {
    NULL, NULL, NULL, NULL, NULL, true
};



//返回空Data
static Data returnEmptyData() {
    Data data;
    data.data = NULL;
    data.isEmpty = true;
    data.type = -1;
    data.oper = &emptyOperation;
    data.others = emptyOtherthings;
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


/// @brief 比较字符串是否相同
/// @param string_a 字符串a
/// @param string_b 字符串b
/// @return SAME-->相同 | DIFFERENT-->不同
static int compareString(char* string_a, char* string_b) {
    if (string_a == string_b) return SAME;  //二者都为空,或者相同
    if (string_a == NULL || string_b == NULL) return DIFFERENT; //一个为空说明不同
    return strcmp(string_a, string_b) == 0 ? SAME : DIFFERENT;  //正常比较
}


/// @brief 比较Others中的描述性字符串是否相同
/// @param other_a a
/// @param other_b b
/// @return SAME-->相同 | DIFFERENT-->不同
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

/// @brief 比较二者Data类型是否相同
/// @param Data_a a
/// @param Data_b b
/// @param cmp _compare类型的函数
/// @return SAME-->相同 | DIFFERENT-->不同
static int compareData(Data* Data_a, Data* Data_b, _compare cmp) {
    if (Data_a->type != Data_b->type) {
        return DIFFERENT;
    }
    if (compareOperation(Data_a->oper, Data_b->oper)) {
        //类型相同带操作函数不同,说明有问题
        printf("\nType is the same but operation is different! Please check!\n");
        return DIFFERENT;
    }

    if (compareOthers(&(Data_a->others), &(Data_b->others))) {
        return DIFFERENT;
    }
    if (cmp(Data_a->data, Data_b->data, Data_a->others.thingOf_Compare)) {
        return DIFFERENT;
    }
    return SAME;

}


//////////////////////////////////////////////////////////////////////////////////////
//释放类


//释放others中的字符串数据
static void freeOthers(Otherthings* others) {

    if (others->isEmpty) return;    //如果other为空,不进行释放
    free(others->thingOf_Compare);
    free(others->thingOf_Copy);
    free(others->thingOf_Free);
    free(others->thingOf_Hash);
    free(others->thingOf_Print);
    others->isEmpty = true;
}


//释放Data数据
void freeData(Data* data) {
    //为空不释放
    if (data->isEmpty) return;
    //data的释放
    data->oper->freedata(data->data, data->others.thingOf_Free);
    freeOthers(&(data->others));
    data->data = NULL;
    data->oper = &emptyOperation;
    data->others = emptyOtherthings;
    data->type = -1;
    data->isEmpty = true;
}

//这个仅仅只会把Entry中的key和value的data和others(不会释放oper,因为同种类型数据是要共用同一个opertion类型的指针)
void freeEntry(Entry* entry) {
    if (entry->isEmpty) return;
    freeData(&(entry->key));
    freeData(&(entry->value));
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


//复制字符串
static char* copyString(char* oldString) {
    if (oldString == NULL) return NULL;
    int len = strlen(oldString);
    char* newString = (char*)malloc((len+1)*sizeof(char));
    if (newString == NULL) return NULL; //
    strcpy(newString, oldString);
    return newString;
}


//复制others
static Otherthings copyOtherthings(Otherthings oldOtherthings) {
    if (oldOtherthings.isEmpty) {
        return emptyOtherthings;
    }
    Otherthings newThing;
    newThing.thingOf_Compare = newThing.thingOf_Copy = newThing.thingOf_Free = newThing.thingOf_Hash = newThing.thingOf_Print = NULL;

    newThing.isEmpty = false;
    newThing.thingOf_Compare = copyString(oldOtherthings.thingOf_Compare);
    if (newThing.thingOf_Compare == NULL) {
        //分配失败,或者本身为空,返回空
        //这也说明提示信息要么不可以为NULL,只能为"",NULL代表错误状态
        return emptyOtherthings;
    }
    newThing.thingOf_Copy = copyString(oldOtherthings.thingOf_Copy);
    if (newThing.thingOf_Copy == NULL) {
        freeOthers(&newThing);
        return emptyOtherthings;
    }
    newThing.thingOf_Free = copyString(oldOtherthings.thingOf_Free);
    if (newThing.thingOf_Free == NULL) {
        freeOthers(&newThing);
        return emptyOtherthings;
        
    }
    newThing.thingOf_Hash = copyString(oldOtherthings.thingOf_Hash);
    if (newThing.thingOf_Hash == NULL) {
        freeOthers(&newThing);
        return emptyOtherthings;
        
    }
    newThing.thingOf_Print = copyString(oldOtherthings.thingOf_Print);
    if (newThing.thingOf_Print == NULL) {
        freeOthers(&newThing);
        return emptyOtherthings;
    }
    return newThing;
}


//复制Data
static Data copyData(Data oldData) {

    if (oldData.isEmpty) {
        return returnEmptyData();
    }
    //复制void* data
    Data newData;

    //copy函数不仅仅只是把指针赋值,还要把整个void* data赋值一遍
    newData.data = oldData.oper->copy(oldData.data, oldData.others.thingOf_Copy);

    if (newData.data == NULL) {
        return returnEmptyData();
    }
    newData.type = oldData.type;

    //提供的相应操作函数因该是全局的
    newData.oper = oldData.oper;
    //由于输入的字符串信息可能是静态区的,所以需要完全复制
    newData.others = copyOtherthings(oldData.others);
    if (newData.others.isEmpty) {
        oldData.oper->freedata(newData.data, oldData.others.thingOf_Free);
        return returnEmptyData();
    }
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
    ull index = (key.oper->hash(key.data, key.others.thingOf_Hash))%pMap->mod;
    //找到一个NONE或者DEl标记的位置
    while (pMap->arr[index].state != NONE_IN_MAP && pMap->arr[index].state != DEL_IN_MAP) {
        //如果发现是同一个key,则更新数据
        if (compareData(&(pMap->arr[index].key), &key, key.oper->cmp) == 0) {
            freeData(&(pMap->arr[index].value));
            pMap->arr[index].value = copyData(value);
            if (pMap->arr[index].value.isEmpty) {
                return Warning;
            } else {
                return Success;
            }
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
        return Warning;
    }
    pMap->arr[index].state = EXIST_IN_MAP;
    pMap->size++;
    return Success;
}


//专门为重哈希做的软拷贝方式添加的Entry
static int addEntryForFreshMap(Map* pMap, Data key, Data value) {
    ull index = (key.oper->hash(key.data, key.others.thingOf_Hash))%pMap->mod;
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
    Entry* newArray = (Entry*)malloc(newLen*sizeof(Entry));
    if (newArray == NULL) return Warning;
    for (int i = 0; i < newLen; i++) {
        //初始化
        newArray[i].state = NONE_IN_MAP;
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



int insertEntryInMap(Map* pMap, Data key, Data val) {
    //当填充因子大于75%时自动扩容
    if (4*(pMap->size) >= 3*(pMap->len)) {
        if (freshMap(pMap) == Warning) {
            return Warning;
        }
    }
    return addEntryFunction(pMap, key, val);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//查找类




//通过key返回key在Map中的位置
static int returnIndexByKey(Map* pMap, Data key) {
    if (pMap->len == 0 || pMap->size == 0 || pMap->arr == NULL) return NOT_FOUND;
    ull index = (key.oper->hash(key.data, key.others.thingOf_Hash))%pMap->mod;
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[index].state == NONE_IN_MAP) {
            return NOT_FOUND;
        }
        if (pMap->arr[index].state == DEL_IN_MAP) {
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

Entry returnEntryByKey(Map* pMap, Data key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        return returnEmptyEntry();
    } else {
        return copyEntry(pMap->arr[index]);
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

Data stackData(void* data, int type, Operation* oper, Otherthings others) {
    Data newData;
    newData.data = data;
    newData.isEmpty = false;
    newData.oper = oper;
    newData.others = others;
    newData.type = type;
    return newData;
}


Otherthings stackOthers(char* thingOf_Free, char* thingOf_Hash, char* thingOf_Compare, char* thingOf_Copy, char* thingOf_Print) {
    Otherthings newOthers;
    newOthers.thingOf_Compare = thingOf_Compare;
    newOthers.thingOf_Copy = thingOf_Copy;
    newOthers.thingOf_Free = thingOf_Free;
    newOthers.thingOf_Hash = thingOf_Hash;
    newOthers.thingOf_Print = thingOf_Print;
    newOthers.isEmpty = false;
    return newOthers;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////