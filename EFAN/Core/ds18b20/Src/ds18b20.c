/*
 * ds18b20.c
 *
 *  Created on: Jan 1, 2025
 *      Author: Administrator
 */

#include "ds18b20.h"
#include "stm32f1xx_hal_tim.h"

#define DS18B20_PORT GPIOA
#define DS18B20_PIN GPIO_PIN_1

extern TIM_HandleTypeDef htim1;

uint8_t presence = 0;
uint8_t Temp_byte1, Temp_byte2;
uint16_t TEMP;
float Temperature = 0;

void delay (uint32_t time)
{
    __HAL_TIM_SET_COUNTER(&htim1,0);
    while ((__HAL_TIM_GET_COUNTER(&htim1))<time);
}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

uint8_t DS18B20_Start (void)
{
	uint8_t Response = 0;
	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);   // set the pin as output
	HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);  // pull the pin low
	delay (480);   // delay according to datasheet

	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
    delay (80);    // delay according to datasheet
	if (!(HAL_GPIO_ReadPin (DS18B20_PORT, DS18B20_PIN))) Response = 1;    // if the pin is low i.e the presence pulse is detected
	else Response = -1;

	delay (400); // 480 us delay totally.

	return Response;
}

void DS18B20_Write (uint8_t data)
{
	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // set as output

	for (int i=0; i<8; i++)
	{
		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1
			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // set as output
			HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);  // pull the pin LOW
			delay (1);  // wait for 1 us

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);  // set as input
			delay (50);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0
			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);
			HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);  // pull the pin LOW
			delay (50);  // wait for 60 us

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
		}
	}
}


uint8_t DS18B20_Read (void){
	uint8_t value = 0;

	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);

	for (int i=0;i<8;i++){
		Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);

		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN,0);
		delay(2);

		Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
		if (HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)){
			value |= 1<<i;
		}
		delay(60);
	}
	return value;
}

float DS18B20_Temperature(void){
	      presence = DS18B20_Start();
		  HAL_Delay(1);
		  DS18B20_Write(0xCC);
		  DS18B20_Write(0x44);
		  HAL_Delay(800);

		  presence = DS18B20_Start();
		  HAL_Delay(1);
		  DS18B20_Write(0xCC);
		  DS18B20_Write(0xBE);

		  Temp_byte1 = DS18B20_Read();
		  Temp_byte2 = DS18B20_Read();
		  TEMP = (Temp_byte2<<8)|Temp_byte1;
		  Temperature = (float)TEMP/16;

		  HAL_Delay(3000);

		  return Temperature;

}
