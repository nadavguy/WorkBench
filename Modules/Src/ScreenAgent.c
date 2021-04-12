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

const unsigned char *previousBluetoothImage;
const unsigned char *previousPlatformImage;
const unsigned char *previousAutoPilotImage;
const unsigned char *previousTriggerModeImage;
const unsigned char *previousSignalImage;
const unsigned char *previousBatteryImage;

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

void centeredString(UWORD XCenterstart, UWORD Ystart, const char * pString, uint16_t textColor, uint16_t backgroundColor)
{
	uint8_t Xstart = 0;

	Xstart = strlen("MAINTENANCE");
	Xstart = fmax( XCenterstart - strlen("MAINTENANCE") * 7 / 2, 0) ;
//	Paint_DrawString_EN(Xstart, Ystart, "MAINTENANCE", &Font12, WHITE,  WHITE);
	Paint_ClearWindows(Xstart, Ystart, Xstart + strlen("MAINTENANCE") * 7, Ystart + 12, WHITE);

	Xstart = strlen(pString);

	Xstart = fmax( XCenterstart - strlen(pString) * 7 / 2, 0) ;
	Paint_DrawString_EN(Xstart, Ystart, pString, &Font12, backgroundColor,  textColor);
}

void screenUpdate(bool drawDeltaImage)
{
	if (shouldReDrawPlatformIcon)
	{
		switch(currentSmaStatus.smaPlatfom)
		{
			case MULTICOPTER:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_VTOLTransition, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Multicopter, previousPlatformImage,
							HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				}
				previousPlatformImage = gImage_Multicopter;
				break; /* optional */

			case VTOLHORIZONTAL:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Multicopter, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Multicopter, previousPlatformImage,
							HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
				}
				previousPlatformImage = gImage_Multicopter;
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Multicopter, HorizontalPltfomTypeX, HorizontalPltfomTypeY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Multicopter, previousPlatformImage,
							HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				}
				previousPlatformImage = gImage_Multicopter;
		}
		shouldReDrawPlatformIcon = false;
	}

	if (shouldReDrawAutoPilotIcon)
	{
		switch(currentSmaStatus.autoPilotConnection)
		{
			case DISCONNECTED:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_AutoPilot_Disconnected, HorizontalAutoPilotX, HorizontalAutoPilotY,
							iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_AutoPilot_Disconnected, previousAutoPilotImage,
							HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
				}
				previousAutoPilotImage = gImage_AutoPilot_Disconnected;
				break; /* optional */

			case CONNECTED:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_AutoPilot_Connected, HorizontalAutoPilotX, HorizontalAutoPilotY,
							iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_AutoPilot_Connected, previousAutoPilotImage,
							HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
				}
				previousAutoPilotImage = gImage_AutoPilot_Connected;
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_AutoPilot_Disconnected, HorizontalAutoPilotX, HorizontalAutoPilotY,
							iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_AutoPilot_Disconnected, previousAutoPilotImage,
							HorizontalAutoPilotX, HorizontalAutoPilotY, iconWidth, iconHeight);
				}
				previousAutoPilotImage = gImage_AutoPilot_Disconnected;
		}
	}

	if (shouldRedrawSignalStrengthIcon)
	{
		switch(tbsLink)
		{
			case NOSIGNAL:
				if (!drawDeltaImage)
				{
				Paint_DrawImage(gImage_Signal_RedNone, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Signal_RedNone, previousSignalImage,
							HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);

				}
				previousSignalImage = gImage_Signal_RedNone;
				break; /* optional */

			case LOW:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Signal_Low, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Signal_Low, previousSignalImage,
							HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				previousSignalImage = gImage_Signal_Low;
				break; /* optional */

			case MEDIUM:
				if (!drawDeltaImage)
				{
				Paint_DrawImage(gImage_Signal_Medium, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Signal_Medium, previousSignalImage,
							HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				previousSignalImage = gImage_Signal_Medium;
				break; /* optional */

			case STRONG:
				if (!drawDeltaImage)
				{
				Paint_DrawImage(gImage_Signal_Strong, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Signal_Strong, previousSignalImage,
							HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				previousSignalImage = gImage_Signal_Strong;
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				if (!drawDeltaImage)
				{
				Paint_DrawImage(gImage_Signal_RedNone, HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Signal_RedNone, previousSignalImage,
							HorizontalTBSSignalX, HorizontalTBSSignalY, iconWidth, iconHeight);
				}
				previousSignalImage = gImage_Signal_RedNone;
		}
		shouldRedrawSignalStrengthIcon = false;
	}

	if (shouldReDrawBluetoothIcon)
	{
		switch(bluetoothConnection)
		{
			case DISCONNECTED:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Bluetooth_Disconnected, HorizontalBluetoothX, HorizontalBluetoothY,
							iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Bluetooth_Disconnected, previousBluetoothImage,
							HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				}
				previousBluetoothImage = gImage_Bluetooth_Disconnected;
				break; /* optional */

			case CONNECTED:
				if (!drawDeltaImage)
				{
				Paint_DrawImage(gImage_Bluetooth_Connected, HorizontalBluetoothX, HorizontalBluetoothY,
						iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Bluetooth_Connected, previousBluetoothImage,
							HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				}
				previousBluetoothImage = gImage_Bluetooth_Connected;
				break; /* optional */

				//		case PAIRING:
				//			Paint_DrawImage(gImage_Bluetooth_Connected_24, HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				//			break; /* optional */

			case SEARCHING:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Bluetooth_Searching, HorizontalBluetoothX, HorizontalBluetoothY,
							iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Bluetooth_Searching, previousBluetoothImage,
							HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				}
				previousBluetoothImage = gImage_Bluetooth_Searching;
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Bluetooth_Disconnected, HorizontalBluetoothX, HorizontalBluetoothY,
							iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Bluetooth_Disconnected, previousBluetoothImage,
							HorizontalBluetoothX, HorizontalBluetoothY, iconWidth, iconHeight);
				}
				previousBluetoothImage = gImage_Bluetooth_Disconnected;
		}
		shouldReDrawBluetoothIcon = false;
	}

	switch(currentSmaStatus.safeairTriggerMode)
	{
		case AUTO:
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Auto_Trigger, HorizontalTriggerModeX, HorizontalTriggerModeY,
						iconWidth, iconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Auto_Trigger, previousTriggerModeImage,
						HorizontalTriggerModeX, HorizontalTriggerModeY, iconWidth, iconHeight);
			}
			previousTriggerModeImage = gImage_SafeAir_Auto_Trigger;
			break; /* optional */

		case MANUAL:
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Manual_Trigger, HorizontalTriggerModeX, HorizontalTriggerModeY,
						iconWidth, iconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Manual_Trigger, previousTriggerModeImage,
						HorizontalTriggerModeX, HorizontalTriggerModeY, iconWidth, iconHeight);
			}
			previousTriggerModeImage = gImage_SafeAir_Manual_Trigger;
			break; /* optional */

			/* you can have any number of case statements */
		default : /* Optional */
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_SafeAir_Manual_Trigger, HorizontalTriggerModeX, HorizontalTriggerModeY,
					iconWidth, iconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_SafeAir_Manual_Trigger, previousTriggerModeImage,
						HorizontalTriggerModeX, HorizontalTriggerModeY, iconWidth, iconHeight);
			}
			previousTriggerModeImage = gImage_SafeAir_Manual_Trigger;
	}

	if (shouldRedrawBatteryIcon)
	{
		switch(currentSmaStatus.batteryStrength)
		{
			case EMPTY:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Battery_RedAlert, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Battery_RedAlert, previousBatteryImage,
							HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				previousBatteryImage = gImage_Battery_RedAlert;
				break; /* optional */

			case LOW:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Battery_Third, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Battery_Third, previousBatteryImage,
							HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				previousBatteryImage = gImage_Battery_Third;
				break; /* optional */

			case MEDIUM:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Battery_Two_Thirds, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Battery_Two_Thirds, previousBatteryImage,
							HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				previousBatteryImage = gImage_Battery_Two_Thirds;
				break; /* optional */

			case STRONG:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Battery_Full, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Battery_Full, previousBatteryImage,
							HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				previousBatteryImage = gImage_Battery_Full;
				break; /* optional */

			case CHARGING:
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Battery_Charging, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Battery_Charging, previousBatteryImage,
							HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				previousBatteryImage = gImage_Battery_Charging;
				break; /* optional */

				/* you can have any number of case statements */
			default : /* Optional */
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Battery_RedAlert, HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Battery_RedAlert, previousBatteryImage,
							HorizontalBatteryX, HorizontalBatteryY, iconWidth, iconHeight);
				}
				previousBatteryImage = gImage_Battery_RedAlert;
		}
		shouldRedrawBatteryIcon = false;
	}

	if (shouldUpdatePlatformText)
	{
		switch (currentSmaStatus.smaPlatformName)
		{
			case M200:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M200 Pro", BLACK, WHITE);
				break;
			case M300:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M300 Pro", BLACK, WHITE);
				break;
			case M600:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M600 Pro", BLACK, WHITE);
				break;
			case PHANTOM:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir Phantom", BLACK, WHITE);
				break;
			case MAVICK:
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir Mavick", BLACK, WHITE);
				break;
			default : /* Optional */
				centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "Unknown platform", BLACK, WHITE);
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
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Manual Trigger", RED, WHITE);
			}
			else if (displayWarning.BITStatus & 0x80)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "GeoFencing", RED, WHITE);
			}
			else if (displayWarning.BITStatus & 0x100)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "AutoPilot", RED, WHITE);
			}
			else if (displayWarning.BITStatus & 0x200)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Freefall", RED, WHITE);
			}
			else if (displayWarning.BITStatus & 0x400)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Critical Angle", RED, WHITE);
			}
		}
		else if (currentSmaStatus.smaState == IDLE)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "IDLE", BLACK, BLUE);
		}
		else if (currentSmaStatus.smaState == ARMED)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "ARMED", BLACK, GREEN);
		}
		else if (currentSmaStatus.smaState == AUTOCALIBRATION)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "CALIBRATION", WHITE, BLACK);
		}
		else if (currentSmaStatus.smaState == MAINTENANCE)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "MAINTENANCE",BLACK , LBBLUE);
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

//			Paint_ClearWindows( HorizontalBatteryX, HorizontalBatteryY, HorizontalBatteryX + iconWidth, HorizontalBatteryY + iconHeight, WHITE);
			Paint_ClearWindows( HorizontalWarningTextX, HorizontalWarningTextY, HorizontalWarningTextX + 14 * Font12.Width, HorizontalWarningTextY + Font12.Height, WHITE);
			shouldClearDisplayedWarning = false;
		}
		shouldUpdateSatusText = false;
	}

	if (!drawDeltaImage)
	{
		Paint_DrawImage(gImage_SafeAir_Logo_59_9, HorizontalSafeAirLogo599IconX, HorizontalSafeAirLogo599IconY, 59, 9);
		Paint_DrawImage(gImage_Battery_Full_Standing, HorizontalSafeAirBatteryIconX, HorizontalSafeAirBatteryIconY, 24, 24);
		//TODO: Clear text before updating, generate value dynamically
		//	  Paint_DrawString_EN(HorizontalSafeAirBatteryTextX, HorizontalSafeAirBatteryTextY, "100%", &Font12, WHITE, BLACK);
		Paint_DrawImage(gImage_Altitude_24, HorizontalAltitudeIconX, HorizontalAltitudeIconY, 24, 24);
		//	  Paint_DrawString_EN(HorizontalAltitudeText1X, HorizontalAltitudeText1Y, "Alt[m]", &Font8, WHITE, BLACK);
		//TODO: Clear text before updating, generate value dynamically
		//	  Paint_DrawString_EN(HorizontalAltitudeText2X, HorizontalAltitudeText2Y, "999.9", &Font8, WHITE, BLACK);
	}
}
