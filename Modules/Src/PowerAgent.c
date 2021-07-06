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

uint16_t currentMeasurementValue[3] = {0};

uint32_t lastVoltageMeasurement = 0;
uint32_t startChargeTime = 0;
uint32_t lastChangeInMeasurement = 0;

float currentVoltages[3] = {3.3, 5 , 4.2};
float previousVoltages[3] = {3.3, 5 , 4.2};
bool isChargingMode = false;
bool didCountChargeCycle = false;

void measureVoltages(bool forceMeasurement)
{
	uint32_t localDeltaTime = 60000;
	if (isChargingMode)
	{
		localDeltaTime = 2000;
	}
	if ( (HAL_GetTick() - lastVoltageMeasurement > localDeltaTime) || (lastVoltageMeasurement == 0) || (forceMeasurement) )
	{
		HAL_GPIO_WritePin(ChargeEnableGPIO, ChargeEnablePIN, GPIO_PIN_SET);
		HAL_ADC_Start_IT(&hadc1);
		HAL_ADC_Start_IT(&hadc2);
		HAL_ADC_Start_IT(&hadc3);
		//	  previousVoltages = currentVoltages;
		memcpy(previousVoltages, currentVoltages, sizeof(currentVoltages));

//		HAL_Delay(1);
		currentMeasurementValue[0] = HAL_ADC_GetValue(&hadc1);
		currentMeasurementValue[1] = HAL_ADC_GetValue(&hadc2);
		currentMeasurementValue[2] = HAL_ADC_GetValue(&hadc3);

		currentVoltages[0] = (float)(currentMeasurementValue[0] * 2.0 / ADCRES) * MCURefVoltage;
		currentVoltages[1] = (float)(currentMeasurementValue[1] * 2.0 / ADCRES) * MCURefVoltage;
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
		//	  if (currentVoltages[0] < 3.1)
		//	  {
		//	  }

		lastVoltageMeasurement = HAL_GetTick();
		if (isUSBConnected)
		{
			HAL_GPIO_WritePin(ChargeEnableGPIO, ChargeEnablePIN, GPIO_PIN_RESET);
			if (currentVoltages[1] < 2)
			{
				isChargingMode = true;
				if ( (HAL_GetTick() - startChargeTime > 45 * 60 * 1000) && (!didCountChargeCycle) && (didCountChargeCycle >= 4.1) )
				{
					didCountChargeCycle = true;
					ee.fullChargeCycles = ee.fullChargeCycles + 1;
					ee_save1();
				}
			}
			else
			{
				isChargingMode = false;
				didCountChargeCycle = true;
				startChargeTime = HAL_GetTick();
				LCD_1IN8_SetBackLight(ee.backLight * 2000);
			}
		}
	}
}
