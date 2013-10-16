################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lists.cpp \
../main.cpp \
../process.cpp \
../processes.cpp \
../processor.cpp \
../utilities.cpp 

OBJS += \
./lists.o \
./main.o \
./process.o \
./processes.o \
./processor.o \
./utilities.o 

CPP_DEPS += \
./lists.d \
./main.d \
./process.d \
./processes.d \
./processor.d \
./utilities.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


