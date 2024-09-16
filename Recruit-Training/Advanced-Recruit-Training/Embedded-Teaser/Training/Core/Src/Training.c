#include "Training.h"

uint8_t outputArray[3];
uint8_t validData; // Set bits 0, 1, 2 if the input array elements were valid

void trainingTask(uint8_t* data)
{
    uint8_t motor1 = data[0];
    uint8_t motor2 = data[1];
    uint8_t lights = data[2];

    uint8_t lstatus = (lights & 0b111);
    uint8_t count;


    if (data[0] == data[1]                    // Check if Motors are in sync
    && (((motor1 & 0b10000001) == 0b10000001) // check if forwards is positive
    ||  ((motor1 & 0b11000001) == 0b01000001) // check if backwards is negative
    ||  ((motor1 & 0b11111110) == 0))){       // or if motors off is 0 velocity

        // Valid for both motors, since they should be in sync
        outputArray[0] = data[0];
        outputArray[1] = data[1];
        validData |= 0b00000011;
    } else {
        outputArray[0] = 0;
        outputArray[1] = 0;
    }

    // Check Lights validity

    while(lstatus){     // count how many bits are set in bits 0-2
        count += lstatus & 1;
        lstatus >>= 1;
    }

    if (count <= 1){    // if there is 1 or less bits set
        outputArray[2] = data[2];
        validData |= 0b00000100;

    } else {            // if 2+ headlight statuses exist
        outputArray[2] = 0;
    }

}
