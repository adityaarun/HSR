################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/basicHSR.cpp \
../src/handGesture.cpp \
../src/hsr.cpp \
../src/main.cpp \
../src/myImage.cpp \
../src/preprocessing.cpp \
../src/roi.cpp 

OBJS += \
./src/basicHSR.o \
./src/handGesture.o \
./src/hsr.o \
./src/main.o \
./src/myImage.o \
./src/preprocessing.o \
./src/roi.o 

CPP_DEPS += \
./src/basicHSR.d \
./src/handGesture.d \
./src/hsr.d \
./src/main.d \
./src/myImage.d \
./src/preprocessing.d \
./src/roi.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


