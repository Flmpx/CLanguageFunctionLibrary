#include "function_1.h"
//传入一个起始值start,终点值end,其中会把区间矫正,改为0<=start<=end<allNum
int letRangeToRight(int* start,int* end,int allNum){
    if(*start>*end){
        int temp;
        temp=*start;
        *start=*end;
        *end=temp;
    }
    *start=(*start)<0?0:(*start);
    *end=(*end)>allNum-1?allNum-1:(*end);
}