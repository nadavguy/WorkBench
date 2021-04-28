################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/App/fatfs.c 

OBJS += \
./FATFS/App/fatfs.o 

C_DEPS += \
./FATFS/App/fatfs.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/App/fatfs.o: ../FATFS/App/fatfs.c FATFS/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -c -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Modules/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Support/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Config" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Fonts" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/GUI_DEV" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/image" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/LCD" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/example" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Core/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Drivers/CMSIS/Include" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/USB_DEVICE/Target" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Middlewares/Third_Party/FatFs/src" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/FATFS/Target" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/USB_DEVICE/App" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/FATFS/App" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/MSC/App" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/MSC/Class/Inc" -I../FATFS/App -I../USB_DEVICE/Target -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../FATFS/Target -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FATFS/App/fatfs.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

