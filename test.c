// #include <stdio.h>
// #include "Function_1/function_1.h"
// int main ()
// {

//     int start,end;
//     scanf("%d %d",&start,&end);
//     letRangeToRight(&start,&end,0,89);
//     printf("%d %d",start,end);

// }



// #include <stdio.h>
// #include <stdlib.h>
// #include "Map/Hash_Map/_hash_map.h"
// #include "Map/Hash_Map/int_oper/_int_oper.h"
// int main()
// {
//     Map map;
//     initializeMap(&map);
//     int num = 10;
//     Data key = stackData(&num, 0, &oper_Int, NULL, false);
//     int n = 200;
//     Data val = stackData(&n, 0, &oper_Int, NULL, false);
//     printf("%d\n", insertEntryInMap(&map, key, val));
//     if (hasKeyInMap(&map, key)) {
//         printf("Yes\n");
//     } else {
//         printf("No\n");
//     }
    
//     freeMap(&map);
//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// // 请根据你的实际目录结构调整头文件路径
// #include "Map/Hash_Map/_hash_map.h"
// #include "Map/Hash_Map/int_oper/_int_oper.h"

// #define TEST_SIZE 100000  // 测试数据量
// #define RANGE 1000000    // 随机数范围

// void test_hash_map() {
//     Map myMap;
//     initializeMap(&myMap);

//     printf("--- 开始暴力测试 ---\n");
//     printf("1. 正在插入 %d 条数据...\n", TEST_SIZE);
    
//     clock_t start = clock();
//     for (int i = 0; i < TEST_SIZE; i++) {
//         int k = i;
//         int v = i * 2;
        
//         // 使用 stackData 创建临时包装，注意：这两个 Data 不需要 freeData
//         // 因为它们只是容器，真正的动态内存会在 insert 内部通过 copy_Int 分配
//         Data keyData = stackData(&k, 1, &oper_Int, other_Int);
//         Data valData = stackData(&v, 1, &oper_Int, other_Int);
        
//         if (insertEntryInMap(&myMap, keyData, valData) != Success) {
//             printf("插入失败! i = %d\n", i);
//             return;
//         }
        
//         if (i % 10000 == 0) printf("已插入 %d...\n", i);
//     }
//     clock_t end = clock();
//     printf("插入完成，耗时: %.2fs，当前 Map 大小: %d, 数组长度: %d\n", 
//            (double)(end - start) / CLOCKS_PER_SEC, myMap.size, myMap.len);

//     printf("\n2. 验证数据准确性...\n");
//     int error_count = 0;
//     for (int i = 0; i < TEST_SIZE; i++) {
//         int k = i;
//         Data keyData = stackData(&k, 1, &oper_Int, other_Int);
        
//         // returnValByKey 返回的是拷贝件，必须 freeData
//         Data res = returnValByKey(&myMap, keyData);
        
//         if (res.isEmpty || *(int*)res.data != i * 2) {
//             error_count++;
//         }
//         freeData(&res); // 必须释放 returnValByKey 产生的拷贝
//     }
//     printf("验证完毕，错误数: %d\n", error_count);

//     printf("\n3. 测试覆盖更新 (Update)...\n");
//     for (int i = 0; i < 1000; i++) {
//         int k = i;
//         int v = 999999; // 更新为新值
//         Data keyData = stackData(&k, 1, &oper_Int, other_Int);
//         Data valData = stackData(&v, 1, &oper_Int, other_Int);
//         insertEntryInMap(&myMap, keyData, valData);
//     }
//     // 验证更新
//     int check_k = 500;
//     Data check_key = stackData(&check_k, 1, &oper_Int, other_Int);
//     Data check_res = returnValByKey(&myMap, check_key);
//     printf("更新验证 (Key 500): Value = %d (预期 999999)\n", *(int*)check_res.data);
//     freeData(&check_res);

//     printf("\n4. 随机删除 50%% 的数据...\n");
//     int del_count = 0;
//     for (int i = 0; i < TEST_SIZE; i += 2) {
//         int k = i;
//         Data keyData = stackData(&k, 1, &oper_Int, other_Int);
//         if (delEntryByKey(&myMap, keyData) == Success) {
//             del_count++;
//         }
//     }
//     printf("成功删除: %d 条，当前 Map 大小: %d\n", del_count, myMap.size);

//     printf("\n5. 删除后的查找测试 (探测空位与删除位)...\n");
//     error_count = 0;
//     for (int i = 0; i < TEST_SIZE; i++) {
//         int k = i;
//         Data keyData = stackData(&k, 1, &oper_Int, other_Int);
//         Data res = returnValByKey(&myMap, keyData);
        
//         if (i % 2 == 0) { // 偶数应该已被删除
//             if (!res.isEmpty) error_count++;
//         } else { // 奇数应该还在
//             if (res.isEmpty || *(int*)res.data != i * 2) error_count++;
//         }
//         freeData(&res);
//     }
//     printf("删除后验证完毕，错误数: %d\n", error_count);

//     printf("\n6. 再次插入数据 (测试占位符复用)...\n");
//     for (int i = 0; i < 1000; i++) {
//         int k = i * 100000; // 插入新 Key
//         int v = 123;
//         Data keyData = stackData(&k, 1, &oper_Int, other_Int);
//         Data valData = stackData(&v, 1, &oper_Int, other_Int);
//         insertEntryInMap(&myMap, keyData, valData);
//     }
//     printf("再次插入完成，当前 Map 大小: %d\n", myMap.size);

//     printf("\n7. 正在释放整个 Map...\n");
//     freeMap(&myMap);
//     printf("Map 已释放。\n");
//     printf("--- 测试结束 ---\n");
// }

// int main() {
//     // 建议在运行前确保你的内存足够
//     test_hash_map();
//     return 0;
// }





// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// // 请根据你的实际目录结构调整头文件路径
// #include "Map/Hash_Map/_hash_map.h"
// #include "Map/Hash_Map/int_oper/_int_oper.h"

// #define TEST_SIZE 200000  // 测试数据总量
// #define UPDATE_RANGE 1000 // 前1000条数据会被更新
// #define NEW_VALUE 999999  // 更新后的统一目标值

// void run_brute_test() {
//     Map myMap;
//     initializeMap(&myMap);

//     printf("========================================\n");
//     printf("        哈希表核心逻辑暴力测试          \n");
//     printf("========================================\n");

//     // 1. 大规模插入测试
//     printf("[1/6] 插入 %d 条原始数据...\n", TEST_SIZE);
//     clock_t start = clock();
//     for (int i = 0; i < TEST_SIZE; i++) {
//         int k = i;
//         int v = i * 2;
//         Data key = stackData(&k, 1, &oper_Int, other_Int);
//         Data val = stackData(&v, 1, &oper_Int, other_Int);
//         if (insertEntryInMap(&myMap, key, val) != Success) {
//             printf("CRITICAL ERROR: 插入 i=%d 时失败\n", i);
//             return;
//         }
//     }
//     clock_t end = clock();
//     printf(">> 完成。耗时: %.3fs | 大小: %d | 数组长度: %d\n", 
//            (double)(end - start) / CLOCKS_PER_SEC, myMap.size, myMap.len);

//     // 2. 覆盖更新测试
//     printf("[2/6] 对前 %d 条数据执行 Update 操作...\n", UPDATE_RANGE);
//     for (int i = 0; i < UPDATE_RANGE; i++) {
//         int k = i;
//         int v = NEW_VALUE;
//         Data key = stackData(&k, 1, &oper_Int, other_Int);
//         Data val = stackData(&v, 1, &oper_Int, other_Int);
//         insertEntryInMap(&myMap, key, val);
//     }
//     printf(">> 完成。前 %d 个 Key 的 Value 理论上已变为 %d\n", UPDATE_RANGE, NEW_VALUE);

//     // 3. 删除操作测试
//     printf("[3/6] 删除所有 [偶数] Key (测试 DEL_IN_MAP 标记)...\n");
//     int deleted = 0;
//     for (int i = 0; i < TEST_SIZE; i += 2) {
//         int k = i;
//         Data key = stackData(&k, 1, &oper_Int, other_Int);
//         if (delEntryByKey(&myMap, key) == Success) {
//             deleted++;
//         }
//     }
//     printf(">> 完成。成功删除 %d 条偶数 Key 数据，当前 Map 大小: %d\n", deleted, myMap.size);

//     // 4. 最终严苛验证
//     printf("[4/6] 启动全量数据逻辑正确性扫描...\n");
//     int errors = 0;
//     for (int i = 0; i < TEST_SIZE; i++) {
//         int k = i;
//         Data key = stackData(&k, 1, &oper_Int, other_Int);
//         Data res = returnValByKey(&myMap, key);

//         if (i % 2 == 0) {
//             // 情况 A: 偶数 Key 应该找不到
//             if (!res.isEmpty) {
//                 printf("Error: Key %d 应该是已删除状态，但依然能搜到！\n", i);
//                 errors++;
//             }
//         } else {
//             // 情况 B: 奇数 Key 应该存在
//             if (res.isEmpty) {
//                 printf("Error: Key %d 应该是存续状态，但搜不到！\n", i);
//                 errors++;
//             } else {
//                 // 校验值是否正确
//                 int actual_v = *(int*)res.data;
//                 int expected_v = (i < UPDATE_RANGE) ? NEW_VALUE : (i * 2);
//                 if (actual_v != expected_v) {
//                     printf("Error: Key %d 的值错误！实际:%d, 预期:%d\n", i, actual_v, expected_v);
//                     errors++;
//                 }
//             }
//         }
//         freeData(&res); // 记得释放查询结果产生的拷贝
//     }
//     printf(">> 扫描完成。发现错误数: %d\n", errors);

//     // 5. 边界探测复用测试
//     printf("[5/6] 测试在已删除的槽位重新插入数据...\n");
//     for (int i = 0; i < 100; i++) {
//         int k = i * 2; // 重新插入之前删掉的偶数
//         int v = 888;
//         Data key = stackData(&k, 1, &oper_Int, other_Int);
//         Data val = stackData(&v, 1, &oper_Int, other_Int);
//         insertEntryInMap(&myMap, key, val);
//     }
//     printf(">> 完成。当前 Map 大小: %d\n", myMap.size);

//     // 6. 内存清理
//     printf("[6/6] 正在销毁 Map 并释放所有内存...\n");
//     freeMap(&myMap);
//     printf(">> 内存已全部回收。\n");

//     if (errors == 0) {
//         printf("\n✨ 测试通过！你的哈希表逻辑非常健壮。 ✨\n");
//     } else {
//         printf("\n❌ 测试失败，请根据上方错误信息排查代码。 ❌\n");
//     }
// }

// int main() {
//     run_brute_test();
//     return 0;
// }






// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// // 请根据你的目录结构修改路径
// #include "Map/Hash_Map/_hash_map.h"
// #include "Map/Hash_Map/int_oper/_int_oper.h"

// #define TEST_SIZE 6000000     // 尝试 20 万级别
// #define UPDATE_COUNT 50000   // 更新前 5 万个数据

// // 辅助计时宏
// #define TIMER_START clock_t t_start = clock();
// #define TIMER_STOP(name) clock_t t_end = clock(); \
//     printf(">> [%s] 耗时: %.4f 秒\n", name, (double)(t_end - t_start) / CLOCKS_PER_SEC);

// void run_performance_test() {
//     Map myMap;
//     initializeMap(&myMap);

//     printf("========================================\n");
//     printf("   哈希表性能测试 (Size: %d)\n", TEST_SIZE);
//     printf("========================================\n");

//     // --- 1. 插入测试 ---
//     {
//         TIMER_START
//         for (int i = 0; i < TEST_SIZE; i++) {
//             int k = i;
//             int v = i * 2;
//             Data kd = stackData(&k, 1, &oper_Int, other_Int);
//             Data vd = stackData(&v, 1, &oper_Int, other_Int);
//             insertEntryInMap(&myMap, kd, vd);
//         }
//         TIMER_STOP("大规模插入 (含多次扩容)")
//     }

//     // --- 2. 更新测试 ---
//     {
//         TIMER_START
//         for (int i = 0; i < UPDATE_COUNT; i++) {
//             int k = i;
//             int v = 999999;
//             Data kd = stackData(&k, 1, &oper_Int, other_Int);
//             Data vd = stackData(&v, 1, &oper_Int, other_Int);
//             insertEntryInMap(&myMap, kd, vd);
//         }
//         TIMER_STOP("覆盖更新 (含旧值释放)")
//     }

//     // --- 3. 查找测试 ---
//     int errors = 0;
//     {
//         TIMER_START
//         for (int i = 0; i < TEST_SIZE; i++) {
//             int k = i;
//             Data kd = stackData(&k, 1, &oper_Int, other_Int);
//             Data res = returnValByKey(&myMap, kd);
            
//             // 简单校验
//             if (res.isEmpty) {
//                 errors++;
//             } else {
//                 int expected = (i < UPDATE_COUNT) ? 999999 : (i * 2);
//                 if (*(int*)res.data != expected) errors++;
//             }
//             freeData(&res); // 释放拷贝件
//         }
//         TIMER_STOP("全量查找 (含数据拷贝与释放)")
//     }

//     // --- 4. 删除测试 ---
//     {
//         TIMER_START
//         for (int i = 0; i < TEST_SIZE; i += 2) {
//             int k = i;
//             Data kd = stackData(&k, 1, &oper_Int, other_Int);
//             delEntryByKey(&myMap, kd);
//         }
//         TIMER_STOP("删除 50%% 数据 (线性探测打补丁)")
//     }

//     // --- 5. 清理测试 ---
//     {
//         TIMER_START
//         freeMap(&myMap);
//         TIMER_STOP("内存彻底销毁")
//     }

//     printf("========================================\n");
//     printf("测试完成。校验错误数: %d\n", errors);
//     if (errors == 0) printf("结果: 完美! (Perfect)\n");
// }

// int main() {
//     // 运行多次看平均值
//     run_performance_test();
//     return 0;
// }




// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <stdbool.h>

// // 根据你的实际路径调整
// #include "Map/Hash_Map/_hash_map.h"
// #include "Map/Hash_Map/int_oper/_int_oper.h"

// #define TEST_SIZE 80000     // 初始插入 20 万条
// #define UPDATE_SIZE 50000    // 更新前 5 万条
// #define REINSERT_SIZE 10000  // 重新插入 1 万条已删除的数据
// #define NEW_VAL_CONST 888888 // 更新后的目标值

// // 简易计时宏
// #define TIME_IT(label, code) { \
//     clock_t start = clock(); \
//     code; \
//     clock_t end = clock(); \
//     printf(">> [%s] 耗时: %.4f 秒\n", label, (double)(end - start) / CLOCKS_PER_SEC); \
// }

// int main() {
//     Map myMap;
//     initializeMap(&myMap);
//     int error_count = 0;

//     printf("================================================\n");
//     printf("开始哈希表暴力压力测试 (Size: %d)\n", TEST_SIZE);
//     printf("================================================\n");

//     // 1. 插入测试
//     TIME_IT("大规模数据插入 (含多次自动扩容)", {
//         for (int i = 0; i < TEST_SIZE; i++) {
//             int k = i;
//             int v = i * 2;
//             // 使用 stackData 包装 (注意：这里传 false 因为 int 没用到 content)
//             Data key = stackData(&k, 1, &oper_Int, NULL, false);
//             Data val = stackData(&v, 1, &oper_Int, NULL, false);
//             if (insertEntryInMap(&myMap, key, val) != Success) {
//                 printf("Error: 插入失败 i=%d\n", i);
//             }
//         }
//     });
//     printf("   当前 Size: %d, Array Len: %d\n", myMap.size, myMap.len);

//     // 2. 更新测试
//     TIME_IT("覆盖更新前 5 万条数据", {
//         for (int i = 0; i < UPDATE_SIZE; i++) {
//             int k = i;
//             int v = NEW_VAL_CONST;
//             Data key = stackData(&k, 1, &oper_Int, NULL, false);
//             Data val = stackData(&v, 1, &oper_Int, NULL, false);
//             insertEntryInMap(&myMap, key, val);
//         }
//     });

//     // 3. 逻辑验证 (查)
//     TIME_IT("全量数据逻辑校验", {
//         for (int i = 0; i < TEST_SIZE; i++) {
//             int k = i;
//             Data key = stackData(&k, 1, &oper_Int, NULL, false);
//             Data res = returnValByKey(&myMap, key);
            
//             if (res.isEmpty) {
//                 error_count++;
//             } else {
//                 int actual = *(int*)res.data;
//                 int expected = (i < UPDATE_SIZE) ? NEW_VAL_CONST : (i * 2);
//                 if (actual != expected) error_count++;
//             }
//             freeData(&res); // 必须释放，因为 returnValByKey 返回的是 malloc 出来的副本
//         }
//     });

//     // 4. 删除测试 (删掉所有偶数)
//     TIME_IT("删除所有偶数 Key (测试 DEL_IN_MAP 标记)", {
//         for (int i = 0; i < TEST_SIZE; i += 2) {
//             int k = i;
//             Data key = stackData(&k, 1, &oper_Int, NULL, false);
//             if (delEntryByKey(&myMap, key) != Success) {
//                 // 这里不计入 error_count，因为逻辑上只要删成功就行
//             }
//         }
//     });
//     printf("   删除后 Size: %d\n", myMap.size);

//     // 5. 删除后的生存校验
//     TIME_IT("验证删除后的数据完整性", {
//         for (int i = 0; i < TEST_SIZE; i++) {
//             int k = i;
//             Data key = stackData(&k, 1, &oper_Int, NULL, false);
//             bool exists = hasKeyInMap(&myMap, key);
//             if (i % 2 == 0 && exists) error_count++; // 偶数本该被删
//             if (i % 2 != 0 && !exists) error_count++; // 奇数本该存在
//         }
//     });

//     // 6. 重新插入测试 (测试墓碑槽位复用)
//     TIME_IT("在已删除槽位重新插入数据", {
//         for (int i = 0; i < REINSERT_SIZE; i++) {
//             int k = i * 2; // 重新插入原本被删的偶数
//             int v = 777;
//             Data key = stackData(&k, 1, &oper_Int, NULL, false);
//             Data val = stackData(&v, 1, &oper_Int, NULL, false);
//             insertEntryInMap(&myMap, key, val);
//         }
//     });

//     // 7. 销毁
//     TIME_IT("内存彻底释放", {
//         freeMap(&myMap);
//     });

//     printf("================================================\n");
//     if (error_count == 0) {
//         printf("测试结论: [完美通过] 0 错误!\n");
//     } else {
//         printf("测试结论: [失败] 发现 %d 处逻辑错误!\n", error_count);
//     }
//     printf("================================================\n");
    

//     return 0;
// }



// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// typedef void (*_printval)(void* val);
// typedef void (*_freeval)(void* val);
// typedef struct Node {
//     int type;
//     void* val;
//     struct Node* sameLevel;
//     _printval print;
//     _freeval freeval;
// } Node;
// typedef struct {
//     int size;
//     Node* head;
//     Node* tail;
// } Array;


// enum info {
//     Warning = -1,
//     None = 0,
//     Success = 1
// };


// void print_Int(void* val) {
//     printf("%d", *(int*)val);
// }
// void print_Bool(void* val) {
//     printf("%s", *(bool*)val == true ? "Ture" : "False");
// }
// void print_Ll(void* val) {
//     printf("%lld", *(long long*)val);
// }


// void print_Array(void* val) {
//     Array* arr = (Array*)val;
//     printf("[");
//     Node* p = arr->head;
//     for (int i = 0; i < arr->size; i++, p = p->sameLevel) {
//         if (i != 0) {
//             printf(",");
//         }
//         p->print(p->val);
//     }
//     printf("]");
// }


// void initialArray(Array* arr) {
//     arr->head = arr->tail = NULL;
//     arr->size = 0;
// }

// int insertValueInArray(Array* arr, void* val, int type, _printval print, _freeval freeval) {
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     if (newNode == NULL) {
//         printf("\nMemory allocation failed\n");
//         return Warning;
//     }
//     newNode->print = print;
//     newNode->freeval = freeval;
//     newNode->sameLevel = NULL;
//     newNode->type = type;
//     newNode->val = val;

//     if (arr->size) {
//         arr->tail->sameLevel = newNode;
//         arr->tail = newNode;
//     } else {
//         arr->head = arr->tail = newNode;
//     }
//     arr->size++;
//     return Success;
// }

// void free_Array(void* arr) {
//     Node* p = ((Array*)arr)->head;
//     Node* q = NULL;
//     while (p) {
//         q = p;
//         p = p->sameLevel;
//         q->freeval(q->val);
//         free(q);
//     }
//     free(arr);
// }


// int main()
// {

//     void* arr = malloc(sizeof(Array));
//     initialArray((Array*)arr);
//     void* arr_son = malloc(sizeof(Array));
//     initialArray((Array*)arr_son);
//     insertValueInArray(arr, arr_son, 0, print_Array, free_Array);
//     for (int i = 0; i < 8; i++) {
//         void* num = malloc(sizeof(int));
//         insertValueInArray(arr, num, 1, print_Int, free);
//     }
//     for (int i = 0; i < 3; i++) {
//         void* num = malloc(sizeof(int));
//         insertValueInArray(arr_son, num, 1, print_Int, free);
//     }
//     print_Array(arr);
//     free_Array(arr);
//     return 0;
// }








#include <stdio.h>
// #include "Map/Hash_Map/_hash_map.h"
// #include "Map/Hash_Map/string_oper/_string_oper.h"
// #include "Map/Hash_Map/int_oper/_int_oper.h"
// #include "Map/Hash_Map/double_oper/_double_oper.h"
#include "Map/Void_Map/Hash_Map_List/_hash_map_list.h"
#include "Map/Void_Map/Hash_Map_List/Oper/double_oper/_double_oper.h"
#include "Map/Void_Map/Hash_Map_List/Oper/int_oper/_int_oper.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include "_hash_map_list.h"
// // 假设你保留了之前的 int_oper.h
// #include "int_oper/_int_oper.h" 

#define TOTAL_DATA 50000

int main() {
    Map myMap;
    initializeMap(&myMap);

    printf("--- 开始链表版哈希表压力测试 ---\n");

    // 1. 插入大量数据
    for (int i = 0; i < TOTAL_DATA; i++) {
        int v = i * 10;
        Data k = stackData(&i, 1, &oper_Int, NULL, false);
        Data val = stackData(&v, 1, &oper_Int, NULL, false);
        insertKeyAndValInMap(&myMap, k, val);
    }
    printf("插入完成, 当前 Size: %d, 桶数: %d\n", myMap.size, myMap.len);

    // 2. 验证数据 (随机抽查)
    int errors = 0;
    for (int i = 0; i < TOTAL_DATA; i += 100) {
        Data k = stackData(&i, 1, &oper_Int, NULL, false);
        Data res = returnValByKey(&myMap, k);
        if (res.isEmpty || *(int*)res.data != i * 10) {
            errors++;
        }
        freeData(&res);
    }
    printf("抽样验证完成, 错误数: %d\n", errors);

    // 3. 删除测试 (删除前一半数据)
    for (int i = 0; i < TOTAL_DATA / 2; i++) {
        Data k = stackData(&i, 1, &oper_Int, NULL, false);
        if (delEntryByKey(&myMap, k) != Success) {
            errors++;
        }
    }
    printf("删除一半数据完成, 当前 Size: %d\n", myMap.size);

    // 4. 验证残留数据
    for (int i = TOTAL_DATA / 2; i < TOTAL_DATA; i += 100) {
        Data k = stackData(&i, 1, &oper_Int, NULL, false);
        if (!hasKeyInMap(&myMap, k)) {
            errors++;
        }
    }
    printf("残留验证完成, 错误总数: %d\n", errors);

    // 5. 内存释放
    freeMap(&myMap);
    printf("Map 已释放.\n");

    if (errors == 0) {
        printf("\n>>> [测试通过] 链表版逻辑完美无瑕! <<<\n");
    }

    return 0;
}


// int main()
// {
//     Map map;
//     initializeMap(&map);
//     double n = 0, m = 2;
//     Data key = stackData(&n, 0, &oper_Double, NULL, false);
//     Data val = stackData(&m, 0, &oper_Double, NULL, false);
//     insertKeyAndValInMap(&map, key, val);
//     insertKeyAndValInMap(&map, val, key);
//     Entry entry = returnEntryByKey(&map, key);
//     printData(key, "key");
//     printf("\n");
//     printEntry(entry);
//     printf("\n");
//     printMap(&map);
//     freeEntry(&entry);
//     freeMap(&map);

// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>

// // 根据你的项目结构调整路径
// #include "Map/Hash_Map/_hash_map.h"
// #include "Map/Hash_Map/string_oper/_string_oper.h"
// #include "Map/Hash_Map/int_oper/_int_oper.h"

// #define TEST_SIZE 100000      // 10万条字符串数据
// #define STR_LEN 20            // 随机字符串长度
// #define TIME_IT(label, code) { \
//     clock_t start = clock(); \
//     code; \
//     clock_t end = clock(); \
//     printf(">> [%s] 耗时: %.4f 秒\n", label, (double)(end - start) / CLOCKS_PER_SEC); \
// }

// // 随机字符串生成器
// void gen_random_str(char *s, const int len) {
//     static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//     for (int i = 0; i < len; ++i) {
//         s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
//     }
//     s[len] = 0;
// }

// int main() {
//     srand((unsigned int)time(NULL));
//     Map stringMap;
//     initializeMap(&stringMap);
    
//     char **key_pool = malloc(TEST_SIZE * sizeof(char*));
//     int error_count = 0;

//     printf("================================================\n");
//     printf("哈希表字符串暴力测试 (Size: %d, KeyLen: %d)\n", TEST_SIZE, STR_LEN);
//     printf("================================================\n");

//     // 1. 数据准备
//     for (int i = 0; i < TEST_SIZE; i++) {
//         key_pool[i] = malloc(STR_LEN + 1);
//         gen_random_str(key_pool[i], STR_LEN);
//     }

//     // 2. 插入测试 (String Key -> Int Value)
//     TIME_IT("字符串 Key 大规模插入", {
//         for (int i = 0; i < TEST_SIZE; i++) {
//             int val_raw = i;
//             // Key 使用 string_oper, Value 使用 int_oper
//             Data k = stackData(key_pool[i], 2, &oper_String, NULL, false);
//             Data v = stackData(&val_raw, 1, &oper_Int, NULL, false);
            
//             if (insertEntryInMap(&stringMap, k, v) != Success) {
//                 error_count++;
//             }
//         }
//     });
//     printf("   当前 Size: %d, 数组长度: %d\n", stringMap.size, stringMap.len);

//     // 3. 查找与校验
//     TIME_IT("全量字符串查找验证", {
//         for (int i = 0; i < TEST_SIZE; i++) {
//             Data k = stackData(key_pool[i], 2, &oper_String, NULL, false);
//             Data res = returnValByKey(&stringMap, k);
            
//             if (res.isEmpty) {
//                 error_count++;
//             } else {
//                 if (*(int*)res.data != i) error_count++;
//                 freeData(&res); // 记得释放 copy 出来的副本
//             }
//         }
//     });

//     // 4. 更新测试
//     TIME_IT("重复 Key 覆盖更新", {
//         for (int i = 0; i < 20000; i++) {
//             int newVal = 999999;
//             Data k = stackData(key_pool[i], 2, &oper_String, NULL, false);
//             Data v = stackData(&newVal, 1, &oper_Int, NULL, false);
//             insertEntryInMap(&stringMap, k, v);
//         }
//     });

//     // 5. 删除测试
//     TIME_IT("删除前 50%% 的字符串 Key", {
//         for (int i = 0; i < TEST_SIZE / 2; i++) {
//             Data k = stackData(key_pool[i], 2, &oper_String, NULL, false);
//             if (delEntryByKey(&stringMap, k) != Success) error_count++;
//         }
//     });

//     // 6. 最终销毁
//     TIME_IT("内存彻底销毁 (Map + KeyPool)", {
//         freeMap(&stringMap);
//         for (int i = 0; i < TEST_SIZE; i++) free(key_pool[i]);
//         free(key_pool);
//     });

//     printf("================================================\n");
//     if (error_count == 0) {
//         printf("结果: 完美! (Perfect)\n");
//     } else {
//         printf("结果: 失败, 错误数: %d\n", error_count);
//     }
//     printf("================================================\n");

//     return 0;
// }