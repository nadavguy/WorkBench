################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_DEVICE/App/usb_device.c \
../USB_DEVICE/App/usbd_cdc_if.c \
../USB_DEVICE/App/usbd_desc.c 

OBJS += \
./USB_DEVICE/App/usb_device.o \
./USB_DEVICE/App/usbd_cdc_if.o \
./USB_DEVICE/App/usbd_desc.o 

C_DEPS += \
./USB_DEVICE/App/usb_device.d \
./USB_DEVICE/App/usbd_cdc_if.d \
./USB_DEVICE/App/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
USB_DEVICE/App/usb_device.o: ../USB_DEVICE/App/usb_device.c USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -c -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Modules/Inc" -I../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../Middlewares/ST/BlueNRG-2/utils -I../Middlewares/ST/BlueNRG-2/includes -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Support/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Config" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Fonts" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/GUI_DEV" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/image" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/LCD" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/example" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"USB_DEVICE/App/usb_device.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
USB_DEVICE/App/usbd_cdc_if.o: ../USB_DEVICE/App/usbd_cdc_if.c USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -c -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Modules/Inc" -I../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../Middlewares/ST/BlueNRG-2/utils -I../Middlewares/ST/BlueNRG-2/includes -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Support/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Config" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Fonts" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/GUI_DEV" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/image" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/LCD" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/example" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"USB_DEVICE/App/usbd_cdc_if.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
USB_DEVICE/App/usbd_desc.o: ../USB_DEVICE/App/usbd_desc.c USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -c -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Modules/Inc" -I../Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -I../Middlewares/ST/BlueNRG-2/utils -I../Middlewares/ST/BlueNRG-2/includes -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Support/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Config" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/Fonts" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/GUI_DEV" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/image" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/LCD" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/example" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"USB_DEVICE/App/usbd_desc.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

