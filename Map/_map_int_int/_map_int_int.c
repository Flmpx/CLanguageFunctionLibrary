#include "_map_int_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum info {
    Warning = -1,
    None = 0,
    Success = 1
};


bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n%2 == 0 || n%3 == 0) return false;
    for (int i = 5; i <= n/i; i+=6) {
        if (n%i == 0 || n%(i+2) == 0) return false;
    }
    return true;
}

int returnLargestPrime(int n) {
    if (n <= 3) return n;
    if (n%2 == 0) n--;
    for (int i = n; ; i-=2) {
        if (isPrime(i)) return i;
    }
    return 2;
}

int hash(int key, int mod) {
    key = key < 0 ? -key : key;
    return key % mod;
}

void initializeMap(Map* pMap) {
    pMap->arr = NULL;
    pMap->len = pMap->size = 0;
    pMap->mod = 2;
}


void freeMap(Map* pMap) {
    free(pMap->arr);
    initializeMap(pMap);
}

//这个只是添加的功能
int addFunctionOfEntry(Map* pMap, int key, int val) {
    int index = hash(key, pMap->mod);
    int flagFindDel = 0;
    int firstDelIndex = pMap->len+10;
    while (pMap->arr[index].key != NONE) {
        if (pMap->arr[index].key != DEL && flagFindDel == 0) {
            firstDelIndex = index;
            flagFindDel = 1;
        } 
        if (pMap->arr[index].key == key) {
            pMap->arr[index].val = val;
            return Success;
        }
        index++;
        index %= pMap->len;
    }
    if (flagFindDel) {
        index = firstDelIndex;
    }
    pMap->arr[index].key = key;
    pMap->arr[index].val = val;
    pMap->size++;
    return Success;
}

int freshMap(Map* pMap) {
    int newLen = (pMap->len + 1)*2;
    int newSize = pMap->size;
    int newMod = returnLargestPrime(newLen);
    Entry* same = (Entry*)malloc(newSize*sizeof(Entry));

    if (same == NULL) {
        return Warning;
    }
    int cnt = 0;
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[i].key != DEL && pMap->arr[i].key != NONE) {
            same[cnt++] = pMap->arr[i];
        }
    }
    freeMap(pMap);
    pMap->mod = newMod;
    pMap->len = newLen;
    //pMap大小会在后面的添加函数中进行增加
    pMap->arr = (Entry*)malloc(newLen*sizeof(Entry));

    if (pMap->arr == NULL) {
        free(same);
        return Warning;
    }
    for (int i = 0; i < newLen; i++) {
        pMap->arr[i].key = pMap->arr[i].val = NONE;
    }

    for (int i = 0; i < cnt; i++) {
        addFunctionOfEntry(pMap, same[i].key, same[i].val);
    }
    free(same);
    return Success;
}

int insertEntryInMap(Map* pMap, int key, int val) {
    if (4*(pMap->size) >= 3*(pMap->len)) {
        freshMap(pMap);
    }
    addFunctionOfEntry(pMap, key, val);
}


int returnIndexByKey(Map* pMap, int key) {
    int index = hash(key, pMap->mod);
    for (int i = 0; i < pMap->len; i++) {
        if (pMap->arr[index].key == key) {
            return index;
        }
        if (pMap->arr[index].key == NONE) {
            return NOT_FOUND;
        }
        index++;
        index %= (pMap->len);
    }
    return NOT_FOUND;
}

int findValByKey(Map* pMap, int key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        return None;
    } else {
        return pMap->arr[index].val;
    }
}

int delEntryByKey(Map* pMap, int key) {
    int index = returnIndexByKey(pMap, key);
    if (index == NOT_FOUND) {
        return None;
    } else {
        pMap->arr[index].key = DEL;
        pMap->arr[index].val = NONE;
        pMap->size--;
        return Success;
    }
}