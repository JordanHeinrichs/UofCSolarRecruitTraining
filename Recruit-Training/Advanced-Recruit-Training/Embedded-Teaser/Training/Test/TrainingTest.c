#include "unity.h"
#include "TrainingTest.h"
#include "Training.h"

extern uint8_t outputArray[3];
extern uint8_t validData;

uint8_t expected_output[3] = {0, 0, 0};

#define VALID 0b111
#define INVALID 0
#define INVALID_MOTORS 0b100
#define INVALID_LIGHTS 0b11

void resetOutput();

void runTrainingTests()
{
    UNITY_BEGIN();
    RUN_TEST(test_EverythingValid);
    RUN_TEST(test_EverythingInvalid);
    RUN_TEST(test_OnlyLightsInvalid);
    RUN_TEST(test_OnlyMotorsInvalid);
    return UNITY_END();
}

void test_EverythingValid(void) {
    uint8_t m1, m2;
    m1 = m2 = 0b1001001;

    uint8_t l = 0b0001100;

    uint8_t valid_data[3] = {m1, m2, l};

    trainingTask(valid_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(valid_data, outputArray, 3, "Everything Valid Array incorrect");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000111, validData, "Everything Valid validData Incorrect");

    resetOutput(0,0,0);

    m1 = 0b00000001;
    m2 = 0b01000001;

    valid_data[0] = expected_output[0] = m1;
    valid_data[1] = expected_output[1] = m2;

    trainingTask(valid_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(valid_data, outputArray, 3, "Everything Valid Array incorrect 2");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0b00000111, validData, "Everything Valid validData Incorrect2");

}

void test_EverythingInvalid(void) {
    resetOutput();
    uint8_t invalid_data[3] = {0xFF, 0xF0, 0xFF};   // Invalid data, should not change outputArray
    uint8_t expected_output[3] = {0, 0, 0};         // Expected output for invalid data
    trainingTask(invalid_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_output, outputArray, 3, "Everything Invalid Array incorrect");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, validData, "Invalid Data Flag Incorrect");
}

void test_OnlyLightsInvalid(void) {
    uint8_t m1, m2;
    
    resetOutput();
    m1 = m2 = 0b10010111;
    uint8_t expected_output[3] = {m1, m2, 0};          // Expected output for invalid data
    
    uint8_t invalid_lights_data[3] = {m1, m2, 0b1000000};
    trainingTask(invalid_lights_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_output, outputArray, 3, "Headlights in no states Array incorrect");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(INVALID_LIGHTS, validData, "Headlights in no states not caught");
    
    resetOutput();
    invalid_lights_data[2] = 0b1100000;
    trainingTask(invalid_lights_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_output, outputArray, 3, "Headlights in multiple states Array incorrect");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(INVALID_LIGHTS, validData, "Headlights in multiple states not caught");
    
    resetOutput();
    invalid_lights_data[2] = 0b10011000;
    trainingTask(invalid_lights_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_output, outputArray, 3, "Both blinkers without hazards Array incorrect");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(INVALID_LIGHTS, validData, "Both blinkers without hazards not caught");
    
    resetOutput();
    invalid_lights_data[2] = 0b1101010;
    trainingTask(invalid_lights_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_output, outputArray, 3, "Not both blinkers with hazards Array incorrect");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(INVALID_LIGHTS, validData, "Not both blinkers with Hazards on not caught");
}

void test_OnlyMotorsInvalid(void) {
    uint8_t l = 0b0000001;
    uint8_t expected_output[3] = {0, 0, l};

    resetOutput();
    uint8_t invalid_motors_data[3] = {0b11100111, 0b10101001, l};
    trainingTask(invalid_motors_data);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_output, outputArray, 3, "Unsynced Motors Array incorrect");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(INVALID_MOTORS, validData, "Unsynced Motors validData incorrect");
    
    resetOutput();
    uint8_t invalid_motors_data2[3] = {0b11001001, 0b01001001, l};
    trainingTask(invalid_motors_data2);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_output, outputArray, 3, "Both Motors not on: Array incorrect");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(INVALID_MOTORS, validData, "Both Motors not on: validData incorrect");
}

//
void resetOutput(){
    outputArray[0] = 0;
    outputArray[1] = 0;
    outputArray[2] = 0;
    
    // expected_output[0] = a;
    // expected_output[1] = b;
    // expected_output[2] = c;

    validData = 0;
}