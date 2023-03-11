################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/main.c \
../User/system_ch32v30x.c 

OBJS += \
./User/ch32v30x_it.o \
./User/main.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/main.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Debug" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Core" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\User" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\Peripheral\inc" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\ws2812b" -I"D:\Projects\My_Awtrix\proj\My_Awtrix\awtrix" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

