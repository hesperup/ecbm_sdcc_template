#################################################################
# AUTO GENERATE AT 2025-11-17 18:04:11 BY unify_builder v3.10.4.0
#################################################################

# Usage:
#  - Build:	make prebuild && make COMPILER_DIR=<dir path>
#  - Clean:	make clean

# Targets Dependences Chain:
#  prebuild
#  all -> postbuild -> bin -> elf -> *.o

# Use 'make V=1' to see the full commands
ifdef V
	Q = 
else
	Q = @
endif

COMPILER_DIR ?= /D/Arm/Keil_v5/C51
ifneq ($(COMPILER_DIR),)
	_PATH_TMP:=$(COMPILER_DIR)/bin:$(PATH)
	export PATH=$(_PATH_TMP)
endif

EXE?=
CC=$(COMPILER_DIR)/BIN/C51$(EXE)
AS=$(COMPILER_DIR)/BIN/A51$(EXE)
CXX=$(COMPILER_DIR)/BIN/C51$(EXE)
LD=$(COMPILER_DIR)/BIN/LX51$(EXE)
AR=$(COMPILER_DIR)/BIN/LIBX51$(EXE)

###########################
# targets
###########################

COLOR_END=\033[0m
COLOR_ERR=\033[31;1m
COLOR_WRN=\033[33;1m
COLOR_SUC=\033[32;1m
COLOR_INF=\033[34;1m

.PHONY : all postbuild bin elf prebuild clean

all: postbuild
	@echo ==========
	@printf "$(COLOR_SUC)ALL DONE.$(COLOR_END)\n"
	@echo ==========

clean:
	-rm -fv ./build/ECBMV3/*.elf ./build/ECBMV3/*.axf ./build/ECBMV3/*.out
	-rm -fv ./build/ECBMV3/*.hex ./build/ECBMV3/*.bin ./build/ECBMV3/*.s19
	-rm -rfv ./build/ECBMV3/.obj

prebuild:
	@printf "$(COLOR_INF)prebuild ...$(COLOR_END)\n"
	@echo nothing to prebuild.

./build/ECBMV3/.obj/ECBM_LIB:
	$(Q)mkdir -p $@
-include ./build/ECBMV3/.obj/ECBM_LIB/adc.d
./build/ECBMV3/.obj/ECBM_LIB/adc.o: ./ECBM_LIB/adc.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/adc.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/adc.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/adc.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/beep.d
./build/ECBMV3/.obj/ECBM_LIB/beep.o: ./ECBM_LIB/beep.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/beep.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/beep.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/beep.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/cmp.d
./build/ECBMV3/.obj/ECBM_LIB/cmp.o: ./ECBM_LIB/cmp.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/cmp.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/cmp.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/cmp.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.d
./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.o: ./ECBM_LIB/ecbm_core.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/ecbm_core.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/eds.d
./build/ECBMV3/.obj/ECBM_LIB/eds.o: ./ECBM_LIB/eds.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/eds.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/eds.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/eds.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/eeprom.d
./build/ECBMV3/.obj/ECBM_LIB/eeprom.o: ./ECBM_LIB/eeprom.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/eeprom.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/eeprom.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/eeprom.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/exti.d
./build/ECBMV3/.obj/ECBM_LIB/exti.o: ./ECBM_LIB/exti.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/exti.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/exti.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/exti.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/gpio.d
./build/ECBMV3/.obj/ECBM_LIB/gpio.o: ./ECBM_LIB/gpio.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/gpio.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/gpio.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/gpio.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/iic.d
./build/ECBMV3/.obj/ECBM_LIB/iic.o: ./ECBM_LIB/iic.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/iic.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/iic.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/iic.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/lcd.d
./build/ECBMV3/.obj/ECBM_LIB/lcd.o: ./ECBM_LIB/lcd.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/lcd.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/lcd.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/lcd.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/lcm.d
./build/ECBMV3/.obj/ECBM_LIB/lcm.o: ./ECBM_LIB/lcm.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/lcm.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/lcm.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/lcm.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/led.d
./build/ECBMV3/.obj/ECBM_LIB/led.o: ./ECBM_LIB/led.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/led.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/led.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/led.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/mdu16.d
./build/ECBMV3/.obj/ECBM_LIB/mdu16.o: ./ECBM_LIB/mdu16.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/mdu16.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/mdu16.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/mdu16.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/nvic.d
./build/ECBMV3/.obj/ECBM_LIB/nvic.o: ./ECBM_LIB/nvic.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/nvic.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/nvic.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/nvic.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/pca.d
./build/ECBMV3/.obj/ECBM_LIB/pca.o: ./ECBM_LIB/pca.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/pca.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/pca.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/pca.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/power.d
./build/ECBMV3/.obj/ECBM_LIB/power.o: ./ECBM_LIB/power.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/power.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/power.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/power.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/pwm.d
./build/ECBMV3/.obj/ECBM_LIB/pwm.o: ./ECBM_LIB/pwm.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/pwm.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/pwm.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/pwm.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.d
./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.o: ./ECBM_LIB/pwm16_out.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/pwm16_out.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/soft_iic.d
./build/ECBMV3/.obj/ECBM_LIB/soft_iic.o: ./ECBM_LIB/soft_iic.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/soft_iic.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/soft_iic.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/soft_iic.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/soft_spi.d
./build/ECBMV3/.obj/ECBM_LIB/soft_spi.o: ./ECBM_LIB/soft_spi.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/soft_spi.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/soft_spi.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/soft_spi.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/spi.d
./build/ECBMV3/.obj/ECBM_LIB/spi.o: ./ECBM_LIB/spi.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/spi.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/spi.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/spi.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/stream.d
./build/ECBMV3/.obj/ECBM_LIB/stream.o: ./ECBM_LIB/stream.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/stream.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/stream.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/stream.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.d
./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.o: ./ECBM_LIB/stream_ecp.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/stream_ecp.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/stream_fur.d
./build/ECBMV3/.obj/ECBM_LIB/stream_fur.o: ./ECBM_LIB/stream_fur.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/stream_fur.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/stream_fur.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/stream_fur.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.d
./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.o: ./ECBM_LIB/stream_modbus.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/stream_modbus.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/timer.d
./build/ECBMV3/.obj/ECBM_LIB/timer.o: ./ECBM_LIB/timer.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/timer.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/timer.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/timer.o)

-include ./build/ECBMV3/.obj/ECBM_LIB/uart.d
./build/ECBMV3/.obj/ECBM_LIB/uart.o: ./ECBM_LIB/uart.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) ./ECBM_LIB/uart.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/ECBM_LIB/uart.lst) OBJECT(./build/ECBMV3/.obj/ECBM_LIB/uart.o)

./build/ECBMV3/.obj:
	$(Q)mkdir -p $@
-include ./build/ECBMV3/.obj/STARTUP.d
./build/ECBMV3/.obj/STARTUP.o: ./STARTUP.A51 Makefile | ./build/ECBMV3/.obj
	@echo assembling $< ...
	$(Q)$(AS) ./STARTUP.A51 INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) SET(LARGE) PRINT(./build/ECBMV3/.obj/STARTUP.lst) OBJECT(./build/ECBMV3/.obj/STARTUP.o) EP

-include ./build/ECBMV3/.obj/main.d
./build/ECBMV3/.obj/main.o: ./main.c Makefile | ./build/ECBMV3/.obj
	@echo compiling $< ...
	$(Q)$(CC) ./main.c OMF2 TABS(4) CODE NOCOND SYMBOLS INCDIR(ECBM_LIB;device;../../../Arm/Keil_v5/C51/INC) DEFINE(__UVISION_VERSION='526') OPTIMIZE(8,SPEED) LARGE ROM(LARGE) PRINT(./build/ECBMV3/.obj/main.lst) OBJECT(./build/ECBMV3/.obj/main.o)

objs = ./build/ECBMV3/.obj/ECBM_LIB/adc.o ./build/ECBMV3/.obj/ECBM_LIB/beep.o ./build/ECBMV3/.obj/ECBM_LIB/cmp.o ./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.o ./build/ECBMV3/.obj/ECBM_LIB/eds.o ./build/ECBMV3/.obj/ECBM_LIB/eeprom.o ./build/ECBMV3/.obj/ECBM_LIB/exti.o ./build/ECBMV3/.obj/ECBM_LIB/gpio.o ./build/ECBMV3/.obj/ECBM_LIB/iic.o ./build/ECBMV3/.obj/ECBM_LIB/lcd.o ./build/ECBMV3/.obj/ECBM_LIB/lcm.o ./build/ECBMV3/.obj/ECBM_LIB/led.o ./build/ECBMV3/.obj/ECBM_LIB/mdu16.o ./build/ECBMV3/.obj/ECBM_LIB/nvic.o ./build/ECBMV3/.obj/ECBM_LIB/pca.o ./build/ECBMV3/.obj/ECBM_LIB/power.o ./build/ECBMV3/.obj/ECBM_LIB/pwm.o ./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.o ./build/ECBMV3/.obj/ECBM_LIB/soft_iic.o ./build/ECBMV3/.obj/ECBM_LIB/soft_spi.o ./build/ECBMV3/.obj/ECBM_LIB/spi.o ./build/ECBMV3/.obj/ECBM_LIB/stream.o ./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.o ./build/ECBMV3/.obj/ECBM_LIB/stream_fur.o ./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.o ./build/ECBMV3/.obj/ECBM_LIB/timer.o ./build/ECBMV3/.obj/ECBM_LIB/uart.o ./build/ECBMV3/.obj/STARTUP.o ./build/ECBMV3/.obj/main.o
elf: $(objs) Makefile
	@printf "$(COLOR_INF)linking ./build/ECBMV3/ecbm ...$(COLOR_END)\n"
	$(LD) ./build/ECBMV3/.obj/ECBM_LIB/adc.o,./build/ECBMV3/.obj/ECBM_LIB/beep.o,./build/ECBMV3/.obj/ECBM_LIB/cmp.o,./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.o,./build/ECBMV3/.obj/ECBM_LIB/eds.o,./build/ECBMV3/.obj/ECBM_LIB/eeprom.o,./build/ECBMV3/.obj/ECBM_LIB/exti.o,./build/ECBMV3/.obj/ECBM_LIB/gpio.o,./build/ECBMV3/.obj/ECBM_LIB/iic.o,./build/ECBMV3/.obj/ECBM_LIB/lcd.o,./build/ECBMV3/.obj/ECBM_LIB/lcm.o,./build/ECBMV3/.obj/ECBM_LIB/led.o,./build/ECBMV3/.obj/ECBM_LIB/mdu16.o,./build/ECBMV3/.obj/ECBM_LIB/nvic.o,./build/ECBMV3/.obj/ECBM_LIB/pca.o,./build/ECBMV3/.obj/ECBM_LIB/power.o,./build/ECBMV3/.obj/ECBM_LIB/pwm.o,./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.o,./build/ECBMV3/.obj/ECBM_LIB/soft_iic.o,./build/ECBMV3/.obj/ECBM_LIB/soft_spi.o,./build/ECBMV3/.obj/ECBM_LIB/spi.o,./build/ECBMV3/.obj/ECBM_LIB/stream.o,./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.o,./build/ECBMV3/.obj/ECBM_LIB/stream_fur.o,./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.o,./build/ECBMV3/.obj/ECBM_LIB/timer.o,./build/ECBMV3/.obj/ECBM_LIB/uart.o,./build/ECBMV3/.obj/STARTUP.o,./build/ECBMV3/.obj/main.o TO ./build/ECBMV3/ecbm PRINT(./build/ECBMV3/ecbm.map) REMOVEUNUSED

bin: elf Makefile
	@printf "$(COLOR_INF)output binary files ...$(COLOR_END)\n"
	$(COMPILER_DIR)/BIN/Ohx51$(EXE) ./build/ECBMV3/ecbm HEXFILE(./build/ECBMV3/ecbm.hex) HEX

postbuild: bin
	@printf "$(COLOR_INF)postbuild ...$(COLOR_END)\n"
	@echo nothing to postbuild.

