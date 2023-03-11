################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ws2812b/ws2812b.c 

OBJS += \
./ws2812b/ws2812b.o 

C_DEPS += \
./ws2812b/ws2812b.d 


# Each subdirectory must supply rules for building sources it contributes
ws2812b/%.o: ../ws2812b/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Debug" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Core" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\User" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Peripheral\inc" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\ws2812b" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\awtrix" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

