################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/preripherals/leds.c \
../src/preripherals/timer.c 

OBJS += \
./src/preripherals/leds.o \
./src/preripherals/timer.o 

C_DEPS += \
./src/preripherals/leds.d \
./src/preripherals/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/preripherals/%.o: ../src/preripherals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O2 -c -fmessage-length=0 -MT"$@" -I../../example_bsp/microblaze_0/include -mlittle-endian -mcpu=v11.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


