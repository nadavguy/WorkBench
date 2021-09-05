/*
 * popupHelper.c
 *
 *  Created on: May 2, 2021
 *      Author: gilad
 */


#include "main.h"
#include "usb_device.h"
#include "GUI_Paint.h"
#include "ScreenAgent.h"
uint32_t popupShowTime = 0;

void showWaitForSAAck()
{
	createEmptyFrame(false, false);
	char localString[12] = "Waiting for\0";
	char localString2[10] = "SafeAir's\0";
	char localString3[15] = "Acknowledgment\0";
	centeredString(64, 68, localString, BLACK, BACKGROUND, 11, Font12);
	centeredString(64, 80, localString2, BLACK, BACKGROUND, 9, Font12);
	centeredString(64, 92, localString3, BLACK, BACKGROUND, 14, Font12);
	updateNextFrame();
}

void waitForPopupInput(void)
{
	popupShowTime = HAL_GetTick();
	if (popupToShow.popupID != 0)
	{
		shouldRenderPopup = true;
		screenUpdate(false);
		switch (popupToShow.popupID)
		{
			case 1:
			{

				while ( (tbsLink == NOSIGNAL) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
//					HAL_Delay(50);
					screenUpdate(false);
					updateNextFrame();
					readUSBData();
				}
				break;
			}
			case 2:
			{
				waitForAckResponse = false;
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{
						forceDisarmEnabled = true;
						waitForAckResponse = true;
						configurationMessageCounter++;
						break;
					}
					sendChannelMessageToTBS();
					sendSafeAirConfigurationMessage(false);
					updateRCState();
					CheckButtons();
//					HAL_Delay(50);
					screenUpdate(false);
					updateNextFrame();
				}
				while (waitForAckResponse)
				{
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					showWaitForSAAck();
				}
				forceDisarmEnabled = false;
//				waitForAckResponse = false;
				break;
			} //End of Force Disarm
			case 3:
			{
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{
						func_fmt();
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				break;
			} // End of RC clear storage
			case 4:
			{
				waitForAckResponse = false;
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{
						formatSDEnabled = true;
						waitForAckResponse = true;
						configurationMessageCounter++;
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				while (waitForAckResponse)
				{
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
				}
				formatSDEnabled = false;
//				waitForAckResponse = false;
				break;
			} //End of Clear SafeAir storage
			case 5:
			{
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 10) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 10) && (popupDrawDirection == DOWN))
					{
						//Make BLE visible
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				break;
			} //End of make bluetooth visible
			case 6:
			{
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 10) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 10) && (popupDrawDirection == DOWN))
					{
						//Make BLE Active
						ee.bluetoothStatus = 1;
						isBLEOn = true;
						ee_save1();
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				break;
			} //End of make bluetooth Active
			case 7:
			{
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 10) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 10) && (popupDrawDirection == DOWN))
					{
						isMSCMode = true;
						MX_MSC_DEVICE_Init();
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				break;
			} //End of change to mass storage
			case 8:
			{
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 10) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 10) && (popupDrawDirection == DOWN))
					{

						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				break;
			} //End of About RC

			case 9:
			{
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 10) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 10) && (popupDrawDirection == DOWN))
					{

						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				break;
			} //End of About BLE

			case 10:
			{

				while (isChargingMode)
				{
					if ( (!popupToShow.isQuestion) &&
							( (okButtonPressDuration >= 1000) || (HAL_GetTick() - popupShowTime > 3000) ) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{
						break;
					}
					updateRCState();
					CheckButtons();
					//					HAL_Delay(50);
					screenUpdate(false);
					updateNextFrame();
				}
				break;
			}

			case 11:
			{
				waitForAckResponse = false;
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN) )
					{
						if (!isAutoCalibActive)
						{
							isAutoCalibActive = true;
						}
						else
						{
							isAutoCalibActive = false;
							safeairConfiguration.state = 1;
						}
						waitForAckResponse = true;
						configurationMessageCounter++;
						break;
					}
					sendChannelMessageToTBS();

					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				while (waitForAckResponse)
				{
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					showWaitForSAAck();
				}
				initMenuPages();
				initPopupMessages();
				break;
			} //End of AutoCalib

			case 12:
			{
				waitForAckResponse = false;
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN) )
					{
						if (!isTestCalibActive)
						{
							isTestCalibActive = true;
						}
						else
						{
							isTestCalibActive = false;
							safeairConfiguration.state = 1;
						}
						waitForAckResponse = true;
						configurationMessageCounter++;
						break;
					}
					sendChannelMessageToTBS();

					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				while (waitForAckResponse)
				{
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					showWaitForSAAck();
				}
				initMenuPages();
				initPopupMessages();
				break;
			} //End of TestCalib

			case 13:
			{
				waitForAckResponse = false;
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{
						testMotorCut = true;
						waitForAckResponse = true;
						configurationMessageCounter++;
						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				while (waitForAckResponse)
				{
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					showWaitForSAAck();
				}
				testMotorCut = false;
				initMenuPages();
				initPopupMessages();
				break;
			} //End of Test Motor Cut

			case 14:
			{
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{

						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				initMenuPages();
				initPopupMessages();
				break;
			}

			case 15:
			{
				while ( (okButtonPressDuration < 1075) )
				{
					if ( (!popupToShow.isQuestion) && (okButtonPressDuration >= 1000) )
					{
						break;
					}
					if ( (popupToShow.isQuestion) && (okButtonPressDuration >= 1000) && (popupDrawDirection == DOWN))
					{

						break;
					}
					sendChannelMessageToTBS();
					updateRCState();
					CheckButtons();
					screenUpdate(false);
					updateNextFrame();
				}
				initMenuPages();
				initPopupMessages();
				break;
			}

			default:
			{
				break;
			}
		}
		memset(&popupToShow, 0, sizeof(popupToShow));
		screenClear();
		setFullDisplay();
		screenUpdate(false);
	}
}
