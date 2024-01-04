################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/peripherals/buttons.c \
../src/peripherals/leds.c \
../src/peripherals/timer.c 

OBJS += \
./src/peripherals/buttons.o \
./src/peripherals/leds.o \
./src/peripherals/timer.o 

C_DEPS += \
./src/peripherals/buttons.d \
./src/peripherals/leds.d \
./src/peripherals/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/peripherals/%.o: ../src/peripherals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O2 -c -fmessage-length=0 -MT"$@" -I../../example_bsp/microblaze_0/include -mlittle-endian -mcpu=v11.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


