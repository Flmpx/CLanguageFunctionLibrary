#ifndef _PRINT_H
#define _PRINT_H
typedef void (*_printval)(void* val);
typedef void (*_freeval)(void* val);
typedef struct Node {
    int type;
    void* val;
    struct Node* sameLevel;
    _printval print;
    _freeval freeval;
} Node;
typedef struct {
    int size;
    Node* head;
    Node* tail;
} Array;

/// @brief 用于初始化数组类型
/// @param arr 传入的Array类型的指针
extern void initialArray(Array* arr);

/// @brief 将元素插入到数组中
/// @param arr Array数组指针
/// @param val 元素指针
/// @param type 元素类型
/// @param print 当前元素的打印函数
/// @param freeval 释放当前元素的函数
/// @return 插入成功返回1, 内存分配失败返回-1
extern int insertValueInArray(Array* arr, void* val, int type, _printval print, _freeval freeval);


//释放类


/// @brief 释放元素链中的元素但不释放Array本身(用于Array类型的自动变量)
/// @param val 传入的值(内部会自动强制转化为Array*)
extern void free_Array(void* val);

/// @brief 释放元素链中的元素同时释放Array本身(用于动态分配的Array类型)
/// @param val 传入的值(内部会自动强制转化为Array*)
extern void free_Array_and_Self(void* val);

//打印类
/*
    命名规则:
            print_*(首字母大写)
            void print_*(void* val)

*/


extern void print_Int(void* val);
extern void print_Bool(void* val);
extern void print_Ll(void* val);
extern void print_Array(void* val);



#endif