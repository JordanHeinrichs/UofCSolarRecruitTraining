/*
 * RedSwitchTask.c
 *
 *  Created on: Jan 20, 2024
 *      Author: dominic
 */

#include "RedSwitchTask.h"

void redToggleTask(void const* arg){
    if(redStatus == 1){
        HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
        osDelay(350 / portTICK_PERIOD_MS);
    } else {
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
    }
}

