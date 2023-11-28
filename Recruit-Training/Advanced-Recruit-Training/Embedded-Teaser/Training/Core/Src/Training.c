#include "Training.h"

// uint8_t 8 bit-unsigned integer
uint8_t outputArray[3];
uint8_t validData; // Set bits 0, 1, 2 if the input array elements were valid
uint8_t isMotorDataValid(uint8_t isMotorOn, uint8_t motorVelocity);

/**
NOTE: I decided that if the motors do not have matching ON/OFF status or do not have matching velocity*, both motor inputs will be flagged as wrong (it's hard to know which motor is "right" when they are not in sync).

* Velocity will be compared in its vector form. i.e. v1 = v2 if and only if they are equal in magnitude and direction.
*/
void trainingTask(uint8_t* data)
{
    // MOTORS
    // Check equality in motor ON/OFF status
    uint8_t isMotorOneOn = 0b00000001 & data[0];
    uint8_t isMotorTwoOn = 0b00000001 & data[1];

    // Check equality in velocity (magnitude and direction) 
    uint8_t motorOneVelocity = (0b11111110 & data[0]) >> 1;
    uint8_t motorTwoVelocity = (0b11111110 & data[1]) >> 1;

    // Check motors are in sync
    uint8_t isSynced = (isMotorOneOn == isMotorTwoOn) && (motorOneVelocity == motorTwoVelocity);

    // If the motors are in sync only need to check if one motor is valid since they must be equal!
    // Set validData bits accordingly
    // If motors are valid, copy data onto outputArray
    if(isSynced && isMotorDataValid(isMotorOneOn, motorOneVelocity)){
        validData = 0b11000000;
        outputArray[0] = data[0];
        outputArray[1] = data[1];
    } else {
        validData = 0b00000000;
    }

    // LIGHTS
    // Check exactly one of the headlight statuses is on
    uint8_t isHeadlightOff = (0b10000000 & data[2]) >> 7;
    uint8_t isHeadlightLow = (0b01000000 & data[2]) >> 6;
    uint8_t isHeadlightHigh = (0b00100000 & data[2]) >> 5;
    uint8_t isHeadlightValid = isHeadlightOff ^ isHeadlightLow ^ isHeadlightHigh;

    // In order to check signal lights we needs to know if hazards are on and then determine the right behaviour.
    uint8_t isHazardOn = (0b00000100 & data[2]) >> 2;
    uint8_t isRightSignalOn = (0b00010000 & data[2]) >> 4;
    uint8_t isLeftSignalOn = (0b00001000 & data[2]) >> 3;
    uint8_t isSignalValid;

    // When hazard light is on, the signals must both be in the same state to denote blinking.
    // When hazards are not on, signals may not be on at the same time
    isSignalValid = isHazardOn ? !(isRightSignalOn ^ isLeftSignalOn) : !(isRightSignalOn && isLeftSignalOn);

    // Copy data onto outputArray if lights are valid
    // Set bit 2 of validData accordingly
    if (isHeadlightValid && isSignalValid)
    {
        validData = 0b00100000 | validData;
        outputArray[2] = data[2];
    } else {
        validData = 0b11011111 & validData;
    }

}

/** @brief Function that takes in motor ON/OFF status and returns 1 if data
* is valid and 0 if data is not valid.  This function only looks at the motor as a
* standalone unit and aasumes that it is synced with the other motor. 
* 
* @param[in] isMotorOn 8 bit integer with value 0000000 or 0000001
* @param[in] motorVelocity 8 bit integer representing the velocity of the motor.
*/
uint8_t isMotorDataValid(uint8_t isMotorOn, uint8_t motorVelocity) {

    if(isMotorOn){
        // If motor is on, the sign of the velocity needs to match the direction
        // Forward: 1, Positive: 0
        uint8_t isForward = (0b10000000 & motorVelocity) >> 6;
        uint8_t velocitySign = (0b00000001 & motorVelocity);
        return (isForward != velocitySign) ? 1 : 0;
    } else {
        // Since motor is off, input is valid iff velocity is 0
        return (!motorVelocity) ? 1 : 0;
    }
    
}
