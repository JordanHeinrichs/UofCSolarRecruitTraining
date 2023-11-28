#include "unity.h"
#include "TrainingTest.h"
#include "Training.h"

extern uint8_t outputArray[3];
extern uint8_t validData;
void resetOutput();

void runTrainingTests()
{
    RUN_TEST(test_EverythingValid);
    RUN_TEST(test_EverythingInvalid);
    RUN_TEST(test_OnlyLightsInvalid);
    RUN_TEST(test_OnlyMotorsInvalid);
}

void test_EverythingValid()
{
    resetOutput();
    uint8_t data[3] = {0b01001011,0b01001011, 0b00110000};
    uint8_t expected[3] = {0b01001011,0b01001011, 0b00110000};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8(0b11100000, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);
}

void test_EverythingInvalid()
{
    resetOutput();
    uint8_t data[3] = {0b11011011, 0b10010000, 0b11111000};
    uint8_t expected[3] = {0,0,0};
    trainingTask(data);
    TEST_ASSERT_EQUAL_UINT8(0b00000000, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);
}

void test_OnlyLightsInvalid()
{
    uint8_t expected[3] = {0b10010111,0b10010111,0};

    // Case 1: Headlights are in two states
    resetOutput();
    uint8_t data1[3] = {0b10010111,0b10010111,0b11000000};
    trainingTask(data1);
    TEST_ASSERT_EQUAL_UINT8(0b11000000, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);

    // Case 2: Hazards off, but both signals are on
    resetOutput();
    uint8_t data2[3] = {0b10010111,0b10010111,0b10011000};
    trainingTask(data2);
    TEST_ASSERT_EQUAL_UINT8(0b11000000, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);

    // Case 3: Hazards on, but signals not flashing
    resetOutput();
    uint8_t data3[3] = {0b10010111,0b10010111,0b10010100};
    trainingTask(data3);
    TEST_ASSERT_EQUAL_UINT8(0b11000000, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);

}

void test_OnlyMotorsInvalid()
{
    uint8_t expected[3] = {0,0,0b01000000};
    // Case 1: Motors not in sync
    resetOutput();
    uint8_t data1[3] = {0b11100111, 0b01001001, 0b01000000};
    trainingTask(data1);
    TEST_ASSERT_EQUAL_UINT8(0b00100000, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);

    // Case 2: Motors in sync, but turned off with non-zero velocity
    resetOutput();
    uint8_t data2[3] = {0b11000000, 0b11000000, 0b01000000};
    trainingTask(data2);
    TEST_ASSERT_EQUAL_UINT8(0b00100000, validData);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, outputArray, 3);
}

void resetOutput() {
    for (int i = 0; i < 3; i++)
    {
        outputArray[i] = 0;
    }
    validData = 0;
}
