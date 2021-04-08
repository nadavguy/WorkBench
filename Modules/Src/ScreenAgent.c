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
	HAL_Delay(1000);
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
	if (shouldReDrawPlatformIcon)
	{
		switch(currentSmaStatus.smaPlatfom)
		{
			case MULTICOPTER:
				Paint_DrawImage(gImage_Multicopter, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
				break; /* optional */

			case VTOLHORIZONTAL:
				Paint_DrawImage(gImage_Multicopter, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				Paint_DrawImage(gImage_Multicopter, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
		}
		shouldReDrawPlatformIcon = false;
	}

	if (shouldReDrawAutoPilotIcon)
	{
		switch(currentSmaStatus.autoPilotConnection)
		{
			case DISCONNECTED:
				Paint_DrawImage(gImage_AutoPilot_Disconnected, HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
				break; /* optional */

			case CONNECTED:
				Paint_DrawImage(gImage_AutoPilot_Connected, HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				Paint_DrawImage(gImage_AutoPilot_Disconnected, HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
		}
	}

	if (shouldRedrawSignalStrengthIcon)
	{
		switch(tbsLink)
		{
			case NOSIGNAL:
				Paint_DrawImage(gImage_Signal_RedNone, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				break; /* optional */

			case LOW:
				Paint_DrawImage(gImage_Signal_Low, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				break; /* optional */

			case MEDIUM:
				Paint_DrawImage(gImage_Signal_Medium, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				break; /* optional */

			case STRONG:
				Paint_DrawImage(gImage_Signal_Strong, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				Paint_DrawImage(gImage_Signal_RedNone, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
		}
		shouldRedrawSignalStrengthIcon = false;
	}

	if (shouldReDrawBluetoothIcon)
	{
		switch(bluetoothConnection)
		{
			case DISCONNECTED:
				Paint_DrawImage(gImage_Bluetooth_Disconnected, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				break; /* optional */

			case CONNECTED:
				Paint_DrawImage(gImage_Bluetooth_Connected, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				break; /* optional */

				//		case PAIRING:
				//			Paint_DrawImage(gImage_Bluetooth_Connected_24, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				//			break; /* optional */

			case SEARCHING:
				Paint_DrawImage(gImage_Bluetooth_Searching, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				Paint_DrawImage(gImage_Bluetooth_Disconnected, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
		}
		shouldReDrawBluetoothIcon = false;
	}

	switch(currentSmaStatus.safeairTriggerMode)
	{
		case AUTO:
			Paint_DrawImage(gImage_SafeAir_Auto_Trigger, HorizontalTriggerModeX, HorizontalTriggerModeY, iconWidth, iconHeight);
			break; /* optional */

		case MANUAL:
			Paint_DrawImage(gImage_SafeAir_Manual_Trigger, HorizontalTriggerModeX, HorizontalTriggerModeY, iconWidth, iconHeight);
			break; /* optional */

			/* you can have any number of case statements */
		default : /* Optional */
			Paint_DrawImage(gImage_SafeAir_Manual_Trigger, HorizontalTriggerModeX, HorizontalTriggerModeY, iconWidth, iconHeight);
	}

	if (shouldRedrawBatteryIcon)
	{
		switch(currentSmaStatus.batteryStrength)
		{
			case EMPTY:
				Paint_DrawImage(gImage_Battery_RedAlert, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				break; /* optional */

			case LOW:
				Paint_DrawImage(gImage_Battery_Third, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				break; /* optional */

			case MEDIUM:
				Paint_DrawImage(gImage_Battery_Two_Thirds, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				break; /* optional */

			case STRONG:
				Paint_DrawImage(gImage_Battery_Full, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				break; /* optional */

			case CHARGING:
				Paint_DrawImage(gImage_Battery_RedAlert, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				Paint_DrawImage(gImage_Battery_RedAlert, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
		}
		shouldRedrawBatteryIcon = false;
	}

	if (shouldUpdatePlatformText)
	{
		switch (currentSmaStatus.smaPlatformName)
		{
			case M200:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M200 Pro", BLACK);
				break;
			case M300:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M300 Pro", BLACK);
				break;
			case M600:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M600 Pro", BLACK);
				break;
			case PHANTOM:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir Phantom", BLACK);
				break;
			case MAVICK:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir Mavick", BLACK);
				break;
			default : /* Optional */
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "Unknown platform", BLACK);
		}
		shouldUpdatePlatformText = false;
	}

	if (shouldUpdateSatusText)
	{
		if (currentSmaStatus.smaState == TRIGGERED)
		{
			Paint_DrawImage(gImage_Parachute_24, HorizontalParachute1X, HorizontalParachute1Y, 24, 24);
			Paint_DrawImage(gImage_Parachute_24, HorizontalParachute2X, HorizontalParachute2Y, 24, 24);
			if (displayWarning.BITStatus & 0x40)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Manual Trigger", RED);
			}
			else if (displayWarning.BITStatus & 0x80)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "GeoFencing", RED);
			}
			else if (displayWarning.BITStatus & 0x100)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "AutoPilot", RED);
			}
			else if (displayWarning.BITStatus & 0x200)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Freefall", RED);
			}
			else if (displayWarning.BITStatus & 0x400)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Critical Angle", RED);
			}
		}
		else if (currentSmaStatus.smaState == IDLE)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "IDLE", BLUE);
		}
		else if (currentSmaStatus.smaState == ARMED)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "ARMED", GREEN);
		}
		else if (currentSmaStatus.smaState == AUTOCALIBRATION)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "CALIBRATION", BLACK);
		}
		else if (currentSmaStatus.smaState == MAINTENANCE)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "MAINTENANCE", LBBLUE);
		}

		if (displayWarning.displayWarning)
		{
			//TODO: Add logic for redrawing only changed icons - important
			if (shouldDrawRedAlertIcon)
			{
				Paint_DrawImage(gImage_WarningRed_Icon_24, HorizontalWarningIconX, HorizontalWarningIconY, iconWidth, iconHeight);
				shouldDrawRedAlertIcon = false;
			}
			if (displayWarning.BITStatus & 0x01)
			{
				Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Critical Bat", &Font12, WHITE, BLACK);
			}
			else if (displayWarning.BITStatus & 0x02)
			{
				Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Low Bat", &Font12, WHITE, BLACK);
			}
			else if (displayWarning.BITStatus & 0x04)
			{
				Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Flash Err", &Font12, WHITE, BLACK);
			}
			else if (displayWarning.BITStatus & 0x08)
			{
				Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Orientation", &Font12, WHITE, BLACK);
			}
			else if (displayWarning.BITStatus & 0x10)
			{
				Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "SA Pyro Err", &Font12, WHITE, BLACK);
			}
			else if (displayWarning.BITStatus & 0x20)
			{
				Paint_DrawString_EN(HorizontalWarningTextX, HorizontalWarningTextY, "RC Low Bat", &Font12, WHITE, BLACK);
			}
			shouldClearDisplayedWarning = true;
		}
		else if ( (!displayWarning.displayWarning) && (shouldClearDisplayedWarning) )
		{

			Paint_ClearWindows( HorizontalBatteryX, HorizontalBatteryY, HorizontalBatteryX + iconWidth, HorizontalBatteryY + iconHeight, WHITE);
			Paint_ClearWindows( HorizontalWarningTextX, HorizontalWarningTextY, HorizontalWarningTextX + 14 * Font12.Width, HorizontalWarningTextY + Font12.Height, WHITE);
			shouldClearDisplayedWarning = false;
		}
		shouldUpdateSatusText = false;
	}

	  Paint_DrawImage(gImage_SafeAir_Logo_59_9, HorizontalSafeAirLogo599IconX, HorizontalSafeAirLogo599IconY, 59, 9);
	  Paint_DrawImage(gImage_Battery_Full_Standing, HorizontalSafeAirBatteryIconX, HorizontalSafeAirBatteryIconY, 24, 24);
	  //TODO: Clear text before updating, generate value dynamically
	  Paint_DrawString_EN(HorizontalSafeAirBatteryTextX, HorizontalSafeAirBatteryTextY, "100%", &Font12, WHITE, BLACK);
	  Paint_DrawImage(gImage_Altitude_24, HorizontalAltitudeIconX, HorizontalAltitudeIconY, 24, 24);
	  Paint_DrawString_EN(HorizontalAltitudeText1X, HorizontalAltitudeText1Y, "Alt[m]", &Font8, WHITE, BLACK);
	  //TODO: Clear text before updating, generate value dynamically
	  Paint_DrawString_EN(HorizontalAltitudeText2X, HorizontalAltitudeText2Y, "999.9", &Font8, WHITE, BLACK);
}
