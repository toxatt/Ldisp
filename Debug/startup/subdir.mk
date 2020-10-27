################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

