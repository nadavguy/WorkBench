/*
 * PushButton.h
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#ifndef INC_PUSHBUTTON_H_
#define INC_PUSHBUTTON_H_

#define armGPIO GPIOE
#define armPIN GPIO_PIN_5

#define triggerGPIO GPIOE
#define triggerPIN GPIO_PIN_9

#define upGPIO GPIOD
#define upPIN GPIO_PIN_3

#define downGPIO GPIOD
#define downPIN GPIO_PIN_4

#define okGPIO GPIOD
#define okPIN GPIO_PIN_7

#define muxGPIO GPIOB
#define muxPIN GPIO_PIN_1

extern GPIO_PinState triggerPinState;
extern GPIO_PinState muxPinState;

extern uint32_t okButtonPressDuration;
extern uint32_t lastAnyButtonPress;

extern void startButtonsPressDetection();
extern void updateButtonsValues(uint16_t armCurrentValue, uint16_t triggerCurrentValue);
extern void CheckButtons(void);
extern void checkChargerMux(void);


#endif /* INC_PUSHBUTTON_H_ */
