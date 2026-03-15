## C语言函数库  

### 1 int letRangeToRight(int* start,int* end,int allNum)  
#### 信息:  
        1 可以把用户输入的区间范围修改正确的函数  
        2 传入一个起始值start,终点值end,其中会把区间矫正,改为0<=start<=end<allNum  
### 2 链表
#### 各函数:
    ```c
    1 初始化链表
    extern void initializeList(List* plist);


    2 添加新元素到链表的尾部
    extern int addNumInEnd(List* plist, int num);


    3 添加新元素到链表的头部
    extern int addNumInStart(List* plist, int num);


    4 在pos位置和pos-1位置的中间添加节点,0<=pos<=size
    //如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
    extern int addNumInPos(List* plist, int num, int pos);


    5 找到链表中值为val的节点,如果有多个,返回第一个节点
    extern Node* findNodeByVal(List* plist, int val); 


    6 通过pos来找到节点
    extern Node* findNodeByPos(List* plist, int pos);


    7 通过值来删除节点,如果存在多个节点,删除第一个
    extern int delNodeByVal(List* plist, int val);


    8 通过在链表中的位置来删除节点
    extern int delNodeByPos(List* plist, int pos);


    9 打印节点的所有值(只有属性int才可以使用这个函数)
    extern void printList(List* list); 


    10 消除链表
    extern void freeList(List* plist); 
    ```