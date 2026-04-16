#ifndef _MAP_STRING_INT_H
#define _MAP_STRING_INT_H
#define NOT_FOUND -1
#define DIFFERENT -1
#define SAME 0
typedef unsigned long long ull;

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    char* val;
    int key;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} List;

typedef struct Map {
    List* arr;
    int size;
    int len;
    int mod;
} Map;


#endif