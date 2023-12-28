################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/blocks.c \
../src/colors.c \
../src/graphics.c \
../src/leds.c \
../src/main.c \
../src/timer.c 

OBJS += \
./src/blocks.o \
./src/colors.o \
./src/graphics.o \
./src/leds.o \
./src/main.o \
./src/timer.o 

C_DEPS += \
./src/blocks.d \
./src/colors.d \
./src/graphics.d \
./src/leds.d \
./src/main.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../example_bsp/microblaze_0/include -mlittle-endian -mcpu=v11.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


