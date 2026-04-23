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








// #include <stdio.h>
// // #include "Map/Hash_Map/_hash_map.h"
// // #include "Map/Hash_Map/string_oper/_string_oper.h"
// // #include "Map/Hash_Map/int_oper/_int_oper.h"
// // #include "Map/Hash_Map/double_oper/_double_oper.h"
// #include "Map/Void_Map/Hash_Map_List/_hash_map_list.h"
// #include "Map/Void_Map/Hash_Map_List/Oper/double_oper/_double_oper.h"
// #include "Map/Void_Map/Hash_Map_List/Oper/int_oper/_int_oper.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <windows.h>
// // #include "_hash_map_list.h"
// // // 假设你保留了之前的 int_oper.h
// // #include "int_oper/_int_oper.h" 

// #define TOTAL_DATA 100000

// int main() {
//     Map myMap;
//     initializeMap(&myMap);

//     printf("--- 开始链表版哈希表压力测试 ---\n");

//     // 1. 插入大量数据
//     for (int i = 0; i < TOTAL_DATA; i++) {
//         int v = i * 10;
//         Data k = stackData(&i, 1, &oper_Int, NULL, false);
//         Data val = stackData(&v, 1, &oper_Int, NULL, false);
//         insertKeyAndValInMap(&myMap, k, val);
//     }
//     printf("插入完成, 当前 Size: %d, 桶数: %d\n", myMap.size, myMap.len);

//     // 2. 验证数据 (随机抽查)
//     int errors = 0;
//     for (int i = 0; i < TOTAL_DATA; i += 100) {
//         Data k = stackData(&i, 1, &oper_Int, NULL, false);
//         Data res = returnValByKey(&myMap, k);
//         if (res.isEmpty || *(int*)res.data != i * 10) {
//             errors++;
//         }
//         freeData(&res);
//     }
//     printf("抽样验证完成, 错误数: %d\n", errors);

//     // 3. 删除测试 (删除前一半数据)
//     for (int i = 0; i < TOTAL_DATA / 2; i++) {
//         Data k = stackData(&i, 1, &oper_Int, NULL, false);
//         if (delEntryByKey(&myMap, k) != Success) {
//             errors++;
//         }
//     }
//     printf("删除一半数据完成, 当前 Size: %d\n", myMap.size);

//     // 4. 验证残留数据
//     for (int i = TOTAL_DATA / 2; i < TOTAL_DATA; i += 100) {
//         Data k = stackData(&i, 1, &oper_Int, NULL, false);
//         if (!hasKeyInMap(&myMap, k)) {
//             errors++;
//         }
//     }
//     printf("残留验证完成, 错误总数: %d\n", errors);

    
//     // 5. 内存释放
//     freeMap(&myMap);
//     printf("Map 已释放.\n");

//     if (errors == 0) {
//         printf("\n>>> [测试通过] 链表版逻辑完美无瑕! <<<\n");
//     }

//     return 0;
// }


// #include <stdio.h>
// #include "Map/Void_Map/Hash_Map_List/_hash_map_list.h"
// #include "Map/Void_Map/Hash_Map_List/Oper/double_oper/_double_oper.h"
// #include "Map/Void_Map/Hash_Map_List/Oper/int_oper/_int_oper.h"
// #include "Map/Void_Map/Hash_Map_List/Oper/bool_oper/_bool_oper.h"

// int main()
// {
//     Map map;
//     initializeMap(&map);
//     bool n = false, m = true;
//     Data key = stackData(&n, 0, &oper_Bool, NULL, false);
//     Data val = stackData(&m, 0, &oper_Bool, NULL, false);
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




// #include <stdio.h>
// #include "Map/_map_string_int/_map_string_int.h"



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <windows.h>






// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
// #include <windows.h> // 如果是在 Linux 下请注释掉这行并删掉 Sleep
// #include "Map/_map_string_int/_map_string_int.h"

// #define TEST_COUNT 500000  // 50 万测试数据
// #define STR_LEN 9          // 字符串长度

// // 简单的计时函数
// double get_time_diff(clock_t start, clock_t end) {
//     return (double)(end - start) / CLOCKS_PER_SEC;
// }

// // 随机字符串生成
// void rand_string(char *str, size_t size) {
//     static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//     for (size_t n = 0; n < size; n++) {
//         str[n] = charset[rand() % (sizeof(charset) - 1)];
//     }
//     str[size] = '\0';
// }

// int main() {
//     srand((unsigned int)time(NULL));
//     Map myMap;
//     initializeMap(&myMap);

//     // --- 关键修改：使用堆内存分配 ---
//     // 分配一个 50万 * 10字节 的大块内存
//     char (*keys)[STR_LEN + 1] = malloc(sizeof(char[STR_LEN + 1]) * TEST_COUNT);
//     if (keys == NULL) {
//         printf("内存分配失败，请尝试减小 TEST_COUNT\n");
//         return -1;
//     }

//     printf("================================================\n");
//     printf("String-Int Map 50万级 堆内存暴力测试\n");
//     printf("================================================\n");

//     // 1. 数据准备
//     for (int i = 0; i < TEST_COUNT; i++) {
//         rand_string(keys[i], STR_LEN);
//     }

//     // 2. 插入测试
//     printf(">> 正在执行插入...\n");
//     clock_t start = clock();
//     for (int i = 0; i < TEST_COUNT; i++) {
//         insertKeyAndValInMap(&myMap, keys[i], i);
//     }
//     clock_t end = clock();
//     printf("   [插入耗时]: %.4f 秒\n", get_time_diff(start, end));
//     printf("   [Map状态]: Size = %d, Buckets = %d\n", myMap.size, myMap.len);

//     // 3. 更新测试
//     printf(">> 正在执行覆盖更新 (前 10万条)...\n");
//     start = clock();
//     for (int i = 0; i < 100000; i++) {
//         insertKeyAndValInMap(&myMap, keys[i], 999999);
//     }
//     end = clock();
//     printf("   [更新耗时]: %.4f 秒\n", get_time_diff(start, end));

//     // 4. 查找验证
//     printf(">> 正在执行全量查找验证...\n");
//     int error_cnt = 0;
//     start = clock();
//     for (int i = 0; i < TEST_COUNT; i++) {
//         int val = returnValByKey(&myMap, keys[i]);
//         if (i < 100000) {
//             if (val != 999999) error_cnt++;
//         } else {
//             if (val != i) error_cnt++;
//         }
//     }
//     end = clock();
//     printf("   [查找耗时]: %.4f 秒\n", get_time_diff(start, end));
//     printf("   [错误计数]: %d\n", error_cnt);

//     // 5. 删除测试
//     printf(">> 正在删除一半的数据...\n");
//     start = clock();
//     for (int i = 0; i < TEST_COUNT / 2; i++) {
//         delEntryByKey(&myMap, keys[i]);
//     }
//     end = clock();
//     printf("   [删除耗时]: %.4f 秒\n", get_time_diff(start, end));
//     printf("   [剩余 Size]: %d\n", myMap.size);

//     // 6. 内存清理
//     printf(">> 正在清理内存...\n");
//     start = clock();
//     freeMap(&myMap);
//     free(keys); // 释放堆内存
//     end = clock();
//     printf("   [清理耗时]: %.4f 秒\n", get_time_diff(start, end));

//     printf("================================================\n");
//     if (error_cnt == 0) {
//         printf("测试结论: [完美通过]\n");
//     } else {
//         printf("测试结论: [失败] 发现 %d 处错误\n", error_cnt);
//     }
//     printf("================================================\n");

//     return 0;
// }






// #define TEST_COUNT 5000000

// // 生成随机字符串
// void rand_string(char *str, size_t size) {
//     const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK";
//     for (size_t n = 0; n < size; n++) {
//         int key = rand() % (int) (sizeof charset - 1);
//         str[n] = charset[key];
//     }
//     str[size] = '\0';
// }

// int main() {
//     Map myMap;
//     initializeMap(&myMap);
    
//     printf("--- String-Int Map 专用压力测试 ---\n");

//     // 1. 批量插入
//     // char keys[TEST_COUNT][10];
//     char (*keys)[10] = malloc(sizeof(char[10]) * TEST_COUNT);
//     for (int i = 0; i < TEST_COUNT; i++) {
//         rand_string(keys[i], 9);
//         insertKeyAndValInMap(&myMap, keys[i], i);
//     }
//     printf("插入 %d 条数据完成，Size: %d, Buckets: %d\n", TEST_COUNT, myMap.size, myMap.len);
//     Sleep(10000);
//     // 2. 更新测试
//     printf("执行更新操作...\n");
//     for (int i = 0; i < 1000; i++) {
//         insertKeyAndValInMap(&myMap, keys[i], 88888); 
//     }

//     // 3. 查找与逻辑验证
//     int error_cnt = 0;
//     for (int i = 0; i < TEST_COUNT; i++) {
//         int val = returnValByKey(&myMap, keys[i]);
//         if (i < 1000) {
//             if (val != 88888) error_cnt++;
//         } else {
//             if (val != i) error_cnt++;
//         }
//     }
//     printf("查找验证完成，错误数: %d\n", error_cnt);

//     // 4. 删除验证
//     printf("删除测试中...\n");
//     for (int i = 0; i < TEST_COUNT / 2; i++) {
//         delEntryByKey(&myMap, keys[i]);
//     }
//     printf("剩余 Size: %d\n", myMap.size);

//     // 5. 打印一小部分看看
//     printf("随机抽看部分 Map 内容:\n");
//     // 这里如果 Map 太大不要全打，可以用你的 printMap 观察一小下
//     // printMap(&myMap); 

//     // 6. 清理
//     freeMap(&myMap);
//     printf("内存清理完成。\n");

//     if (error_cnt == 0) {
//         printf("\n>>> [结论] String-Int 版本运行完美！ <<<\n");
//     }
//     free(keys);
//     return 0;
// }

// int main()
// {
//     Map map;
//     initializeMap(&map);
//     insertKeyAndValInMap(&map, "dddd", 23);
//     insertKeyAndValInMap(&map, "ddd", 111);
//     printMap(&map);
//     printf("\n");
//     if (hasKeyInMap(&map, "c")) printf("Yes\n");
//     else printf("No\n");
//     if (hasKeyInMap(&map, "ddddd")) printf("Yes\n");
//     else printf("No\n");

//     freeMap(&map);
//     return 0;
// }

// #include <windows.h>
// #include <stdio.h>
// #include "Map/Void_Map/_hash_map_list.h"
// #include "Map\Void_Map\Oper\string_oper\_string_oper.h"
// #include "Map\Void_Map\Oper\int_oper\_int_oper.h"
// #include "Map\Void_Map\Oper\bool_oper\_bool_oper.c"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
// #include <stdbool.h>

// // 包含你的头文件，路径请根据你的实际目录修改
// // #include "void_map.h" 
// // #include "_string_oper.h"
// // #include "_int_oper.h"

// // ================= 配置区 =================
// #define TEST_COUNT 5000000    // 插入的总条数，可以自由修改
// #define KEY_LEN 12           // 随机字符串Key的长度
// // ==========================================

// // 导入你在 _string_oper.c 和 _int_oper.c 中定义的 Info 结构体
// // 注意：如果你的 .c 文件里没有 extern 这些 Info，请在对应 .h 里声明一下
// extern InfoOfData Info_String; 
// extern InfoOfData Info_Int;

// // 计时辅助函数
// double get_seconds(clock_t start, clock_t end) {
//     return (double)(end - start) / CLOCKS_PER_SEC;
// }

// // 随机字符串生成器
// void generate_rand_string(char *str, int len) {
//     static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//     for (int i = 0; i < len; i++) {
//         str[i] = charset[rand() % (sizeof(charset) - 1)];
//     }
//     str[len] = '\0';
// }

// int main() {
//     srand((unsigned int)time(NULL));
    
//     Map myMap;
//     // 1. 初始化 Map：传入字符串作为 Key 的策略，整数作为 Value 的策略
//     initializeMap(&myMap, Info_String, Info_Int);

//     printf("================================================\n");
//     printf("开始 void_map 压力测试 [数据量: %d]\n", TEST_COUNT);
//     printf("Key类型: String, Value类型: Int\n");
//     printf("================================================\n");

//     // 2. 准备数据：在堆上分配 Key 数组，避免栈溢出
//     printf(">> 正在生成随机数据...\n");
//     char (*keys)[KEY_LEN + 1] = malloc(sizeof(char[KEY_LEN + 1]) * TEST_COUNT);
//     if (!keys) {
//         printf("内存分配失败！\n");
//         return -1;
//     }
//     for (int i = 0; i < TEST_COUNT; i++) {
//         generate_rand_string(keys[i], KEY_LEN);
//     }

//     // 3. 插入测试
//     printf(">> 正在执行插入...\n");
//     clock_t start = clock();
//     for (int i = 0; i < TEST_COUNT; i++) {
//         // 因为是 void_map，直接传指针。content 传 NULL。
//         insertKeyAndValInMap(&myMap, keys[i], NULL, &i, NULL);
//     }
//     clock_t end = clock();
//     printf("   [插入耗时]: %.4f 秒 (Size: %d, Buckets: %d)\n", 
//            get_seconds(start, end), myMap.size, myMap.len);

//     // 4. 查找验证
//     printf(">> 正在执行全量查找验证...\n");
//     int error_cnt = 0;
//     start = clock();
//     for (int i = 0; i < TEST_COUNT; i++) {
//         Data res = returnValByKey(&myMap, keys[i], NULL);
//         if (res.isEmpty) {
//             error_cnt++;
//         } else {
//             // 获取返回的 int 指针并比对
//             int val = *(int*)res.data;
//             if (val != i) error_cnt++;
            
//             // 重要：根据你的 returnValByKey 注释，返回的 Data 是复制出来的，需要释放
//             // 如果你的实现里 returnValByKey 不产生新 malloc，则不需要下面这行
//             // free(res.data); 
//         }
//     }
//     end = clock();
//     printf("   [查找耗时]: %.4f 秒\n", get_seconds(start, end));
//     printf("   [错误计数]: %d\n", error_cnt);

//     // 5. 更新测试 (覆盖前 1/10 的数据)
//     printf(">> 正在更新部分数据...\n");
//     int newVal = 888888;
//     for (int i = 0; i < TEST_COUNT / 10; i++) {
//         insertKeyAndValInMap(&myMap, keys[i], NULL, &newVal, NULL);
//     }
//     printf("   [更新完成] 检查第一个元素: %d (预期: 888888)\n", 
//             *(int*)returnValByKey(&myMap, keys[0], NULL).data);

//     Sleep(5000);
//     // 6. 删除测试
//     printf(">> 正在删除一半的数据...\n");
//     start = clock();
//     for (int i = 0; i < TEST_COUNT / 2; i++) {
//         delEntryByKey(&myMap, keys[i], NULL);
//     }
//     end = clock();
//     printf("   [删除耗时]: %.4f 秒, 剩余 Size: %d\n", get_seconds(start, end), myMap.size);

//     // 7. 清理
//     Sleep(5000);
//     printf(">> 正在清理内存...\n");
//     freeMap(&myMap);
//     Sleep(5000);
//     free(keys);
//     Sleep(5000);
//     printf(">> 测试结束。\n");

//     return 0;
// }


// int main()
// {

//     Map map_1, map_2;
//     initializeMap(&map_1, Info_String, Info_Int);
//     int n = 777;
//     insertKeyAndValInMap(&map_1, "ddd", NULL, &n, NULL);
//     printMap(&map_1);
//     freeMap(&map_1);
    
//     printf("\n");
    
//     initializeMap(&map_2, Info_String, Info_Bool);
//     bool a = false;
//     insertKeyAndValInMap(&map_2, "djflfjla", NULL, &a, NULL);
//     insertKeyAndValInMap(&map_2, "djflfa", NULL, &a, NULL);
//     printMap(&map_2);
//     freeMap(&map_2);
//     return 0;
// }





// #include <windows.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include "Map/Void_Map/_hash_map_list.h"
// #include "Map\Void_Map\Oper\string_oper\_string_oper.h"
// #include "Map\Void_Map\Oper\int_oper\_int_oper.h"
// #include "Map\Void_Map\Oper\bool_oper\_bool_oper.c"
// const char all[] =  "abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ!@#$^&*()_+-=?][{}";
// #define MAX 10
// void generate(char* string, int len) {
//     for (int i = 0; i < len - 1; i++) {
//         string[i] = all[rand()%(sizeof(all)-1)];
//     }
//     string[len] = '\0';
// }
// int main()
// {
//     srand(time(NULL));
//     Map map;
//     char string[MAX][101];
//     for (int i = 0; i < MAX; i++) {
//         generate(string[i], 8);
//     }
//     initializeMap(&map, Info_String, Info_Bool);
//     for (int i = 0; i < MAX; i++) {
//         bool val = (i%2 == 0);
//         insertKeyAndValInMap(&map, string[i], NULL, &val, NULL);
//     }
//     printMap(&map);
//     freeMap(&map);
//     return 0;
// }

// #include <stdio.h>
// #include "List\Void_List\void_list.h"
// #include "List\Void_List\Oper\string_oper\_string_oper.h"
// int main()
// {
//     List list;
//     initializeList(&list, Info_String);
//     insertDataAtEndInList(&list, "djfakjf", NULL);
//     insertDataAtEndInList(&list, "djfakjf", NULL);
//     printList(&list);
//     freeList(&list);

//     return 0;
// }


// #include <stdio.h>
// #include "Map\Multiple_Void_Map\Hash_Map_List\Oper\int_oper\_int_oper.h"
// #include "Map\Multiple_Void_Map\Hash_Map_List\Oper\string_oper\_string_oper.h"
// #include "Map\Multiple_Void_Map\Hash_Map_List\_hash_map_list.h"
// #include <time.h>
// #include <stdlib.h>
// const char all[] =  "abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ0123456789";
// #define MAX 10
// void generate(char* string, int len) {
//     for (int i = 0; i < len; i++) {
//         int temp = rand()%(sizeof(all)-1);
//         string[i] = all[temp];
//     }
//     string[len] = '\0';
// }
// int main()
// {
//     Map map;
//     initializeMap(&map);
//     srand(time(NULL));
//     char string[10][101];
//     for (int i = 0; i < 10; i++) {
//         generate(string[i], 10);
//     }
//     for (int i = 0; i < 10; i++) {
//         //stack只是整合数据,不会复制
//         Data key = stackData(string[i], NULL, 0, Info_String);
//         Data val = stackData(&i, NULL, 1, Info_Int);
//         //会自动复制数据
//         insertKeyAndValInMap(&map, key, val);
//     }

//     for (int i = 0; i < 10; i++) {
//         Data val = stackData(string[i], NULL, 0, Info_String);
//         Data key = stackData(&i, NULL, 1, Info_Int);
//         insertKeyAndValInMap(&map, key, val);
//     }

//     printMap(&map);
//     freeMap(&map);

//     return 0;
// }


#include <stdio.h>
#include <stdbool.h>
#include "List\Multiple_Void_List\multiple_void_list.h"
#include "List\Multiple_Void_List\Oper\bool_oper\_bool_oper.h"
#include "List\Multiple_Void_List\Oper\int_oper\_int_oper.h"
#include "List\Multiple_Void_List\Oper\string_oper\_string_oper.h"
int main()
{
    List list;
    initializeList(&list);
    
    for (int i = 0; i < 12; i++) {
        bool temp = (i&1) == 0;
        Data val = stackData(&temp, NULL, 0, Info_Bool);
        insertDataAtEndInList(&list, val);
        
    }
    for (int i = 0; i < 12; i++) {
        Data val = stackData(&i, NULL, 0, Info_Int);
        insertDataAtEndInList(&list, val);
    }
    Data val;
    int a = 10;
    val = stackData(&a, NULL, 0, Info_Int);

    returnPtrDataByData(&list, val);
    val = stackData("领主", NULL, 2, Info_String);
    insertDataAtStartInList(&list, val);
    insertDataAtPosInList(&list, val, 3);
    printList(&list);
    freeList(&list);
    return 0;
}