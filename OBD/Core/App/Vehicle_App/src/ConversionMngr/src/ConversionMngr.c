#include "ConversionMngr.h"
#include "PIDsDatabase.h"

#define CONV_MAX_UNITS 201



/* implementation */

u8_t u8_ConvertOBDToPhysicalValue(u8_t pid,
                               u8_t A,
                               u8_t B,
                               u8_t C,
                               u8_t D,
                               u8_t* output_string){
    
    ConvUnitType LOC_ptr_convertFunction = NULLPTR;
    u8_t LOC_u8_retVal = 0;

    if((pid < CONV_MAX_UNITS) && (output_string != NULLPTR)){
        LOC_ptr_convertFunction = p_getConvFunction(pid);
        if(LOC_ptr_convertFunction != NULLPTR){
            LOC_u8_retVal = LOC_ptr_convertFunction(A,B,C,D, output_string);
        }else{
            LOC_u8_retVal = 0;
        }
    
    }else{
        LOC_u8_retVal = 0;
    }

    return LOC_u8_retVal;
}


u32_t u32_getConvertedSize(void){
    return getConvertedSize();
}
