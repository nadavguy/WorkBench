################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f777vitx.s 

OBJS += \
./Core/Startup/startup_stm32f777vitx.o 

S_DEPS += \
./Core/Startup/startup_stm32f777vitx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32f777vitx.o: ../Core/Startup/startup_stm32f777vitx.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Modules/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Support/Inc" -I"C:/Users/gilad/Downloads/STM32MiniCar-master (3)/RCF777Based/Hardware/Screen/example" -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32f777vitx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

