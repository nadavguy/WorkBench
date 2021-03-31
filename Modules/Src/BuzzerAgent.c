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
tBuzzer_Pattern testBuzzerPattern;

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
    }
    if (buzzerPhase >= currentPattern.patternLength + 1)
    {
    	buzzerPhase = 0;
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
	testBuzzerPattern.patternDuration[0] = 5800;
	testBuzzerPattern.patternDuration[1] = 200;
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

	testBuzzerPattern.patternOnOff[0] = 0;
	testBuzzerPattern.patternOnOff[1] = 1;
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
}
