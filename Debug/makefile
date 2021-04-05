################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Support/Src/subdir.mk
-include Modules/Src/subdir.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Middlewares/ST/BlueNRG-2/utils/subdir.mk
-include Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic/subdir.mk
-include Middlewares/ST/BlueNRG-2/hci/controller/subdir.mk
-include Middlewares/ST/BlueNRG-2/hci/subdir.mk
-include Hardware/Screen/image/subdir.mk
-include Hardware/Screen/example/subdir.mk
-include Hardware/Screen/LCD/subdir.mk
-include Hardware/Screen/GUI_DEV/subdir.mk
-include Hardware/Screen/Fonts/subdir.mk
-include Hardware/Screen/Config/subdir.mk
-include Hardware/MSC/Class/Src/subdir.mk
-include Hardware/MSC/App/subdir.mk
-include FATFS/Target/subdir.mk
-include FATFS/App/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/custom/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include BlueNRG_2/Target/subdir.mk
-include BlueNRG_2/App/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := RC-BeyondTheIronCurtain
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
RC-BeyondTheIronCurtain.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
RC-BeyondTheIronCurtain.list \

OBJCOPY_BIN += \
RC-BeyondTheIronCurtain.bin \


# All Target
all: main-build

# Main-build Target
main-build: RC-BeyondTheIronCurtain.elf secondary-outputs

# Tool invocations
RC-BeyondTheIronCurtain.elf: $(OBJS) $(USER_OBJS) C:\Users\gilad\Downloads\STM32MiniCar-master\ (3)\RCF777Based\STM32F777VITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "RC-BeyondTheIronCurtain.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\gilad\Downloads\STM32MiniCar-master (3)\RCF777Based\STM32F777VITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="RC-BeyondTheIronCurtain.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

RC-BeyondTheIronCurtain.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "RC-BeyondTheIronCurtain.list"
	@echo 'Finished building: $@'
	@echo ' '

RC-BeyondTheIronCurtain.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "RC-BeyondTheIronCurtain.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
