################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/pruebita-hilos.c \
../src/pruebita-leer-archivos.c 

OBJS += \
./src/pruebita-hilos.o \
./src/pruebita-leer-archivos.o 

C_DEPS += \
./src/pruebita-hilos.d \
./src/pruebita-leer-archivos.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


