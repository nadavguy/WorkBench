################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Src/BleAgent.c \
../Modules/Src/BuzzerAgent.c \
../Modules/Src/ConfigParams.c \
../Modules/Src/EEPROMAgent.c \
../Modules/Src/LogAgent.c \
../Modules/Src/PowerAgent.c \
../Modules/Src/PushButton.c \
../Modules/Src/ScreenAgent.c \
../Modules/Src/TBSAgent.c \
../Modules/Src/ci_func.c \
../Modules/Src/cmd_interp.c \
../Modules/Src/stm32746g_qspi.c 

OBJS += \
./Modules/Src/BleAgent.o \
./Modules/Src/BuzzerAgent.o \
./Modules/Src/ConfigParams.o \
./Modules/Src/EEPROMAgent.o \
./Modules/Src/LogAgent.o \
./Modules/Src/PowerAgent.o \
./Modules/Src/PushButton.o \
./Modules/Src/ScreenAgent.o \
./Modules/Src/TBSAgent.o \
./Modules/Src/ci_func.o \
./Modules/Src/cmd_interp.o \
./Modules/Src/stm32746g_qspi.o 

C_DEPS += \
./Modules/Src/BleAgent.d \
./Modules/Src/BuzzerAgent.d \
./Modules/Src/ConfigParams.d \
./Modules/Src/EEPROMAgent.d \
./Modules/Src/LogAgent.d \
./Modules/Src/PowerAgent.d \
./Modules/Src/PushButton.d \
./Modules/Src/ScreenAgent.d \
./Modules/Src/TBSAgent.d \
./Modules/Src/ci_func.d \
./Modules/Src/cmd_interp.d \
./Modules/Src/stm32746g_qspi.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/Src/BleAgent.o: ../Modules/Src/BleAgent.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/BleAgent.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/BuzzerAgent.o: ../Modules/Src/BuzzerAgent.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/BuzzerAgent.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/ConfigParams.o: ../Modules/Src/ConfigParams.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/ConfigParams.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/EEPROMAgent.o: ../Modules/Src/EEPROMAgent.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/EEPROMAgent.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/LogAgent.o: ../Modules/Src/LogAgent.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/LogAgent.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/PowerAgent.o: ../Modules/Src/PowerAgent.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/PowerAgent.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/PushButton.o: ../Modules/Src/PushButton.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/PushButton.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/ScreenAgent.o: ../Modules/Src/ScreenAgent.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/ScreenAgent.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/TBSAgent.o: ../Modules/Src/TBSAgent.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/TBSAgent.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/ci_func.o: ../Modules/Src/ci_func.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/ci_func.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/cmd_interp.o: ../Modules/Src/cmd_interp.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/cmd_interp.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Src/stm32746g_qspi.o: ../Modules/Src/stm32746g_qspi.c Modules/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -DSTM32F7 -c -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Modules/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Support/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Config" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/Fonts" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/GUI_DEV" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/image" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/LCD" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/Screen/example" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/CMSIS/Include" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Middlewares/Third_Party/FatFs/src" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/Target" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/USB_DEVICE/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/FATFS/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/App" -I"/home/nadav/Documents/MXProjects/RC-BeyondTheIronCurtain/Hardware/MSC/Class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Modules/Src/stm32746g_qspi.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

