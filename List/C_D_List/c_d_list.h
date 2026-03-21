#ifndef C_D_LIST_H
#define C_D_LIST_H

typedef struct cdnode {
    struct cdnode* prev;
    int val;
    struct cdnode* next;
} CDNode;

typedef struct {
    CDNode* head;
    int size;
} CDList;



#endif



