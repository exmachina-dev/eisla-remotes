################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/LCD.cpp \
../Sources/PCA9670.cpp \
../Sources/display.cpp \
../Sources/menu.cpp \
../Sources/protocol.cpp 

C_SRCS += \
../Sources/Events.c \
../Sources/main.c 

OBJS += \
./Sources/Events.o \
./Sources/LCD.o \
./Sources/PCA9670.o \
./Sources/display.o \
./Sources/main.o \
./Sources/menu.o \
./Sources/protocol.o 

C_DEPS += \
./Sources/Events.d \
./Sources/main.d 

CPP_DEPS += \
./Sources/LCD.d \
./Sources/PCA9670.d \
./Sources/display.d \
./Sources/menu.d \
./Sources/protocol.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	echo -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/PDD" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/IO_Map" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Sources" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Generated_Code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	echo -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/PDD" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Static_Code/IO_Map" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Sources" -I"C:/Users/Adrian/Documents/repos/eisla-remotes/varmo_lite/Generated_Code" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


