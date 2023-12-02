#include "Training.h"

uint8_t outputArray[3] = {0,0,0};
uint8_t validData = 0; // Set bits 0, 1, 2 if the input array elements were valid

// Defines for Motors
#define MOTOR_FWD 0b10000001
#define MOTOR_BWD 0b11000001
#define MOTOR_ON 0b10000000
#define VELOCITY 0b111110
#define VELOCITY_SIGN  0b1000000
#define DIRECTION 0b1

// Defines for Headlights
#define HEADS 0b111
#define OFF 0b1
#define LOW 0b10
#define HIGH 0b100

// Defines for Blinkers
#define BLINKERS 0b111000
#define RIGHT 0b1
#define LEFT 0b10
#define HAZARDS 0b100

void trainingTask(uint8_t* data)
{
    // Extract Data
    uint8_t motor1 = data[0];
    uint8_t motor2 = data[1];
    uint8_t lights = data[2];

    // Velocities
    uint8_t m1_velocity = (motor1 & VELOCITY) >> 1;
    uint8_t m2_velocity = (motor2 & VELOCITY) >> 1;

    // Motor On/Off
    uint8_t m1_status = (motor1 & MOTOR_ON) >> 7;
    uint8_t m2_status = (motor2 & MOTOR_ON) >> 7;
    
    // Motors are synced if velocities are the same 
    // and both on or both off
    uint8_t isSynced = (m1_velocity == m2_velocity) // Velocities Equal
                    && (m1_status == m2_status);    // Both on or both off

    if(isSynced){ // Velocity and Status are equal
        // Separate motor directions
        uint8_t m1_dir = motor1 & DIRECTION;
        uint8_t m2_dir = motor2 & DIRECTION;

        // Sign bit of velocity
        uint8_t m1_vnbit = motor1 & VELOCITY_SIGN;
        uint8_t m2_vnbit = motor2 & VELOCITY_SIGN;

        if(m1_dir != m1_vnbit       // If direction is opposite to the velocity sign
        && m2_dir != m2_vnbit) {    
            if(m1_dir == m2_dir){    // Directions are the same
                outputArray[0] = data[0];
                outputArray[1] = data[1];
                validData |= 0b00000011;
            }
        } else if ((m1_status && m2_status) == 0){     // or both motors are off
            outputArray[0] = data[0];
            outputArray[1] = data[1];
            validData |= 0b00000011;
            
        } else {
            outputArray[0] = 0;
            outputArray[1] = 0;
            validData = 0b000000000;
        }
    }
    
    // Valid Positive/Negative Velocity
    uint8_t headlights = (lights & HEADS);
    uint8_t blinkers = (lights & BLINKERS) >> 3;

    // Separate Headlight Bits
    uint8_t off = headlights & OFF;
    uint8_t low = headlights & LOW;
    uint8_t high = headlights & HIGH;

    // Separate Blinker Bits
    uint8_t right = blinkers & RIGHT;
    uint8_t left = blinkers & LEFT;
    uint8_t hazards = blinkers & HAZARDS;

    // Valid Booleans
    uint8_t isValidHead = 0;
    uint8_t isValidBlink = 0;

    // Check Headights validity
    // Boolean for Valid Headlights: 
        // ~High*~Low*Off + ~High*Low*~Off + High*~Low*~Off
        // high XOR low XOR off AND NOT(high AND low AND off)
    if ((high ^ low ^ off) 
        && !(high && low && off)){
        isValidHead = 1;
    }

    // L = Left, R = Right, H = Hazards
    // Boolean for Valid Blinkers: 
        // Right*Low*Haz + ~Right~Left + ~Right~Haz + ~Left~Haz
    if((left && right && hazards)
        || (!right && !left)
        || (!right && !hazards)
        || (!left && !hazards)){
            isValidBlink = 1;
    }

    // If Headlights and Blinkers are both valid
    if(isValidHead && isValidBlink){
            outputArray[2] = data[2];
            validData |= 0b00000100;
    }
}
