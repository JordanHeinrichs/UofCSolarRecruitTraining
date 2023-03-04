#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_can.h"
#include "cmsis_os.h"
#include "main.h"

//TODO: Define an external CAN handle (same variable as in main)
extern CAN_HandleTypeDef hcan2;

//TODO: Define an external CAN Mutex handle (same variable as in main)
extern osMutexId_t mUtex;

//TODO: Define external CAN_Tx header (same variable as in main)
extern CAN_TxHeaderTypeDef CanTXHeader;


//TODO: Define external green LED toggle task (same variable as in main)
extern uint8_t green_message_flag;


void greenLedToggleTask(void const* arg);
