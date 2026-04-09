#ifndef FUNCTION_1_H
#define FUNCTION_1_H
//传入一个起始值start,终点值end,其中会把区间矫正,改为min<=start<=end<max
//如果输入的区间没有人,则函数返回0,同时不改变原区间 否则返回区间成员数
extern int letRangeToRight(int* start,int* end,int min,int max);
#endif