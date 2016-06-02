################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/BitIoLdd4.c \
../Generated_Code/BitIoLdd5.c \
../Generated_Code/Cpu.c \
../Generated_Code/DIRECTION_1.c \
../Generated_Code/DIRECTION_2.c \
../Generated_Code/ENCODER.c \
../Generated_Code/ENCODER_PUSH.c \
../Generated_Code/ExtIntLdd1.c \
../Generated_Code/ExtIntLdd2.c \
../Generated_Code/ExtIntLdd3.c \
../Generated_Code/ExtIntLdd4.c \
../Generated_Code/ExtIntLdd5.c \
../Generated_Code/IntI2cLdd1.c \
../Generated_Code/LCD.c \
../Generated_Code/LED_DEBUG.c \
../Generated_Code/LED_STATUS_1.c \
../Generated_Code/LED_STATUS_2.c \
../Generated_Code/LED_STATUS_3.c \
../Generated_Code/LED_STATUS_4.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PUSH_BUTTON_REC.c \
../Generated_Code/PUSH_BUTTON_SEND.c \
../Generated_Code/T_100ms.c \
../Generated_Code/T_500ms.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/BitIoLdd4.o \
./Generated_Code/BitIoLdd5.o \
./Generated_Code/Cpu.o \
./Generated_Code/DIRECTION_1.o \
./Generated_Code/DIRECTION_2.o \
./Generated_Code/ENCODER.o \
./Generated_Code/ENCODER_PUSH.o \
./Generated_Code/ExtIntLdd1.o \
./Generated_Code/ExtIntLdd2.o \
./Generated_Code/ExtIntLdd3.o \
./Generated_Code/ExtIntLdd4.o \
./Generated_Code/ExtIntLdd5.o \
./Generated_Code/IntI2cLdd1.o \
./Generated_Code/LCD.o \
./Generated_Code/LED_DEBUG.o \
./Generated_Code/LED_STATUS_1.o \
./Generated_Code/LED_STATUS_2.o \
./Generated_Code/LED_STATUS_3.o \
./Generated_Code/LED_STATUS_4.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PUSH_BUTTON_REC.o \
./Generated_Code/PUSH_BUTTON_SEND.o \
./Generated_Code/T_100ms.o \
./Generated_Code/T_500ms.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/BitIoLdd4.d \
./Generated_Code/BitIoLdd5.d \
./Generated_Code/Cpu.d \
./Generated_Code/DIRECTION_1.d \
./Generated_Code/DIRECTION_2.d \
./Generated_Code/ENCODER.d \
./Generated_Code/ENCODER_PUSH.d \
./Generated_Code/ExtIntLdd1.d \
./Generated_Code/ExtIntLdd2.d \
./Generated_Code/ExtIntLdd3.d \
./Generated_Code/ExtIntLdd4.d \
./Generated_Code/ExtIntLdd5.d \
./Generated_Code/IntI2cLdd1.d \
./Generated_Code/LCD.d \
./Generated_Code/LED_DEBUG.d \
./Generated_Code/LED_STATUS_1.d \
./Generated_Code/LED_STATUS_2.d \
./Generated_Code/LED_STATUS_3.d \
./Generated_Code/LED_STATUS_4.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PUSH_BUTTON_REC.d \
./Generated_Code/PUSH_BUTTON_SEND.d \
./Generated_Code/T_100ms.d \
./Generated_Code/T_500ms.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/PDD" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/IO_Map" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Sources" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


