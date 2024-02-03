/*
 * BlueSwitchTask.c
 *
 *  Created on: Nov. 23, 2022
 *      Author: marce
 */

#include "BlueSwitchTask.h"

static const uint32_t BLUE_LED_EXID = 0xCCCCCCC;

void blueSwitchTask(void const* arg)
{
    uint8_t data[1] = {0x89};

    for (;;)	//Just a short hand for a infinite loop
    {
    	if (HAL_GPIO_ReadPin(BLUE_SWITCH_GPIO_Port, BLUE_SWITCH_Pin)) {		//Reads the pin and if (high) 1 sets data to 0x89
    		data[0] = 0x89;
    	} else {
    		data[0] = 0x0;
    	}

    	if (osMutexWait(SPIMutexHandle, 0) == osOK) {						//Checks Mutex and if has it
			CANMsg msg = {.extendedID = BLUE_LED_EXID, .DLC = 1, .data = data};	//Compiles a CAN message **DLC** - Length of data
																									   //**extendedID - is the difference
    		sendExtendedCANMessage(&msg);										//Sends Message
			osMutexRelease(SPIMutexHandle);										//Released Mutex
    	}
    }
}
