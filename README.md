# Void
- 注: M(Multiple)为一种数据结构中可以插入任意类型, S(Single)为一种数据结构中只能插入一种类型, 但这种类型任意  
- 在List中的数据叫做MData或者SData
- 在Map中的数据叫做MVal, MKey, SVal, SKey, MEntry, SEntry
- 具体什么类型, 在括号中解释
## 文件夹结构
    Void/
    ├── List/
    │   ├── Multiple_Void_List/
    │   │   ├── _multiple_void_list.h
    │   │   └── _multiple_void_list.c
    │   └── Single_Void_List/
    │       ├── _single_void_list.h
    │       └── _single_void_list.c
    ├── Map/
    │   ├── Multiple_Void_Map/
    │   │   ├── Hash_Map_List/
    │   │   │   ├── _multiple_void_map_list.h
    │   │   │   └── _multiple_void_map_list.c
    │   │   └── Hash_Map_OA/
    │   │       ├── _multiple_void_map_oa.h
    │   │       └── _multiple_void_map_oa.c
    │   └── Single_Void_Map/
    │       ├── Hash_Map_List/
    │       │   ├── _single_void_map_list.h
    │       │   └── _single_void_map_list.c
    │       └── Hash_Map_OA/
    │           ├── _single_void_map_oa.h
    │           └── _single_void_map_oa.c
    ├── Oper/
    │   ├── bool_oper/
    │   │   ├── _bool_oper.h
    │   │   └── _bool_oper.c
    │   ├── double_oper/
    │   │   ├── _double_oper.h
    │   │   └── _double_oper.c
    │   ├── int_oper/
    │   │   ├── _int_oper.h
    │   │   └── _int_oper.c
    │   └── string_oper/
    │       ├── _string_oper.h
    │       └── _string_oper.c
    ├── _void_base.h
    └── README.md

            
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
    
    1. List_M-->存储任意类型数据的List
    
    2. List_S-->存储单一类型数据的List


### Map
    1. ChainMap_M-->存储任意类型数据的ChainMap
    
    2. Entry_M_inChainMap-->在ChainMap中的存储任意类型数据的Entry(即包含key和val)
    
    3. OAMap_M-->存储任意类型数据的OAMap
    
    4. Entry_M_inOAMap-->在OAMap中存储任意类型数据的Entry(即包含key和val)
    
    5. ChainMap_S-->存储单一类型数据的ChainMap
    
    6. Entry_S_inChainMap-->在ChainMap中的存储单一类型数据的Entry(即包含key和val)
    
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

## 函数内容
- 注: 不可见函数的命名规则一致, 不展示
#### 1 List(链表)
##### 1 List_S(单一类型)
    1. void initSList(List_S* plist, InfoOfData* valInfo);
    
    2. void freeSDataInSList(List_S* plist, Data_S* inputData);
    
    3. Data_S getPtrSDataBySDataInSList(List_S* plist, void* data, void* content);
    
    4. Data_S getCopySDataByPosInSList(List_S* plist, int pos);
    
    5. Data_S getPtrSDataByPosInSList(List_S* plist, int pos);
    
    6. bool hasSDataInSList(List_S* plist, void* data, void* content);
    
    7. InfoOfReturn insertSDataAtEndInSList(List_S* plist, void* data, void* content);
    
    8. InfoOfReturn insertSDataAtStartInSList(List_S* plist, void* data, void* content);
    
    9. InfoOfReturn insertSDataAtPosInSList(List_S* plist, void* data, void* content, 
    int pos);
    
    10. InfoOfReturn delEndNodeInSList(List_S* plist);
    
    11. InfoOfReturn delStartNodeInSList(List_S* plist);
    
    12. InfoOfReturn delNodeBySDataInSList(List_S* plist, void* data, void* content);
    
    13. InfoOfReturn delNodeByPosInSList(List_S* plist, int pos);
    
    14. void reverseSList(List_S* plist);
    
    15. void printSList(List_S* plist);
    
    16. void freeSList(List_S* plist);


##### 2 List_M(多类型)
    1. void initMList(List_M* plist);
    
    2. void freeMDataInMList(Data_M* inputData);
    
    3. Data_M getPtrMDataByMDataInMList(List_M* plist, Data_M inputData);
    
    4. Data_M getCopyMDataByPosInMList(List_M* plist, int pos);
    
    5. Data_M getPtrMDataByPosInMList(List_M* plist, int pos);
    
    6. bool hasMDataInMList(List_M* plist, Data_M inputData);
    
    7. InfoOfReturn insertMDataAtEndInMList(List_M* plist, Data_M inputData);
    
    8. InfoOfReturn insertMDataAtStartInMList(List_M* plist, Data_M inputData);
    
    9. InfoOfReturn insertMDataAtPosInMList(List_M* plist, Data_M inputData, int pos);
    
    10. InfoOfReturn delEndNodeInMList(List_M* plist);
    
    11. InfoOfReturn delStartNodeInMList(List_M* plist);
    
    12. InfoOfReturn delNodeByMDataInMList(List_M* plist, Data_M inputData);
    
    13. InfoOfReturn delNodeByPosInMList(List_M* plist, int pos);
    
    14. Data_M stackMDataInMList(void* data, void* content, int type, InfoOfData* dataInfo);
    
    15. void reverseMList(List_M* plist);
    
    16. void printMList(List_M* plist);
    
    17. void freeMList(List_M* plist);

#### 2 Map(散列表)
##### 1 ChainMap_S(使用链表法处理冲突的SMap)
    1. void initSChainMap(ChainMap_S* pMap, InfoOfData* keyInfo, InfoOfData* valInfo);
    
    2. void freeSKeyInSChainMap(ChainMap_S* pMap, Data_S* keyData);

    3. void freeSValInSChainMap(ChainMap_S* pMap, Data_S* valData);
    
    4. void freeSEntryInSChianMap(Entry_S_inChainMap* entry, ChainMap_S* pMap);
    
    5. void freeSChainMap(ChainMap_S* pMap);
    
    6. InfoOfReturn insertSKeyAndSValInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent, void* 
    valdata, void* valcontent);
    
    7. Data_S getCopySValBySKeyInSChianMap(ChainMap_S* pMap, void* keydata, void* keycontent);
    
    8. Data_S getPtrSValBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent);
    
    9. Entry_S_inChainMap getCopySEntryBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent);
    
    10. bool hasSKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent);
    
    11. InfoOfReturn delSEntryBySKeyInSChainMap(ChainMap_S* pMap, void* keydata, void* keycontent);
    
    12. void printSDataInSChainMap(Data_S data, char* tip, InfoOfData* InfoOfKeyOrVal);
    
    13. void printSEntryInSChainMap(Entry_S_inChainMap entry, ChainMap_S* pMap);
    
    14. void printSChainMap(ChainMap_S* pMap);
##### 2 ChainMap_M(使用链表法处理冲突的MMap)
    1. void initMChainMap(ChainMap_M* pMap);
    
    2. void freeMKeyInMChainMap(Data_M* inputData);

    3. void freeMValInMChainMap(Data_M* inputData);
    
    4. void freeMEntryInMChainMap(Entry_M_inChainMap* entry);
    
    5. void freeMChainMap(ChainMap_M* pMap);
    
    6. InfoOfReturn insertMKeyAndMValInMChainMap(ChainMap_M* pMap, Data_M key, Data_M val);
    
    7. Data_M getCopyMValByMKeyInMChainMap(ChainMap_M* pMap, Data_M key);
    
    8. Data_M getPtrMValByMKeyInMChainMap(ChainMap_M* pMap, Data_M key);
    
    9. Entry_M_inChainMap getCopyMEntryByMKeyInMChainMap(ChainMap_M* pMap, Data_M key);
    
    10. bool hasMKeyInMChainMap(ChainMap_M* pMap, Data_M key);
    
    11. InfoOfReturn delMEntryByMKeyInMChainMap(ChainMap_M* pMap, Data_M key);
    
    12. Data_M stackMDataInMChainMap(void* data, void* content, int type, InfoOfData* dataInfo);
    
    13. void printMDataInMChainMap(Data_M data, char* tip);
    
    14. void printMEntryInMChainMap(Entry_M_inChainMap entry);
    
    15. void printMChainMap(ChainMap_M* pMap);
##### 3 OAMap_M(使用开放定址法(Open Address)处理冲突的MMap)

    1. void initMOAMap(OAMap_M* pMap);
    
    2. void freeMKeyInMOAMap(Data_M* inputData);

    3. void freeMValInMOAMap(Data_M* inputData);
    
    4. void freeMEntryInMOAMap(Entry_M_inOAMap* entry);
    
    5. void freeMOAMap(OAMap_M* pMap);
    
    6. InfoOfReturn insertMKeyAndMValInMOAMap(OAMap_M* pMap, Data_M key, Data_M val);
    
    7. Data_M getCopyMValByMKeyInMOAMap(OAMap_M* pMap, Data_M key);
    
    8. Data_M getPtrMValByMKeyInMOAMap(OAMap_M* pMap, Data_M key);
    
    8. Entry_M_inOAMap getCopyMEntryByKeyInMOAMap(OAMap_M* pMap, Data_M key);
    
    10. bool hasKeyInMOAMap(OAMap_M* pMap, Data_M key);
    
    11. InfoOfReturn delMEntryByMKeyInMOAMap(OAMap_M* pMap, Data_M key);
    
    12. Data_M stackMDataInMOAMap(void* data, void* content, int type, InfoOfData* dataInfo);
    
    13. void printMDataInMOAMap(Data_M data, char* tip);
    
    14. void printMEntryInMOAMap(Entry_M_inOAMap entry);
    
    15. void printMOAMap(OAMap_M* pMap);

## 其他注意事项
    1. 如果某种类型是S(单一类型), 那它函数传入的不再是Data类型, 而是void* data和void* content