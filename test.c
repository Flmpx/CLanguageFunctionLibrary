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


// #include <stdio.h>
// #include <stdbool.h>
// #include "List\Multiple_Void_List\multiple_void_list.h"
// #include "List\Multiple_Void_List\Oper\bool_oper\_bool_oper.h"
// #include "List\Multiple_Void_List\Oper\int_oper\_int_oper.h"
// #include "List\Multiple_Void_List\Oper\string_oper\_string_oper.h"
// int main()
// {
//     List list;
//     initializeList(&list);
    
//     for (int i = 0; i < 12; i++) {
//         bool temp = (i&1) == 0;
//         Data val = stackData(&temp, NULL, 0, Info_Bool);
//         insertDataAtEndInList(&list, val);
        
//     }
//     for (int i = 0; i < 12; i++) {
//         Data val = stackData(&i, NULL, 0, Info_Int);
//         insertDataAtEndInList(&list, val);
//     }
//     Data val;
//     int a = 10;
//     val = stackData(&a, NULL, 0, Info_Int);

//     returnPtrDataByData(&list, val);
//     val = stackData("领主", NULL, 2, Info_String);
//     insertDataAtStartInList(&list, val);
//     insertDataAtPosInList(&list, val, 3);
//     printList(&list);
//     freeList(&list);
//     return 0;
// }


/*
        可以尝试把InfoOfData设置为指针,减少空间
*/

// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"
// #include <stdio.h>
// #include <stdbool.h>
// int main()
// {
//     ChainMap_S map;
//     initSChainMap(&map, &Info_String, &Info_Int);
//     int n = 10;
//     List_S list;
//     List_M list_1;
//     initSList(&list, &Info_Int);
//     initMList(&list_1);
//     for (int i = 0; i < 1000000; i++) {
//         insertDataAtEndInSList(&list, &i, NULL);
//         _MData val = stackDataInMList(&i, NULL, 0, &Info_Int);
//         insertMDataAtStartInMList(&list_1, val);
//     }
//     // printSList(&list);
//     printf("\n");
//     // printMList(&list_1);
//     printf("\n");
//     insertSKeyAndSValInSChainMap(&map, "djfal", NULL, &n, NULL);
//     printSChainMap(&map);
//     ChainMap_M map_2;
//     initMChainMap(&map_2);
//     Data_M a = stackMDataInMChainMap("ddd", NULL, 0, &Info_String);

//     Data_M b = stackMDataInMChainMap(&n, NULL, 1, &Info_Int);

//     insertMKeyAndMValInMChainMap(&map_2, a, b);
//     insertMKeyAndMValInMChainMap(&map_2, b, a);
//     printMChainMap(&map_2);
//     freeMChainMap(&map_2);
    
//     freeSChainMap(&map);
//     freeSList(&list);
//     freeMList(&list_1);
//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <windows.h>
// // 包含你提供的所有头文件
// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"

// // 计时辅助宏
// // 使用大括号 { } 开启局部作用域，避免变量名冲突
// #define TIMER_START { clock_t start = clock();
// #define TIMER_END(name) clock_t end = clock(); \
//     printf("[%s] 耗时: %.4f 秒\n", name, (double)(end - start) / CLOCKS_PER_SEC); }

// // --- 1. 测试 Single Void List (SList) ---
// void test_SList(int count) {
//     printf("=== 开始测试 SList (数量: %d) ===\n", count);
//     List_S list;
//     initSList(&list, &Info_Int);

//     TIMER_START
//     for (int i = 0; i < count; i++) {
//         insertSDataAtEndInSList(&list, &i, NULL);
//     }
//     TIMER_END("SList 尾部插入")

//     // 测试获取与修改
//     Data_S ptrData = getPtrSDataByPosInSList(&list, count / 2);
//     if (!ptrData.isEmpty) *(int*)ptrData.data = 999999;

//     TIMER_START
//     freeSList(&list);
//     printf("\n!!!!!已停止!!!!!!!!\n\n");
    
//     TIMER_END("SList 内存释放")
//     printf("\n");
// }

// // --- 2. 测试 Multiple Void List (MList) ---
// void test_MList(int count) {
//     printf("=== 开始测试 MList (异构数据测试) ===\n");
//     List_M list;
//     initMList(&list);
    
//     // 测试混合类型插入
//     int i_val = 100;
//     double d_val = 3.1415;
//     char* s_val = "Hello Multiple List";
    
//     insertMDataAtEndInMList(&list, stackMDataInMList(&i_val, NULL, 0, &Info_Int));
//     insertMDataAtEndInMList(&list, stackMDataInMList(&d_val, NULL, 1, &Info_Double));
//     insertMDataAtEndInMList(&list, stackMDataInMList(s_val, NULL, 2, &Info_String));
    
//     printf("混合列表内容: ");
//     printMList(&list);
//     printf("\n");
    
//     // 大规模释放压力测试
//     printf("正在进行 MList %d 次插入...\n", count);
//     for (int i = 0; i < count; i++) {
//         insertMDataAtStartInMList(&list, stackMDataInMList(&i, NULL, 0, &Info_Int));
//     }
    
//     TIMER_START
//     freeMList(&list);
//     printf("\n!!!!!已停止!!!!!!!!\n\n");
    
//     TIMER_END("MList 内存释放 (含异构逻辑)")
//     printf("\n");
// }

// // --- 3. 测试 Single Map (SMap With List) ---
// void test_SMap(int count) {
//     printf("=== 开始测试 SMap (String -> Int) ===\n");
//     ChainMap_S map;
//     initSChainMap(&map, &Info_String, &Info_Int);
    
//     TIMER_START
//     for (int i = 0; i < count; i++) {
//         char key[20];
//         sprintf(key, "key_%d", i);
//         insertSKeyAndSValInSChainMap(&map, key, NULL, &i, NULL);
//     }
//     TIMER_END("SMap 插入")
    
//     // 测试查询
//     Data_S res = getPtrSValBySKeyInSChainMap(&map, "key_500", NULL);
//     if (!res.isEmpty) printf("查询 key_500 结果: %d\n", *(int*)res.data);
    
//     TIMER_START
//     freeSChainMap(&map);
//     printf("\n!!!!!已停止!!!!!!!!\n\n");
    
//     TIMER_END("SMap 释放")
//     printf("\n");
// }

// // --- 4. 测试 Multiple Map (MMap With List) ---
// void test_MMap_List() {
//     printf("=== 开始测试 MMap (List Chaining) ===\n");
//     ChainMap_M mmap;
//     initMChainMap(&mmap);

//     int age = 25;
//     double score = 95.5;

//     // 存入: String -> Int
//     insertMKeyAndMValInMChainMap(&mmap, 
//         stackMDataInMChainMap("UserAge", NULL, 0, &Info_String),
//         stackMDataInMChainMap(&age, NULL, 1, &Info_Int));

//     // 存入: Int -> Double (演示异构 Key)
//     int key_id = 1001;
//     insertMKeyAndMValInMChainMap(&mmap, 
//         stackMDataInMChainMap(&key_id, NULL, 1, &Info_Int),
//         stackMDataInMChainMap(&score, NULL, 2, &Info_Double));

//     printMChainMap(&mmap);
//     printf("\n");

//     freeMChainMap(&mmap);

//     printf("\n!!!!!已停止!!!!!!!!\n\n");
    
//     printf("MMap_List 释放完成\n\n");
// }

// // --- 5. 测试 Multiple Map (MMap With OA) ---
// void test_MMap_OA(int count) {
//     printf("=== 开始测试 MMap (Open Addressing) ===\n");
//     OAMap_M mapOA;
//     initMOAMap(&mapOA);

//     TIMER_START
//     for (int i = 0; i < count; i++) {
//         // 使用整数作为 Key, 字符串作为 Val
//         char val_str[32];
//         sprintf(val_str, "value_is_%d", i);
        
//         Data_M k = stackMDataInMOAMap(&i, NULL, 0, &Info_Int);
//         Data_M v = stackMDataInMOAMap(val_str, NULL, 1, &Info_String);
        
//         insertMKeyAndMValInMOAMap(&mapOA, k, v);
//     }
//     TIMER_END("MMap_OA 插入")

//     // 删除测试
//     int target = count / 2;
//     Data_M delKey = stackMDataInMOAMap(&target, NULL, 0, &Info_Int);
//     delMEntryByMKeyInMOAMap(&mapOA, delKey);
//     printf("删除了 Key: %d\n", target);

//     TIMER_START
//     freeMOAMap(&mapOA);
//     printf("\n!!!!!已停止!!!!!!!!\n\n");
    
//     TIMER_END("MMap_OA 释放")
//     printf("\n");
// }

// int main() {
//     //设置大规模测试样本量
//     int large_scale = 5000000; // 10万条数据压力测试

//     printf("--- 开始系统综合测试 ---\n\n");

//     test_SList(large_scale);
//     test_MList(large_scale);
//     test_SMap(large_scale);
//     test_MMap_List();
//     test_MMap_OA(large_scale / 2); // OA 模式通常对装载因子敏感，测试 5万条
//     printf("\n!!!!!已停止!!!!!!!!\n\n");
    
//     printf("--- 所有测试完成 ---\n");
    
//     return 0;
// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <windows.h>
// // 包含你提供的所有头文件
// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #ifdef _WIN32
// #include <windows.h>
// #define sleep(x) Sleep((x) * 1000)
// #else
// #include <unistd.h>
// #endif

// // // 包含底层基础头文件
// // #include "Void/_void_base.h"

// // // 包含操作函数头文件 (假设路径如下)
// // #include "Oper/int_oper/_int_oper.h"
// // #include "Oper/string_oper/_string_oper.h"

// // // 包含 List 头文件
// // #include "List/Single_Void_List/_single_void_list.h"
// // #include "List/Multiple_Void_List/_multiple_void_list.h"

// // // 包含 Map 头文件
// // #include "Map/Single_Void_Map/Hash_Map_List/_single_void_map_list.h"
// // #include "Map/Multiple_Void_Map/Hash_Map_List/_multiple_void_map_list.h"
// // #include "Map/Multiple_Void_Map/Hash_Map_OA/_multiple_void_map_oa.h"

// /**
//  * 测试参数配置
//  */
// #define TEST_VOLUME 10000   // 测试数据量，可以根据需要修改此值
// #define PRINT_LIMIT 10      // 打印预览的数量限制，防止控制台刷屏

// // 外部引用的全局静态操作信息（由您的 Oper 模块提供）
// extern InfoOfData int_info;
// extern InfoOfData Info_String;

// // 计时辅助宏
// #define START_TIMER() clock_t start_t = clock()
// #define STOP_TIMER(name) \
//     clock_t end_t = clock(); \
//     printf("[计时] %s 耗时: %.3f 秒\n", name, (double)(end_t - start_t) / CLOCKS_PER_SEC)

// /**
//  * 释放并停留
//  */
// void release_and_pause(const char* name) {
//     printf("[系统] 正在释放 %s 的内存...\n", name);
//     // 这里调用具体的释放函数在各测试函数内部完成
//     printf("[系统] 释放完毕，进入 3 秒观察期（请观察任务管理器/top）...\n");
//     sleep(3);
//     printf("--------------------------------------------------\n\n");
// }

// /**
//  * 1. 测试 List_S (单一类型链表 - 整数)
//  */
// void test_SList() {
//     printf(">>> 开始测试 List_S (单一类型: int) 数据量: %d\n", TEST_VOLUME);
//     List_S list;
//     initSList(&list, &int_info);

//     START_TIMER();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         int* val = (int*)malloc(sizeof(int));
//         *val = i;
//         insertSDataAtEndInSList(&list, val, NULL);
//     }
//     STOP_TIMER("List_S 插入");

//     printf("[状态] 插入完成，准备释放...\n");
//     freeSList(&list);
//     release_and_pause("List_S");
// }

// /**
//  * 2. 测试 List_M (多类型链表 - int & string 混合)
//  */
// void test_MList() {
//     printf(">>> 开始测试 List_M (多类型混合) 数据量: %d\n", TEST_VOLUME);
//     List_M list;
//     initMList(&list);

//     START_TIMER();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         if (i % 2 == 0) {
//             int* v = malloc(sizeof(int)); *v = i;
//             Data_M dm = stackMDataInMList(v, NULL, 0, &int_info);
//             insertMDataAtEndInMList(&list, dm);
//         } else {
//             char* s = malloc(20); sprintf(s, "str_%d", i);
//             Data_M dm = stackMDataInMList(s, NULL, 1, &string_info);
//             insertMDataAtEndInMList(&list, dm);
//         }
//     }
//     STOP_TIMER("List_M 插入");

//     freeMList(&list);
//     release_and_pause("List_M");
// }

// /**
//  * 3. 测试 ChainMap_S (单类型链表哈希表: int -> string)
//  */
// void test_SChainMap() {
//     printf(">>> 开始测试 ChainMap_S (int -> string) 数据量: %d\n", TEST_VOLUME);
//     ChainMap_S map;
//     initSChainMap(&map, &int_info, &string_info);

//     START_TIMER();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         int* k = malloc(sizeof(int)); *k = i;
//         char* v = malloc(20); sprintf(v, "val_%d", i);
//         insertSKeyAndSValInSChainMap(&map, k, NULL, v, NULL);
//     }
//     STOP_TIMER("ChainMap_S 插入");

//     // 随机查询测试
//     int search_k = TEST_VOLUME / 2;
//     printf("[验证] 查询键 %d...\n", search_k);
//     Data_S res = getPtrSValBySKeyInSChainMap(&map, &search_k, NULL);
//     if (res.data != NULL) printf("[验证] 找到结果: %s\n", (char*)res.data);

//     freeSChainMap(&map);
//     release_and_pause("ChainMap_S");
// }

// /**
//  * 4. 测试 OAMap_M (多类型开放定址哈希表)
//  */
// void test_MOAMap() {
//     printf(">>> 开始测试 OAMap_M (多类型开放定址) 数据量: %d\n", TEST_VOLUME / 2); // OA通常不建议太满
//     OAMap_M map;
//     initMOAMap(&map);

//     START_TIMER();
//     for (int i = 0; i < TEST_VOLUME / 2; i++) {
//         int* k_ptr = malloc(sizeof(int)); *k_ptr = i;
//         int* v_ptr = malloc(sizeof(int)); *v_ptr = i * 10;
        
//         Data_M key = stackMDataInMOAMap(k_ptr, NULL, 0, &int_info);
//         Data_M val = stackMDataInMOAMap(v_ptr, NULL, 0, &int_info);
//         insertMKeyAndMValInMOAMap(&map, key, val);
//     }
//     STOP_TIMER("OAMap_M 插入");

//     freeMOAMap(&map);
//     release_and_pause("OAMap_M");
// }

// int main() {
//     printf("==================================================\n");
//     printf("   Void 泛型数据结构库 - 压力与内存自动化测试\n");
//     printf("==================================================\n\n");

//     test_SList();
//     test_MList();
//     test_SChainMap();
//     test_MOAMap();

//     printf("所有测试已完成。\n");
//     return 0;
// }




// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <windows.h>

// // 包含你提供的所有头文件
// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"

// /**
//  * 测试配置
//  */
// #define TEST_VOLUME 5000000  // 测试数据量，你可以随意修改这个值进行压力测试

// // 假设这些全局静态变量已经在对应的 _oper.c 中定义
// // extern InfoOfData int_info;
// // extern InfoOfData string_info;
// // extern InfoOfData double_info;

// // 计时辅助
// void print_duration(const char* label, clock_t start) {
//     clock_t end = clock();
//     double duration = (double)(end - start) / CLOCKS_PER_SEC;
//     printf("[%s] 耗时: %.4f 秒\n", label, duration);
// }

// // 释放后的缓冲观察
// void memory_pause(const char* msg) {
//     printf(">> %s 释放完成。暂停 3 秒观察内存回收情况...\n", msg);
//     Sleep(3000);
//     printf("--------------------------------------------------\n");
// }

// /**
//  * 1. 测试 List_S (单一类型: int)
//  */
// void test_SList() {
//     printf("开始测试: List_S (Single Type List - Int)\n");
//     List_S list;
//     initSList(&list, &Info_Int);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         int* data = (int*)malloc(sizeof(int));
//         *data = i;
//         insertSDataAtEndInSList(&list, data, NULL);
//     }
//     print_duration("List_S 批量插入", start);

//     freeSList(&list);
//     memory_pause("List_S");
// }

// /**
//  * 2. 测试 List_M (多类型混合)
//  */
// void test_MList() {
//     printf("开始测试: List_M (Multiple Type List - Int & String)\n");
//     List_M list;
//     initMList(&list);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         if (i % 2 == 0) {
//             int* d = malloc(sizeof(int)); *d = i;
//             insertMDataAtEndInMList(&list, stackMDataInMList(d, NULL, 1, &Info_Int));
//         } else {
//             char* s = _strdup("Multiple_Void_Test");
//             insertMDataAtEndInMList(&list, stackMDataInMList(s, NULL, 2, &Info_String));
//         }
//     }
//     print_duration("List_M 批量插入", start);

//     freeMList(&list);
//     memory_pause("List_M");
// }

// /**
//  * 3. 测试 ChainMap_S (单一类型哈希表: int -> int)
//  */
// void test_SChainMap() {
//     printf("开始测试: ChainMap_S (Single Type Map - Int to Int)\n");
//     ChainMap_S map;
//     initSChainMap(&map, &Info_Int, &Info_Int);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         int* k = malloc(sizeof(int)); *k = i;
//         int* v = malloc(sizeof(int)); *v = i * 2;
//         insertSKeyAndSValInSChainMap(&map, k, NULL, v, NULL);
//     }
//     print_duration("ChainMap_S 批量插入", start);

//     // 测试查询
//     int search_key = TEST_VOLUME / 2;
//     Data_S result = getPtrSValBySKeyInSChainMap(&map, &search_key, NULL);
//     if (result.data) {
//         printf("查询成功: Key=%d, Val=%d\n", search_key, *(int*)result.data);
//     }

//     freeSChainMap(&map);
//     memory_pause("ChainMap_S");
// }

// /**
//  * 4. 测试 ChainMap_M (多类型哈希表)
//  */
// void test_MChainMap() {
//     printf("开始测试: ChainMap_M (Multiple Type Map)\n");
//     ChainMap_M map;
//     initMChainMap(&map);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         int* k = malloc(sizeof(int)); *k = i;
//         double* v = malloc(sizeof(double)); *v = (double)i + 0.5;
        
//         Data_M key = stackMDataInMChainMap(k, NULL, 1, &Info_Int);
//         Data_M val = stackMDataInMChainMap(v, NULL, 3, &Info_Double);
//         insertMKeyAndMValInMChainMap(&map, key, val);
//     }
//     print_duration("ChainMap_M 批量插入", start);

//     freeMChainMap(&map);
//     memory_pause("ChainMap_M");
// }

// /**
//  * 5. 测试 OAMap_M (开放定址法)
//  */
// void test_MOAMap() {
//     printf("开始测试: OAMap_M (Open Address Multiple Type Map)\n");
//     OAMap_M map;
//     initMOAMap(&map);

//     // 注意：开放定址法在 TEST_VOLUME 很大且没有自动扩容时会很慢或失败
//     // 这里取一个小一点的量或者确保你的实现支持扩容
//     int oa_volume = TEST_VOLUME / 5; 

//     clock_t start = clock();
//     for (int i = 0; i < oa_volume; i++) {
//         int* k = malloc(sizeof(int)); *k = i;
//         int* v = malloc(sizeof(int)); *v = i;
//         insertMKeyAndMValInMOAMap(&map, 
//             stackMDataInMOAMap(k, NULL, 1, &Info_Int), 
//             stackMDataInMOAMap(v, NULL, 1, &Info_Int));
//     }
//     print_duration("OAMap_M 批量插入", start);

//     freeMOAMap(&map);
//     memory_pause("OAMap_M");
// }

// int main() {
//     printf("==================================================\n");
//     printf("   Void 库 自动化压力与内存测试启动\n");
//     printf("   当前单项测试规模: %d\n", TEST_VOLUME);
//     printf("==================================================\n\n");

//     test_SList();
//     test_MList();
//     test_SChainMap();
//     test_MChainMap();
//     test_MOAMap();

//     printf("所有测试完成。按回车键退出...\n");
//     getchar();
//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <windows.h>

// // 包含你提供的所有头文件
// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"

/**
 * 测试参数
 */
// #define TEST_VOLUME 10000000

// // 引用全局操作信息
// // extern InfoOfData int_info;
// // extern InfoOfData string_info;
// // extern InfoOfData double_info;

// // 计时辅助
// void print_timer(const char* msg, clock_t start) {
//     printf("[%s] 耗时: %.3f 秒\n", msg, (double)(clock() - start) / CLOCKS_PER_SEC);
// }

// // 释放并观察
// void pause_3s(const char* name) {
//     printf(">> %s 已调用 free。进入 3 秒观察期...\n", name);
//     Sleep(3000);
//     printf("--------------------------------------------------\n");
// }

// /**
//  * 1. 测试 List_S (整数)
//  * 核心：直接传局部变量地址 &i
//  */
// void test_SList() {
//     printf("开始测试 List_S (数据量: %d)\n", TEST_VOLUME);
//     List_S list;
//     initSList(&list, &Info_Int);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         // 你的库会复制数据，所以直接传 i 的地址是安全的
//         insertSDataAtEndInSList(&list, &i, NULL);
//     }
//     print_timer("List_S 插入", start);

//     freeSList(&list);
//     pause_3s("List_S");
// }

// /**
//  * 2. 测试 List_M (混合类型)
//  */
// void test_MList() {
//     printf("开始测试 List_M (数据量: %d)\n", TEST_VOLUME);
//     List_M list;
//     initMList(&list);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         if (i % 2 == 0) {
//             insertMDataAtEndInMList(&list, stackMDataInMList(&i, NULL, 0, &Info_Int));
//         } else {
//             // 传常量字符串地址，库会复制字符串内容
//             insertMDataAtEndInMList(&list, stackMDataInMList("TestString", NULL, 1, &Info_String));
//         }
//     }
//     print_timer("List_M 插入", start);

//     freeMList(&list);
//     pause_3s("List_M");
// }

// /**
//  * 3. 测试 ChainMap_S (Int -> Double)
//  */
// void test_SChainMap() {
//     printf("开始测试 ChainMap_S (数据量: %d)\n", TEST_VOLUME);
//     ChainMap_S map;
//     initSChainMap(&map, &Info_Int, &Info_Double);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         int k = i;
//         double v = i * 1.5;
//         // 关键：这里完全没有 malloc，全靠你的库内部 copy
//         insertSKeyAndSValInSChainMap(&map, &k, NULL, &v, NULL);
//     }
//     print_timer("ChainMap_S 插入", start);

//     freeSChainMap(&map);
//     pause_3s("ChainMap_S");
// }

// /**
//  * 4. 测试 ChainMap_M (混合键值对)
//  */
// void test_MChainMap() {
//     printf("开始测试 ChainMap_M (数据量: %d)\n", TEST_VOLUME);
//     ChainMap_M map;
//     initMChainMap(&map);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME; i++) {
//         int k = i;
//         char* v = "MapValue";
//         insertMKeyAndMValInMChainMap(&map, 
//             stackMDataInMChainMap(&k, NULL, 0, &Info_Int), 
//             stackMDataInMChainMap(v, NULL, 1, &Info_String));
//     }
//     print_timer("ChainMap_M 插入", start);

//     freeMChainMap(&map);
//     pause_3s("ChainMap_M");
// }

// /**
//  * 5. 测试 OAMap_M (开放定址法)
//  */
// void test_MOAMap() {
//     printf("开始测试 OAMap_M (数据量: %d)\n", TEST_VOLUME / 2);
//     OAMap_M map;
//     initMOAMap(&map);

//     clock_t start = clock();
//     for (int i = 0; i < TEST_VOLUME / 2; i++) {
//         int k = i;
//         int v = i * 10;
//         insertMKeyAndMValInMOAMap(&map, 
//             stackMDataInMOAMap(&k, NULL, 0, &Info_Int), 
//             stackMDataInMOAMap(&v, NULL, 0, &Info_Int));
//     }
//     print_timer("OAMap_M 插入", start);

//     freeMOAMap(&map);
//     pause_3s("OAMap_M");
// }

// int main() {
//     printf("================================================\n");
//     printf("   Void 库 自动化压力与内存测试 (非动态分配模式)\n");
//     printf("   测试说明：外部不使用 malloc，完全由库内部复制数据\n");
//     printf("================================================\n\n");

//     test_SList();
//     test_MList();
//     test_SChainMap();
//     test_MChainMap();
//     test_MOAMap();

//     printf("全部测试结束，请确认内存是否已完全回落至初始值。\n");
//     printf("按回车键退出程序...");
//     getchar();

//     return 0;
// }





// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <windows.h>
// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"


// #define MAX 100000

// const char all[] =  "abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ0123456789";
// void generate(char* string, int len) {
//     for (int i = 0; i < len; i++) {
//         int temp = rand()%(sizeof(all)-1);
//         string[i] = all[temp];
//     }
//     string[len] = '\0';
// }


// void testChainMap_S() {
//     ChainMap_S map;
//     initSChainMap(&map, &Info_String, &Info_Int);
//     for (int i = 0; i < MAX; i++) {
//         char string[101];
//         generate(string, 20);
//         insertSKeyAndSValInSChainMap(&map, string, NULL, &i, NULL);
//     }
//     printf("\nChainMap_S插入结束\n\n");
//     Sleep(5000);
//     freeSChainMap(&map);
//     printf("\nChainMap_S释放结束\n\n");
//     Sleep(5000);
    
// }

// void testChainMap_M() {
//     ChainMap_M map;
//     initMChainMap(&map);

//     for (int i = 0; i < MAX; i++) {
//         char string[101];
//         generate(string, 20);
//         Data_M k = stackMDataInMChainMap(string, NULL, 0, &Info_String);
//         Data_M v = stackMDataInMChainMap(&i, NULL, 1, &Info_Int);
//         insertMKeyAndMValInMChainMap(&map, k, v);
//         insertMKeyAndMValInMChainMap(&map, v, k);
//     }
    
//     printf("\nChainMap_M插入结束\n\n");
//     Sleep(5000);
//     freeMChainMap(&map);
//     printf("\nChainMap_M释放结束\n\n");
//     Sleep(5000);
// }

// void testOAMap_M() {
//     OAMap_M map;
//     initMOAMap(&map);
    
//     for (int i = 0; i < MAX; i++) {
//         char string[101];
//         generate(string, 20);
//         Data_M k = stackMDataInMOAMap(string, NULL, 0, &Info_String);
//         Data_M v = stackMDataInMOAMap(&i, NULL, 1, &Info_Int);
//         insertMKeyAndMValInMOAMap(&map, k, v);
//         insertMKeyAndMValInMOAMap(&map, v, k);
//     }
    
//     printf("\nOAMap_M插入结束\n\n");
//     Sleep(5000);
//     freeMOAMap(&map);
//     printf("\nOAMap_M释放结束\n\n");
//     Sleep(5000);

// }



// int main()
// {
//     testChainMap_M();
//     testChainMap_S();
//     testOAMap_M();


//     return 0;
// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <windows.h>

// // 包含你提供的所有头文件
// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// // #include "Void\Map\Single_Void_Map\Hash_Map_OA\_single_void_map_oa.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"

// // 引用外部提供的 InfoOfData 指针
// extern InfoOfData* Info_Int;
// extern InfoOfData* Info_Double;
// extern InfoOfData* Info_String;
// extern InfoOfData* Info_Bool;

// #define TEST_SIZE 20000  // 测试数据量

// /**
//  * 辅助函数：显示时间损耗
//  */
// void print_elapsed(const char* label, clock_t start) {
//     double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
//     printf("[%s] 耗时: %.4f 秒\n", label, duration);
// }

// int main() {
//     printf("==================================================\n");
//     printf("   OAMap_S (单一类型开放定址法) 自动化验证程序\n");
//     printf("   测试规模: %d | 模式: 深拷贝 (栈数据)\n", TEST_SIZE);
//     printf("==================================================\n\n");

//     OAMap_S map;
//     // 初始化：Key 使用 Int，Value 使用 String
//     initSOAMap(&map, Info_Int, Info_String);

//     // --- 1. 批量插入测试 ---
//     printf("1. 正在执行批量插入...\n");
//     int success_count = 0;
//     clock_t start = clock();
    
//     for (int i = 0; i < TEST_SIZE; i++) {
//         int key = i;
//         char buf[32];
//         sprintf(buf, "Value_%d", i);

//         // 直接传局部变量地址，库内部会执行 deep copy
//         if (insertSKeyAndSValInSOAMap(&map, &key, NULL, buf, NULL) == Success) {
//             success_count++;
//         }
//     }
//     print_elapsed("批量插入", start);
//     printf("成功插入数量: %d / %d\n\n", success_count, TEST_SIZE);

//     // --- 2. 插入有效性验证 (准确性检查) ---
//     printf("2. 正在验证数据准确性 (随机抽样)...\n");
//     int check_keys[] = {0, TEST_SIZE / 2, TEST_SIZE - 1};
//     for (int i = 0; i < 3; i++) {
//         int target_key = check_keys[i];
//         // 获取指针以读取数据
//         Data_S result = getPtrSValBySKeyInSOAMap(&map, &target_key, NULL);
        
//         if (!result.isEmpty) {
//             printf("  - 查找 Key[%d]: 得到 \"%s\" (校验通过)\n", target_key, (char*)result.data);
//         } else {
//             printf("  - 查找 Key[%d]: 失败 (验证未通过!)\n", target_key);
//         }
//     }
//     printf("\n");

//     // --- 3. 覆盖测试 (验证更新逻辑) ---
//     printf("3. 验证 Key 覆盖更新...\n");
//     int update_key = TEST_SIZE / 2;
//     char* new_val = "Updated_Value";
//     insertSKeyAndSValInSOAMap(&map, &update_key, NULL, new_val, NULL);
    
//     Data_S updated_res = getPtrSValBySKeyInSOAMap(&map, &update_key, NULL);
//     printf("  - 更新 Key[%d] 为 \"%s\"\n", update_key, (char*)updated_res.data);
//     printf("\n");

//     // --- 4. 删除验证 ---
//     printf("4. 验证删除功能...\n");
//     int del_key = 100;
//     if (delSEntryBySKeyInSOAMap(&map, &del_key, NULL) == Success) {
//         bool exists = hasSKeyInSOAMap(&map, &del_key, NULL);
//         printf("  - 删除 Key[%d] 成功，再次查询存在状态: %s\n", 
//                del_key, exists ? "仍存在(异常)" : "已消失(正常)");
//     }
//     printf("\n");

//     // --- 5. 内存清理与终期观察 ---
//     printf("5. 执行 freeSOAMap 释放所有深拷贝副本...\n");
//     start = clock();
//     freeSOAMap(&map);
//     print_elapsed("内存释放", start);

//     printf("\n所有验证完成。请观察任务管理器，内存应已完全回落。\n");
//     printf("按回车键退出...");
//     getchar();

//     return 0;
// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <windows.h>

// // 包含你要求的所有头文件
// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// // #include "Void\Map\Single_Void_Map\Hash_Map_OA\_single_void_map_oa.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"

// #define MAX 100000

// // 保持你提供的随机字符串生成逻辑
// const char all[] = "abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ0123456789";
// void generate(char* string, int len) {
//     for (int i = 0; i < len; i++) {
//         int temp = rand() % (sizeof(all) - 1);
//         string[i] = all[temp];
//     }
//     string[len] = '\0';
// }

// /**
//  * OAMap_S 专项测试程序
//  * 遵循深拷贝逻辑，外部不使用 malloc
//  */
// void testOAMap_S() {
//     printf("===== 开始 OAMap_S (Int -> String) 测试 =====\n");
//     OAMap_S map;
//     // 使用你提供的全局 Info 变量指针
//     initSOAMap(&map, &Info_Int, &Info_String);

//     clock_t start_time = clock();
//     int success_count = 0;

//     // 1. 压力插入测试
//     for (int i = 0; i < MAX; i++) {
//         int key = i;
//         char val_str[21];
//         generate(val_str, 20);

//         // 插入并验证返回值是否为 Success
//         if (insertSKeyAndSValInSOAMap(&map, &key, NULL, val_str, NULL) == Success) {
//             success_count++;
//         }
//     }
    
//     clock_t end_time = clock();
//     printf("插入 %d 条数据耗时: %.3f 秒\n", MAX, (double)(end_time - start_time) / CLOCKS_PER_SEC);
//     printf("成功插入数量: %d\n", success_count);

//     // 2. 随机验证数据有效性
//     printf("正在验证数据准确性...\n");
//     int test_key = MAX / 2;
//     // 使用 getPtr 获取数据指针进行校验
//     Data_S result = getPtrSValBySKeyInSOAMap(&map, &test_key, NULL);
    
//     if (!result.isEmpty) {
//         printf("验证成功: Key[%d] 对应 Value 为: %s\n", test_key, (char*)result.data);
//     } else {
//         printf("验证失败: 未找到 Key[%d]\n", test_key);
//     }

//     // 3. 删除测试
//     int del_key = 10;
//     if (delSEntryBySKeyInSOAMap(&map, &del_key, NULL) == Success) {
//         printf("删除 Key[%d] 成功\n", del_key);
//     }

//     printf("等待 5 秒观察内存占用...\n");
//     Sleep(5000);

//     // 4. 释放内存
//     freeSOAMap(&map);
//     printf("OAMap_S 释放完成，请检查内存回落情况。\n");
//     printf("==========================================\n\n");
//     Sleep(5000);
// }

// // 保持你示例中的其他测试函数结构
// void testChainMap_S() {
//     ChainMap_S map;
//     initSChainMap(&map, &Info_String, &Info_Int);
//     for (int i = 0; i < MAX; i++) {
//         char string[101];
//         generate(string, 20);
//         insertSKeyAndSValInSChainMap(&map, string, NULL, &i, NULL);
//     }
//     printf("\nChainMap_S插入结束\n\n");
//     Sleep(5000);
//     freeSChainMap(&map);
//     printf("\nChainMap_S释放结束\n\n");
//     Sleep(5000);
// }

// void testChainMap_M() {
//     ChainMap_M map;
//     initMChainMap(&map);
//     for (int i = 0; i < MAX; i++) {
//         char string[101];
//         generate(string, 20);
//         Data_M k = stackMDataInMChainMap(string, NULL, 0, &Info_String);
//         Data_M v = stackMDataInMChainMap(&i, NULL, 1, &Info_Int);
//         insertMKeyAndMValInMChainMap(&map, k, v);
//     }
//     printf("\nChainMap_M插入结束\n\n");
//     Sleep(5000);
//     freeMChainMap(&map);
//     printf("\nChainMap_M释放结束\n\n");
//     Sleep(5000);
// }

// int main() {
//     srand((unsigned int)time(NULL));
    
//     // 运行你的示例测试
//     testChainMap_M();
//     testChainMap_S();
    
//     // 运行新写的 OAMap_S 测试
//     testOAMap_S();

//     return 0;
// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>
// #include <windows.h>

// // 包含你项目的所有核心头文件
// #include "Void\List\Multiple_Void_List\_multiple_void_list.h"
// #include "Void\List\Single_Void_List\_single_void_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
// #include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
// #include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
// #include "Void\Oper\bool_oper\_bool_oper.h"
// #include "Void\Oper\double_oper\_double_oper.h"
// #include "Void\Oper\int_oper\_int_oper.h"
// #include "Void\Oper\string_oper\_string_oper.h"
// #include "Void\_void_base.h"

// #define MAX 1000000

// // 保持你提供的随机字符串生成逻辑
// const char all[] = "abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ0123456789";
// void generate(char* string, int len) {
//     for (int i = 0; i < len; i++) {
//         int temp = rand() % (sizeof(all) - 1);
//         string[i] = all[temp];
//     }
//     string[len] = '\0';
// }

// /**
//  * 针对 OAMap_M 的专项测试程序
//  */
// void testOAMap_M() {
//     OAMap_M map;
//     clock_t start, end;
//     initMOAMap(&map);

//     printf("--- OAMap_M 压力与有效性测试开始 ---\n");

//     // 1. 批量插入测试并显示时间
//     int success_count = 0;

//     start = clock();
//     for (int i = 0; i < MAX; i++) {
//         char key_buf[21];
//         generate(key_buf, 20);
        
//         // 使用 stackMData 封装数据，传入 &Info 指针
//         Data_M k = stackMDataInMOAMap(key_buf, NULL, 0, &Info_String);
//         Data_M v = stackMDataInMOAMap(&i, NULL, 1, &Info_Int);
        
//         // 验证插入是否成功 (返回值为 Success 即为 1)
//         if (insertMKeyAndMValInMOAMap(&map, k, v) == Success) {
//             success_count++;
//         }
//         if (insertMKeyAndMValInMOAMap(&map, v, k) == Success) {
//             success_count++;
//         }

//     }

//     // 插入一个固定键值对用于最后的精确有效性检验
//     char test_key[] = "Verify_Key_999";
//     int test_val = 88888;
//     Data_M vk = stackMDataInMOAMap(test_key, NULL, 0, &Info_String);
//     Data_M vv = stackMDataInMOAMap(&test_val, NULL, 1, &Info_Int);
//     insertMKeyAndMValInMOAMap(&map, vk, vv);

//     end = clock();
//     printf("批量插入 %d 条数据完成。\n", MAX);
//     printf("成功计数: %d | 耗时: %.3f 秒\n", success_count, (double)(end - start) / CLOCKS_PER_SEC);

//     // 2. 检验插入是否有效 (数据一致性检查)
//     printf("正在检验数据有效性...\n");
//     // 通过 getPtr 获取数据指针
//     Data_M result = getPtrMValByMKeyInMOAMap(&map, vk);
    
//     if (!result.isEmpty) {
//         int val = *(int*)result.data;
//         if (val == test_val) {
//             printf("[成功] 数据验证通过: Key='%s' -> Val=%d\n", test_key, val);
//         } else {
//             printf("[失败] 数据损坏: 期望 %d, 实际得到 %d\n", test_val, val);
//         }
//     } else {
//         printf("[失败] 找不到预设的验证 Key！\n");
//     }

//     // 3. 内存释放测试
//     printf("等待 5 秒后释放内存...\n");
//     Sleep(5000);
    
//     start = clock();
//     freeMOAMap(&map);
//     end = clock();
    
//     printf("OAMap_M 释放完成，耗时: %.3f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);
//     printf("--------------------------------------\n\n");
//     Sleep(5000);
// }

// int main() {
//     srand((unsigned int)time(NULL));

//     // 执行 OAMap_M 测试
//     testOAMap_M();
    
//     return 0;
// }





#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

// 包含你项目的所有核心头文件
#include "Void\List\Multiple_Void_List\_multiple_void_list.h"
#include "Void\List\Single_Void_List\_single_void_list.h"
#include "Void\Map\Multiple_Void_Map\Hash_Map_List\_multiple_void_map_list.h"
#include "Void\Map\Multiple_Void_Map\Hash_Map_OA\_multiple_void_map_oa.h"
#include "Void\Map\Single_Void_Map\Hash_Map_List\_single_void_map_list.h"
#include "Void\Oper\bool_oper\_bool_oper.h"
#include "Void\Oper\double_oper\_double_oper.h"
#include "Void\Oper\int_oper\_int_oper.h"
#include "Void\Oper\string_oper\_string_oper.h"
#include "Void\_void_base.h"

int main()
{
    
    return 0;
}