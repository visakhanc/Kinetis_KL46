################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Freescale/SDK_1.3_FRDM-KL46Z/platform/utilities/src/fsl_debug_console.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/platform/utilities/src/fsl_misc_utilities.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/platform/utilities/src/print_scan.c 

OBJS += \
./utils/fsl_debug_console.o \
./utils/fsl_misc_utilities.o \
./utils/print_scan.o 

C_DEPS += \
./utils/fsl_debug_console.d \
./utils/fsl_misc_utilities.d \
./utils/print_scan.d 


# Each subdirectory must supply rules for building sources it contributes
utils/fsl_debug_console.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/platform/utilities/src/fsl_debug_console.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DNDEBUG -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utils/fsl_misc_utilities.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/platform/utilities/src/fsl_misc_utilities.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DNDEBUG -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utils/print_scan.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/platform/utilities/src/print_scan.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DNDEBUG -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


