#ifndef C_S_LIST_H
#define C_S_LIST_H

typedef struct csnode {
    int val;
    struct csnode* next;
} CSNode;


typedef struct {
    CSNode* tail;
    int size;
} CSList;



#endif