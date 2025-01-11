/*
 * Motor.c
 *
 *  Created on: Jan 7, 2025
 *      Author: Administrator
 */

#include "Motor.h"


extern TIM_HandleTypeDef htim3;



void Motor_Stop(void){
	// Set to Stop the Motor
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
	HAL_Delay(1000);
}

void Motor_Run_Lowspeed(void){
	// Set the rotation direction
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
	//Run the motor at a slow speed
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,700);
	 HAL_Delay(2000);
}

void Motor_Run_Mediumspeed(void){
	// Set the rotation direction
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
	//Run the motor at a medium speed
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,1200);
	 HAL_Delay(2000);
}

void Motor_Run_Highspeed(void){
	// Set the rotation direction
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
	//Run the motor at a High speed
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,2000);
	 HAL_Delay(2000);
}




