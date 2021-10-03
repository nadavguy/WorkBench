/*
 * BuzzerAgent.c
 *
 *  Created on: Mar 31, 2021
 *      Author: root
 */

#include "main.h"
uint8_t buzzerPhase = 0;
uint8_t cycleCounter = 0;

float startBuzzerPhase = 0;
float currentBuzzerPhase = 0;

tBuzzer_Pattern currentPattern;
tBuzzer_Pattern *nextPattern;

tBuzzer_Pattern testBuzzerPattern;
tBuzzer_Pattern idleBuzzerPattern;
tBuzzer_Pattern armedBuzzerPattern;
tBuzzer_Pattern noBuzzerPattern;
tBuzzer_Pattern noTelemetryPattern;
tBuzzer_Pattern lowTelemetryPattern;
tBuzzer_Pattern lowRCBatteryPattern;
tBuzzer_Pattern triggeredSafeAirPattern;

bool isBuzzerCycleEnded = true;

void setBuzzerPattern(tBuzzer_Pattern patternToSet)
{
    if (currentPattern.id == 8)
    {
    	cycleCounter++;
    }

    if (cycleCounter >= 5)
    {
    	currentPattern = noBuzzerPattern;
    }
    else
    {
    	currentPattern = patternToSet;
    }
    buzzerPhase = 0;
}

void updateBuzzerStatus(void)
{
    if (buzzerPhase == 0)
    {
        startBuzzerPhase = HAL_GetTick();
        buzzerPhase++;
        if (currentPattern.id != noBuzzerPattern.id)
        {
        	isBuzzerCycleEnded = false;
        }
        else
        {
        	isBuzzerCycleEnded = true;
        }
    }
    if (buzzerPhase >= currentPattern.patternLength + 1)
    {
    	buzzerPhase = 0;
    	isBuzzerCycleEnded = true;
    	if (currentPattern.isSingleCycle)
    	{
    		nextPattern = &noBuzzerPattern;
    		setBuzzerPattern(noBuzzerPattern);
    	}
    	else
    	{
    		setBuzzerPattern(*nextPattern);
    	}
        return;
    }
    if (HAL_GetTick() - startBuzzerPhase > currentPattern.patternDuration[buzzerPhase - 1])
    {
        startBuzzerPhase = HAL_GetTick();
        buzzerPhase++;
    }
    else
    {
    	HAL_GPIO_WritePin(BuzzerGPIO, BuzzerPIN, currentPattern.patternOnOff[buzzerPhase - 1]);
    }
}

void initBuzzerPatterns(void)
{
	testBuzzerPattern.patternLength = 2;
	testBuzzerPattern.patternDuration[0] = 400;
	testBuzzerPattern.patternDuration[1] = 400;
	testBuzzerPattern.patternDuration[2] = 125;
	testBuzzerPattern.patternDuration[3] = 125;
	testBuzzerPattern.patternDuration[4] = 125;
	testBuzzerPattern.patternDuration[5] = 125;
	testBuzzerPattern.patternDuration[6] = 125;
	testBuzzerPattern.patternDuration[7] = 125;
	testBuzzerPattern.patternDuration[8] = 125;
	testBuzzerPattern.patternDuration[9] = 125;
	testBuzzerPattern.patternDuration[10] = 1000;
	testBuzzerPattern.patternDuration[11] = 1000;
	testBuzzerPattern.patternDuration[12] = 0;
	testBuzzerPattern.patternDuration[13] = 0;
	testBuzzerPattern.patternDuration[14] = 0;
	testBuzzerPattern.patternDuration[15] = 0;

	testBuzzerPattern.patternOnOff[0] = 1;
	testBuzzerPattern.patternOnOff[1] = 0;
	testBuzzerPattern.patternOnOff[2] = 0;
	testBuzzerPattern.patternOnOff[3] = 0;
	testBuzzerPattern.patternOnOff[4] = 0;
	testBuzzerPattern.patternOnOff[5] = 0;
	testBuzzerPattern.patternOnOff[6] = 0;
	testBuzzerPattern.patternOnOff[7] = 0;
	testBuzzerPattern.patternOnOff[8] = 0;
	testBuzzerPattern.patternOnOff[9] = 0;
	testBuzzerPattern.patternOnOff[10] = 0;
	testBuzzerPattern.patternOnOff[11] = 0;
	testBuzzerPattern.patternOnOff[12] = 0;
	testBuzzerPattern.patternOnOff[13] = 0;
	testBuzzerPattern.patternOnOff[14] = 0;
	testBuzzerPattern.patternOnOff[15] = 0;

	testBuzzerPattern.isSingleCycle = true;
	testBuzzerPattern.id = 1;

	idleBuzzerPattern.patternLength = 4;
	idleBuzzerPattern.patternDuration[0] = 200;
	idleBuzzerPattern.patternDuration[1] = 200;
	idleBuzzerPattern.patternDuration[2] = 200;
	idleBuzzerPattern.patternDuration[3] = 200;
	idleBuzzerPattern.patternDuration[4] = 0;
	idleBuzzerPattern.patternDuration[5] = 0;
	idleBuzzerPattern.patternDuration[6] = 0;
	idleBuzzerPattern.patternDuration[7] = 0;
	idleBuzzerPattern.patternDuration[8] = 0;
	idleBuzzerPattern.patternDuration[9] = 0;
	idleBuzzerPattern.patternDuration[10] = 0;
	idleBuzzerPattern.patternDuration[11] = 0;
	idleBuzzerPattern.patternDuration[12] = 0;
	idleBuzzerPattern.patternDuration[13] = 0;
	idleBuzzerPattern.patternDuration[14] = 0;
	idleBuzzerPattern.patternDuration[15] = 0;

	idleBuzzerPattern.patternOnOff[0] = 0;
	idleBuzzerPattern.patternOnOff[1] = 1;
	idleBuzzerPattern.patternOnOff[2] = 0;
	idleBuzzerPattern.patternOnOff[3] = 1;
	idleBuzzerPattern.patternOnOff[4] = 0;
	idleBuzzerPattern.patternOnOff[5] = 0;
	idleBuzzerPattern.patternOnOff[6] = 0;
	idleBuzzerPattern.patternOnOff[7] = 0;
	idleBuzzerPattern.patternOnOff[8] = 0;
	idleBuzzerPattern.patternOnOff[9] = 0;
	idleBuzzerPattern.patternOnOff[10] = 0;
	idleBuzzerPattern.patternOnOff[11] = 0;
	idleBuzzerPattern.patternOnOff[12] = 0;
	idleBuzzerPattern.patternOnOff[13] = 0;
	idleBuzzerPattern.patternOnOff[14] = 0;
	idleBuzzerPattern.patternOnOff[15] = 0;

	idleBuzzerPattern.isSingleCycle = true;
	idleBuzzerPattern.id = 2;

	noBuzzerPattern.patternLength = 16;
	noBuzzerPattern.patternDuration[0] = 100;
	noBuzzerPattern.patternDuration[1] = 100;
	noBuzzerPattern.patternDuration[2] = 100;
	noBuzzerPattern.patternDuration[3] = 100;
	noBuzzerPattern.patternDuration[4] = 100;
	noBuzzerPattern.patternDuration[5] = 100;
	noBuzzerPattern.patternDuration[6] = 100;
	noBuzzerPattern.patternDuration[7] = 100;
	noBuzzerPattern.patternDuration[8] = 100;
	noBuzzerPattern.patternDuration[9] = 100;
	noBuzzerPattern.patternDuration[10] = 100;
	noBuzzerPattern.patternDuration[11] = 100;
	noBuzzerPattern.patternDuration[12] = 100;
	noBuzzerPattern.patternDuration[13] = 100;
	noBuzzerPattern.patternDuration[14] = 100;
	noBuzzerPattern.patternDuration[15] = 100;

	noBuzzerPattern.patternOnOff[0] = 0;
	noBuzzerPattern.patternOnOff[1] = 0;
	noBuzzerPattern.patternOnOff[2] = 0;
	noBuzzerPattern.patternOnOff[3] = 0;
	noBuzzerPattern.patternOnOff[4] = 0;
	noBuzzerPattern.patternOnOff[5] = 0;
	noBuzzerPattern.patternOnOff[6] = 0;
	noBuzzerPattern.patternOnOff[7] = 0;
	noBuzzerPattern.patternOnOff[8] = 0;
	noBuzzerPattern.patternOnOff[9] = 0;
	noBuzzerPattern.patternOnOff[10] = 0;
	noBuzzerPattern.patternOnOff[11] = 0;
	noBuzzerPattern.patternOnOff[12] = 0;
	noBuzzerPattern.patternOnOff[13] = 0;
	noBuzzerPattern.patternOnOff[14] = 0;
	noBuzzerPattern.patternOnOff[15] = 0;

	noBuzzerPattern.isSingleCycle = false;
	noBuzzerPattern.id = 3;

	armedBuzzerPattern.patternLength = 2;
	armedBuzzerPattern.patternDuration[0] = 200;
	armedBuzzerPattern.patternDuration[1] = 200;
	armedBuzzerPattern.patternDuration[2] = 0;
	armedBuzzerPattern.patternDuration[3] = 0;
	armedBuzzerPattern.patternDuration[4] = 0;
	armedBuzzerPattern.patternDuration[5] = 0;
	armedBuzzerPattern.patternDuration[6] = 0;
	armedBuzzerPattern.patternDuration[7] = 0;
	armedBuzzerPattern.patternDuration[8] = 0;
	armedBuzzerPattern.patternDuration[9] = 0;
	armedBuzzerPattern.patternDuration[10] = 0;
	armedBuzzerPattern.patternDuration[11] = 0;
	armedBuzzerPattern.patternDuration[12] = 0;
	armedBuzzerPattern.patternDuration[13] = 0;
	armedBuzzerPattern.patternDuration[14] = 0;
	armedBuzzerPattern.patternDuration[15] = 0;

	armedBuzzerPattern.patternOnOff[0] = 0;
	armedBuzzerPattern.patternOnOff[1] = 1;
	armedBuzzerPattern.patternOnOff[2] = 0;
	armedBuzzerPattern.patternOnOff[3] = 0;
	armedBuzzerPattern.patternOnOff[4] = 0;
	armedBuzzerPattern.patternOnOff[5] = 0;
	armedBuzzerPattern.patternOnOff[6] = 0;
	armedBuzzerPattern.patternOnOff[7] = 0;
	armedBuzzerPattern.patternOnOff[8] = 0;
	armedBuzzerPattern.patternOnOff[9] = 0;
	armedBuzzerPattern.patternOnOff[10] = 0;
	armedBuzzerPattern.patternOnOff[11] = 0;
	armedBuzzerPattern.patternOnOff[12] = 0;
	armedBuzzerPattern.patternOnOff[13] = 0;
	armedBuzzerPattern.patternOnOff[14] = 0;
	armedBuzzerPattern.patternOnOff[15] = 0;

	armedBuzzerPattern.isSingleCycle = true;
	armedBuzzerPattern.id = 4;


	noTelemetryPattern.patternLength = 6;
	noTelemetryPattern.patternDuration[0] = 100;
	noTelemetryPattern.patternDuration[1] = 100;
	noTelemetryPattern.patternDuration[2] = 100;
	noTelemetryPattern.patternDuration[3] = 100;
	noTelemetryPattern.patternDuration[4] = 100;
	noTelemetryPattern.patternDuration[5] = 4500;
	noTelemetryPattern.patternDuration[6] = 0;
	noTelemetryPattern.patternDuration[7] = 0;
	noTelemetryPattern.patternDuration[8] = 0;
	noTelemetryPattern.patternDuration[9] = 0;
	noTelemetryPattern.patternDuration[10] = 0;
	noTelemetryPattern.patternDuration[11] = 0;
	noTelemetryPattern.patternDuration[12] = 0;
	noTelemetryPattern.patternDuration[13] = 0;
	noTelemetryPattern.patternDuration[14] = 0;
	noTelemetryPattern.patternDuration[15] = 0;

	noTelemetryPattern.patternOnOff[0] = 1; //On
	noTelemetryPattern.patternOnOff[1] = 0; //Off
	noTelemetryPattern.patternOnOff[2] = 1;
	noTelemetryPattern.patternOnOff[3] = 0;
	noTelemetryPattern.patternOnOff[4] = 1;
	noTelemetryPattern.patternOnOff[5] = 0;
	noTelemetryPattern.patternOnOff[6] = 0;
	noTelemetryPattern.patternOnOff[7] = 0;
	noTelemetryPattern.patternOnOff[8] = 0;
	noTelemetryPattern.patternOnOff[9] = 0;
	noTelemetryPattern.patternOnOff[10] = 0;
	noTelemetryPattern.patternOnOff[11] = 0;
	noTelemetryPattern.patternOnOff[12] = 0;
	noTelemetryPattern.patternOnOff[13] = 0;
	noTelemetryPattern.patternOnOff[14] = 0;
	noTelemetryPattern.patternOnOff[15] = 0;

	noTelemetryPattern.isSingleCycle = false;
	noTelemetryPattern.id = 5;


	lowTelemetryPattern.patternLength = 6;
	lowTelemetryPattern.patternDuration[0] = 300;
	lowTelemetryPattern.patternDuration[1] = 100;
	lowTelemetryPattern.patternDuration[2] = 300;
	lowTelemetryPattern.patternDuration[3] = 100;
	lowTelemetryPattern.patternDuration[4] = 300;
	lowTelemetryPattern.patternDuration[5] = 3900;
	lowTelemetryPattern.patternDuration[6] = 0;
	lowTelemetryPattern.patternDuration[7] = 0;
	lowTelemetryPattern.patternDuration[8] = 0;
	lowTelemetryPattern.patternDuration[9] = 0;
	lowTelemetryPattern.patternDuration[10] = 0;
	lowTelemetryPattern.patternDuration[11] = 0;
	lowTelemetryPattern.patternDuration[12] = 0;
	lowTelemetryPattern.patternDuration[13] = 0;
	lowTelemetryPattern.patternDuration[14] = 0;
	lowTelemetryPattern.patternDuration[15] = 0;

	lowTelemetryPattern.patternOnOff[0] = 1; //On
	lowTelemetryPattern.patternOnOff[1] = 0; //Off
	lowTelemetryPattern.patternOnOff[2] = 1;
	lowTelemetryPattern.patternOnOff[3] = 0;
	lowTelemetryPattern.patternOnOff[4] = 1;
	lowTelemetryPattern.patternOnOff[5] = 0;
	lowTelemetryPattern.patternOnOff[6] = 0;
	lowTelemetryPattern.patternOnOff[7] = 0;
	lowTelemetryPattern.patternOnOff[8] = 0;
	lowTelemetryPattern.patternOnOff[9] = 0;
	lowTelemetryPattern.patternOnOff[10] = 0;
	lowTelemetryPattern.patternOnOff[11] = 0;
	lowTelemetryPattern.patternOnOff[12] = 0;
	lowTelemetryPattern.patternOnOff[13] = 0;
	lowTelemetryPattern.patternOnOff[14] = 0;
	lowTelemetryPattern.patternOnOff[15] = 0;

	lowTelemetryPattern.isSingleCycle = false;
	lowTelemetryPattern.id = 6;


	lowRCBatteryPattern.patternLength = 2;
	lowRCBatteryPattern.patternDuration[0] = 200;
	lowRCBatteryPattern.patternDuration[1] = 19800;
	lowRCBatteryPattern.patternDuration[2] = 0;
	lowRCBatteryPattern.patternDuration[3] = 0;
	lowRCBatteryPattern.patternDuration[4] = 0;
	lowRCBatteryPattern.patternDuration[5] = 0;
	lowRCBatteryPattern.patternDuration[6] = 0;
	lowRCBatteryPattern.patternDuration[7] = 0;
	lowRCBatteryPattern.patternDuration[8] = 0;
	lowRCBatteryPattern.patternDuration[9] = 0;
	lowRCBatteryPattern.patternDuration[10] = 0;
	lowRCBatteryPattern.patternDuration[11] = 0;
	lowRCBatteryPattern.patternDuration[12] = 0;
	lowRCBatteryPattern.patternDuration[13] = 0;
	lowRCBatteryPattern.patternDuration[14] = 0;
	lowRCBatteryPattern.patternDuration[15] = 0;

	lowRCBatteryPattern.patternOnOff[0] = 1; //On
	lowRCBatteryPattern.patternOnOff[1] = 0; //Off
	lowRCBatteryPattern.patternOnOff[2] = 0;
	lowRCBatteryPattern.patternOnOff[3] = 0;
	lowRCBatteryPattern.patternOnOff[4] = 0;
	lowRCBatteryPattern.patternOnOff[5] = 0;
	lowRCBatteryPattern.patternOnOff[6] = 0;
	lowRCBatteryPattern.patternOnOff[7] = 0;
	lowRCBatteryPattern.patternOnOff[8] = 0;
	lowRCBatteryPattern.patternOnOff[9] = 0;
	lowRCBatteryPattern.patternOnOff[10] = 0;
	lowRCBatteryPattern.patternOnOff[11] = 0;
	lowRCBatteryPattern.patternOnOff[12] = 0;
	lowRCBatteryPattern.patternOnOff[13] = 0;
	lowRCBatteryPattern.patternOnOff[14] = 0;
	lowRCBatteryPattern.patternOnOff[15] = 0;

	lowRCBatteryPattern.isSingleCycle = false;
	lowRCBatteryPattern.id = 7;


	triggeredSafeAirPattern.patternLength = 16;
	triggeredSafeAirPattern.patternDuration[0] = 200;
	triggeredSafeAirPattern.patternDuration[1] = 180;
	triggeredSafeAirPattern.patternDuration[2] = 180;
	triggeredSafeAirPattern.patternDuration[3] = 160;
	triggeredSafeAirPattern.patternDuration[4] = 160;
	triggeredSafeAirPattern.patternDuration[5] = 140;
	triggeredSafeAirPattern.patternDuration[6] = 140;
	triggeredSafeAirPattern.patternDuration[7] = 120;
	triggeredSafeAirPattern.patternDuration[8] = 120;
	triggeredSafeAirPattern.patternDuration[9] = 100;
	triggeredSafeAirPattern.patternDuration[10] = 100;
	triggeredSafeAirPattern.patternDuration[11] = 80;
	triggeredSafeAirPattern.patternDuration[12] = 80;
	triggeredSafeAirPattern.patternDuration[13] = 60;
	triggeredSafeAirPattern.patternDuration[14] = 60;
	triggeredSafeAirPattern.patternDuration[15] = 40;

	triggeredSafeAirPattern.patternOnOff[0] = 1; //On
	triggeredSafeAirPattern.patternOnOff[1] = 0; //Off
	triggeredSafeAirPattern.patternOnOff[2] = 1;
	triggeredSafeAirPattern.patternOnOff[3] = 0;
	triggeredSafeAirPattern.patternOnOff[4] = 1;
	triggeredSafeAirPattern.patternOnOff[5] = 0;
	triggeredSafeAirPattern.patternOnOff[6] = 1;
	triggeredSafeAirPattern.patternOnOff[7] = 0;
	triggeredSafeAirPattern.patternOnOff[8] = 1;
	triggeredSafeAirPattern.patternOnOff[9] = 0;
	triggeredSafeAirPattern.patternOnOff[10] = 1;
	triggeredSafeAirPattern.patternOnOff[11] = 0;
	triggeredSafeAirPattern.patternOnOff[12] = 1;
	triggeredSafeAirPattern.patternOnOff[13] = 0;
	triggeredSafeAirPattern.patternOnOff[14] = 1;
	triggeredSafeAirPattern.patternOnOff[15] = 0;

	triggeredSafeAirPattern.isSingleCycle = false;
	triggeredSafeAirPattern.id = 8;
}
