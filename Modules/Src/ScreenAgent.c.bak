/*
 * ScreenAgent.c
 *
 *  Created on: Mar 25, 2021
 *      Author: gilad
 */


#include "main.h"
#include "image.h"
#include "BatteryImages.h"
#include "LogoImages.h"
#include "LocationImages.h"
#include "AutoPilotImages.h"
#include "SignalImages.h"
#include "SafeAirImages.h"
#include "BluetoothImages.h"
#include "PlatformImages.h"
#include "LCD_Test.h"
#include "LCD_1in8.h"
#include "DEV_Config.h"

void screenInit(void)
{
	DEV_Module_Init();
	LCD_1IN8_SetBackLight(1000);
	LCD_1IN8_Init(SCAN_DIR_DFT);
	LCD_1IN8_Clear(BLACK);

//	printf("Paint_NewImage\r\n");
	Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);

//	printf("Set Clear and Display Funtion\r\n");
	Paint_SetClearFuntion(LCD_1IN8_Clear);
	Paint_SetDisplayFuntion(LCD_1IN8_DrawPaint);

//	printf("Paint_Clear\r\n");
	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);

	Paint_DrawImage(gImage_Logo, 16, 0, 128, 128);
	Paint_DrawString_EN(1, 98, "Version", &Font12, WHITE,  BLACK);
	Paint_DrawFloatNum (1, 110 ,1.000, 2,  &Font12, BLACK, WHITE);
	Paint_DrawString_EN(104, 98, "BuildID", &Font12, WHITE,  BLACK);
	Paint_DrawFloatNum (124, 110 ,1.010, 2,  &Font12, BLACK, WHITE);
}

void screenClear(void)
{
	LCD_1IN8_Clear(BLACK);

	Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);

	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);
}

void centeredString(UWORD XCenterstart, UWORD Ystart, const char * pString, uint16_t textColor)
{
	uint8_t Xstart = 0;
	Xstart = strlen(pString);

	Xstart = fmax( XCenterstart - strlen(pString) * 7 / 2, 0) ;

	Paint_DrawString_EN(Xstart, Ystart, pString, &Font12, WHITE,  textColor);
}

void screenUpdate(void)
{
//	Paint_DrawImage(gImage_Logo_36, HorizontalLogoX, HorizontalLogoY, 36, 36);
//
//	switch(safeairPlatform)
//	{
//		case MULTICOPTER:
//			Paint_DrawImage(gImage_Multicopter_24, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case VTOLHORIZONTAL:
//			Paint_DrawImage(gImage_Multicopter_24, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
//			break; /* optional */
//
//			/* you can have any number of case statements */
//		default : /* Optional */
//			Paint_DrawImage(gImage_Multicopter_24, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
//	}
//
//	switch(autoPilotConnection)
//	{
//		case DISCONNECTED:
//			Paint_DrawImage(gImage_AutoPilot_Disconnected, HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case CONNECTED:
//			Paint_DrawImage(gImage_AutoPilot_Connected, HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
//			break; /* optional */
//
//			/* you can have any number of case statements */
//		default : /* Optional */
//			Paint_DrawImage(gImage_No_AutoPilot_24, HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
//	}
//
//	switch(tbsLink)
//	{
//		case NOSIGNAL:
//			Paint_DrawImage(gImage_Signal_Cellular_24, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case LOW:
//			Paint_DrawImage(gImage_Signal_Cellular_24, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case MEDIUM:
//			Paint_DrawImage(gImage_Signal_Cellular_24, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case STRONG:
//			Paint_DrawImage(gImage_Signal_Cellular_24, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
//			break; /* optional */
//
//			/* you can have any number of case statements */
//		default : /* Optional */
//			Paint_DrawImage(gImage_Signal_Cellular_24, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
//	}
//
//	switch(bluetoothConnection)
//	{
//		case DISCONNECTED:
//			Paint_DrawImage(gImage_Bluetooth_Connected_24, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case CONNECTED:
//			Paint_DrawImage(gImage_Bluetooth_Connected_24, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case PAIRING:
//			Paint_DrawImage(gImage_Bluetooth_Connected_24, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case SEARCHING:
//			Paint_DrawImage(gImage_Bluetooth_Connected_24, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
//			break; /* optional */
//
//			/* you can have any number of case statements */
//		default : /* Optional */
//			Paint_DrawImage(gImage_Bluetooth_Connected_24, HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
//	}
//
//	switch(batteryStrength)
//	{
//		case EMPTY:
//			Paint_DrawImage(gImage_baseline_battery_charging_full_black_24, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case LOW:
//			Paint_DrawImage(gImage_baseline_battery_charging_full_black_24, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case MEDIUM:
//			Paint_DrawImage(gImage_baseline_battery_charging_full_black_24, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case STRONG:
//			Paint_DrawImage(gImage_baseline_battery_charging_full_black_24, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
//			break; /* optional */
//
//		case CHARGING:
//			Paint_DrawImage(gImage_baseline_battery_charging_full_black_24, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
//			break; /* optional */
//
//			/* you can have any number of case statements */
//		default : /* Optional */
//			Paint_DrawImage(gImage_baseline_battery_charging_full_black_24, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
//	}
//
//	if (displayWarning.displayWarning)
//	{
//
//		Paint_DrawImage(gImage_baseline_battery_charging_full_black_24, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
//		Paint_DrawImage(gImage_WarningRed_Icon_24, HorizontalWarningIconX, HorizontalWarningIconY, iconWidth, iconHeight);
//		if (displayWarning.BITStatus & 0x01)
//		{
//			Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Crit Bat", &Font12, WHITE, BLACK);
//		}
//		else if (displayWarning.BITStatus & 0x02)
//		{
//			Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Low Bat", &Font12, WHITE, BLACK);
//		}
//		else if (displayWarning.BITStatus & 0x04)
//		{
//			Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Flash Err", &Font12, WHITE, BLACK);
//		}
//		else if (displayWarning.BITStatus & 0x08)
//		{
//			Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Orientation", &Font12, WHITE, BLACK);
//		}
//		else if (displayWarning.BITStatus & 0x016)
//		{
//			Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Pyro Err", &Font12, WHITE, BLACK);
//		}
//		else if (displayWarning.BITStatus & 0x016)
//		{
//			Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "RC Low Bat", &Font12, WHITE, BLACK);
//		}
//	}
//	else
//	{
//
//		Paint_ClearWindows( HorizontalBatteryX, HorizontalBatteryY, HorizontalBatteryX + iconWidth, HorizontalBatteryY + iconHeight, WHITE);
//		Paint_ClearWindows( HorizontalWarningTextX, HorizontalWarningTextY, HorizontalWarningTextX + 14 * Font12.Width, HorizontalWarningTextY + Font12.Height, WHITE);
//	}
//	if
//	  centeredString(80, 24, "Centered Text");
}
