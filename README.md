# FocX



## 设计理念
1.基于Data_S和Data_M进行泛型设计, 结构体内容如下  
```c


typedef struct Data_S {
    void* data; //存储数据的void* 指针
    void* content;  //存储描述性信息的void* 指针(比如描述二维数组的col和row)
    bool isEmpty;   //Data_S是否为空
} Data_S;



typedef struct Data_M {
    void* data; //存储数据的void* 指针
    void* content;  //存储描述性信息的void* 指针(比如描述二维数组的col和row)
    InfoOfData* dataInfo;   //由于要存储多种类型数据, Data_M自带InfoOfData类型数据指针(Data_S由于存储的是单一类型(比如一个DList_S中只存int), 那完全可以让DList_S结构体来存储InfoOfData, 以达到解释内存的目的)
    int type;   //数据标签(用于区分, 但不是主要区分标志)
    bool isEmpty;   //Data_M是否为空
} Data_M;

```

- 注: M(Multiple)为一种数据结构中可以插入任意类型, S(Single)为一种数据结构中只能插入一种类型, 但这种类型任意  
- 在List中的数据叫做MData或者SData
- 在Map中的数据叫做MVal, MKey, SVal, SKey, MEntry, SEntry
- 具体什么类型, 在括号中解释
## 文件夹结构
    ├─base.c 
    ├─base.h 
    ├─List 
    │ ├─DList 
    │ │ ├─Multiple_Data 
    │ │ │ ├─dlist_mdata.c 
    │ │ │ └─dlist_mdata.h 
    │ │ └─Single_Data 
    │ │   ├─dlist_sdata.c 
    │ │   └─dlist_sdata.h 
    │ └─SList 
    ├─Map 
    │ ├─ChainMap 
    │ │ ├─Multiple_Data 
    │ │ │ ├─chainmap_mdata.c 
    │ │ │ └─chainmap_mdata.h 
    │ │ └─Single_Data 
    │ │   ├─chainmap_sdata.c 
    │ │   └─chainmap_sdata.h 
    │ └─OAMap 
    │   ├─Multiple_Data 
    │   │ ├─oamap_mdata.c 
    │   │ └─oamap_mdata.h 
    │   └─Single_Data 
    │     ├─oamap_sdata.c 
    │     └─oamap_sdata.h 
    ├─Oper 
    │ ├─bool_oper 
    │ │ ├─_bool_oper.c 
    │ │ └─_bool_oper.h 
    │ ├─double_oper 
    │ │ ├─_double_oper.c 
    │ │ └─_double_oper.h 
    │ ├─int_oper 
    │ │ ├─_int_oper.c 
    │ │ └─_int_oper.h 
    │ └─string_oper 
    │   ├─_string_oper.c 
    │   └─_string_oper.h 
    └─README.md 

            
## 变量命名规则
    1. 变量名开头一定是本质(如:ChainMap代表使用链表来处理冲突的Map, List代表链表)
    
    2. 变量名后下划线后代表当前数据结构内部使用的是S(任意类型)还是M(单一类型)
    
    3. 数据类型下划线后代表的是其他属性, 比如位置inList(在链表里面), inChainMap(在用链表处理冲突的Map里面)
- 一个函数中的变量不需要严格遵循这个规则, 但要可阅读性强
## 变量内容
- 注: 不可见变量的命名规则一致, 不介绍  
### 基础
    
    1. InfoOfData-->用于存储的变量的操作函数和内容(全局静态变量)
    
    2. Data_S-->存储的单一类型的数据(不自带InfoOfData, 由它的上一级存储它的InfoOfData以节省内存, 比如List_S中的Data_S的InfoOfData就是存在List_S结构体中的)
    
    3. Data_M-->存储任意类型的数据(自带InfoOfData)
    4. Operation-->当前数据的操作函数, 具体见自定义数据的使用方法

### List
#### 1 DList
    
    1. DList_M-->存储任意类型数据的DList
    
    2. DList_S-->存储单一类型数据的DList


### Map
#### 1 OAMap
    
    1. OAMap_M-->存储任意类型数据的OAMap
    
    2. OAMap_S-->存储单一类型数据的OAMap  
    
    3. Entry_M_inOAMap-->在OAMap中存储任意类型数据的Entry(即包含key和val)  
    
    4. Entry_S_inOAMap-->在OAMap中存储单一类型数据的Entry(即包含key和val)

#### 2 ChainMap
    
    1. ChainMap_M-->存储任意类型数据的ChainMap
    
    2. ChainMap_S-->存储单一类型数据的ChainMap
    
    3. Entry_M_inChainMap-->在ChainMap中的存储任意类型数据的Entry(即包含key和val)
    
    4. Entry_S_inChainMap-->在ChainMap中的存储单一类型数据的Entry(即包含key和val)
    
    
    
### 其他
    1. CmpResult-->数据比较结果枚举类型, 里面右两个值  
        1. SAME-->相同 
        2. DIFFERENT-->不同
    2. InfoOfReturn-->返回信息, 有三个值 
        1. Warning-->操作失败(比如插入数据时内存分配失败, 要删除空链表中的数据) 
        2. None-->操作无效(比如上传链表中的元素, 但没找, 那么删除就无效) 
        3. Success-->操作成功操作(比如链表插入元素成功操作)
    3. Position-->位置index(比如在开放定址法处理冲突的Map中, 通过返回位置下标来找到数据)
    
    



## 函数命名规则
    1. 函数名字内的变量遵循"变量属性_变量本质"的命名方式, 比如getSValBySKeyInSChainMap表示在存储单一类型数据的ChianMap中通过单一数据类型的Key来返回SVal
    
    2. get-->得到
    
    3. Copy/Ptr-->这个数据是复制一份还是穿一个指针
    
    4. in-->在哪种数据结构中
    
    5. free-->释放
    
    6. print-->打印
    
    7. has-->有没有
    
    8. insert-->插入
    
    9. del-->删除
    
    10. reverse-->反转(一般是链表)
- 由于Node不公开, 故函数的命名直接使用Node就行了, 不公开的函数重名也没事, 但要可读性强

## 其他注意事项
    1. 如果某种类型是S(单一类型), 那它函数传入的不再是Data类型, 而是void* data和void* content