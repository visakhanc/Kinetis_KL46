################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU/cpu_c.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/cpu_core.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config/os_app_hooks.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_cfg_app.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_core.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU/os_cpu_c.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_dbg.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_flag.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_int.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_mem.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_msg.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_mutex.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_pend_multi.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_prio.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_q.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_sem.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_stat.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_task.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_tick.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_time.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_tmr.c \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_var.c 

S_UPPER_SRCS += \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU/cpu_a.S \
C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU/os_cpu_a.S 

OBJS += \
./ucosiii/cpu_a.o \
./ucosiii/cpu_c.o \
./ucosiii/cpu_core.o \
./ucosiii/os_app_hooks.o \
./ucosiii/os_cfg_app.o \
./ucosiii/os_core.o \
./ucosiii/os_cpu_a.o \
./ucosiii/os_cpu_c.o \
./ucosiii/os_dbg.o \
./ucosiii/os_flag.o \
./ucosiii/os_int.o \
./ucosiii/os_mem.o \
./ucosiii/os_msg.o \
./ucosiii/os_mutex.o \
./ucosiii/os_pend_multi.o \
./ucosiii/os_prio.o \
./ucosiii/os_q.o \
./ucosiii/os_sem.o \
./ucosiii/os_stat.o \
./ucosiii/os_task.o \
./ucosiii/os_tick.o \
./ucosiii/os_time.o \
./ucosiii/os_tmr.o \
./ucosiii/os_var.o 

C_DEPS += \
./ucosiii/cpu_c.d \
./ucosiii/cpu_core.d \
./ucosiii/os_app_hooks.d \
./ucosiii/os_cfg_app.d \
./ucosiii/os_core.d \
./ucosiii/os_cpu_c.d \
./ucosiii/os_dbg.d \
./ucosiii/os_flag.d \
./ucosiii/os_int.d \
./ucosiii/os_mem.d \
./ucosiii/os_msg.d \
./ucosiii/os_mutex.d \
./ucosiii/os_pend_multi.d \
./ucosiii/os_prio.d \
./ucosiii/os_q.d \
./ucosiii/os_sem.d \
./ucosiii/os_stat.d \
./ucosiii/os_task.d \
./ucosiii/os_tick.d \
./ucosiii/os_time.d \
./ucosiii/os_tmr.d \
./ucosiii/os_var.d 

S_UPPER_DEPS += \
./ucosiii/cpu_a.d \
./ucosiii/os_cpu_a.d 


# Each subdirectory must supply rules for building sources it contributes
ucosiii/cpu_a.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU/cpu_a.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/cpu_c.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU/cpu_c.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/cpu_core.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/cpu_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_app_hooks.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config/os_app_hooks.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_cfg_app.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_cfg_app.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_core.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_cpu_a.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU/os_cpu_a.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_cpu_c.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU/os_cpu_c.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_dbg.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_dbg.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_flag.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_flag.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_int.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_int.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_mem.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_mem.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_msg.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_msg.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_mutex.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_mutex.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_pend_multi.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_pend_multi.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_prio.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_prio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_q.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_q.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_sem.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_sem.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_stat.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_stat.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_task.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_task.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_tick.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_tick.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_time.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_time.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_tmr.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_tmr.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ucosiii/os_var.o: C:/Freescale/SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source/os_var.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"CPU_MKL46Z256VLH4" -DFSL_RTOS_UCOSIII -DFRDM_KL46Z -DFREEDOM -I"../Sources" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-LIB" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uC-CPU/ARM-Cortex-M0/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Source" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/uCOS-III/Ports/ARM-Cortex-M0/Generic/GNU" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/rtos/uCOSIII/src/config" -IC:\Freescale\SDK_1.3_FRDM-KL46Z/platform/hal/inc -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/drivers/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/system/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/osa/inc" -I../frdmkl46z -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL46Z4/include" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/inc" -I"C:\Freescale\SDK_1.3_FRDM-KL46Z/platform/utilities/src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


