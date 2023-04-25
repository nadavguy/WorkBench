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

tBuzzer_Pattern currentPattern = {0};
tBuzzer_Pattern *nextPattern;

tBuzzer_Pattern testBuzzerPattern = {0};
tBuzzer_Pattern idleBuzzerPattern = {0};
tBuzzer_Pattern armedBuzzerPattern = {0};
tBuzzer_Pattern noBuzzerPattern = {0};
tBuzzer_Pattern noTelemetryBuzzerPattern = {0};
tBuzzer_Pattern lowTelemetryBuzzerPattern = {0};
tBuzzer_Pattern lowRCBatteryBuzzerPattern = {0};
tBuzzer_Pattern triggeredBuzzerPattern = {0};


bool isBuzzerCycleEnded = true;

void setBuzzerPattern(tBuzzer_Pattern patternToSet)
{
    if (currentPattern.id == triggeredBuzzerPattern.id)
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

void updateBuzzerPattern(void)
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


	noTelemetryBuzzerPattern.patternLength = 6;
	noTelemetryBuzzerPattern.patternDuration[0] = 100;
	noTelemetryBuzzerPattern.patternDuration[1] = 100;
	noTelemetryBuzzerPattern.patternDuration[2] = 100;
	noTelemetryBuzzerPattern.patternDuration[3] = 100;
	noTelemetryBuzzerPattern.patternDuration[4] = 100;
	noTelemetryBuzzerPattern.patternDuration[5] = 4500;
	noTelemetryBuzzerPattern.patternDuration[6] = 0;
	noTelemetryBuzzerPattern.patternDuration[7] = 0;
	noTelemetryBuzzerPattern.patternDuration[8] = 0;
	noTelemetryBuzzerPattern.patternDuration[9] = 0;
	noTelemetryBuzzerPattern.patternDuration[10] = 0;
	noTelemetryBuzzerPattern.patternDuration[11] = 0;
	noTelemetryBuzzerPattern.patternDuration[12] = 0;
	noTelemetryBuzzerPattern.patternDuration[13] = 0;
	noTelemetryBuzzerPattern.patternDuration[14] = 0;
	noTelemetryBuzzerPattern.patternDuration[15] = 0;

	noTelemetryBuzzerPattern.patternOnOff[0] = 1; //On
	noTelemetryBuzzerPattern.patternOnOff[1] = 0; //Off
	noTelemetryBuzzerPattern.patternOnOff[2] = 1;
	noTelemetryBuzzerPattern.patternOnOff[3] = 0;
	noTelemetryBuzzerPattern.patternOnOff[4] = 1;
	noTelemetryBuzzerPattern.patternOnOff[5] = 0;
	noTelemetryBuzzerPattern.patternOnOff[6] = 0;
	noTelemetryBuzzerPattern.patternOnOff[7] = 0;
	noTelemetryBuzzerPattern.patternOnOff[8] = 0;
	noTelemetryBuzzerPattern.patternOnOff[9] = 0;
	noTelemetryBuzzerPattern.patternOnOff[10] = 0;
	noTelemetryBuzzerPattern.patternOnOff[11] = 0;
	noTelemetryBuzzerPattern.patternOnOff[12] = 0;
	noTelemetryBuzzerPattern.patternOnOff[13] = 0;
	noTelemetryBuzzerPattern.patternOnOff[14] = 0;
	noTelemetryBuzzerPattern.patternOnOff[15] = 0;

	noTelemetryBuzzerPattern.isSingleCycle = false;
	noTelemetryBuzzerPattern.id = 5;


	lowTelemetryBuzzerPattern.patternLength = 6;
	lowTelemetryBuzzerPattern.patternDuration[0] = 300;
	lowTelemetryBuzzerPattern.patternDuration[1] = 100;
	lowTelemetryBuzzerPattern.patternDuration[2] = 300;
	lowTelemetryBuzzerPattern.patternDuration[3] = 100;
	lowTelemetryBuzzerPattern.patternDuration[4] = 300;
	lowTelemetryBuzzerPattern.patternDuration[5] = 3900;
	lowTelemetryBuzzerPattern.patternDuration[6] = 0;
	lowTelemetryBuzzerPattern.patternDuration[7] = 0;
	lowTelemetryBuzzerPattern.patternDuration[8] = 0;
	lowTelemetryBuzzerPattern.patternDuration[9] = 0;
	lowTelemetryBuzzerPattern.patternDuration[10] = 0;
	lowTelemetryBuzzerPattern.patternDuration[11] = 0;
	lowTelemetryBuzzerPattern.patternDuration[12] = 0;
	lowTelemetryBuzzerPattern.patternDuration[13] = 0;
	lowTelemetryBuzzerPattern.patternDuration[14] = 0;
	lowTelemetryBuzzerPattern.patternDuration[15] = 0;

	lowTelemetryBuzzerPattern.patternOnOff[0] = 1; //On
	lowTelemetryBuzzerPattern.patternOnOff[1] = 0; //Off
	lowTelemetryBuzzerPattern.patternOnOff[2] = 1;
	lowTelemetryBuzzerPattern.patternOnOff[3] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[4] = 1;
	lowTelemetryBuzzerPattern.patternOnOff[5] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[6] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[7] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[8] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[9] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[10] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[11] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[12] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[13] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[14] = 0;
	lowTelemetryBuzzerPattern.patternOnOff[15] = 0;

	lowTelemetryBuzzerPattern.isSingleCycle = false;
	lowTelemetryBuzzerPattern.id = 6;


	lowRCBatteryBuzzerPattern.patternLength = 2;
	lowRCBatteryBuzzerPattern.patternDuration[0] = 200;
	lowRCBatteryBuzzerPattern.patternDuration[1] = 19800;
	lowRCBatteryBuzzerPattern.patternDuration[2] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[3] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[4] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[5] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[6] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[7] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[8] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[9] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[10] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[11] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[12] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[13] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[14] = 0;
	lowRCBatteryBuzzerPattern.patternDuration[15] = 0;

	lowRCBatteryBuzzerPattern.patternOnOff[0] = 1; //On
	lowRCBatteryBuzzerPattern.patternOnOff[1] = 0; //Off
	lowRCBatteryBuzzerPattern.patternOnOff[2] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[3] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[4] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[5] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[6] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[7] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[8] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[9] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[10] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[11] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[12] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[13] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[14] = 0;
	lowRCBatteryBuzzerPattern.patternOnOff[15] = 0;

	lowRCBatteryBuzzerPattern.isSingleCycle = false;
	lowRCBatteryBuzzerPattern.id = 7;


	triggeredBuzzerPattern.patternLength = 16;
	triggeredBuzzerPattern.patternDuration[0] = 200;
	triggeredBuzzerPattern.patternDuration[1] = 180;
	triggeredBuzzerPattern.patternDuration[2] = 180;
	triggeredBuzzerPattern.patternDuration[3] = 160;
	triggeredBuzzerPattern.patternDuration[4] = 160;
	triggeredBuzzerPattern.patternDuration[5] = 140;
	triggeredBuzzerPattern.patternDuration[6] = 140;
	triggeredBuzzerPattern.patternDuration[7] = 120;
	triggeredBuzzerPattern.patternDuration[8] = 120;
	triggeredBuzzerPattern.patternDuration[9] = 100;
	triggeredBuzzerPattern.patternDuration[10] = 100;
	triggeredBuzzerPattern.patternDuration[11] = 80;
	triggeredBuzzerPattern.patternDuration[12] = 80;
	triggeredBuzzerPattern.patternDuration[13] = 60;
	triggeredBuzzerPattern.patternDuration[14] = 60;
	triggeredBuzzerPattern.patternDuration[15] = 40;

	triggeredBuzzerPattern.patternOnOff[0] = 1; //On
	triggeredBuzzerPattern.patternOnOff[1] = 0; //Off
	triggeredBuzzerPattern.patternOnOff[2] = 1;
	triggeredBuzzerPattern.patternOnOff[3] = 0;
	triggeredBuzzerPattern.patternOnOff[4] = 1;
	triggeredBuzzerPattern.patternOnOff[5] = 0;
	triggeredBuzzerPattern.patternOnOff[6] = 1;
	triggeredBuzzerPattern.patternOnOff[7] = 0;
	triggeredBuzzerPattern.patternOnOff[8] = 1;
	triggeredBuzzerPattern.patternOnOff[9] = 0;
	triggeredBuzzerPattern.patternOnOff[10] = 1;
	triggeredBuzzerPattern.patternOnOff[11] = 0;
	triggeredBuzzerPattern.patternOnOff[12] = 1;
	triggeredBuzzerPattern.patternOnOff[13] = 0;
	triggeredBuzzerPattern.patternOnOff[14] = 1;
	triggeredBuzzerPattern.patternOnOff[15] = 0;

	triggeredBuzzerPattern.isSingleCycle = false;
	triggeredBuzzerPattern.id = 8;
}
