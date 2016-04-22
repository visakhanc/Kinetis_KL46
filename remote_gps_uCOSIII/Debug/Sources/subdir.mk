################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/fsl_uart_irq.c \
../Sources/gps_parse.c \
../Sources/gps_task.c \
../Sources/gsm_task.c \
../Sources/http_utils.c \
../Sources/main.c \
../Sources/num_utils.c 

OBJS += \
./Sources/fsl_uart_irq.o \
./Sources/gps_parse.o \
./Sources/gps_task.o \
./Sources/gsm_task.o \
./Sources/http_utils.o \
./Sources/main.o \
./Sources/num_utils.o 

C_DEPS += \
./Sources/fsl_uart_irq.d \
./Sources/gps_parse.d \
./Sources/gps_task.d \
./Sources/gsm_task.d \
./Sources/http_utils.d \
./Sources/main.d \
./Sources/num_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


