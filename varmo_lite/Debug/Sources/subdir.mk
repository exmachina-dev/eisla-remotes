################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/MenuSystem.cpp 

C_SRCS += \
../Sources/Events.c \
../Sources/display.c \
../Sources/main.c \
../Sources/protocol.c 

OBJS += \
./Sources/Events.o \
./Sources/MenuSystem.o \
./Sources/display.o \
./Sources/main.o \
./Sources/protocol.o 

C_DEPS += \
./Sources/Events.d \
./Sources/display.d \
./Sources/main.d \
./Sources/protocol.d 

CPP_DEPS += \
./Sources/MenuSystem.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/PDD" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/IO_Map" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Sources" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/PDD" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/IO_Map" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Sources" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Generated_Code" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


