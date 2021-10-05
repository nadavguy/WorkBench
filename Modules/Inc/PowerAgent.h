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
extern bool isChargingMode;
extern bool firstMeasurementAboveThreshold;
extern bool didCountChargeCycle;

extern uint8_t previousBatteryCharge;
extern uint8_t cyclesAboveThresholdCounter;

extern uint32_t startChargeTime;
extern uint32_t lastChangeInMeasurement;

extern void measureVoltages(bool forceMeasurement);
extern int8_t convertVoltageToPercent(float inputVoltage);

#endif /* INC_POWERAGENT_H_ */
