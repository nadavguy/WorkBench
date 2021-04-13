/*
 * BuzzerAgent.c
 *
 *  Created on: Mar 31, 2021
 *      Author: root
 */

#include "main.h"
uint8_t buzzerPhase = 0;

float startBuzzerPhase = 0;
float currentBuzzerPhase = 0;

tBuzzer_Pattern currentPattern;
tBuzzer_Pattern *nextPattern;

tBuzzer_Pattern testBuzzerPattern;
tBuzzer_Pattern idleBuzzerPattern;
tBuzzer_Pattern armedBuzzerPattern;
tBuzzer_Pattern noBuzzerPattern;

bool isBuzzerCycleEnded = true;

void setBuzzerPattern(tBuzzer_Pattern patternToSet)
{
    currentPattern = patternToSet;
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
        HAL_GPIO_WritePin(BuzzerGPIO, BuzzerPIN, 1-currentPattern.patternOnOff[buzzerPhase - 1]);
        startBuzzerPhase = HAL_GetTick();
        buzzerPhase++;
    }
}

void initBuzzerPatterns(void)
{
	testBuzzerPattern.patternLength = 2;
	testBuzzerPattern.patternDuration[0] = 400;
	testBuzzerPattern.patternDuration[1] = 600;
	testBuzzerPattern.patternDuration[2] = 0;
	testBuzzerPattern.patternDuration[3] = 0;
	testBuzzerPattern.patternDuration[4] = 0;
	testBuzzerPattern.patternDuration[5] = 0;
	testBuzzerPattern.patternDuration[6] = 0;
	testBuzzerPattern.patternDuration[7] = 0;
	testBuzzerPattern.patternDuration[8] = 0;
	testBuzzerPattern.patternDuration[9] = 0;
	testBuzzerPattern.patternDuration[10] = 0;
	testBuzzerPattern.patternDuration[11] = 0;
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

	testBuzzerPattern.isSingleCycle = false;
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

	idleBuzzerPattern.patternOnOff[0] = 1;
	idleBuzzerPattern.patternOnOff[1] = 0;
	idleBuzzerPattern.patternOnOff[2] = 1;
	idleBuzzerPattern.patternOnOff[3] = 0;
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

	noBuzzerPattern.patternLength = 1;
	noBuzzerPattern.patternDuration[0] = 100;
	noBuzzerPattern.patternDuration[1] = 0;
	noBuzzerPattern.patternDuration[2] = 0;
	noBuzzerPattern.patternDuration[3] = 0;
	noBuzzerPattern.patternDuration[4] = 0;
	noBuzzerPattern.patternDuration[5] = 0;
	noBuzzerPattern.patternDuration[6] = 0;
	noBuzzerPattern.patternDuration[7] = 0;
	noBuzzerPattern.patternDuration[8] = 0;
	noBuzzerPattern.patternDuration[9] = 0;
	noBuzzerPattern.patternDuration[10] = 0;
	noBuzzerPattern.patternDuration[11] = 0;
	noBuzzerPattern.patternDuration[12] = 0;
	noBuzzerPattern.patternDuration[13] = 0;
	noBuzzerPattern.patternDuration[14] = 0;
	noBuzzerPattern.patternDuration[15] = 0;

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

	armedBuzzerPattern.patternOnOff[0] = 1;
	armedBuzzerPattern.patternOnOff[1] = 0;
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
}
