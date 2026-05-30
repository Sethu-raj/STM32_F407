################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/001_LED_TOGGLE.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/001_LED_TOGGLE.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/001_LED_TOGGLE.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/hp/STM32CubeIDE/workspace_1.18.0/18_GPIO_Driver/Inc" -I"C:/Users/hp/STM32CubeIDE/workspace_1.18.0/18_GPIO_Driver/Drivers/Inc" -I"C:/Users/hp/STM32CubeIDE/workspace_1.18.0/18_GPIO_Driver/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/001_LED_TOGGLE.cyclo ./Src/001_LED_TOGGLE.d ./Src/001_LED_TOGGLE.o ./Src/001_LED_TOGGLE.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

