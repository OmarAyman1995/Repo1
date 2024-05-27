#include "ConvUnits.h"
#include "services.h"
#include "string.h"
#include "BitMath.h"

/*
    Reference link to the conversion equations: https://en.wikipedia.org/wiki/OBD-II_PIDs
*/

static u32_t GLOB_u32Converted_Size = 0;

u32_t getConvertedSize(void){
    return GLOB_u32Converted_Size;
}

u8_t ConvVehicle_Speed(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = A;
    if(result > 255){
        return 0;
    }
    /* output */
    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}


u8_t ConvEngine_RPM(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = ((float32_t) ((256U * A) + B) / 4U);
    if(result > (float32_t)16383.75){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}


u8_t ConvAir_Intake_Temprature(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = A - 40U;
    
    if((result < -40) || (result > 215)){
        return 0;
    }
    /* output */
    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}


u8_t ConvThrottle_Position(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (((float32_t)100/255) * A);
    
    /* check range */
    if(result > 100 || result < 0){
        return 0;

    }
    /* output */
    GLOB_u32Converted_Size = floatToString(result, output_string,1);
    return 1;
}


u8_t ConvPIDS_Supported(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    // u32_t result = 0;
    // char buffer[1] = {0};

    // /* Equation */
    // result = ((u32_t)D << 24U) | ((u32_t)C << 16U) | ((u32_t)B << 8U) | ((u32_t)A);
    // strcpy(output_string, "");
    // /* output */
    // for(u8_t i = 0; i < 32U; i++){
    //     decimalToString(i, buffer);
    //     strcat(output_string, buffer);
    //     strcat(output_string, "=");
    //     decimalToString(GET_BIT(result, 31U - i), buffer);
    //     strcat(output_string, buffer);
    //     strcat(output_string, "\n");
    // }

     i8_t result1 [5];
     i8_t result2 [5];
     i8_t result3 [5];
     i8_t result4 [5];

    GLOB_u32Converted_Size = decimalToString(A,result1);
    strcat(output_string, "A=");
    strcat(output_string,result1);

    GLOB_u32Converted_Size += decimalToString(B,result2);
    strcat(output_string, " B=");
    strcat(output_string,result2);
    
    GLOB_u32Converted_Size += decimalToString(C,result3);
    strcat(output_string, " C=");
    strcat(output_string,result3);

    GLOB_u32Converted_Size += decimalToString(D,result4);
    strcat(output_string, " D=");
    strcat(output_string,result4);
    GLOB_u32Converted_Size += 11; // the letters A=, B=, C=, C=
    return 1;

}

u8_t ConvCollect4Numbers(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = (D << 24U) | (C << 16U) | (B << 8U) | (A);

    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}





u8_t ConvFuelSystemStatus(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    u32_t result = 0;

    /* Equation */
    result = A;

    if((result == 0) || (result == 1) || (result == 2) || (result == 4) || (result == 8)  || (result == 16)){
        GLOB_u32Converted_Size = decimalToString(result, output_string);
        return 1;
    }else{
        return 0;

    }
    
}


u8_t ConvFuelTrim(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = ( (((float32_t)100/128) * A) - 100U);
    
    if((result < -100) || (result > (float32_t)99.21875)){
        return 0;

    }
    /* output */
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}


u8_t ConvFuelPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = 3U * A;
    if((result < 0) || (result > 765)){
        return 0;

    }
    /* output */
    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}


u8_t ConvTimingAdvance(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = ( ((float32_t)A / 2U) - 64U);
    if((result < (float32_t)-64) || (result > (float32_t)63.5)){
        return 0;

    }
    /* output */
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}


u8_t ConvMassFlowRate(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (((float32_t)(256U * A) + B) / 100U);
    if(result > (float32_t)655.35){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}


u8_t ConvCommandedSecondaryAirStatus(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;
    
    /* Equation */
    result = A;

    if((result == 1) || (result == 2) || (result == 4) || (result == 8)){
        GLOB_u32Converted_Size = decimalToString(result, output_string);
        return 1;
    }else{
        return 0;

    }
}


u8_t ConvOxygenSensorPresentIn2Banks(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = A;

    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}


u8_t ConvOxygenSensor1VoltageFuel(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result1 = 0;
    float32_t result2 = 0;
    i32_t i = 0;
    /* Equation */
    result1 = (float32_t)A/200;
    result2 = (((float32_t)100/128)*B) - 100;
    if(result1 > (float32_t)1.275){
        return 0;
    }
    if((result2 < (float32_t)-100) || (result2 > (float32_t)99.21875)){
        return 0;

    }
    strcpy(output_string, "A=");
    i += 2;
    i += floatToString(result1, output_string+i, 3);
    strcat(output_string, " B=");
    i += 3;
    i += floatToString(result2, output_string+i, 3);
    GLOB_u32Converted_Size = i;
    return 1;
}

u8_t ConvRunTimeSinceEngineStarts(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = (256U*A) + B;
    if(result > 65535){
        return 0;

    }
    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}

u8_t ConvFuelRailPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (256U*A) + B;
    result = (float32_t)0.079*result;
    if(result > (float32_t)5177.265){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}

u8_t ConvFuelRailGaugePressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = (10U * (256U*A)) + B;
    if(result > 655350){
        return 0;

    }
    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}

u8_t ConvOxygenSensor1ABCD(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result1 = 0;
    float32_t result2 = 0;
    i32_t i = 0;

    /* Equation */
    result1 = ((float32_t)2/65536) * (256*A+B);
    result2 = ((float32_t)8/65536) * (256*C+D);
    if(result1 >= 2){
        return 0;
        
    }
    if(result2 >= 8){
        return 0;

    }
    strcpy(output_string, "AB=");
    i += 3;
    i += floatToString(result1, output_string+i, 3);
    strcat(output_string, " CD=");
    i += 4;
    i += floatToString(result2, output_string+i, 3);
    GLOB_u32Converted_Size = i;
    return 1;
}

u8_t ConvOxygenSensor1RatioCurrent(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result1 = 0;
    float32_t result2 = 0;
    i32_t i = 0;

    /* Equation */
    result1 = ((float32_t)2/65536) * (256*A+B);
    result2 = ((float32_t)(256*C+D)/256) - 128;
    if(result1 >= 2 || result1 < 0){
        return 0;

    }
    if(result2 < -128 || result2 >= 128){
        return 0;
    }
    strcpy(output_string, "AB=");
    i += 3;
    i += floatToString(result1, output_string+i, 3);
    strcat(output_string, " CD=");
    i += 4;
    i += floatToString(result2, output_string+i, 3);
    GLOB_u32Converted_Size = i;
    return 1;
}


u8_t ConvCatalystTemperature(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (((float32_t)(256U * A) + B) / 10U);
    result -= 40;
    if(result < (float32_t)-40 || result > (float32_t)6513.5){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}

u8_t ConvControlModuleVoltage(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (256U*A) + B;
    result = (float32_t)result/1000;
    if(result > (float32_t)65.535){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}

u8_t ConvAbsoluteLoadValue(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (((float32_t)100/255) * A);
    result = result* ((float32_t)100/255);
    if(result > 25700){
        return 0;

    }
    /* output */
    GLOB_u32Converted_Size = floatToString(result, output_string,3); 
    return 1;
}

u8_t ConvCommandedAirFuelEqRatio(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (256 * A + B);
    result = result * ((float32_t)2/65536);
    if(result >= 2){
        return 0;

    }
    /* output */
    GLOB_u32Converted_Size = floatToString(result, output_string,3); 
    return 1;
}

u8_t ConvMaxValuesForSensors(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    u32_t result1 = 0;
    u32_t result2 = 0;
    u32_t result3 = 0;
    u32_t result4 = 0;
    i32_t i = 0;

    /* Equation */
    result1 = A;
    result2 = B;
    result3 = C;
    result4 = D * 10;
    if(result1 > 255 || result2 > 255 || result3 > 255 || result4 > 2550){
        return 0;
    }
    strcpy(output_string, "A=");
    i += 2;
    i += decimalToString(result1, output_string+i);
    strcat(output_string, " B=");
    i += 3;
    i += decimalToString(result2, output_string+i);
    strcat(output_string, " C=");
    i += 3;
    i += decimalToString(result3, output_string+i);
    strcat(output_string, " D=");
    i += 3;
    i += decimalToString(result4, output_string+i);
    GLOB_u32Converted_Size = i;
    return 1;
}

u8_t ConvMaxValueForAirFlowRate(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = (10*A);
    if(result > 2550){
        return 0;
        
    }
    /* output */
    GLOB_u32Converted_Size = decimalToString(result, output_string); 
    return 1;
}

u8_t ConvAbsEvapSystemPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (((float32_t)(256U * A) + B) / 200U);
    if(result > (float32_t)327.675){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}

u8_t ConvEvapSystemPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (((float32_t)(256U * A) + B) / 4U);
    if(result < (float32_t)-8192 || result > (float32_t)8191.75){
        return 0;
    }

    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}

u8_t ConveShortTermBanks(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result1 = 0;
    float32_t result2 = 0;
    i32_t i = 0;

    /* Equation */
    result1 = ((float32_t)100/128) * A - 100;
    result2 = ((float32_t)100/128) * B - 100;

    strcpy(output_string, "A=");
    i += 2;
    i += floatToString(result1, output_string+i, 1);
    strcat(output_string, " B=");
    i += 3;
    GLOB_u32Converted_Size = i;
    return 1;
}

u8_t ConveFuelInjectionTiming(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (((float32_t)(256U * A) + B) / 128U) - 210;
    if(result < (float32_t)-210 || result > (float32_t)301.992188){
        return 0;
    }
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}

u8_t ConveEngineFuelRate(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (((float32_t)(256U * A) + B) / 20U);
    if(result > (float32_t)3212.75){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string, 3);
    return 1;
}


u8_t ConveDriverDemandEngineTorque(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = A - 125;
    if(result < (i32_t)-125 || result > (i32_t)130){
        return 0;
   
    }
    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}

u8_t ConveMassAirFlowSensor(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (float32_t)(256*A+B) / 32;
    if(result > (float32_t)2047.96875){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string , 2);
    return 1;
}

u8_t ConveTransmissionActualGear(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (float32_t)(256*C+D) / 1000;
    if(result > 65535){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string , 3);
    return 1;
}

u8_t ConvDieselExhaustFluid(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = ((float32_t)B/2);
    if(result > (float32_t)127.5){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string , 3);
    return 1;
}

u8_t ConvOdometer(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    float32_t result = 0;

    /* Equation */
    result = (float32_t)((A*0x1000000) + (B*65536) + (C*256) + (D)) / 10;
    if(result > (float32_t)429496729.5){
        return 0;

    }
    GLOB_u32Converted_Size = floatToString(result, output_string , 1);
    return 1;
}

u8_t ConvEvapSystemVaporPressure(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
        float32_t result = 0;

    /* Equation */
    result = 256 * A + B;
    if (result < -32768 || result > 32767)
    {
        return 0;
    }
    
    GLOB_u32Converted_Size = floatToString(result, output_string , 1);
    return 1;
}

u8_t ConvFuelLeveInput(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string){
    i32_t result = 0;

    /* Equation */
    result = (256U*A) + B;
    if(result > 25700){
        return 0;

    }
    GLOB_u32Converted_Size = decimalToString(result, output_string);
    return 1;
}