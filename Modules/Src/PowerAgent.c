/*
 * PowerAgent.c
 *
 *  Created on: Jun 3, 2021
 *      Author: gilad
 */


#include "main.h"
#include "adc.h"
#include "LCD_1in8.h"

uint8_t previousBatteryCharge = 0;
uint8_t cyclesAboveThresholdCounter = 0;

uint16_t currentMeasurementValue[3] = {0};

uint32_t lastVoltageMeasurement = 0;
uint32_t startChargeTime = 0;
uint32_t lastChangeInMeasurement = 0;
uint32_t ThresholdReachedTime = 0;

float currentVoltages[3] = {3.3, 5 , 4.2};
float previousVoltages[3] = {3.3, 5 , 4.2};
float ChargerMaxChargingVoltage = 4.25;

bool isChargingMode = false;
bool didCountChargeCycle = false;
bool firstMeasurementAboveThreshold = false;

void measureVoltages(bool forceMeasurement)
{
	uint32_t localDeltaTime = 60000;
	if (isChargingMode)
	{
		localDeltaTime = 5 * 60 * 1000;
	}

	HAL_ADC_Start_IT(&hadc1);
	HAL_ADC_Start_IT(&hadc2);
	currentMeasurementValue[0] = HAL_ADC_GetValue(&hadc1);
	currentMeasurementValue[1] = HAL_ADC_GetValue(&hadc2);
	currentVoltages[0] = (float)(currentMeasurementValue[0] * 2.0 / ADCRES) * MCURefVoltage;
	currentVoltages[1] = (float)(currentMeasurementValue[1] * 2.0 / ADCRES) * MCURefVoltage;

	if ( (isUSBConnected) && (currentVoltages[1] < 2) && (!isChargingMode))
	{
		isChargingMode = true;
		cyclesAboveThresholdCounter = ee.lastStepInCVChargeCycle;

	}
	else if ( (isUSBConnected) && (currentVoltages[1] >= 2))
	{
		isChargingMode = false;
		didCountChargeCycle = false;
		startChargeTime = HAL_GetTick();
	}
	else if ( (!isUSBConnected) && (ee.lastStepInCVChargeCycle != 0) )
	{
		isChargingMode = false;
		ee.lastStepInCVChargeCycle = 0;
		ee_save1();
	}

	if ( (HAL_GetTick() - lastVoltageMeasurement > localDeltaTime) || (lastVoltageMeasurement == 0) || (forceMeasurement) )
	{
		HAL_GPIO_WritePin(ChargeEnableGPIO, ChargeEnablePIN, GPIO_PIN_SET);
		HAL_ADC_Start_IT(&hadc3);
		memcpy(previousVoltages, currentVoltages, sizeof(currentVoltages));
		currentMeasurementValue[2] = HAL_ADC_GetValue(&hadc3);
		currentVoltages[2] = (float)(currentMeasurementValue[2] * 2.0 / ADCRES) * MCURefVoltage;
		if (currentVoltages[0] < 3.1)
		{
			sprintf(terminalBuffer,"Low 3.3V regulator output: %1.3f", currentVoltages[0]);
			logData(terminalBuffer, false, false, false);
		}
		if (currentVoltages[1] < 4.8)
		{
			sprintf(terminalBuffer,"Low 5.1V regulator output: %1.3f", currentVoltages[1]);
			logData(terminalBuffer, false, false, false);
		}
		batteryVoltage = currentVoltages[2];

		lastVoltageMeasurement = HAL_GetTick();
		if (isUSBConnected)
		{
			HAL_GPIO_WritePin(ChargeEnableGPIO, ChargeEnablePIN, GPIO_PIN_RESET);
		}

		//
//		if (!isChargingMode)
//		{
//			ee.lastStepInCVChargeCycle = 0;
//			ee_save1();
//		}
//		else
//		{
//			cyclesAboveThresholdCounter = ee.lastStepInCVChargeCycle;
//		}
	}
	if (isChargingMode)
	{

		if ((!didCountChargeCycle) && (currentVoltages[2] >= ChargerMaxChargingVoltage - 0.1)
				&& (!firstMeasurementAboveThreshold))
		{
			ThresholdReachedTime = HAL_GetTick();
			firstMeasurementAboveThreshold = true;
//			cyclesAboveThresholdCounter++;
			ee.lastStepInCVChargeCycle = cyclesAboveThresholdCounter;
			ee_save1();
		}

		if ( (HAL_GetTick() - ThresholdReachedTime > 5 * 60 * 1000 )
				&& (firstMeasurementAboveThreshold) && (!didCountChargeCycle))
		{
			cyclesAboveThresholdCounter++;
			ThresholdReachedTime = HAL_GetTick();
			currentVoltages[2] = (ChargerMaxChargingVoltage - 0.1) + cyclesAboveThresholdCounter * ( 1.0 / 100.0);
			lastVoltageMeasurement = HAL_GetTick();
			ee.lastStepInCVChargeCycle = cyclesAboveThresholdCounter;
			ee_save1();
		}

		if ( ( (HAL_GetTick() - ThresholdReachedTime >= 75 * 60 * 1000) || (cyclesAboveThresholdCounter >= 15) )
				&& (!didCountChargeCycle) && (currentVoltages[2] >= ChargerMaxChargingVoltage - 0.1) )
		{
			didCountChargeCycle = true;
			ee.fullChargeCycles = ee.fullChargeCycles + 1;
			currentVoltages[2] = batteryVoltage;
			ee.lastStepInCVChargeCycle = cyclesAboveThresholdCounter;
			ee_save1();
		}
		batteryVoltage = currentVoltages[2];
	}
}

int8_t convertVoltageToPercent(float inputVoltage)
{
	uint8_t ret = 0;
	if (inputVoltage <= 3.5)
	{
		ret = 0;
	}
	else if ( (inputVoltage > 3.5) && (inputVoltage <= 3.6) && (cyclesAboveThresholdCounter == 0) )
	{
		ret = (int8_t)(inputVoltage * (42.5) - 148.75);
	}
	else if ( (inputVoltage > 3.6) && (inputVoltage <= 3.8) && (cyclesAboveThresholdCounter == 0) )
	{
		ret = (int8_t)(inputVoltage * (233.75) - 837.25);
	}
	else if ( (inputVoltage > 3.8) && (inputVoltage <= 4) && (cyclesAboveThresholdCounter == 0) )
	{
		ret = (int8_t)(inputVoltage * (106.25) - 352.75);
	}
	else if ( (inputVoltage > 4) && (inputVoltage <= 4.15) && (cyclesAboveThresholdCounter == 0) )
	{
		ret = (int8_t)(inputVoltage * (85) - 267.75);
	}
	else if ( (cyclesAboveThresholdCounter >= 0) && (firstMeasurementAboveThreshold))
	{
		ret = (int8_t)(85 + cyclesAboveThresholdCounter );
	}

	return ret;
}
