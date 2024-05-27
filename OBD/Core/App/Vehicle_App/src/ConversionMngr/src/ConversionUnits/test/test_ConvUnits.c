#include "unity.h"
#include "ConvUnits.h"
#include "services.h"



void test_pids_supported(void){
    // setup
    u8_t output_string [150] = {0};
    u8_t A = 0x01;
    u8_t B = 0x01;
    u8_t C = 0x01;
    u8_t D = 0x01;

    // act
    ConvPIDS_Supported(A , B, C, D, output_string);
    printf("%s", output_string);
   
    // assert
    
    // cleanup
    printf("\nend");
}

void test_monitor_dtc(void){
    // setup
    u8_t output_string [150] = {0};
    u8_t A = 0xff;
    u8_t B = 0xff;
    u8_t C = 0xff;
    u8_t D = 0xff;

    // act
    ConvMonitor_DTC(A , B, C, D, output_string);
    printf("%s", output_string);
   
    // assert
    
    // cleanup
    printf("\nend");

}

void test_fuel_trim(void){
    // setup
    u8_t output_string [150] = {0};

    u8_t A = 60;
    u8_t B = 0xaa;
    u8_t C = 0xaa;
    u8_t D = 0xaa;
    
    // act
    ConvFuelTrim(A , B, C, D, output_string);
    printf("%s", output_string);
    // assert
    // TEST_ASSERT_EQUAL_FLOAT(20, result);

    // cleanup
}

void test_fuel_pressure(void){
    // setup
    u8_t output_string [150] = {0};
    u8_t A = 6;
    u8_t B = 0xaa;
    u8_t C = 0xaa;
    u8_t D = 0xaa;
    
    // act
    ConvFuelPressure(A , B, C, D, output_string);
    printf("%s", output_string);
    // assert
    // TEST_ASSERT_EQUAL_FLOAT(23.52941176471, result);

    // cleanup
}
