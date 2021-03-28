################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BlueNRG_2/App/app_bluenrg_2.c 

OBJS += \
./BlueNRG_2/App/app_bluenrg_2.o 

C_DEPS += \
./BlueNRG_2/App/app_bluenrg_2.d 


# Each subdirectory must supply rules for building sources it contributes
BlueNRG_2/App/app_bluenrg_2.o: ../BlueNRG_2/App/app_bluenrg_2.c BlueNRG_2/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../Middlewares/ST/BlueNRG-2/utils -I../Middlewares/ST/BlueNRG-2/includes -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/BSP/custom" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/BlueNRG_2/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/BlueNRG_2/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"BlueNRG_2/App/app_bluenrg_2.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

