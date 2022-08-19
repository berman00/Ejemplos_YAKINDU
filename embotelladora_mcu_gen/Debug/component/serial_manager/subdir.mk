################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/serial_manager/serial_manager.c \
../component/serial_manager/serial_port_uart.c 

OBJS += \
./component/serial_manager/serial_manager.o \
./component/serial_manager/serial_port_uart.o 

C_DEPS += \
./component/serial_manager/serial_manager.d \
./component/serial_manager/serial_port_uart.d 


# Each subdirectory must supply rules for building sources it contributes
component/serial_manager/%.o: ../component/serial_manager/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL43Z256VLH4 -DCPU_MKL43Z256VLH4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/board" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/source" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/drivers" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/component/uart" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/component/serial_manager" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/utilities" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/component/lists" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/device" -I"/Users/valen/Code/MCUXpresso/workspace/embotelladora_mcu_gen/CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


