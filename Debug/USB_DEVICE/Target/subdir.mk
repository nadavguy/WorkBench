################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_DEVICE/Target/usbd_conf.c 

OBJS += \
./USB_DEVICE/Target/usbd_conf.o 

C_DEPS += \
./USB_DEVICE/Target/usbd_conf.d 


# Each subdirectory must supply rules for building sources it contributes
USB_DEVICE/Target/usbd_conf.o: ../USB_DEVICE/Target/usbd_conf.c USB_DEVICE/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"USB_DEVICE/Target/usbd_conf.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

