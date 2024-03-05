/*
 * FrameHelper.c
 *
 *  Created on: May 5, 2021
 *      Author: gilad
 */

#include "main.h"
#include "DEV_Config.h"
#include "LCD_1in8.h"

uint8_t numberOfDisplayedSafeAirIcons = 0;

uint32_t LCDArraySize = 40960;

void createEmptyFrame(bool isMenuFrame)
{
	if (!isMenuFrame)
	{
		memset(nextFrameToDraw,0x00,LCDArraySize);

		for (int i = 0 ; i < (LCDArraySize - SCREEN_WIDTH * STATUSBAR_HEIGHT * 2) /2 ; i++)
		{
			nextFrameToDraw[(i + SCREEN_WIDTH * STATUSBAR_HEIGHT) * 2] = BACKGROUND_HIGH_BYTE;
			nextFrameToDraw[(i + SCREEN_WIDTH * STATUSBAR_HEIGHT) * 2 + 1] = BACKGROUND_LOW_BYTE;
		}
	}
	else if (isMenuFrame)
	{
		memset(nextFrameToDraw,0xFF,LCDArraySize);
	}
}

void displayNextFrame(void)
{
//	LCD_1IN8_SetCursor(0, 0);
	if (HAL_GetTick() - lastFrameDisplayed > 30)
	{
		HAL_SPI_Transmit(&DEV_SPI, (uint8_t *)nextFrameToDraw, LCDArraySize, 1500);
//		createEmptyFrame();
		lastFrameDisplayed = HAL_GetTick();
	}
}

void addImageToNextFrame(const unsigned char *image, uint8_t Height, uint8_t Width, uint8_t Xstart, uint8_t Ystart)
{
	for (int i = 0 ; i < Height ; i++)
	{
		memcpy(&nextFrameToDraw[(Ystart + i) * SCREEN_WIDTH * 2 + Xstart * 2],&image[Width * 2 * i], Width * 2);
	}
}

void addRectangleToFrame(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd, uint16_t Color)
{
	for (int i = 0 ; i < (xEnd - xStart) * (yEnd - yStart) ; i++)
	{
		nextFrameToDraw[(i + SCREEN_WIDTH * yStart + xStart) * 2] = (uint8_t)((Color & 0xFF00) >> 8 );
		nextFrameToDraw[(i + SCREEN_WIDTH * yStart + xStart) * 2 + 1] = (uint8_t)((Color & 0x00FF));
	}
}

void prepareNextFrame(void)
{

}
