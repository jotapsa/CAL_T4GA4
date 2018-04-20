################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Aux.cpp \
../Cli.cpp \
../Connection.cpp \
../Container.cpp \
../Garage.cpp \
../GarbageManagement.cpp \
../GraphViewer.cpp \
../Parser.cpp \
../Place.cpp \
../RandomEngine.cpp \
../Station.cpp \
../Street.cpp \
../Vehicle.cpp \
../main.cpp 

OBJS += \
./Aux.o \
./Cli.o \
./Connection.o \
./Container.o \
./Garage.o \
./GarbageManagement.o \
./GraphViewer.o \
./Parser.o \
./Place.o \
./RandomEngine.o \
./Station.o \
./Street.o \
./Vehicle.o \
./main.o 

CPP_DEPS += \
./Aux.d \
./Cli.d \
./Connection.d \
./Container.d \
./Garage.d \
./GarbageManagement.d \
./GraphViewer.d \
./Parser.d \
./Place.d \
./RandomEngine.d \
./Station.d \
./Street.d \
./Vehicle.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


