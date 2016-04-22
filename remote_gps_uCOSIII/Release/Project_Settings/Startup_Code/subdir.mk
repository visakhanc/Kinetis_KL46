################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c \
../Project_Settings/Startup_Code/system_MKL46Z4.c 

S_UPPER_SRCS += \
../Project_Settings/Startup_Code/startup_MKL46Z4.S 

OBJS += \
./Project_Settings/Startup_Code/startup.o \
./Project_Settings/Startup_Code/startup_MKL46Z4.o \
./Project_Settings/Startup_Code/system_MKL46Z4.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d \
./Project_Settings/Startup_Code/system_MKL46Z4.d 

S_UPPER_DEPS += \
./Project_Settings/Startup_Code/startup_MKL46Z4.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DNDEBUG -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


