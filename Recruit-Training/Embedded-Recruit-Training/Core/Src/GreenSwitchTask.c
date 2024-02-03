/*
 * GreenSwitchTask.c
 *
 *  Created on: Jan 20, 2024
 *      Author: dominic
 */

#include "GreenSwitchTask.h"

static const uint32_t GREEN_LED_ID = 0xAAA;

void greenSwitchTask(void const* arg)
{
    uint8_t data[2] = {0xA5, 0xA5};

    for (;;)
    {
    	if (HAL_GPIO_ReadPin(GREEN_SWITCH_GPIO_Port, GREEN_SWITCH_Pin)) {
    		data[0] = 0x5A;
    		data[1] = 0x5A;
    	} else {
    		data[0] = 0xA5;
    		data[1] = 0xA5;
    	}

    	if (osMutexWait(SPIMutexHandle, 0) == osOK) {
			CANMsg msg = {.ID = GREEN_LED_ID, .DLC = 2, .data = data};
    		sendCANMessage(&msg);
			osMutexRelease(SPIMutexHandle);
    	}
    }
}
