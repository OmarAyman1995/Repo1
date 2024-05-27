#include "JsonLibrary.h"
#include "string.h"
#include "stdio.h"


JsonString StoredJsonString = {0};


void JsonInit(JsonString *_userString){
    _userString->Buffer[0] = '{';
}


void JsonAdd(JsonString *_userString, uint8_t *_key, uint8_t *_value, uint8_t _keyisNumber){
    uint8_t tempBuffer[100] = {0};
    uint16_t size = 0;

    if(_keyisNumber == 1){
        size = (uint16_t)sprintf(tempBuffer, "\"%d\":\"%s\",", *_key, _value);
    }else{
        size = (uint16_t)sprintf(tempBuffer, "\"%s\":\"%s\",", _key, _value);
    }
    strncat(_userString->Buffer, tempBuffer, size);
    _userString->size += size;
    _userString->numberOfKeys++;
}


void JsonStringfy(JsonString *_userString){
    _userString->Buffer[_userString->size++] = '}';
}


void JsonReset(JsonString *_userString){
    memset(_userString, 0, sizeof(JsonString));
}
