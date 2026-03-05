#include <stdio.h>
#include "Function_1/function_1.h"
int main ()
{

    int start,end;
    scanf("%d %d",&start,&end);
    letRangeToRight(&start,&end,89);
    printf("%d %d",start,end);

}