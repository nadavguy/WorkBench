/*
 * BuzzerAgent.h
 *
 *  Created on: Mar 31, 2021
 *      Author: root
 */

#ifndef INC_BUZZERAGENT_H_
#define INC_BUZZERAGENT_H_

#define BuzzerGPIO GPIOE
#define BuzzerPIN GPIO_PIN_0

typedef struct sBuzzer_Pattern
{
    uint8_t patternLength;
    uint16_t patternOnOff[16];
    uint16_t patternDuration[16];
    bool isSingleCycle;
    uint8_t id;
}tBuzzer_Pattern;

extern uint8_t buzzerPhase;

extern float startBuzzerPhase;
extern float currentBuzzerPhase;

extern tBuzzer_Pattern currentPattern;
extern tBuzzer_Pattern *nextPattern;

extern tBuzzer_Pattern testBuzzerPattern;
extern tBuzzer_Pattern idleBuzzerPattern;
extern tBuzzer_Pattern armedBuzzerPattern;
extern tBuzzer_Pattern noBuzzerPattern;
extern tBuzzer_Pattern noTelemetryPattern;
extern tBuzzer_Pattern lowTelemetryPattern;
extern tBuzzer_Pattern lowRCBatteryPattern;
extern tBuzzer_Pattern triggeredSafeAirPattern;

extern bool isBuzzerCycleEnded;

extern void setBuzzerPattern(tBuzzer_Pattern patternToSet);
extern void updateBuzzerStatus(void);
extern void initBuzzerPatterns(void);


#endif /* INC_BUZZERAGENT_H_ */
