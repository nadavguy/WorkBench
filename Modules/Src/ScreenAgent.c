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
#include "DotImages.h"
#include "LCD_Test.h"
#include "LCD_1in8.h"
#include "DEV_Config.h"
#include "usb_device.h"
#include "ScreenSaverImages.h"
#include "DataTransferImages.h"

const unsigned char *previousBluetoothImage;
const unsigned char *previousPlatformImage;
const unsigned char *previousAutoPilotImage;
const unsigned char *previousTriggerModeImage;
const unsigned char *previousSignalImage;
const unsigned char *previousBatteryImage;
const unsigned char *previousRCBatteryImage;
const unsigned char *previousAltitudeOrGPSImage;
const unsigned char *previousDataTransferImage;

bool shouldRenderBatteryPercent = false;
bool shouldRenderMenu = false;
bool isMenuDisplayed = false;
bool shouldClearScreen = false;
bool shouldRenderItem = false;
bool isItemDisplayed = false;
bool isParameterUpdateRequired = false;
bool shouldRenderPopup = false;
bool isPopupDisplayed = false;
bool isPortrait = false;
bool renderCompleteFrame = false;
bool isBluetoothDisplayed = false;
bool isAutoPilotDisplayed = false;
bool isPlatformDisplayed = false;
bool isTriggerModeDisplayed = true;
bool isSafeAirBatteryDisplayed = true;
bool isAltitudeDisplayed = true;
bool isGPSPositionDisplayed = false;
bool shouldRenderDataTransfer = false;

uint8_t PlatfomTypeX = 0;
uint8_t PlatfomTypeY = 0;
uint8_t AutoPilotX = 0;
uint8_t AutoPilotY = 0;
uint8_t TBSSignalX = 0;
uint8_t TBSSignalY = 0;
uint8_t BluetoothX = 0;
uint8_t BluetoothY = 0;
uint8_t DataTransferX = 0;
uint8_t DataTransferY = 0;
uint8_t TriggerModeX = 0;
uint8_t TriggerModeY = 0;
uint8_t BatteryX = 0;
uint8_t BatteryY = 0;
uint8_t SystemTextX = 0;
uint8_t SystemTextY = 0;
uint8_t SafeAirBatteryX = 0;
uint8_t SafeAirBatteryY = 0;
uint8_t Parachute1X = 0;
uint8_t Parachute1Y = 0;
uint8_t Parachute2X = 0;
uint8_t Parachute2Y = 0;
uint8_t SystemStatusTextX = 0;
uint8_t SystemStatusTextY = 0;
uint8_t WarningIconX = 0;
uint8_t WarningIconY = 0;
uint8_t WarningTextX = 0;
uint8_t WarningTextY = 0;
uint8_t LineStartX = 0;
uint8_t LineEndX = 0;
uint8_t LineY = 0;
uint8_t AltitudeOrGPSX = 0;
uint8_t AltitudeOrGPSY = 0;
uint8_t ChargingModeImageX = 0;
uint8_t ChargingModeImageY = 0;
uint8_t ChargingModePercentTextX = 0;
uint8_t ChargingModePercentTextY = 0;
uint8_t dotCycle = 0;
uint8_t FullLogoX = 0;
uint8_t FullLogoY = 0;
uint8_t FullLogoWidth = 0;
uint8_t FullLogoHeight = 0;
uint8_t lowerBarDisplayID = 0;
int8_t velX = 3;
int8_t velY = 3;
uint8_t posX = 0;
uint8_t posY = 0;

uint32_t lastBatteryRefresh = 0;
uint32_t lastBITStatusChange = 0;
uint32_t lastFrameDisplayed = 0;
uint32_t lastFullFrameDisplayed = 0 ;
uint32_t lastDotRefresh = 0 ;
uint32_t lastLogDataRefresh = 0;

tUINT8_ITEM uint8Item;
tUINT16_ITEM uint16Item;
tUINT32_ITEM uint32Item;

tSTRING_ITEM stringItem;

MENUDRAWType menuDrawDirection = FULL;
MENUDRAWType itemDrawDirection = FULL;
MENUDRAWType popupDrawDirection = FULL;

tPOPUP popupToShow;

tIMAGE_DATA statusBarImageArray[5];
tIMAGE_DATA safeairBarImageArray[5];

uint8_t nextFrameToDraw[40960] = {0xFF};

void screenInit(void)
{
	isPortrait = (bool)ee.screenOreintation;
	DEV_Module_Init();
	LCD_1IN8_SetBackLight(ee.backLight * 2000);
	if (isPortrait)
	{
		LCD_1IN8_Init(L2R_U2D);
		LCD_1IN8_Clear(BLACK);
		Paint_NewImage(LCD_1IN8_HEIGHT,LCD_1IN8_WIDTH, 0, WHITE);
		FullLogoWidth = VerticalFullLogoWidth;
		FullLogoHeight = VerticalFullLogoHeight;
		FullLogoX = VerticalFullLogoX;
		FullLogoY = VerticalFullLogoY;
	}
	else
	{
		LCD_1IN8_Init(U2D_R2L);
		LCD_1IN8_Clear(BLACK);
		Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);
		//		FullLogoWidth = HorizontalFullLogoWidth;
		//		FullLogoHeight = HorizontalFullLogoHeight;
		//		FullLogoX = HorizontalFullLogoX;
		//		FullLogoY = HorizontalFullLogoY;
	}

	Paint_SetClearFuntion(LCD_1IN8_Clear);
	Paint_SetDisplayFuntion(LCD_1IN8_DrawPaint);

	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);

	if (isPortrait)
	{
		Paint_DrawImage(gImage_ParaZero_Logo_100_121_LSB, 14, 1, 100, 121);
		Paint_DrawString_EN(1, 130, "Version", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (1, 142 ,fwVersion, 2,  &Font12, BLACK, WHITE);
		Paint_DrawString_EN(70, 130, "BuildID", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (70, 142 ,buildID, 2,  &Font12, BLACK, WHITE);
	}
	else
	{
		Paint_DrawImage(gImage_Logo, 16, 0, 128, 128);
		Paint_DrawString_EN(1, 98, "Version", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (1, 110 ,fwVersion, 2,  &Font12, BLACK, WHITE);
		Paint_DrawString_EN(104, 98, "BuildID", &Font12, WHITE,  BLACK);
		Paint_DrawFloatNum (124, 110 ,buildID, 2,  &Font12, BLACK, WHITE);
	}


	HAL_Delay(1000);
}

void screenClear(void)
{
	if (isPortrait)
	{
		Paint_NewImage(LCD_1IN8_HEIGHT,LCD_1IN8_WIDTH, 0, WHITE);
	}
	else
	{
		Paint_NewImage(LCD_1IN8_WIDTH,LCD_1IN8_HEIGHT, 0, WHITE);
	}

	Paint_Clear(WHITE);
	DEV_Delay_ms(1000);
}

void centeredString(UWORD XCenterstart, UWORD Ystart, const char * pString, uint16_t textColor, uint16_t backgroundColor, uint8_t numberOfCharactersToClear, sFONT localFont)
{
	uint8_t Xstart = 0;

	Xstart = fmax( XCenterstart - numberOfCharactersToClear * localFont.Width / 2, 0) ;
	if (!renderCompleteFrame)
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, WHITE);
	}
	else if ( (renderCompleteFrame) && (!isMenuDisplayed) && (!isPopupDisplayed) )
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, backgroundColor);
	}
	else if ( (renderCompleteFrame) && ( (isMenuDisplayed) || (isPopupDisplayed) ) )
	{
		Paint_ClearWindows(Xstart, Ystart, Xstart + numberOfCharactersToClear * localFont.Width, Ystart + localFont.Height, WHITE);
	}
	Xstart = strlen(pString);
	Xstart = fmax( XCenterstart - strlen(pString) * localFont.Width / 2, 0) ;
	Paint_DrawString_EN(Xstart, Ystart, pString, &localFont, backgroundColor,  textColor);
}

void renderSafeAirBattery(bool drawDeltaImage)
{
	if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
	{
		switch (currentSmaStatus.batteryStrength)
		{
			case EMPTY:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_Battery_Alert, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_Battery_Alert, previousBatteryImage,
							SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousBatteryImage = gImage_SafeAir_Battery_Alert;
				break; /* optional */
			}

			case LOW:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_Battery_Low, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_Battery_Low, previousBatteryImage,
							SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousBatteryImage = gImage_SafeAir_Battery_Low;
				break; /* optional */
			}

			case MEDIUM:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_Battery_Medium, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_Battery_Medium, previousBatteryImage,
							SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousBatteryImage = gImage_SafeAir_Battery_Medium;
				break; /* optional */
			}

			case STRONG:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_Battery_Full, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_Battery_Full, previousBatteryImage,
							SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousBatteryImage = gImage_SafeAir_Battery_Full;
				break; /* optional */
			}

			case CHARGING:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_External_Power, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_External_Power, previousBatteryImage,
							SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousBatteryImage = gImage_SafeAir_External_Power;
				break; /* optional */
			}

			/* you can have any number of case statements */
			default: /* Optional */
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_Battery_Alert, SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_Battery_Alert, previousBatteryImage,
							SafeAirBatteryX, SafeAirBatteryY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousBatteryImage = gImage_SafeAir_Battery_Alert;
			}
		}
	}
}

void updateStatusText(void)
{
	if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
	{
		if (currentSmaStatus.smaState == TRIGGERED)
		{
			addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, RED);
			if (displayWarning.BITStatus & 0x40)
			{
				centeredString(SystemStatusTextX, SystemStatusTextY, "Manual Trigger", WHITE, RED, 14, Font12);
			}
			else if (displayWarning.BITStatus & 0x80)
			{
				centeredString(SystemStatusTextX, SystemStatusTextY, "GeoFencing", WHITE, RED, 14, Font12);
			}
			else if (displayWarning.BITStatus & 0x100)
			{
				centeredString(SystemStatusTextX, SystemStatusTextY, "AutoPilot", WHITE, RED, 14, Font12);
			}
			else if (displayWarning.BITStatus & 0x200)
			{
				centeredString(SystemStatusTextX, SystemStatusTextY, "Freefall", WHITE, RED, 14, Font12);
			}
			else if (displayWarning.BITStatus & 0x400)
			{
				centeredString(SystemStatusTextX, SystemStatusTextY, "Critical Angle", WHITE, RED, 14, Font12);
			}
		}
		else if ( ((currentSmaStatus.smaState == IDLE) /*&& (!displayWarning.displayWarning) && (displayWarning.BITStatus == 0)*/) || (isInfwUpdateMode) )
		{

			if (!isInfwUpdateMode)
			{
				addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3,BLUE);
				centeredString(SystemStatusTextX, SystemStatusTextY, "Idle", WHITE, BLUE, 14, Font12);

			}
			else
			{
				char localString[18] = "";
				sprintf(localString,"P#: %d / %d", packID, totalPackID);
				addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3,GRAYBLUE);
				centeredString(SystemStatusTextX, SystemStatusTextY, localString, WHITE, GRAYBLUE, 14, Font12);
			}
			previousBITStatus = displayWarning.BITStatus;
		}
		else if ((currentSmaStatus.smaState == ARMED) /*&& (!displayWarning.displayWarning) && (displayWarning.BITStatus == 0)*/)
		{
			addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, PZGREEN);
			centeredString(SystemStatusTextX, SystemStatusTextY, "Armed", WHITE, PZGREEN, 14, Font12);
			previousBITStatus = displayWarning.BITStatus;
		}
		else if (currentSmaStatus.smaState == AUTOCALIBRATION)
		{
			addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, GRAYBLUE);
			centeredString(SystemStatusTextX, SystemStatusTextY, "Calibration", WHITE, GRAYBLUE, 14, Font12);
		}
		else if (currentSmaStatus.smaState == TESTFLIGHT)
		{
			addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, DARKBLUE);
			centeredString(SystemStatusTextX, SystemStatusTextY, "Test-Flight", WHITE, DARKBLUE, 14, Font12);
		}
		else if (currentSmaStatus.smaState == MAINTENANCE)
		{
			addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, CYAN);
			centeredString(SystemStatusTextX, SystemStatusTextY, "Maintenance", BLACK, CYAN, 14, Font12);
		}
	}
}

void updateBITStatus(void)
{

	if (displayWarning.displayWarning)
	{
		if (shouldDrawRedAlertIcon)
		{
			//			if  ( (currentSmaStatus.smaState != ARMED) && (displayWarning.BITStatus != 0) )
			//			{
			//				addRectangleToFrame(0, SystemStatusTextY - 2, VerticalDisplayCenterWidth * 2, SystemStatusTextY - 2 + Font12.Height + 3, YELLOW);
			//				centeredString(SystemStatusTextX, SystemStatusTextY, "Error", BLACK, YELLOW, 14, Font12);
			//			}
			shouldUpdateStatusText = false;
		}
		Paint_ClearWindows(0, WarningTextY, VerticalDisplayCenterWidth * 2, WarningTextY + Font12.Height, BACKGROUND);
		if ( (displayWarning.BITStatus & 0x01) && (!isNoSignal) && (everReceivedConfigurationMessage) )
		{
			centeredString(WarningTextX, WarningTextY, "SA Critical Bat", BLACK, BACKGROUND, 14, Font12);
		}
		else if ( (displayWarning.BITStatus & 0x02) && (!isNoSignal) && (everReceivedConfigurationMessage) )
		{
			centeredString(WarningTextX, WarningTextY, "SA Low Bat", BLACK, BACKGROUND, 14, Font12);
		}
		else if ( (displayWarning.BITStatus & 0x04) && (!isNoSignal) && (everReceivedConfigurationMessage) )
		{
			centeredString(WarningTextX, WarningTextY, "SA Flash Error", BLACK, BACKGROUND, 14, Font12);
		}
		else if ( (displayWarning.BITStatus & 0x08) && (currentSmaStatus.smaState == IDLE) && (!isNoSignal) && (everReceivedConfigurationMessage) )
		{
			centeredString(WarningTextX, WarningTextY, "SA Orientation", BLACK, BACKGROUND, 14, Font12);
		}
		else if ( (displayWarning.BITStatus & 0x10) && (!isNoSignal) && (everReceivedConfigurationMessage) )
		{
			centeredString(WarningTextX, WarningTextY, "SA Pyro Error", BLACK, BACKGROUND, 14, Font12);
		}
		else if (displayWarning.BITStatus & 0x20)
		{
			centeredString(WarningTextX, WarningTextY, "RC Low Bat", BLACK, BACKGROUND, 14, Font12);
		}
		else if ( (displayWarning.BITStatus & abnormalGyro) && (ee.informationLevel & 0x1) )
		{
			centeredString(WarningTextX, WarningTextY, "Abnormal Gyro", BLACK, BACKGROUND, 14, Font12);
		}
		else if ( (displayWarning.BITStatus & abnormalAcceleration) && (ee.informationLevel & 0x1) )
		{
			centeredString(WarningTextX, WarningTextY, "Abnormal Accel", BLACK, BACKGROUND, 14, Font12);
		}
		else if ( (displayWarning.BITStatus & abnormalAngle) && (ee.informationLevel & 0x1) )
		{
			centeredString(WarningTextX, WarningTextY, "Abnormal Angle", BLACK, BACKGROUND, 14, Font12);
		}
	}
	else if ((!displayWarning.displayWarning) && (shouldClearDisplayedWarning))
	{

		if (!isPortrait)
		{
			Paint_ClearWindows(WarningIconX, WarningIconY, WarningIconX + statusBarIconWidth, WarningIconY + statusBarIconHeight, WHITE);
			Paint_ClearWindows(WarningTextX, WarningTextY, WarningTextX + 14 * Font12.Width, WarningTextY + Font12.Height, WHITE);
		}
		else
		{
			Paint_ClearWindows(0, WarningTextY, VerticalDisplayCenterWidth * 2, WarningTextY + Font12.Height, BACKGROUND);
		}
		shouldClearDisplayedWarning = false;
	}

}

void updatePlatformText(void)
{

	switch (currentSmaStatus.smaPlatformName)
	{
		case M200:
		{
			if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
			{
				centeredString(SystemTextX, SystemTextY, "SafeAir M200 Pro", BLACK, BACKGROUND, 16, Font12);
			}
			break;
		}
		case M300:
		{
			if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
			{
				centeredString(SystemTextX, SystemTextY, "SafeAir M300 Pro", BLACK, BACKGROUND, 16, Font12);
			}
			break;
		}
		case M600:
		{
			if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
			{
				centeredString(SystemTextX, SystemTextY, "SafeAir M600 Pro", BLACK, BACKGROUND, 16, Font12);
			}
			break;
		}
		case PHANTOM:
		{
			centeredString(SystemTextX, SystemTextY, "SafeAir Phantom", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case MAVIC:
		{
			centeredString(SystemTextX, SystemTextY, "SafeAir Mavic", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case SAFEAIR:
		{
			centeredString(SystemTextX, SystemTextY, "SafeAir", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case TAILID:
		{
			if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
			{
				if (isTailIDAlreadyReceived)
				{
					centeredString(SystemTextX, SystemTextY, safeAirTailID, BLACK, BACKGROUND, 11, Font16);
				}
				else
				{
					centeredString(SystemTextX, SystemTextY, "Waiting TailID", BLACK, BACKGROUND, 16, Font12);
				}
			}
			break;
		}
		case PHANTOMEU:
		{
			centeredString(SystemTextX, SystemTextY, "Phantom EU", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		case MAVICEU:
		{
			centeredString(SystemTextX, SystemTextY, "Mavic EU", BLACK, BACKGROUND, 16, Font12);
			break;
		}
		default: /* Optional */
		{
			centeredString(SystemTextX, SystemTextY, "Unknown platform", BLACK, BACKGROUND, 16, Font12);
		}
	}
	previousSmaStatus.smaPlatformName = currentSmaStatus.smaPlatformName;

}

void redrawBatteryIcon(bool drawDeltaImage)
{
	switch (batteryStrength)
	{
		case EMPTY:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_RC_Battery_Alert, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_RC_Battery_Alert, previousRCBatteryImage,
						BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			previousRCBatteryImage = gImage_RC_Battery_Alert;
			break; /* optional */
		}
		case LOW:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_RC_Battery_Low, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_RC_Battery_Low, previousRCBatteryImage,
						BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			previousRCBatteryImage = gImage_RC_Battery_Low;
			break; /* optional */
		}
		case MEDIUM:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_RC_Battery_Medium, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_RC_Battery_Medium, previousRCBatteryImage,
						BatteryX, BatteryY, statusBarIconWidth, statusBarIconWidth);
			}
			previousRCBatteryImage = gImage_RC_Battery_Medium;
			break; /* optional */
		}
		case STRONG:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_RC_Battery_Full, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_RC_Battery_Full, previousRCBatteryImage,
						BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			previousRCBatteryImage = gImage_RC_Battery_Full;
			break; /* optional */
		}
		case CHARGING:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_RC_Battery_Charging, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_RC_Battery_Charging, previousRCBatteryImage,
						BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			previousRCBatteryImage = gImage_RC_Battery_Charging;
			break; /* optional */
		}
		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_RC_Battery_Alert, BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_RC_Battery_Alert, previousRCBatteryImage,
						BatteryX, BatteryY, statusBarIconWidth, statusBarIconHeight);
			}
			previousRCBatteryImage = gImage_RC_Battery_Alert;
		}
	}
}

void redrawTriggerModeIcon(bool drawDeltaImage)
{
	if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
	{
		switch (currentSmaStatus.safeairTriggerMode)
		{
			case AUTO:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_Auto_Trigger, TriggerModeX, TriggerModeY,
							safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_Auto_Trigger, previousTriggerModeImage,
							TriggerModeX, TriggerModeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousTriggerModeImage = gImage_SafeAir_Auto_Trigger;
				break; /* optional */
			}

			case MANUAL:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_Manual_Trigger, TriggerModeX, TriggerModeY,
							safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_Manual_Trigger, previousTriggerModeImage,
							TriggerModeX, TriggerModeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousTriggerModeImage = gImage_SafeAir_Manual_Trigger;
				break; /* optional */
			}

			default: /* Optional */
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_SafeAir_Manual_Trigger, TriggerModeX, TriggerModeY,
							safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_SafeAir_Manual_Trigger, previousTriggerModeImage,
							TriggerModeX, TriggerModeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousTriggerModeImage = gImage_SafeAir_Manual_Trigger;
			}
		}
	}
}

void redrawBluetoothIcon(bool drawDeltaImage)
{
	switch (bluetoothConnection)
	{
		case DISCONNECTED:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Bluetooth_Disconnected, BluetoothX, BluetoothY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Bluetooth_Disconnected, previousBluetoothImage,
						BluetoothX, BluetoothY, statusBarIconWidth, statusBarIconHeight);
			}
			previousBluetoothImage = gImage_Bluetooth_Disconnected;
			break; /* optional */
		}

		case CONNECTED:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Bluetooth_Connected, BluetoothX, BluetoothY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Bluetooth_Connected, previousBluetoothImage,
						BluetoothX, BluetoothY, statusBarIconWidth, statusBarIconHeight);
			}
			previousBluetoothImage = gImage_Bluetooth_Connected;
			break; /* optional */
		}

		case SEARCHING:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Bluetooth_Searching, BluetoothX, BluetoothY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Bluetooth_Searching, previousBluetoothImage,
						BluetoothX, BluetoothY, statusBarIconWidth, statusBarIconHeight);
			}
			previousBluetoothImage = gImage_Bluetooth_Searching;
			break; /* optional */
		}

		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Bluetooth_Disconnected, BluetoothX, BluetoothY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Bluetooth_Disconnected, previousBluetoothImage,
						BluetoothX, BluetoothY, statusBarIconWidth, statusBarIconHeight);
			}
			previousBluetoothImage = gImage_Bluetooth_Disconnected;
		}
	}
}

void redrawSignalStrengthIcon(bool drawDeltaImage)
{
	switch (tbsLink)
	{
		case NOSIGNAL:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_RedNone, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_RedNone, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);

			}
			previousSignalImage = gImage_Signal_RedNone;
			break; /* optional */
		}

		case LOW:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_Low, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_Low, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			previousSignalImage = gImage_Signal_Low;
			break; /* optional */
		}

		case MEDIUM:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_Medium, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_Medium, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			previousSignalImage = gImage_Signal_Medium;
			break; /* optional */
		}

		case STRONG:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_Strong, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_Strong, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			previousSignalImage = gImage_Signal_Strong;
			break; /* optional */
		}

		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_Signal_RedNone, TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_Signal_RedNone, previousSignalImage,
						TBSSignalX, TBSSignalY, statusBarIconWidth, statusBarIconHeight);
			}
			previousSignalImage = gImage_Signal_RedNone;
		}
	}
}

void redrawAutoPilotIcon(bool drawDeltaImage)
{
	if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
	{
		switch (currentSmaStatus.autoPilotConnection)
		{
			case DISCONNECTED:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_AutoPilot_Disconnected, AutoPilotX, AutoPilotY,
							safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_AutoPilot_Disconnected, previousAutoPilotImage,
							AutoPilotX, AutoPilotY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousAutoPilotImage = gImage_AutoPilot_Disconnected;
				break; /* optional */
			}

			case CONNECTED:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_AutoPilot_Connected, AutoPilotX, AutoPilotY,
							safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_AutoPilot_Connected, previousAutoPilotImage,
							AutoPilotX, AutoPilotY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousAutoPilotImage = gImage_AutoPilot_Connected;
				break; /* optional */
			}

			default: /* Optional */
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_AutoPilot_Disconnected, AutoPilotX, AutoPilotY,
							safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_AutoPilot_Disconnected, previousAutoPilotImage,
							AutoPilotX, AutoPilotY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousAutoPilotImage = gImage_AutoPilot_Disconnected;
			}
		}
	}
}

void redrawPlatformIcon(bool drawDeltaImage)
{
	if ( (!isNoSignal) && (everReceivedConfigurationMessage) )
	{
		switch (currentSmaStatus.smaPlatfom)
		{
			case MULTICOPTER:
			{
				if (!drawDeltaImage)
				{

					Paint_DrawImage(gImage_Multicopter, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);

				}
				else
				{
					Paint_DrawDeltaImage(gImage_Multicopter, previousPlatformImage,
							PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousPlatformImage = gImage_Multicopter;
				break; /* optional */
			}

			case VTOLHORIZONTAL:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_VTOLHorizontal, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_VTOLHorizontal, previousPlatformImage,
							PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousPlatformImage = gImage_VTOLHorizontal;
				break; /* optional */
			}

			case VTOLTRANSITION:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_VTOLTransition, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_VTOLTransition, previousPlatformImage,
							PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousPlatformImage = gImage_VTOLTransition;
				break; /* optional */
			}

			case VTOLVERTICAL:
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_VTOLVertical, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_VTOLVertical, previousPlatformImage,
							PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousPlatformImage = gImage_VTOLVertical;
				break; /* optional */
			}

			default: /* Optional */
			{
				if (!drawDeltaImage)
				{
					Paint_DrawImage(gImage_Multicopter, PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				else
				{
					Paint_DrawDeltaImage(gImage_Multicopter, previousPlatformImage,
							PlatfomTypeX, PlatfomTypeY, safeAirBarIconWidth, safeAirBarIconHeight);
				}
				previousPlatformImage = gImage_Multicopter;
			}
		}
	}
}

void drawAltitudeIcon(bool drawDeltaImage)
{

	if (!drawDeltaImage)
	{
		if (lowerBarDisplayID == 0)
		{
			Paint_DrawImage(gImage_Altitude, AltitudeOrGPSX, AltitudeOrGPSY, statusBarIconWidth, statusBarIconHeight);
		}
		else if (lowerBarDisplayID == 1)
		{
			Paint_DrawImage(gImage_StopWatch, AltitudeOrGPSX, AltitudeOrGPSY, statusBarIconWidth, statusBarIconHeight);
		}
		else
		{
			Paint_DrawImage(gImage_Altitude, AltitudeOrGPSX, AltitudeOrGPSY, statusBarIconWidth, statusBarIconHeight);
		}
	}
	else
	{
		if (lowerBarDisplayID == 0)
		{
			Paint_DrawDeltaImage(gImage_Altitude, previousAltitudeOrGPSImage,
					AltitudeOrGPSX, AltitudeOrGPSY, statusBarIconWidth, statusBarIconHeight);
		}
		else if (lowerBarDisplayID == 1)
		{
			Paint_DrawDeltaImage(gImage_StopWatch, previousAltitudeOrGPSImage,
					AltitudeOrGPSX, AltitudeOrGPSY, statusBarIconWidth, statusBarIconHeight);
		}
		else
		{
			Paint_DrawDeltaImage(gImage_Altitude, previousAltitudeOrGPSImage,
					AltitudeOrGPSX, AltitudeOrGPSY, statusBarIconWidth, statusBarIconHeight);
		}
	}
	if (lowerBarDisplayID == 0)
	{
		previousAltitudeOrGPSImage = gImage_Altitude;
	}
	else if (lowerBarDisplayID == 1)
	{
		previousAltitudeOrGPSImage = gImage_StopWatch;
	}
	else
	{
		previousAltitudeOrGPSImage = gImage_Altitude;
	}


}

void drawTBSTxRxIcon(bool drawDeltaImage)
{
	switch (tbsTXRXStatus)
	{
		case TBSIDLE:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_DataTransferIdle, DataTransferX, DataTransferY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_DataTransferIdle, previousDataTransferImage,
						DataTransferX, DataTransferY, statusBarIconWidth, statusBarIconHeight);
			}
			previousDataTransferImage = gImage_DataTransferIdle;
			break; /* optional */
		}

		case TBSTX:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_DataTransferTransmit, DataTransferX, DataTransferY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_DataTransferTransmit, previousDataTransferImage,
						DataTransferX, DataTransferY, statusBarIconWidth, statusBarIconHeight);
			}
			previousDataTransferImage = gImage_DataTransferTransmit;
			break; /* optional */
		}

		case TBSRX:
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_DataTransferReceive, DataTransferX, DataTransferY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_DataTransferReceive, previousDataTransferImage,
						DataTransferX, DataTransferY, statusBarIconWidth, statusBarIconHeight);
			}
			previousDataTransferImage = gImage_DataTransferReceive;
			break; /* optional */
		}

		default: /* Optional */
		{
			if (!drawDeltaImage)
			{
				Paint_DrawImage(gImage_DataTransferIdle, DataTransferX, DataTransferY,
						statusBarIconWidth, statusBarIconHeight);
			}
			else
			{
				Paint_DrawDeltaImage(gImage_DataTransferIdle, previousDataTransferImage,
						DataTransferX, DataTransferY, statusBarIconWidth, statusBarIconHeight);
			}
			previousDataTransferImage = gImage_DataTransferIdle;
		}
	}
}

void screenUpdate(bool drawDeltaImage)
{
	numberOfDisplayedSafeAirIcons = 1 * isAutoPilotDisplayed + 1 * isPlatformDisplayed +
			1 * isTriggerModeDisplayed + 1 * isSafeAirBatteryDisplayed;
	setIconPositionOnScreen();
	if ( (!isMenuDisplayed) && (!isPopupDisplayed) )
	{
		if (!isLegacyDronePlatform)
		{
			if ( (shouldReDrawPlatformIcon) && (isPlatformDisplayed) )
			{
				redrawPlatformIcon(drawDeltaImage);
				shouldReDrawPlatformIcon = false;
			} // End of Should draw platform icon

			if ( (shouldReDrawAutoPilotIcon) && (isAutoPilotDisplayed) )
			{
				redrawAutoPilotIcon(drawDeltaImage);
				shouldReDrawAutoPilotIcon = false;
			} // End of should draw Auto-pilot icon

			if ( (shouldRedrawSafeAirBatteryIcon) && (isSafeAirBatteryDisplayed) )
			{
				renderSafeAirBattery(drawDeltaImage);
				shouldRedrawSafeAirBatteryIcon = false;
			}

			if ( (shouldReDrawTriggerModeIcon) && (isTriggerModeDisplayed) )
			{
				redrawTriggerModeIcon(drawDeltaImage);
				shouldReDrawTriggerModeIcon = false;
			}// End of should redraw trigger mode

			if ( (shouldDrawSafeAirAltitude) )
			{
				char localText[17] = "";
				Paint_DrawLine(LineStartX, LineY, LineEndX, LineY, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
				if (lowerBarDisplayID == 0)
				{
					if ((currentSmaStatus.smaState != ARMED) && (currentSmaStatus.smaState != TRIGGERED) && (!isAutoCalibActive) && (!isTestCalibActive))
					{
						sprintf(localText, "%06.1f m", 0.0);
					}
					else
					{
						sprintf(localText, "%06.1f m", currentSmaStatus.Altitude);
					}
				}
				else if (lowerBarDisplayID == 1)
				{
					//					int localMinutes = durationMultiplier * 30 + remainingCalibrationTime / (60 * 1000);
					//					int localSeconds = 0;
					int localHours = remainingCalibrationTime / (3600);
					int localMinutes = (remainingCalibrationTime - localHours * 3600) / 60;
					//					int localSeconds = remainingCalibrationTime - localMinutes * 60;
					//					if (durationMultiplier == 0)
					//					{
					//						localSeconds = remainingCalibrationTime - (remainingCalibrationTime / (60 * 1000)) * 60 * 1000;
					//					}
					sprintf(localText, "%02d:%02d", localHours, localMinutes);
				}
				else
				{
					if ((currentSmaStatus.smaState != ARMED) && (currentSmaStatus.smaState != TRIGGERED) && (!isAutoCalibActive) && (!isTestCalibActive))
					{
						sprintf(localText, "%06.1f m", 0.0);
					}
					else
					{
						sprintf(localText, "%06.1f m", currentSmaStatus.Altitude);
					}
				}
				centeredString(74, 138, localText, BLACK, BACKGROUND, 8, Font16);
				drawAltitudeIcon(drawDeltaImage);
				shouldDrawSafeAirAltitude = false;
			}
		}
		else
		{
			Paint_DrawImage(gImage_ParaZero_Logo_Legacy_62_77, FullLogoX, FullLogoY, FullLogoWidth, FullLogoHeight);
		}

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

		if (shouldRedrawBatteryIcon)
		{
			redrawBatteryIcon(drawDeltaImage);
			shouldRedrawBatteryIcon = false;
		} // End of should redraw battery icon

		if (shouldUpdatePlatformText)
		{
			//TODO: update to display Tail ID or PlatformType
			updatePlatformText();
			shouldUpdatePlatformText = false;
		} // End of should update platform text

		if (shouldUpdateStatusText)
		{

			updateStatusText();
			shouldUpdateStatusText = false;
		} // End of should update status text

		if ( (menuLevel == DEVELOPER) )
		{
			if ( (tbsTXRXStatus != TBSRX) && (HAL_GetTick() - lastLogDataRefresh < 500) )
			{
				tbsTXRXStatus = TBSRX;
//				drawTBSTxRxIcon(drawDeltaImage);
			}
			else if ( (HAL_GetTick() - lastLogDataRefresh >= 500) && (HAL_GetTick() - lastLogDataRefresh < 1000) )
			{
//				lastLogDataRefresh = HAL_GetTick();
//				drawTBSTxRxIcon(drawDeltaImage);
			}
			if (HAL_GetTick() - lastLogDataRefresh >= 1000)
			{
				tbsTXRXStatus = TBSIDLE;
//				drawTBSTxRxIcon(drawDeltaImage);
				shouldRenderDataTransfer = false;
//				lastLogDataRefresh = HAL_GetTick();
			}
			drawTBSTxRxIcon(drawDeltaImage);
		}

		if (HAL_GetTick() - lastBITStatusChange >= 500)
		{
			lastBITStatusChange = HAL_GetTick();
			updateBITStatus();
		}
	} // end of RC and SafeAir data display
	else if (isMenuDisplayed)
	{
		if (shouldRenderMenu)
		{
			drawMenu(shouldClearScreen, menuDrawDirection);
			shouldRenderMenu = false;
			lastReceivedCRSFMessage = HAL_GetTick();
		}
		if (shouldRenderItem)
		{
			drawItem(false, itemDrawDirection);
			shouldRenderItem = false;
			lastReceivedCRSFMessage = HAL_GetTick();
		}

	} // End of is Menu displayed
	if(shouldRenderPopup)
	{
		drawPopup();
		shouldRenderPopup = false;
		lastReceivedCRSFMessage = HAL_GetTick();
	}
}

void drawMenu(bool clearScreen, MENUDRAWType howToDraw)
{
	if (clearScreen)
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true, false);
	}

	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
	}
	else
	{
		MenuRectangleStartX = HorizontalMenuRectangleStartX;
		MenuRectangleStartY = HorizontalMenuRectangleStartY;
		MenuRectangleHeight = HorizontalMenuRectangleHeight;
		MenuRectangleWidth = HorizontalMenuRectangleWidth;
		DisplayCenterWidth = HorizontalDisplayCenterWidth;
	}

	if (howToDraw == FULL)
	{
		for (int i = 0; i < pagesArray[currentCursorPosition.currentPageID].numberOfItemsInPage; i++)
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + MenuRectangleHeight * i,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + MenuRectangleHeight * ( i + 1),
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
			if (i == currentCursorPosition.cursorPosition)
			{
				centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * i,
						pagesArray[currentCursorPosition.currentPageID].itemsArray[i], BLACK, LGRAY, 16, Font12);
			}
			else
			{
				centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * i,
						pagesArray[currentCursorPosition.currentPageID].itemsArray[i], BLACK, WHITE, 16, Font12);
			}
		}
	}
	else if (howToDraw == UP)
	{
		centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * (currentCursorPosition.cursorPosition + 1),
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition + 1], BLACK, WHITE, 16, Font12);
		centeredString(DisplayCenterWidth, MenuRectangleStartY+ 1 + MenuRectangleHeight * currentCursorPosition.cursorPosition,
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition], BLACK, LGRAY, 16, Font12);
	}
	else if (howToDraw == DOWN)
	{
		centeredString(DisplayCenterWidth, MenuRectangleStartY + 1 + MenuRectangleHeight * (currentCursorPosition.cursorPosition - 1),
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition - 1], BLACK, WHITE, 16, Font12);
		centeredString(DisplayCenterWidth, MenuRectangleStartY+ 1 + MenuRectangleHeight * currentCursorPosition.cursorPosition,
				pagesArray[currentCursorPosition.currentPageID].itemsArray[currentCursorPosition.cursorPosition], BLACK, LGRAY, 16, Font12);
	}
}

void drawItem(bool clearScreen, MENUDRAWType howToDraw)
{
	if ((clearScreen) || (!isItemDisplayed) )
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true, false);
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
	uint8_t MenuRectangleStartX = 0;
	uint8_t MenuRectangleStartY = 0;
	uint8_t MenuRectangleHeight = 0;
	uint8_t MenuRectangleWidth = 0;
	uint8_t DisplayCenterWidth = 0;
	uint8_t PopupRectangleHeight = 0;
	uint8_t QuestionRectangleHeight = 0;

	if (isPortrait)
	{
		MenuRectangleStartX = VerticalMenuRectangleStartX;
		MenuRectangleStartY = VerticalMenuRectangleStartY;
		MenuRectangleHeight = VerticalMenuRectangleHeight;
		MenuRectangleWidth = VerticalMenuRectangleWidth;
		DisplayCenterWidth = VerticalDisplayCenterWidth;
		PopupRectangleHeight = VerticalPopupRectangleHeight;
		QuestionRectangleHeight = VerticalQuestionRectangleHeight;
	}
	else
	{
		MenuRectangleStartX = HorizontalMenuRectangleStartX;
		MenuRectangleStartY = HorizontalMenuRectangleStartY;
		MenuRectangleHeight = HorizontalMenuRectangleHeight;
		MenuRectangleWidth = HorizontalMenuRectangleWidth;
		DisplayCenterWidth = HorizontalDisplayCenterWidth;
		PopupRectangleHeight = HorizontalPopupRectangleHeight;
		QuestionRectangleHeight = HorizontalQuestionRectangleHeight;
	}

	isPopupDisplayed = true;
	isItemDisplayed = false;
	isMenuDisplayed = false;
	if (popupDrawDirection == FULL)
	{
		Paint_Clear(WHITE);
		createEmptyFrame(true, false);
		Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY ,
				MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + PopupRectangleHeight,
				BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );

		if (popupToShow.isQuestion)
		{
			Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + QuestionRectangleHeight,
					MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + QuestionRectangleHeight + MenuRectangleHeight,
					BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );
		}

		Paint_DrawRectangle( MenuRectangleStartX, MenuRectangleStartY + PopupRectangleHeight,
				MenuRectangleStartX + MenuRectangleWidth, MenuRectangleStartY + PopupRectangleHeight + MenuRectangleHeight,
				BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY );

		for (int i = 0 ; i < popupToShow.numberOfItemsInPopup - 2; i++)
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + MenuRectangleHeight * (i + 1) + 1,
					popupToShow.itemsArray[i], BLACK, WHITE, 16, Font12);
		}
	}

	if (popupToShow.isQuestion)
	{
		if ( (popupDrawDirection == FULL) || (popupDrawDirection == UP))
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + QuestionRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 2], BLACK, LGRAY, 16, Font12);

			centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, WHITE, 16, Font12);
		}
		else
		{
			centeredString( DisplayCenterWidth, MenuRectangleStartY + QuestionRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 2], BLACK, WHITE, 16, Font12);

			centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
					popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, LGRAY, 16, Font12);
		}
	}
	else
	{
		centeredString( DisplayCenterWidth, MenuRectangleStartY + PopupRectangleHeight + 1,
				popupToShow.itemsArray[popupToShow.numberOfItemsInPopup - 1], BLACK, LGRAY, 16, Font12);
	}
}

void setFullDisplay(void)
{
	shouldRedrawBatteryIcon = true;
	shouldRedrawSignalStrengthIcon = true;
	shouldReDrawBluetoothIcon = isBLEOn;

	shouldUpdatePlatformText = true;

	shouldUpdateStatusText = true;

	shouldReDrawAutoPilotIcon = false;
	shouldReDrawPlatformIcon = false;
	shouldReDrawTriggerModeIcon = true;
	shouldRedrawSafeAirBatteryIcon = true;
	shouldDrawSafeAirAltitude = true;

	shouldClearDisplayedWarning = false;
	isPopupDisplayed = false;
	isMenuDisplayed = false;
	isItemDisplayed = false;
	shouldRenderPopup = false;
	shouldRenderItem = false;
	shouldRenderMenu = false;

	//	shouldDrawRedAlertIcon = false;
}

void setIconPositionOnScreen(void)
{
	if (isPortrait)
	{

		BluetoothX = VerticalBluetoothX;
		BluetoothY = VerticalBluetoothY;
		DataTransferX = VerticalDataTransferX;
		DataTransferY = VerticalDataTransferY;
		TBSSignalX = VerticalTBSSignalX;
		TBSSignalY = VerticalTBSSignalY;
		BatteryX = VerticalBatteryX;
		BatteryY = VerticalBatteryY;

		AutoPilotY = VerticalAutoPilotY;

		SystemStatusTextX = VerticalSystemStatusTextX;
		SystemStatusTextY = VerticalSystemStatusTextY;

		SystemTextX = VerticalSystemTextX;
		SystemTextY = VerticalSystemTextY;

		WarningTextX = VerticalWarningTextX;
		WarningTextY = VerticalWarningTextY;

		LineStartX = VerticalSafeAirLineStartX;
		LineEndX = VerticalSafeAirLineEndX;
		LineY = VerticalSafeAirLineY;

		AltitudeOrGPSX = VerticalAltitudeOrGPSX;
		AltitudeOrGPSY = VerticalAltitudeOrGPSY;


		SafeAirBatteryX = (numberOfDisplayedSafeAirIcons /2 - 1 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;//VerticalSafeAirBatteryX;
		SafeAirBatteryY = VerticalSafeAirBatteryY;
		TriggerModeX = (numberOfDisplayedSafeAirIcons /2 - 2 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
		TriggerModeY = VerticalTriggerModeY;
		PlatfomTypeX = (numberOfDisplayedSafeAirIcons /2 - 3 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
		PlatfomTypeY = VerticalPltfomTypeY;
		AutoPilotX = (numberOfDisplayedSafeAirIcons /2 - 4 ) * safeAirBarIconWidth + VerticalDisplayCenterWidth;
		AutoPilotY = VerticalAutoPilotY;

		ChargingModeImageX = VerticalChargingModeX;
		ChargingModeImageY = VerticalChargingModeX;
		ChargingModePercentTextX = VerticalChargingModePercentX;
		ChargingModePercentTextY = VerticalChargingModePercentY;

		FullLogoX = VerticalFullLogoX;
		FullLogoY = VerticalFullLogoY;
	}
	else
	{
		PlatfomTypeX = HorizontalPltfomTypeX;
		PlatfomTypeY = HorizontalPltfomTypeY;
		AutoPilotX = HorizontalAutoPilotX;
		AutoPilotY = HorizontalAutoPilotY;
		DataTransferX = VerticalDataTransferX;
		DataTransferY = VerticalDataTransferY;
		TBSSignalX = HorizontalTBSSignalX;
		TBSSignalY = HorizontalTBSSignalY;
		BluetoothX = HorizontalBluetoothX;
		BluetoothY = HorizontalBluetoothY;
		TriggerModeX = HorizontalTriggerModeX;
		TriggerModeY = HorizontalTriggerModeY;
		BatteryX = HorizontalBatteryX;
		BatteryY = HorizontalBatteryY;
		SystemTextX = HorizontalSystemTextX;
		SystemTextY = HorizontalSystemTextY;
		SafeAirBatteryX = HorizontalSafeAirBatteryTextX;
		SafeAirBatteryY = HorizontalSafeAirBatteryTextY;
		//		FullLogoX = HorizontalFullLogoX;
		//		FullLogoY = HorizontalFullLogoY;
	}
}

void drawChargingDots(void)
{
	if (dotCycle == 0)
	{
		Paint_DrawImage(gImage_WeakDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeSecondDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeThirdDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_SuperStrongDot, VerticalChargingModeForthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeFifthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
	}
	else if (dotCycle == 1)
	{
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_WeakDot, VerticalChargingModeSecondDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeThirdDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeForthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_SuperStrongDot, VerticalChargingModeFifthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
	}
	else if (dotCycle == 2)
	{
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeSecondDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_WeakDot, VerticalChargingModeThirdDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeForthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeFifthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_SuperStrongDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
	}
	else if (dotCycle == 3)
	{
		Paint_DrawImage(gImage_SuperStrongDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeSecondDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeThirdDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_WeakDot, VerticalChargingModeForthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeFifthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
	}
	else if (dotCycle == 4)
	{
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_SuperStrongDot, VerticalChargingModeSecondDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeThirdDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeForthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_WeakDot, VerticalChargingModeFifthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
	}
	else if (dotCycle == 5)
	{
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeSecondDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_SuperStrongDot, VerticalChargingModeThirdDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_StrongDot, VerticalChargingModeForthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_MediumDot, VerticalChargingModeFifthDotX, VerticalChargingModeDotY, 12, 12);
		Paint_DrawImage(gImage_WeakDot, VerticalChargingModeFirstDotX, VerticalChargingModeDotY, 12, 12);
	}
	if (HAL_GetTick() - lastDotRefresh > 100)
	{
		lastDotRefresh = HAL_GetTick();
		dotCycle++;
		if (dotCycle >= 6)
		{
			dotCycle = 0;
		}
	}
}

void drawScreenSaver(void)
{
	Paint_DrawMovingObject(gImage_LoGoScreenSaver, gImage_LoGoScreenSaverTemplate,
			posX, posY, 26, 30);
	if ( (posX + velX>= 0) && (posX + velX + 26 <= SCREEN_WIDTH) )
	{
		posX += velX;
	}
	else
	{
		velX = -velX;
		posX += velX;
	}
	if  ( (posY + velY>= 0) && (posY + velY + 30 <= SCREEN_HEIGHT) )
	{
		posY += velY;
	}
	else
	{
		velY = -velY;
		posY += velY;
	}
}
