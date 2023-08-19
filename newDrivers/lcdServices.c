#include "lcdServices.h"

s8_t* ptr_s8FloatToString(s64_t s64FloatNumber,s8_t s8FloatSize)
{
    s32_t LOC_s32Counter ; 
    s32_t LOC_s32part1 = (s32_t) s64FloatNumber;
    s64_t LOC_s64Temp = s64FloatNumber - (s64_t)LOC_s32part1;
    LOC_s64Temp = LOC_s64Temp * 100.0;
    s32_t LOC_s32part2 = (s32_t)LOC_s64Temp;
    
    s32_t LOC_s32Div  = LOC_s32part2 ;
    s8_t  LOC_s32reminder  = 0;
    static s8_t LOC_ptrArray[10];
    for(LOC_s32Counter=s8FloatSize-2;LOC_s32Counter>s8FloatSize-4;LOC_s32Counter--)
    {
       LOC_s32reminder = LOC_s32Div%10;
       LOC_ptrArray[LOC_s32Counter] = LOC_s32reminder+48;
       LOC_s32Div/=10;
    }
    LOC_ptrArray[LOC_s32Counter--]= '.';
    LOC_s32Div  = LOC_s32part1 ;
    for(;LOC_s32Counter>=0;LOC_s32Counter--)
    {
       LOC_s32reminder = LOC_s32Div%10;
       LOC_ptrArray[LOC_s32Counter] = LOC_s32reminder+48;
       LOC_s32Div/=10;  
    }
    LOC_ptrArray[s8FloatSize-1] = '\0';
    return LOC_ptrArray;
}

