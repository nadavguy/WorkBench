/*
 * BuzzerAgent.h
 *
 *  Created on: Mar 31, 2021
 *      Author: root
 */

#ifndef INC_BUZZERAGENT_H_
#define INC_BUZZERAGENT_H_

#define BuzzerGPIO GPIOB
#define BuzzerPIN GPIO_PIN_11

typedef struct sBuzzer_Pattern
{
    uint8_t patternLength;
    uint8_t patternOnOff[16];
    uint16_t patternDuration[16];
}tBuzzer_Pattern;

extern uint8_t buzzerPhase;

extern float startBuzzerPhase;
extern float currentBuzzerPhase;

extern bool isBuzzerCycleEnded;

extern tBuzzer_Pattern currentPattern;
extern tBuzzer_Pattern testBuzzerPattern;

extern void setBuzzerPattern(tBuzzer_Pattern patternToSet);
extern void updateBuzzerStatus(void);
extern void initBuzzerPatterns(void);


#endif /* INC_BUZZERAGENT_H_ */
