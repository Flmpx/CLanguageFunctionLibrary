#include "function_1.h"
//传入一个起始值start,终点值end,其中会把区间矫正,改为min<=start<=end<max
//如果输入的区间没有人,则函数返回0,同时不改变原区间,否则返回区间成员数
int letRangeToRight(int* start,int* end,int min,int max){
    if(*start>*end){
        int temp;
        temp=*start;
        *start=*end;
        *end=temp;
    }
    if(*end<min||*start>max) return 0;
    *start=(*start)<min?min:(*start);
    *end=(*end)>max?max:(*end);
    return *end-*start+1;
}