/*
 * PowerAgent.c
 *
 *  Created on: Jun 3, 2021
 *      Author: gilad
 */


#include "main.h"
#include "adc.h"

uint8_t previousBatteryCharge = 0;
uint8_t cyclesAboveThresholdCounter = 0;

uint16_t currentADCMeasurementValue[3] = {0};

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
bool FirstOrSecond = false;

void measureVoltages(bool forceMeasurement)
{
	uint32_t localDeltaTime = 60000;
	if (isChargingMode)
	{
		localDeltaTime = 5 * 60 * 1000;
	}

	if (FirstOrSecond)
	{
		ADC_ChannelConfTypeDef sConfig;
		sConfig.Channel      = ADC_CHANNEL_1;                /* Sampled channel number */
		sConfig.Rank         = 1;          /* Rank of sampled channel number ADCx_CHANNEL */
		sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;    /* Sampling time (number of clock cycles unit) */
		sConfig.Offset = 0;

		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			/* Channel Configuration Error */
			Error_Handler();
		}

		if (HAL_ADC_Start(&hadc1) != HAL_OK)
		{
			/* Start Conversation Error */
			Error_Handler();
		}

		/*##-4- Wait for the end of conversion #####################################*/
		/*  For simplicity reasons, this example is just waiting till the end of the
		      conversion, but application may perform other tasks while conversion
		      operation is ongoing. */
		if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
		{
			/* End Of Conversion flag not set on time */
			Error_Handler();
		}
		else
		{
			/* ADC conversion completed */
			/*##-5- Get the converted value of regular channel  ########################*/
			currentADCMeasurementValue[0] = HAL_ADC_GetValue(&hadc1);
		}


		currentVoltages[0] = (float)(currentADCMeasurementValue[0] * 2.0 / ADCRES) * MCURefVoltage;
	}
	else
	{
		ADC_ChannelConfTypeDef sConfig;
		sConfig.Channel      = ADC_CHANNEL_4;                /* Sampled channel number */
		sConfig.Rank         = 1;          /* Rank of sampled channel number ADCx_CHANNEL */
		sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;    /* Sampling time (number of clock cycles unit) */
		sConfig.Offset = 0;
		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			/* Channel Configuration Error */
			Error_Handler();
		}

		if (HAL_ADC_Start(&hadc1) != HAL_OK)
		{
			/* Start Conversation Error */
			Error_Handler();
		}

		/*##-4- Wait for the end of conversion #####################################*/
		/*  For simplicity reasons, this example is just waiting till the end of the
		      conversion, but application may perform other tasks while conversion
		      operation is ongoing. */
		if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
		{
			/* End Of Conversion flag not set on time */
			Error_Handler();
		}
		else
		{
			/* ADC conversion completed */
			/*##-5- Get the converted value of regular channel  ########################*/
			currentADCMeasurementValue[1] = HAL_ADC_GetValue(&hadc1);
		}
		currentVoltages[1] = (float)(currentADCMeasurementValue[1] * 2.0 / ADCRES) * MCURefVoltage;


	}
	FirstOrSecond = !FirstOrSecond;
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
		//		HAL_Delay(2);
		uint32_t localTime = HAL_GetTick();
		while (HAL_GetTick() - localTime < 3)
		{
//			int a= 1;
		}
		HAL_ADC_Start_IT(&hadc3);
		memcpy(previousVoltages, currentVoltages, sizeof(currentVoltages));
		currentADCMeasurementValue[2] = HAL_ADC_GetValue(&hadc3);
		currentVoltages[2] = (float)(currentADCMeasurementValue[2] * 2.0 / ADCRES) * MCURefVoltage;
		//		sprintf(terminalBuffer,"Voltage battery: %6.3f, %d",currentVoltages[2], currentMeasurementValue[2]);
		//		logData(terminalBuffer, false, false, false);
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
			if (HAL_GetTick() > MASTERCHIEF * 1000)
			{
				ee.fullChargeCycles = ee.fullChargeCycles + 1;
			}
			currentVoltages[2] = batteryVoltage;
			ee.lastStepInCVChargeCycle = cyclesAboveThresholdCounter;
			ee_save1();
		}
		batteryVoltage = currentVoltages[2];
	}
}

int8_t convertBatteryVoltageToPercent(float inputVoltage)
{
	uint8_t ret = 0;
	if (ee.batteryType == 1)
	{
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
		else
		{
			ret = (int8_t)(85 + cyclesAboveThresholdCounter );
		}
	}

	return (ret);
}
