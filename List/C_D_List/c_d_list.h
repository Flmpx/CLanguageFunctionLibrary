#ifndef C_D_LIST_H
#define C_D_LIST_H
#include <stdbool.h>
typedef struct cdnode {
    struct cdnode* prev;
    int val;
    struct cdnode* next;
} CDNode;

typedef struct {
    CDNode* head;
    int size;
} CDList;

/// @brief 初始化链表
/// @param plist 链表指针
extern void initializeCDList(CDList* plist);


extern bool isEmptyCDList(CDList* plist);



CDNode* findNodeByValInCDList(CDList* plist, int val);



extern CDNode* findNodeByPosInCDList(CDList* plist, int pos);


int insertValAtEndInCDList(CDList* plist, int val);


int insertValAtStartInCDList(CDList* plist, int val);


int insertValAtPosInCDList(CDList* plist, int val, int pos);



extern int delStartNodeInCDList(CDList* plist);


extern int delEndNodeInCDList(CDList* plist);

int delNodeByValInCDList(CDList* plist, int val);


int delNodeByPosInCDList(CDList* plist, int pos);


void reverseCircleList(CDList* plist);


void printCDListFromStart(CDList* plist);



void printCDListFromPos(CDList* plist, int pos);



void freeCDList(CDList* plist);
#endif



