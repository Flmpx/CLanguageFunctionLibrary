#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef void (*_printval)(void* val);
typedef void (*_freeval)(void* val);
typedef struct Node {
    int type;
    void* val;
    struct Node* sameLevel;
    _printval print;
    _freeval freeval;
} Node;
typedef struct {
    int size;
    Node* head;
    Node* tail;
} Array;


enum info {
    Warning = -1,
    None = 0,
    Success = 1
};


void print_Int(void* val) {
    printf("%d", *(int*)val);
}
void print_Bool(void* val) {
    printf("%s", *(bool*)val == true ? "True" : "False");
}
void print_Ll(void* val) {
    printf("%lld", *(long long*)val);
}


void print_Array(void* val) {
    Array* arr = (Array*)val;
    printf("[");
    Node* p = arr->head;
    for (int i = 0; i < arr->size; i++, p = p->sameLevel) {
        if (i != 0) {
            printf(",");
        }
        p->print(p->val);
    }
    printf("]");
}


void initialArray(Array* arr) {
    arr->head = arr->tail = NULL;
    arr->size = 0;
}

int insertValueInArray(Array* arr, void* val, int type, _printval print, _freeval freeval) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed\n");
        return Warning;
    }
    newNode->print = print;
    newNode->freeval = freeval;
    newNode->sameLevel = NULL;
    newNode->type = type;
    newNode->val = val;

    if (arr->size) {
        arr->tail->sameLevel = newNode;
        arr->tail = newNode;
    } else {
        arr->head = arr->tail = newNode;
    }
    arr->size++;
    return Success;
}

void free_Array(void* val) {
    Array* arr = (Array*)val;
    Node* p = arr->head;
    Node* q = NULL;
    while (p) {
        q = p;
        p = p->sameLevel;
        q->freeval(q->val);
        free(q);
    }
    initialArray(arr);
}

void free_Array_and_Self(void* val) {
    free_Array(val);
    free(val);
}



int main()
{

    Array arr;
    initialArray(&arr);
    Array* arr_son = (Array*)malloc(sizeof(Array));
    initialArray(arr_son);
    insertValueInArray(&arr, arr_son, 0, print_Array, free_Array_and_Self);
    for (int i = 0; i < 8; i++) {
        void* num = malloc(sizeof(int));
        *(int*)num = i;
        insertValueInArray(&arr, num, 1, print_Int, free);
    }
    for (int i = 0; i < 3; i++) {
        void* num = malloc(sizeof(int));
        *(int*)num = i;
        insertValueInArray(arr_son, num, 1, print_Int, free);
    }
    print_Array(&arr);
    free_Array(&arr);
    return 0;
}