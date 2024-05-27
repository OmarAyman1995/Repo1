
#include "typedefs.h"
#include "stddef.h"

#ifndef SERVICES
#define SERVICES

#define NEGATIVE_SEARCH   -1

/// @brief Function to copy an array into another
/// @param dest destination array
/// @param src source array
/// @param size size of elements to be copied
void cpy_array(u8_t* dest,const u8_t* src,size_t size);

u8_t* ptr_u8ClearArray(u8_t* arr_u8DesiredArray, size_t s64Size);

/// @brief a linear search algorithm
/// @param desiredValue the value we are looking for
/// @param array the array that we are searching in, note that the array must be terminated by "#"
/// @param size size of array
/// @return the index number if return is -1 this means that the value is not foundin the array
i32_t linearSearch(u8_t desiredValue,const u8_t *array,u16_t size);


// Function to convert float to string
i32_t floatToString(float32_t num, char str[], u32_t precision);

i32_t decimalToString(i32_t num, char str[]);


/// @brief this function used to convert integer to array of characters
/// @param s8Num     : the integer the user wants to convert.
/// @param ptr_s8Str : distanation array contains the chars converted.
/// @param s32Base   : base of the source Integer (decimal "10",Hex "16",binary "2").
/// @return          : distanation array contains the chars converted.
i8_t* ptr_s8ConvertItoa(i32_t s8Num, i8_t* ptr_s8Str, i32_t s32Base);


/// @brief  this function reverses the array elements upside down.
/// @param arrStr    : source array to be converted.
/// @param s32Length : the length of the source array.
/// @return          : NAN
void vid_reverse(i8_t arrStr[], i32_t s32Length);


#endif
