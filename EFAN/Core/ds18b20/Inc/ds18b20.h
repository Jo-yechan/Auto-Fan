/*
 * ds18b20.h
 *
 *  Created on: Jan 1, 2025
 *      Author: Administrator
 */

#ifndef DS18B20_INC_DS18B20_H_
#define DS18B20_INC_DS18B20_H_

#include "main.h"


void delay (uint32_t time);

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

uint8_t DS18B20_Start (void);

void DS18B20_Write (uint8_t data);

uint8_t DS18B20_Read (void);

float DS18B20_Temperature(void);


#endif /* DS18B20_INC_DS18B20_H_ */
