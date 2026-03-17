## C语言函数库  

### [1 小功能函数_1](https://github.com/Flmpx/CLanguageFunctionLibrary/tree/master/Function_1/)  
#### 各函数:
    ```c
        1 可以把用户输入的区间范围修改正确的函数  
        \\ 传入一个起始值start,终点值end,其中会把区间矫正,改为0<=start<=end<allNum  
        extern int letRangeToRight(int* start,int* end,int allNum)
    ```
### [2 单向链表](https://github.com/Flmpx/CLanguageFunctionLibrary/tree/master/SList/)
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


    8 删除头节点
    int delStartNode(List* plist);


    9 删除尾节点
    int delEndNode(List* plist);


    10 通过在链表中的位置来删除节点
    extern int delNodeByPos(List* plist, int pos);


    11 打印节点的所有值(只有属性int才可以使用这个函数)
    extern void printList(List* list); 


    12 消除链表
    extern void freeList(List* plist); 

    ```
### [3 双向链表](https://github.com/Flmpx/CLanguageFunctionLibrary/tree/master/DList/) 
#### 各函数:  
    ```c
    1 初始化链表
    extern void initializeList(List* plist);


    2 通过val来找到节点,并返回节点,如果没找到,返回NULL
    extern Node* findNodeByVal(List* plist, int val);


    3 通过位置来返回节点,如果没有,返回NULL,其中0 <= pos < size
    extern Node* findNodeByPos(List* plist, int pos);


    4 在链表的尾部插入新元素
    extern int insertNodeAtEnd(List* plist, int val);


    5 在链表的头部插入新元素
    extern int insertNodeAtStart(List* plist, int val);


    6 在pos位置和pos-1位置的中间添加节点,0<=pos<=size
    // 如果pos=0,那就是在开头添加节点,如果pos=size,就是在尾部添加节点
    extern int insertNodeAtPos(List* plist, int val, int pos);


    7 删除头节点
    extern int delStartNode(List* plist);


    8 删除尾节点
    extern int delEndNode(List* plist);


    9 通过val来删除节点,如果有多个,删除第一个
    extern int delNodeByVal(List* plist, int val);


    10 删除pos位置的节点
    extern int delNodeByPos(List* plist, int pos);


    11 反转整个链表
    extern void reverseList(List* plist);


    12 打印链表的val
    extern void printList(List* plist);


    13 清除链表
    extern void freeList(List* plist);

    ```