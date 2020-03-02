################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MIMXRT1021.c 

OBJS += \
./device/system_MIMXRT1021.o 

C_DEPS += \
./device/system_MIMXRT1021.d 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -D_DEBUG=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DUSB_STACK_BM -DFSL_OSA_BM_TASK_ENABLE=0 -DFSL_OSA_BM_TIMER_CONFIG=0 -DSERIAL_PORT_TYPE_UART=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\board" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\source" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\usb\device\source\ehci" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\usb\include" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\usb\device\include" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\usb\device\source" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\usb\phy" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\component\osa" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\drivers" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\device" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\CMSIS" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\component\lists" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\utilities" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\component\serial_manager" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\xip" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\component\uart" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\usb\device\class\audio" -I"C:\Users\takeshi\Documents\MCUXpressoIDE_11.1.0_3209\workspace\evkmimxrt1020_dev_audio_generator_bm\usb\device\class" -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


