/*
 * PowerAgent.h
 *
 *  Created on: Jun 3, 2021
 *      Author: gilad
 */

#ifndef INC_POWERAGENT_H_
#define INC_POWERAGENT_H_

#include "main.h"

//#define VBatGPIO GPIOA
//#define VBatPIN GPIO_PIN_3
//#define FiveVoltGPIO GPIOA
//#define FiveVoltPIN GPIO_PIN_2
//#define ThreePointThreeGPIO GPIOA
//#define ThreePointThreePIN GPIO_PIN_1
#define ChargeEnableGPIO GPIOE
#define ChargeEnablePIN GPIO_PIN_1
#define ADCRES 4096

extern void measureVoltages(void);

#endif /* INC_POWERAGENT_H_ */
