################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../job.cpp \
../lists.cpp \
../main.cpp \
../processor.cpp \
../scheduler.cpp \
../utilities.cpp 

OBJS += \
./job.o \
./lists.o \
./main.o \
./processor.o \
./scheduler.o \
./utilities.o 

CPP_DEPS += \
./job.d \
./lists.d \
./main.d \
./processor.d \
./scheduler.d \
./utilities.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


