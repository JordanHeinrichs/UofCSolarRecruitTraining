/*
 * GreenSwitch.c
 *
 *  Created on: Jan. 20, 2024
 *      Author: Alend Maci
 */

#include "GreenSwitch.h"

//Check state of switch on PC9 GPIO 
static const uint32_t GREEN_LED_EXID = 0xAAA;
//ON message is 0x5A5A
//OFF is 0xA5A5

void greenSwitch(void const *arg){

    uint32_t data[1] = {0x5A5A};

    for(;;){
        if (HAL_GPIO_ReadPin(GREEN_SWITCH_GPIO_Port, GREEN_SWITCH_Pin)) { //checks pin 9 if HIGH
            data[0] = 0x5A5A;
        } else {
            data[0] = 0xA5A5;
        }

        if (osMutexWait(SPIMutexHandle, 0) == osOK) {				        		
            CANMsg msg = {.extendedID = GREEN_LED_EXID, .DLC = 1, .data = data};
            sendCANMessage(&msg);	
            //sendExtendedCANMessage(&msg); OLD code										
            osMutexRelease(SPIMutexHandle);										
        }
    }
}