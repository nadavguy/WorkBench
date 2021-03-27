################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/hci_tl.c 

OBJS += \
./Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/hci_tl.o 

C_DEPS += \
./Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/hci_tl.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/hci_tl.o: ../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/hci_tl.c Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -c -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Modules/Inc" -I../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../Middlewares/ST/BlueNRG-2/utils -I../Middlewares/ST/BlueNRG-2/includes -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Support/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Config" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Fonts" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/GUI_DEV" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/image" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/LCD" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/example" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/hci_tl.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

