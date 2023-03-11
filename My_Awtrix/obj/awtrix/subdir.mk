################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../awtrix/awtrix.c \
../awtrix/awtrix_font.c 

OBJS += \
./awtrix/awtrix.o \
./awtrix/awtrix_font.o 

C_DEPS += \
./awtrix/awtrix.d \
./awtrix/awtrix_font.d 


# Each subdirectory must supply rules for building sources it contributes
awtrix/%.o: ../awtrix/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Debug" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Core" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\User" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Peripheral\inc" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\ws2812b" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\awtrix" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

