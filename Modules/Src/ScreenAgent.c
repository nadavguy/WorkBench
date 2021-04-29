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

bool shouldRenderBatteryPercent = false;
bool shouldRenderMenu = false;
bool isMenuDisplayed = false;
bool shouldClearScreen = false;
bool shouldRenderItem = false;
bool isItemDisplayed = false;
bool isParameterUpdateRequired = false;
bool shouldRenderPopup = false;
bool isPopupDisplayed = false;



uint32_t lastBatteryRefresh = 0;
uint32_t lastBITStatusChange = 0;

tUINT8_ITEM uint8Item;
tUINT16_ITEM uint16Item;
tUINT32_ITEM uint32Item;

tSTRING_ITEM stringItem;

MENUDRAWType menuDrawDirection = FULL;
MENUDRAWType itemDrawDirection = FULL;
MENUDRAWType popupDrawDirection = FULL;

tPOPUP popupToShow;

void screenInit(void)
{
	DEV_Module_Init();
	LCD_1IN8_SetBackLight(ee.backLight);
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
	Paint_DrawFloatNum (1, 110 ,fwVersion, 2,  &Font12, BLACK, WHITE);
	Paint_DrawString_EN(104, 98, "BuildID", &Font12, WHITE,  BLACK);
	Paint_DrawFloatNum (124, 110 ,buildID, 2,  &Font12, BLACK, WHITE);
	HAL_Delay(1000);
}

void screenClear(void)
{
//	LCD_1IN8_Clear(BLACK);

	Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);

	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);
}

void centeredString(UWORD XCenterstart, UWORD Ystart, const char * pString, uint16_t textColor, uint16_t backgroundColor, uint8_t numberOfCharactersToClear)
{
	uint8_t Xstart = 0;

	Xstart = fmax( XCenterstart - numberOfCharactersToClear * 7 / 2, 0) ;
//	Paint_DrawString_EN(Xstart, Ystart, "MAINTENANCE", &Font12, WHITE,  WHITE);
	Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * 7, Ystart + 12, WHITE);

	Xstart = strlen(pString);

	Xstart = fmax( XCenterstart - strlen(pString) * 7 / 2, 0) ;
	Paint_DrawString_EN(Xstart, Ystart, pString, &Font12, backgroundColor,  textColor);
}

void renderSafeAirBatteryPercent()
{
	char batteryPercentString[4] = "";
	char pr[1] = "%";
	char tempBatteryPercentString[5] = "";
	uint8_t batteryPercent = 0;
	batteryPercent = (uint8_t) ((currentSmaStatus.batteryVoltage * 166.6667
			- 600) / 5) * 5;
	sprintf(batteryPercentString, "%03d%s", batteryPercent, pr);
	memcpy(tempBatteryPercentString, batteryPercentString, 5);
	tempBatteryPercentString[4] = 0;
	//TODO: Clear text before updating, generate value dynamically
	Paint_ClearWindows(HorizontalSafeAirBatteryTextX,
			HorizontalSafeAirBatteryTextY,
			HorizontalSafeAirBatteryTextX + 5 * Font8.Width,
			HorizontalSafeAirBatteryTextY + Font8.Height, WHITE);
	Paint_DrawString_EN(HorizontalSafeAirBatteryTextX,
			HorizontalSafeAirBatteryTextY, tempBatteryPercentString, &Font8,
			WHITE, BLACK);
}

void updateStatusText(void)
{
	if (currentSmaStatus.smaState == TRIGGERED)
	{
		Paint_DrawImage(gImage_Parachute_24, HorizontalParachute1X, HorizontalParachute1Y, 24, 24);
		Paint_DrawImage(gImage_Parachute_24, HorizontalParachute2X, HorizontalParachute2Y, 24, 24);
		//			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "TRIGGERED", BLACK, RED);
		if (displayWarning.BITStatus & 0x40)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Manual Trigger", RED, WHITE, 14);
		}
		else if (displayWarning.BITStatus & 0x80)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "GeoFencing", RED, WHITE, 14);
		}
		else if (displayWarning.BITStatus & 0x100)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "AutoPilot", RED, WHITE, 14);
		}
		else if (displayWarning.BITStatus & 0x200)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Freefall", RED, WHITE, 14);
		}
		else if (displayWarning.BITStatus & 0x400)
		{
			centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Critical Angle", RED, WHITE, 14);
		}
	}
	else if ((currentSmaStatus.smaState == IDLE) && (!displayWarning.displayWarning) && (displayWarning.BITStatus == 0))
	{
		centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "IDLE", BLACK, BLUE, 14);
		previousBITStatus = displayWarning.BITStatus;
	}
	else if ((currentSmaStatus.smaState == ARMED) && (!displayWarning.displayWarning) && (displayWarning.BITStatus == 0))
	{
		centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "ARMED", BLACK, GREEN, 14);
		previousBITStatus = displayWarning.BITStatus;
	}
	else if (currentSmaStatus.smaState == AUTOCALIBRATION)
	{
		centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "CALIBRATION", WHITE, BLACK, 14);
	}
	else if (currentSmaStatus.smaState == MAINTENANCE)
	{
		centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "MAINTENANCE", BLACK, CYAN, 14);
	}

	if (displayWarning.displayWarning)
	{
		if (shouldDrawRedAlertIcon)
		{
			if (currentSmaStatus.smaState != ARMED)
			{
				centeredString(HorizontalSystemStatusTextX, HorizontalSystemStatusTextY, "Error", BLACK, YELLOW, 14);
			}
			Paint_DrawImage(gImage_WarningRed_Icon_24, HorizontalWarningIconX, HorizontalWarningIconY, iconWidth, iconHeight);
			shouldDrawRedAlertIcon = false;
			shouldUpdateStatusText = false;
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
		displayWarning.displayWarning = false;
		//			shouldClearDisplayedWarning = true;
	}
	else if ((!displayWarning.displayWarning) && (shouldClearDisplayedWarning))
	{

		Paint_ClearWindows(HorizontalWarningIconX, HorizontalWarningIconY, HorizontalWarningIconX + iconWidth, HorizontalWarningIconY + iconHeight, WHITE);
		Paint_ClearWindows(HorizontalWarningTextX, HorizontalWarningTextY, HorizontalWarningTextX + 14 * Font12.Width, HorizontalWarningTextY + Font12.Height, WHITE);
		shouldClearDisplayedWarning = false;
	}
}

void updatePlatformText(void)
{
	switch (currentSmaStatus.smaPlatformName)
	{
	case M200:
		centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M200 Pro", BLACK, WHITE, 16);
		break;
	case M300:
		centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M300 Pro", BLACK, WHITE, 16);
		break;
	case M600:
		centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir M600 Pro", BLACK, WHITE, 16);
		break;
	case PHANTOM:
		centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir Phantom", BLACK, WHITE, 16);
		break;
	case MAVICK:
		centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "SafeAir Mavick", BLACK, WHITE, 16);
		break;
	default: /* Optional */
		centeredString(HorizontalSystemTextX, HorizontalSystemTextY, "Unknown platform", BLACK, WHITE, 16);
	}
	previousSmaStatus.smaPlatformName = currentSmaStatus.smaPlatformName;
}

void redrawBatteryIcon(bool drawDeltaImage)
{
	switch (currentSmaStatus.batteryStrength)
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
	default: /* Optional */
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
}

void redrawTriggerModeIcon(bool drawDeltaImage)
{
	switch (currentSmaStatus.safeairTriggerMode)
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
	default: /* Optional */
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
}

void redrawBluetoothIcon(bool drawDeltaImage)
{
	switch (bluetoothConnection)
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
	default: /* Optional */
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
}

void redrawSignalStrengthIcon(bool drawDeltaImage)
{
	switch (tbsLink)
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
	default: /* Optional */
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
}

void redrawAutoPilotIcon(bool drawDeltaImage)
{
	switch (currentSmaStatus.autoPilotConnection)
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
	default: /* Optional */
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

void redrawPlatformIcon(bool drawDeltaImage)
{
	switch (currentSmaStatus.smaPlatfom)
	{
	case MULTICOPTER:
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
	default: /* Optional */
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
}

void screenUpdate(bool drawDeltaImage)
{
	if ( (!isMenuDisplayed) && (!isPopupDisplayed) )
	{
		if (shouldReDrawPlatformIcon)
		{
			redrawPlatformIcon(drawDeltaImage);
			shouldReDrawPlatformIcon = false;
		} // End of Should draw platform icon

		if (shouldReDrawAutoPilotIcon)
		{
			redrawAutoPilotIcon(drawDeltaImage);
			shouldReDrawAutoPilotIcon = false;
		} // End of should draw Auto-pilot icon

		if (shouldRedrawSignalStrengthIcon)
		{
			redrawSignalStrengthIcon(drawDeltaImage);
			shouldRedrawSignalStrengthIcon = false;
		} // end of should draw signal strength icon

		if (shouldReDrawBluetoothIcon)
		{
			redrawBluetoothIcon(drawDeltaImage);
			shouldReDrawBluetoothIcon = false;
		}// End of should draw bluetooth icon

		if (shouldReDrawTriggerModeIcon)
		{
			redrawTriggerModeIcon(drawDeltaImage);
			shouldReDrawTriggerModeIcon = false;
		}// End of should redraw trigger mode

		if (shouldRedrawBatteryIcon)
		{
			redrawBatteryIcon(drawDeltaImage);
			shouldRedrawBatteryIcon = false;
		} // End of should redraw battery icon

		if (shouldUpdatePlatformText)
		{
			updatePlatformText();
			shouldUpdatePlatformText = false;
		} // End of should update platform text

		if ( (shouldUpdateStatusText)  && (HAL_GetTick() - lastBITStatusChange > 500) )
		{
			lastBITStatusChange = HAL_GetTick();
			updateStatusText();
			shouldUpdateStatusText = false;
		} // End of should update status text

		if (!drawDeltaImage)
		{
			Paint_DrawImage(gImage_SafeAir_Logo_74_11, HorizontalSafeAirLogo7411IconX, HorizontalSafeAirLogo7411IconY, 74, 11);
			Paint_DrawImage(gImage_Battery_Full, HorizontalSafeAirBatteryIconX, HorizontalSafeAirBatteryIconY,
					iconWidth, iconHeight);
			Paint_DrawImage(gImage_Altitude_24, HorizontalAltitudeIconX, HorizontalAltitudeIconY, iconWidth, iconHeight);
		}

		if ( (shouldRenderBatteryPercent) || (HAL_GetTick() - lastBatteryRefresh > 60000) ) //|| (lastBatteryRefresh == 0)
		{
			renderSafeAirBatteryPercent();
			//	  Paint_DrawString_EN(HorizontalAltitudeText1X, HorizontalAltitudeText1Y, "Alt[m]", &Font8, WHITE, BLACK);
			//TODO: Clear text before updating, generate value dynamically
			//	  Paint_DrawString_EN(HorizontalAltitudeText2X, HorizontalAltitudeText2Y, "999.9", &Font8, WHITE, BLACK);
			lastBatteryRefresh = HAL_GetTick();
			shouldRenderBatteryPercent = false;
		} // End of should draw SafeAir battery value
	} // end of RC and SafeAir data display
	else if (isMenuDisplayed)
	{
		if (shouldRenderMenu)
		{
			drawMenu(shouldClearScreen, menuDrawDirection);
			shouldRenderMenu = false;
		}
		if (shouldRenderItem)
		{
			drawItem(false, itemDrawDirection);
			shouldRenderItem = false;
		}

	} // End of is Menu displayed
	if(shouldRenderPopup)
	{
		drawPopup();
		shouldRenderPopup = false;
	}
}

void drawMenu(bool clearScreen, MENUDRAWType howToDraw)
{
	if (clearScreen)
	{
		Paint_Clear(WHITE);
	}

	if (howToDraw == FULL)
	{
		for (int i = 0; i < pagesArray[currentCursorPosition.currentPageID].numberOfItemsInPage; i++)
		{
			Paint_DrawRectangle( HorizontalMenuRectangleStartX, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * i,
					HorizontalMenuRectangleStartX+HorizontalMenuRectangleWidth, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * ( i + 1),
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			if (i == currentCursorPosition.cursorPosition)
			{
				centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY+ 1 + HorizontalMenuRectangleHeight * i,
						pagesArray[currentCursorPosition.currentPageID].itemsArray[i], BLACK, LGRAY, 16);
			}
			else
			{
				centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + 1 + HorizontalMenuRectangleHeight * i,
						pagesArray[currentCursorPosition.currentPageID].itemsArray[i], BLACK, WHITE, 16);
			}
		}
	}
	else if (howToDraw == UP)
	{
		centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + 1 + HorizontalMenuRectangleHeight * (currentCursorPosition.cursorPosition + 1),
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition + 1], BLACK, WHITE, 16);
		centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY+ 1 + HorizontalMenuRectangleHeight * currentCursorPosition.cursorPosition,
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition], BLACK, LGRAY, 16);
	}
	else if (howToDraw == DOWN)
	{
		centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + 1 + HorizontalMenuRectangleHeight * (currentCursorPosition.cursorPosition - 1),
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition - 1], BLACK, WHITE, 16);
		centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY+ 1 + HorizontalMenuRectangleHeight * currentCursorPosition.cursorPosition,
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition], BLACK, LGRAY, 16);
	}
}

void drawItem(bool clearScreen, MENUDRAWType howToDraw)
{
	if ((clearScreen) || (!isItemDisplayed) )
	{
		Paint_Clear(WHITE);
	}
	if ( pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
			cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == UINT16_ITEM )
	{
		if ( !(isItemDisplayed) )
		{
			multiplierIndex = 0;
			memcpy(&uint16Item, (uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
					nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], sizeof(tUINT16_ITEM));
			itemIDtoUpdate = uint16Item.itemID;
		}
		isItemDisplayed = true;
		updateUint16Item(howToDraw);
	}
	if ( pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth - 1]].
			cellTypeArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth - 1]] == STRING_ITEM )
	{
		if ( !(isItemDisplayed) )
		{
			multiplierIndex = 0;
			memcpy(&stringItem, (uint32_t *)pagesArray[currentCursorPosition.previousPageID[currentCursorPosition.menuDepth -1]].
					nextCellIDArray[currentCursorPosition.previousPageCursorPosition[currentCursorPosition.menuDepth -1]], sizeof(tSTRING_ITEM));
			itemIDtoUpdate = stringItem.itemID;
		}
		isItemDisplayed = true;
		updateStringItem(howToDraw);
	}
}

void drawPopup(void)
{
	isPopupDisplayed = true;
	isItemDisplayed = false;
	isMenuDisplayed = false;
	if (popupDrawDirection == FULL)
	{
		Paint_Clear(WHITE);
		Paint_DrawRectangle( HorizontalMenuRectangleStartX, HorizontalMenuRectangleStartY ,
				HorizontalMenuRectangleStartX+HorizontalMenuRectangleWidth, HorizontalMenuRectangleStartY + HorizontalPopupRectangleHeight,
				BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );

		if (popupToShow.isQuestion)
		{
			Paint_DrawRectangle( HorizontalMenuRectangleStartX, HorizontalMenuRectangleStartY + HorizontalQuestionRectangleHeight,
					HorizontalMenuRectangleStartX+HorizontalMenuRectangleWidth, HorizontalMenuRectangleStartY + HorizontalQuestionRectangleHeight + HorizontalMenuRectangleHeight,
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
		}

		Paint_DrawRectangle( HorizontalMenuRectangleStartX, HorizontalMenuRectangleStartY + HorizontalPopupRectangleHeight,
				HorizontalMenuRectangleStartX+HorizontalMenuRectangleWidth, HorizontalMenuRectangleStartY + HorizontalPopupRectangleHeight + HorizontalMenuRectangleHeight,
				BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );

		for (int i = 0 ; i < popupToShow.numberOfItemsInPopup - 2; i++)
		{
			centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalMenuRectangleHeight * (i + 1) + 1,
					popupToShow.itemsArray[i], BLACK, WHITE, 16);
		}
	}

	if (popupToShow.isQuestion)
	{
		if ( (popupDrawDirection == FULL) || (popupDrawDirection == UP))
		{
			centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalQuestionRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 2], BLACK, LGRAY, 16);

			centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalPopupRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, WHITE, 16);
		}
		else
		{
			centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalQuestionRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 2], BLACK, WHITE, 16);

			centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalPopupRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, LGRAY, 16);
		}
	}
	else
	{
		centeredString(HorizontalDisplayCenterWidth, HorizontalMenuRectangleStartY + HorizontalPopupRectangleHeight + 1,
				popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, LGRAY, 16);
	}
}

void setFullDisplay(void)
{
	shouldUpdateStatusText = true;
	shouldRedrawBatteryIcon = true;
	shouldRedrawSignalStrengthIcon = true;
	shouldDrawRedAlertIcon = false;
	shouldReDrawPlatformIcon = true;
	shouldUpdatePlatformText = true;
	shouldReDrawAutoPilotIcon = true;
	shouldReDrawBluetoothIcon = true;
	shouldReDrawTriggerModeIcon = true;
	shouldClearDisplayedWarning = true;
	isPopupDisplayed = false;
	isMenuDisplayed = false;
	isItemDisplayed = false;
	shouldRenderPopup = false;
	shouldRenderItem = false;
	shouldRenderMenu = false;
}
