/*
 * PushButton.h
 *
 *  Created on: Mar 22, 2021
 *      Author: gilad
 */

#ifndef INC_PUSHBUTTON_H_
#define INC_PUSHBUTTON_H_

#define armGPIO GPIOE
#define armPIN GPIO_PIN_11

#define triggerGPIO GPIOE
#define triggerPIN GPIO_PIN_9

#define upGPIO GPIOC
#define upPIN GPIO_PIN_11

#define downGPIO GPIOC
#define downPIN GPIO_PIN_10

#define okGPIO GPIOC
#define okPIN GPIO_PIN_9

extern uint32_t okButtonPressDuration;

extern void startButtonsPressDetection();
extern void updateButtonsValues(uint16_t armCurrentValue, uint16_t triggerCurrentValue);
extern void CheckButtons(void);


#endif /* INC_PUSHBUTTON_H_ */
