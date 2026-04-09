#ifndef C_S_LIST_H
#define C_S_LIST_H
#include <stdbool.h>

typedef struct csnode {
    int val;
    struct csnode* next;
} CSNode;


typedef struct {
    CSNode* tail;
    int size;
} CSList;

//判断链表是否为空
bool isEmptyCSList(CSList* plist);



void initializeCSList(CSList* plist);



int insertValAtEndInCSList(CSList* plist, int val);



int insertValAtStartInCSList(CSList* plist, int val);


int insertValAtPosInCSList(CSList* plist, int val, int pos);



CSNode* findNodeByValInCSList(CSList* plist, int val);



CSNode* findNodeByPosInCSList(CSList* plist, int pos);



int delStartNodeInCSList(CSList* plist);



int delEndNodeInCSList(CSList* plist);



int delNodeByValInCSList(CSList* plist, int val);



int delNodeByPosInCSList(CSList* plist, int pos);



void printCSListFromStart(CSList* plist);



void printCSListFromPos(CSList* plist, int pos);



void freeCSList(CSList* plist);

#endif