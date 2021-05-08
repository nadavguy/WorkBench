/*
 * FrameHelper.h
 *
 *  Created on: May 5, 2021
 *      Author: gilad
 */

#ifndef INC_FRAMEHELPER_H_
#define INC_FRAMEHELPER_H_

#define BACKGROUND_HIGH_BYTE 0XE7
#define BACKGROUND_LOW_BYTE 0x3C
#define BACKGROUND 0xE73C

#define SCREEN_WIDTH 128
#define STATUSBAR_HEIGHT 25

extern uint8_t numberOfDisplayedSafeAirIcons;

extern void createEmptyFrame(void);
extern void updateNextFrame(void);
extern void addImageToNextFrame(const unsigned char *image, uint8_t Height, uint8_t Width, uint8_t Xstart, uint8_t Ystart);
extern void addRectangleToFrame(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd, uint16_t Color);


#endif /* INC_FRAMEHELPER_H_ */
