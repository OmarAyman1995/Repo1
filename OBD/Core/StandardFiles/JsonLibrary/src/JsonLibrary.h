#ifndef _JSON_LIB_H
#define _JSON_LIB_H

#include "stdint.h"


#define JSON_BUFFER_SIZE 1000


typedef struct 
{
    uint8_t Buffer[JSON_BUFFER_SIZE];
    uint32_t size;
    uint16_t numberOfKeys;
}JsonString;


void JsonInit(JsonString *_userString);

void JsonAdd(JsonString *_userString, uint8_t *_key, uint8_t *_value, uint8_t _keyisNumber);

void JsonStringfy(JsonString *_userString);

void JsonReset(JsonString *_userString);

#endif // !_JSON_LIB_H
