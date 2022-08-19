################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL43Z256VLH4 -DCPU_MKL43Z256VLH4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/board" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/source" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/drivers" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/component/uart" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/component/serial_manager" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/utilities" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/component/lists" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/device" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_nogen/CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


