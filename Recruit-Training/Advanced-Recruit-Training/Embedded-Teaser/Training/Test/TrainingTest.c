#include "unity.h"
#include "TrainingTest.h"
#include "Training.h"

extern uint8_t outputArray[3];
extern uint8_t validData;

void runTrainingTests()
{
    UNITY_BEGIN();
    RUN_TEST(test_EverythingIsValid());
    RUN_TEST(test_EverythingIsInvalid());
    RUN_TEST(test_OnlyLightsIsInvalid());
    RUN_TEST(test_MotorsAreInvalid());
    return UNITY_END();
}

void test_EverythingValid()
{
    uint8_t data[3] = {0b10000001, 0b100000001, 0b1111001};
    trainingTask(data);
}

void test_EverythingInvalid()
{
    uint8_t data[3] = {0b10000001, 0b000000001, 0b1111111};
    trainingTask(data);
}

void test_OnlyLightsInvalid()
{
    uint8_t data[3] = {0b10000001, 0b100000001, 0b1111111};
    trainingTask(data);
}

void test_OnlyMotorsInvalid()
{
    uint8_t data[3] = {0b10100000, 0b10100000, 0b1111001};
    trainingTask(data);
}
