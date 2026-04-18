#include "_map_string_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static ull mod = 1000000007;
static ull base = 131;

static Entry returnEmptyEntry() {
    Entry entry;
    entry.isEmpty = true;
    entry.key = NULL;
    entry.val = NOT_FOUND;
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

static void initializeList(List* plist) {
    plist->head = plist->tail = NULL;
    plist->size = 0;
}

static bool isEmptyList(List* plist) {
    return plist->size == 0;
}

static Node* findNodeByKey(List* plist, char* key) {
    if (isEmptyList(plist)) return NULL;
    Node* p = plist->head;
    for (int i = 0; i < plist->size; i++, p = p->next) {
        if (strcmp(key, p->entry.key) == 0) {
            return p;
        }
    }
    return NULL;
}

//这个只管添加,不会复制
static int insertKeyAndValInList(List* plist, char* key, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }

    newNode->entry.key = key;
    newNode->entry.val = val;
    newNode->entry.isEmpty = false;
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
    if (isEmptyList(plist)) return None;
    Node* p = plist->head;

    if (plist->size > 1) {
        plist->head = plist->head->next;
        plist->head->prev = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }
    free(p->entry.key);
    free(p);
    plist->size--;
    return Success;
}

static int delEndNode(List* plist) {
    if (isEmptyList(plist)) return None;
    Node* p = plist->tail;
    
    if (plist->size > 1) {
        plist->tail = plist->tail->prev;
        plist->tail->next = NULL;
    } else {
        plist->head = plist->tail = NULL;
    }
    free(p->entry.key);
    free(p);
    plist->size--;
    return Success;
}


static int delNodeByKey(List* plist, char* key) {
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
    
    free(p->entry.key);
    free(p);
    plist->size--;
    return Success;
}


static void freeList(List* plist) {
    if (isEmptyList(plist)) return;
    Node* p = plist->head;
    Node* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q->entry.key);
        free(q);
    }
    initializeList(plist);
}

void freeEntry(Entry entry) {
    free(entry.key);
    entry.isEmpty = true;
    entry.key = NULL;
    entry.val = NOT_FOUND;
}

void freeMap(Map* pMap) {
    for (int i = 0; i < pMap->len; i++) {
        freeList(&(pMap->arr[i]));
    }
    free(pMap->arr);
    initializeMap(pMap);
}




static ull hashString(char* string) {
    int len = strlen(string);
    ull result = 0;
    for (int i = 0; i < len; i++) {
        result += (result * base % mod + string[i] + 199)%mod;
    }
    return result;
}


static char* copyString(char* key) {
    int len = strlen(key);
    char* newString = (char*)malloc((len+1)*sizeof(char));
    if (newString == NULL) {
        printf("\nMemory allocation failed\n");
        return NULL;
    }
    strcpy(newString, key);
    return newString;
}

static int addKeyAndValFunction(Map* pMap, char* key, int val) {
    ull index = hashString(key)%(pMap->mod);
    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p) {
        p->entry.val = val;
        return Success;
    }
    //这里的字符串要重新复制一个
    char* newString = copyString(key);
    if (newString == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    insertKeyAndValInList(&(pMap->arr[index]), newString, val);
    pMap->size++;
    return Success;
}

static int addFuctionForFreshMap(Map* pMap, char* key, int val) {
    ull index = hashString(key)%(pMap->mod);
    if(insertKeyAndValInList(&(pMap->arr[index]), key, val) == Warning) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    pMap->size++;
    return Success;
}

//这个不会删除char* 所指向的字符串的数据,这是软删除
static void freeListForFreshMap(List* plist) {
    if (isEmptyList(plist)) return;
    Node* p = plist->head;
    Node* q = NULL;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    initializeList(plist);
}


static int freshMap(Map* pMap) {
    int newLen;
    if (pMap->len == 0) {
        newLen = 16;
    } else {
        newLen = pMap->len*2;
    }
    
    Map newMap;
    newMap.arr = (List*)malloc(newLen*sizeof(List));
    if (newMap.arr == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    newMap.len = newLen;
    newMap.mod = returnLargestPrime(newLen);
    newMap.size = 0;
    
    //初始话新List数组
    for (int i = 0; i < newLen; i++) {
        initializeList(&(newMap.arr[i]));
    }

    for (int i = 0; i < pMap->len; i++) {
        Node* p = pMap->arr[i].head;
        for (int j = 0; j < pMap->arr[i].size; j++, p = p->next) {
            if (addFuctionForFreshMap(&newMap, p->entry.key, p->entry.val) == Warning) {
                printf("\nMemory allocation failed\n");
                return Warning;
            }
        }
        //释放掉这个位置的链表(软删除)
        freeListForFreshMap(&(pMap->arr[i]));
    }
    free(pMap->arr);

    *pMap = newMap;
    return Success;

    
}





int insertKeyAndValInMap(Map* pMap, char* key, int val) {
    if (4*pMap->size >= 3*pMap->len || pMap->len == 0) {
        if (freshMap(pMap) == Warning) {
            printf("\nMemory allocation failed\n");
            return Warning;
        }
    }
    addKeyAndValFunction(pMap, key, val);
    return Success;
}


//-1代表没找到
int returnValByKey(Map* pMap, char* key) {
    ull index = hashString(key)%(pMap->mod);
    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return NOT_FOUND;
    } else {
        return p->entry.val;
    }
}

static Entry copyEntry(Entry oldEntry) {
    Entry newEntry;
    newEntry.isEmpty = oldEntry.isEmpty;
    newEntry.key = copyString(oldEntry.key);
    newEntry.val = oldEntry.val;
    if (newEntry.key == NULL) {
        printf("\nMemory allocation failed\n");
        return returnEmptyEntry();
    }
    return newEntry;
}

Entry returnEntryByKey(Map* pMap, char* key) {
    ull index = hashString(key)%(pMap->mod);
    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p == NULL) {
        return returnEmptyEntry();
    } else {
        Entry newEntry = copyEntry(p->entry);
        if (newEntry.isEmpty) {
            printf("\nMemory allocation failed\n");
            return returnEmptyEntry();
        }
        return newEntry;
    }
}

bool hasKeyInMap(Map* pMap, char* key) {
    ull index = hashString(key)%(pMap->mod);
    Node* p = findNodeByKey(&(pMap->arr[index]), key);
    if (p) {
        return true;
    } else {
        return false;
    }
}


int delEntryByKey(Map* pMap, char* key) {
    if (pMap->arr == NULL || pMap->size == 0 || pMap->len == 0) return Warning;
    ull index = hashString(key)%(pMap->mod);
    if (delNodeByKey(&(pMap->arr[index]), key) == None) {
        printf("\nNot found! Cannot del\n");
        return None;
    }
    pMap->size--;
    return Success;
}

void printEntry(Entry entry) {
    if (entry.isEmpty) {
        printf("\nEntry is empty, cannot print\n");
        return;
    }
    printf("[key: %s, val: %d]", entry.key, entry.val);
}

void printMap(Map* pMap) {
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