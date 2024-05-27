#ifndef STDFILE_H
#define STDFILE_H


#include "BitMath.h"
#include "typedefs.h"


#define LINE_END  0XFF
typedef enum
{
    FRAME_OK,
    FRAME_ERROR,
}Frame_Status;

typedef enum
{
    BAD_COMMAND,
    GOOD_COMMAND
}BluetoothCommandStatus;

typedef enum
{
    STORAGE_OK,
    STORAGE_NOK,
}Storage_Status;



#endif
