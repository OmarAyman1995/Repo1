#include "services.h"
#include "math.h"

void cpy_array(u8_t* dest,const u8_t* src,size_t size)
{
    for (size_t i=0;i<size;i++)
    {
        dest[i]=src[i];
    }
}

u8_t* ptr_u8ClearArray(u8_t* arr_u8DesiredArray, size_t s64Size)
{
    for (size_t LOC_s64Counter = 0; LOC_s64Counter < s64Size; LOC_s64Counter++)
    {
        arr_u8DesiredArray[LOC_s64Counter] = 0;
    }
    return arr_u8DesiredArray;
}


i32_t linearSearch(u8_t desiredValue,const u8_t *array,u16_t size)
{
  i32_t returnIndex=NEGATIVE_SEARCH;          /*-1 indicating index not found*/
  for(u8_t i=0;i<size;i++)
  {
    if(array[i]==desiredValue)
    {
      returnIndex=i;
    }

    else
    {
      /*do nothing*/
    }
  }

  return returnIndex;
}


i32_t floatToString(float32_t num, char str[], u32_t precision) {
    if (num == 0) {
        str[0] = '0';
        str[1] = '.';
        for (u32_t i = 0; i < precision; ++i) {
            str[i + 2] = '0';
        }
        str[precision + 2] = '\0';
        return precision + 3; // Size of the resulting string
    }

    // Handle sign
    i32_t integerPart = (i32_t)num;
    u32_t i = decimalToString(num, str);

    // Add decimal point
    str[i++] = '.';
    
    // Handle decimal part
    if(integerPart < 0){
        
        integerPart = integerPart * -1;
        num = num * -1;
    }
    if(num < 0 && num > -1){
        // put - front of 0.
        num = num * -1;
        str[0] = '-';
        str[1] = '0';
        str[2] = '.';
        i = 3;
    }
    
    float32_t decimalPart = num - integerPart;
    u32_t decimalCount = 0;

    while (decimalCount < precision) {
        decimalPart *= 10;
        str[i++] = ((i32_t)decimalPart) % 10 + '0';
        decimalPart -= (i32_t)decimalPart;
        decimalCount++;
    }

    // Null-terminate the string
    str[i] = '\0';

    return i; // Size of the resulting string (excluding null terminator)
}


i32_t decimalToString(i32_t num, char str[]) {
    int i = 0;
    int isNegative = 0;

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Extract digits in reverse order
    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    // Add negative sign if necessary
    if (isNegative) {
        str[i++] = '-';
    }

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    // Null-terminate the string
    str[i] = '\0';

    return i; // Size of the resulting string (excluding null terminator)
}


i8_t *ptr_s8ConvertItoa(i32_t s8Num, i8_t *ptr_s8Str, i32_t s32Base)
{
    int i = 0;
    u8_t  isNegative = 0;

    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (s8Num == 0) {
        ptr_s8Str[i++] = '0';
        ptr_s8Str[i] = '\0';
        return ptr_s8Str;
    }

    // In standard itoa(), negative numbers are handled
    // only with base 10. Otherwise numbers are
    // considered unsigned.
    if (s8Num < 0 && s32Base == 10) {
        isNegative = 1;
        s8Num = -s8Num;
    }

    // Process individual digits
    while (s8Num != 0) {
        int rem = s8Num % s32Base;
        ptr_s8Str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        s8Num = s8Num / s32Base;
    }

    // If number is negative, append '-'
    if (isNegative)
        ptr_s8Str[i++] = '-';

    ptr_s8Str[i] = '\0'; // Append string terminator

    // Reverse the string
    vid_reverse(ptr_s8Str, i);

    return ptr_s8Str;
}

void vid_reverse(i8_t arrStr[], i32_t s32Length)
{
    int start = 0;
    int end = s32Length - 1;
    while (start < end)
    {
    char temp = arrStr[start];
    arrStr[start] = arrStr[end];
    arrStr[end] = temp;
    end--;
    start++;
    }
}

