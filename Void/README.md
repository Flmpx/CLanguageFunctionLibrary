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

            

- 注: M(Multiple)为一种数据结构中可以插入任意类型, S(Single)为一种数据结构中只能插入一种类型, 但这种类型任意  
## 函数内容
#### 1 List(链表)
##### 1 SList(单一类型)
    1. void initSList(_SList* plist, InfoOfData* valInfo);
    
    2. void freeDataInSList(_SList* plist, _SData* inputData);
    
    3. _SData getPtrDataByDataInSList(_SList* plist, void* data, void* content);
    
    4. _SData getCopyDataByPosInSList(_SList* plist, int pos);
    
    5. _SData getPtrDataByPosInSList(_SList* plist, int pos);
    
    6. bool hasDataInSList(_SList* plist, void* data, void* content);
    
    7. InfoOfReturn insertDataAtEndInSList(_SList* plist, void* data, void* content);
    
    8. InfoOfReturn insertDataAtStartInSList(_SList* plist, void* data, void* content);
    
    9. InfoOfReturn insertDataAtPosInSList(_SList* plist, void* data, void* content, int pos);
    
    10. InfoOfReturn delEndNodeInSList(_SList* plist);
    
    11. InfoOfReturn delStartNodeInSList(_SList* plist);
    
    12. InfoOfReturn delNodeByDataInSList(_SList* plist, void* data, void* content);
    
    13. InfoOfReturn delNodeByPosInSList(_SList* plist, int pos);
    
    14. void reverseSList(_SList* plist);
    
    15. printSList(_SList* plist);
    
    16. freeSList(_SList* plist);


##### 2 MList(多类型)
    1. void initMList(_MList* plist);

    2. void freeDataInMList(_MData* inputData);
    
    3. _MData getPtrDataByDataInMList(_MList* plist, _MData inputData);
    
    4. _MData getCopyDataByPosInMList(_MList* plist, int pos);
    
    5. _MData getPtrDataByPosInMList(_MList* plist, int pos);
    
    6. bool hasDataInMList(_MList* plist, _MData inputData);
    
    7. InfoOfReturn insertDataAtEndInMList(_MList* plist, _MData inputData);
    
    8. InfoOfReturn insertDataAtStartInMList(_MList* plist, _MData inputData);
    
    9. InfoOfReturn insertDataAtPosInMList(_MList* plist, _MData inputData, int pos);
    
    10. InfoOfReturn delEndNodeInMList(_MList* plist);
    
    11. InfoOfReturn delStartNodeInMList(_MList* plist);
    
    12. InfoOfReturn delNodeByDataInMList(_MList* plist, _MData inputData);
    
    13. InfoOfReturn delNodeByPosInMList(_MList* plist, int pos);
    
    14. _MData stackDataInMList(void* data, void* content, int type, InfoOfData* dataInfo);
    
    15. void reverseMList(_MList* plist);
    
    16. void printMList(_MList* plist);
    
    17. void freeMList(_MList* plist);

#### 2 Map(散列表)
##### 1 SMapWithList(使用链表法处理冲突的SMap)
    1. void initSMapWithList(_SMapWithList* pMap, InfoOfData* keyInfo, InfoOfData* valInfo);
    
    2. void freeDataInSMapWithList(_SData* data, InfoOfData* infoOfKeyOrVal);
    
    3. void freeEntryInSMapWithList(_SEntryWithList* entry, _SMapWithList* pMap);
    
    4. void freeSMapWithList(_SMapWithList* pMap);
    
    5. InfoOfReturn insertKeyAndValInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent, void* 
    valdata, void* valcontent);
    
    6. _SData getCopyValByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);
    
    7. _SData getPtrValByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);
    
    8. _SEntryWithList getCopyEntryByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);
    
    9. bool hasKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);
    
    10. InfoOfReturn delEntryByKeyInSMapWithList(_SMapWithList* pMap, void* keydata, void* keycontent);
    
    11. void printDataInSMapWithList(_SData data, char* tip, InfoOfData* InfoOfKeyOrVal);
    
    12. void printEntryInSMapWithList(_SEntryWithList entry, _SMapWithList* pMap);
    
    13. void printSMapWithList(_SMapWithList* pMap);
##### 2 MMapWithList(使用链表法处理冲突的MMap)
    1. void initMMapwithList(_MMapWithList* pMap);

    2. void freeDataInMMapWithList(_MData* data);
    
    3. void freeEntryInMMapWithList(_MEntryWithList* entry);
    
    4. void freeMMapWithList(_MMapWithList* pMap);
    
    5. InfoOfReturn insertKeyAndValInMMapWithList(_MMapWithList* pMap, _MData key, _MData val);
    
    6. _MData getCopyValByKeyInMMapWithList(_MMapWithList* pMap, _MData key);
    
    7. _MData getPtrValByKeyInMMapWithList(_MMapWithList* pMap, _MData key);
    
    8. _MEntryWithList getCopyEntryByKeyInMMapWithList(_MMapWithList* pMap, _MData key);
    
    9. bool hasKeyInMMapWithList(_MMapWithList* pMap, _MData key);
    
    10. InfoOfReturn delEntryByKeyInMMapWithList(_MMapWithList* pMap, _MData key);
    
    11. _MData stackDataInMMapWithList(void* data, void* content, int type, InfoOfData* dataInfo);
    
    12. void printDataInMMapWithList(_MData data, char* tip);
    
    13. void printEntryInMMapWithList(_MEntryWithList entry);
    
    14. void printMMapWithList(_MMapWithList* pMap);
##### 3 MMapWithOA(使用开放定址法(Open Address)处理冲突的MMap)
    1. void initMMapWithOA(_MMapWithOA* pMap);
    
    2. void freeDataInMMapWithOA(_MData* data);
    
    3. void freeEntryInMMapWithOA(_MEntryWithOA* entry);
    
    4. void freeMMapWithOA(_MMapWithOA* pMap);
    
    5. InfoOfReturn insertKeyAndValInMMapWithOA(_MMapWithOA* pMap, _MData key, _MData val);
    
    6. _MData getCopyValByKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);
    
    7. _MData getPtrValByKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);
    
    8. _MEntryWithOA getCopyEntryByKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);
    
    9. bool hasKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);
    
    10. InfoOfReturn delEntryByKeyInMMapWithOA(_MMapWithOA* pMap, _MData key);
    
    11. _MData stackDataInMMapWithOA(void* data, void* content, int type, InfoOfData* dataInfo);
    
    12. void printDataInMMapWithOA(_MData data, char* tip);
    
    13. void printEntryInMMapWithOA(_MEntryWithOA entry);
    
    14. void printMMapWithOA(_MMapWithOA* pMap);
    