#include "HWIndepServices.h"



/* Write your Test Cases Based on Unity */
/* This is An Example */
uint32_t add(uint32_t x, uint32_t y)
{
    return x+y;
}

void setUp(void) {
  /*Constructor*/
}

void tearDown(void) {
    /*Deconstructor*/
}
void TC1(void) {
  TEST_ASSERT_EQUAL_INT(7, add(6,1));
  TEST_ASSERT_EQUAL_INT(7, add(6,1));
}
void TC2(void) {
  TEST_ASSERT_EQUAL_INT(7, add(6,1));
  TEST_ASSERT_EQUAL_INT(5, add(6,1));
}
void TC3(void) {
  TEST_ASSERT_EQUAL_INT(7, add(6,1));
  TEST_ASSERT_EQUAL_INT(7, add(6,1));
}
void TC4(void) {
  TEST_ASSERT_EQUAL_INT(7, add(6,1));
  TEST_ASSERT_EQUAL_INT(5, add(6,1));
}

void UnitTestingEnvironment(void)
{
  /* At first you need to implement your own functions
  let say (add) and the test cases for these functions
  let say (test_addition1,test_addition2)*/
  /* start the unity and our service */
  UNITY_BEGIN();
  /* Run your own test case with any name */
  RUN_TEST(TC1);
  /* call this functio to send the data of the test case name
  and if it passed or failled*/
  SaveUnitTestResults();
  /* another test case */
  RUN_TEST(TC2);
  /* another calling of this function after every test case calling */
  SaveUnitTestResults();
  /* another test case */
  RUN_TEST(TC3);
  /* another calling of this function after every test case calling */
  SaveUnitTestResults();
  /* another test case */
  RUN_TEST(TC4);
  /* another calling of this function after every test case calling */
  SaveUnitTestResults();
  /* we use this function to deinit the service */
  Unit_Testing_DeInit();
  /* Unity test framework cleanup */
  UNITY_END();
}
