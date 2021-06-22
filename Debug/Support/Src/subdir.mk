################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Support/Src/Common.c \
../Support/Src/ConfigurationHelper.c \
../Support/Src/FrameHelper.c \
../Support/Src/ItemHelper.c \
../Support/Src/MenuHelper.c \
../Support/Src/PopupHelper.c \
../Support/Src/TimeHelper.c \
../Support/Src/TypeDefs.c \
../Support/Src/iap.c \
../Support/Src/ymodem.c 

OBJS += \
./Support/Src/Common.o \
./Support/Src/ConfigurationHelper.o \
./Support/Src/FrameHelper.o \
./Support/Src/ItemHelper.o \
./Support/Src/MenuHelper.o \
./Support/Src/PopupHelper.o \
./Support/Src/TimeHelper.o \
./Support/Src/TypeDefs.o \
./Support/Src/iap.o \
./Support/Src/ymodem.o 

C_DEPS += \
./Support/Src/Common.d \
./Support/Src/ConfigurationHelper.d \
./Support/Src/FrameHelper.d \
./Support/Src/ItemHelper.d \
./Support/Src/MenuHelper.d \
./Support/Src/PopupHelper.d \
./Support/Src/TimeHelper.d \
./Support/Src/TypeDefs.d \
./Support/Src/iap.d \
./Support/Src/ymodem.d 


# Each subdirectory must supply rules for building sources it contributes
Support/Src/Common.o: ../Support/Src/Common.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/Common.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/ConfigurationHelper.o: ../Support/Src/ConfigurationHelper.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/ConfigurationHelper.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/FrameHelper.o: ../Support/Src/FrameHelper.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/FrameHelper.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/ItemHelper.o: ../Support/Src/ItemHelper.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/ItemHelper.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/MenuHelper.o: ../Support/Src/MenuHelper.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/MenuHelper.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/PopupHelper.o: ../Support/Src/PopupHelper.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/PopupHelper.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/TimeHelper.o: ../Support/Src/TimeHelper.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/TimeHelper.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/TypeDefs.o: ../Support/Src/TypeDefs.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/TypeDefs.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/iap.o: ../Support/Src/iap.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/iap.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Support/Src/ymodem.o: ../Support/Src/ymodem.c Support/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../FATFS/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Support/Src/ymodem.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

