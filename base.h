#ifndef BASE_H
#define BASE_H
#include <stdbool.h>
#include <stdio.h>
#define NOT_FOUND -1
typedef unsigned long long ull;
typedef int Position;


#ifdef ENTRY_STATE_IN_OAMAP

enum EntryStateInMap {
    DEL_IN_MAP = -1,
    NONE_IN_MAP = 0,
    EXIST_IN_MAP = 1
};

#endif

#ifdef ENTRY_STATE_IN_OASET

enum EntryStateInSet {
    DEL_IN_SET = -1,
    NONE_IN_SET = 0,
    EXIST_IN_SET = 1
};


#endif














//注:Data和Entry的空不能作为有效的内容,只是为了在出现问题时返回空

/*
使用方法:
    1 创建当前类型数据的所有操作函数
    2 把相关函数的指针整合成一个Operation类型的数据
    3 使用stackData函数和成Data类型(包括key和val)
    4 插入到Map或者List中
    5 每次使用完Map(List)后必须释放掉Map(List),使用free的相关函数

注: 1 同一中类型的操作函数应该一致
    2 stackData函数返回的时自动变量,不可以free
    3 (函数带有Copy字样的)通过key等返回的Entry是malloc出来的,使用完记得释放,如果无法找到或者无法创建Data或者Entry,会输出提示信息,同时返回空Data或Entry
    4 content内容一般为结构体,比如二维动态数组content的应该为,注意要是指针
                        typedef struct {
                            int row;
                            int col;
                        } MetriArray;





*/



typedef enum cmpresult {
    SAME = 0,
    DIFFERENT = 1,
} CmpResult;



typedef enum info {
    Warning = -1,
    None = 0,
    Success = 1
} InfoOfReturn;

//以下函数都需要自己提供

/// @brief 释放void* data
typedef void (*_freedata)(void* data, void* content);

/// @brief 对void* data的内容进行hash的函数(hash函数必须返回ull类型的数据)
typedef ull (*_hashdata)(void* data, void* content);

/// @brief 对void* data进行比较的函数
typedef CmpResult (*_cmpdata)(void* data_a, void* content_a, void* data_b, void* content_b);

/// @brief 对void* data进行复制的函数
typedef void* (*_copydata)(void* data, void* content);

/// @brief 对Data进行输出的函数
typedef void (*_printdata)(void* data, void* content);


/// @brief 按自己的方式释放content
typedef void (*_freecontent)(void* content);


/// @brief 通过按自己的方式解析content内容,然后创建一个完全一样的
typedef void* (*_copycontent)(void* content);


/// @brief 创建的这种类型的变量是不允许删除的(把他设置为全局变量),它代表的是某一种类型的相关操作函数
typedef struct Operation {
    _freedata freedata;
    _hashdata hashdata;
    _cmpdata cmpdata;
    _copydata copydata;
    _printdata printdata;
    _copycontent copycontent;
    _freecontent freecontent;
} Operation;


typedef struct InfoOfData {
    //此为后期可能拓展
    // InfoOfData** son;
    // int sizeofInfoSon;
    Operation* oper;
    bool hasContent;
} InfoOfData;


/// @brief 只能容纳一种数据的Data类型, 操作函数会由List或者Map提供
typedef struct Data_S {
    void* data;
    void* content;
    bool isEmpty;
    bool isOwner;
} Data_S;


/// @brief 可容纳多种数据的Data类型, 操作函数自带
typedef struct Data_M {
    void* data;
    void* content;
    InfoOfData* dataInfo;
    int type;
    bool isEmpty;
    bool isOwner;
} Data_M;

//OWN, 为了保证数据是自己的, 会自动复制一份, data: 数据指针, content: 描述性信息指针, dataInfo: InfoOfData类型指针, type: 数据标签
#define Data_M_OWN(data, content, dataInfo, type) ((Data_M){(data), (content), (dataInfo), (type), false, true})


//REF, 数据不是自己的, 只是传个指针, 不会自动复制, data: 数据指针, content: 描述性信息指针, dataInfo: InfoOfData类型指针, type: 数据标签
#define Data_M_REF(data, content, dataInfo, type) ((Data_M){(data), (content), (dataInfo), (type), false, false})

//OWN, 为了保证数据是自己的, 会自动复制一份, data: 数据指针, content: 描述性信息指针
#define Data_S_OWN(data, content) ((Data_S){(data), (content), false, true})
//REF, 数据不是自己的, 只是传个指针, 不会自动复制, data: 数据指针, content: 描述性信息指针
#define Data_S_REF(data, content) ((Data_S){(data), (content), false, false})


//Map中的key是否为OWN/REF都无效,最终都为OWN

#ifdef GET_LARGESTPRIME


/// @brief 返回小于等于n的最大质数
/// @param n n
/// @return 最大质数
extern int getLargestPrime(int n);


#endif

//直接提供Data的复制, 比较, 空数据的获得

#ifdef DATA_S_OPER

/////////////////////////////
//空数据的获得

/// @brief 得到空数据Data_S
/// @return 空数据Data_S
extern Data_S getEmptySData();

//////////////////////////////
//数据的比较

/// @brief 比较两个Data_S是否相同
/// @param Data_a Data_S类型数据1
/// @param info_a InfoOfData类型数据指针1
/// @param Data_b Data_S类型数据2
/// @param info_b InfoofData类型数据指针2
/// @return 比较结果, 使用SAME和DIFFERENT来进行判断
extern CmpResult compareSData(Data_S Data_a, InfoOfData* info_a, Data_S Data_b, InfoOfData* info_b);

///////////////////////////////////////
//数据的复制

/// @brief 复制Data_S的全部内容(深拷贝, 赋值后的Data.isOwner = true), 需要提供InfoOfData类型数据指针以便进行复制
/// @param inputData 输入的Data_S类型数据
/// @param info InfoOfData类型数据指针
/// @return 复制好的Data_S类型数据
extern Data_S deepCopySData(Data_S inputData, InfoOfData* info);


/// @brief 复制Data_S的内容(视情况复制, 如果有控制权, 直接复制全部内容, 如果没有, 等同于输入的Data_S), 需要提供InfoOfData类型数据指针以便进行复制
/// @param inputData 输入的Data_S类型数据
/// @param info InfoOfData类型数据指针
/// @return 智能复制好的Data_S数据
extern Data_S smartCopySData(Data_S inputData, InfoOfData* info);

///////////////////////////////////
//数据的释放

/// @brief 释放掉Data_S数据
/// @param inputData 输入的Data_S类型数据
/// @param info InfoOfData类型数据指针
extern void freeSData(Data_S* inputData, InfoOfData* info);

#endif

#ifdef DATA_M_OPER
/////////////////////////////
//空数据的获得

/// @brief 得到空数据Data_M
/// @return 空数据Data_M
extern Data_M getEmptyMData();

//////////////////////////////
//数据的比较

/// @brief 比较两个Data_M是否相同
/// @param Data_a Data_M类型数据1
/// @param Data_b Data_M类型数据2
/// @return 比较结果, 使用SAME和DIFFERENT来进行判断
extern CmpResult compareMData(Data_M Data_a, Data_M Data_b);

///////////////////////////////////////
//数据的复制



/// @brief 复制Data_M的全部内容, 包括void* data和void* content
/// @param inputData 输入的Data_M类型数据
/// @return 复制好的Data_M类型数据
extern Data_M deepCopyMData(Data_M inputData);


/// @brief 复制Data_M的内容, 如果具备控制权, 那就会复制全部内容, 如果不具备控制权, 等同于输入的Data_M
/// @param inputData 输入的Data_M类型数据
/// @return 智能复制好的Data_M类型数据
extern Data_M smartCopyMData(Data_M inputData);


///////////////////////////////////
//数据的释放

/// @brief 释放掉Data_M数据
/// @param inputData 输入的Data_M类型数据
extern void freeMData(Data_M* inputData);

#endif







#endif