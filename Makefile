#################################################################
# AUTO GENERATE AT 2025-11-20 11:20:53 BY unify_builder v3.10.4.0
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

## Detect user home directory in a cross-platform way and normalize separators
HOME_DIR := $(HOME)
ifeq ($(strip $(HOME_DIR)),)
	HOME_DIR := $(USERPROFILE)
endif
HOME_DIR := $(subst \,/,$(HOME_DIR))

COMPILER_DIR ?= $(HOME_DIR)/.eide/tools/sdcc_mcs51/sdcc-4.5.0-with-binutils
ifneq ($(COMPILER_DIR),)
ifeq ($(OS),Windows_NT)
 	# Use Windows-style PATH separator and backslashes for compatibility
 	_COMPILER_BIN:=$(subst /,\\,$(COMPILER_DIR))\bin
	# Try to locate cc1 under libexec and add it to PATH so sdcpp can execute it
	_CC1_PATH:=$(firstword $(wildcard $(COMPILER_DIR)/libexec/sdcc/*/cc1.exe))
	ifeq ($(_CC1_PATH),)
		# fallback: no cc1 found via wildcard - try common libexec path inside user's home
		_CC1_DIR_FALLBACK:=$(subst /,\,$(HOME_DIR))\.eide\tools\sdcc_mcs51\sdcc-4.5.0-with-binutils\libexec\sdcc\x86_64-w64-mingw32\12.1.0
		_PATH_TMP:=$(_COMPILER_BIN);$(_CC1_DIR_FALLBACK);$(PATH)
		# fallback: no cc1 found via wildcard
		_PATH_TMP:=$(_COMPILER_BIN);$(PATH)
	else
		_CC1_DIR:=$(subst /,\\,$(dir $(_CC1_PATH)))
		_PATH_TMP:=$(_COMPILER_BIN);$(_CC1_DIR);$(PATH)
	endif
else
 	_PATH_TMP:=$(COMPILER_DIR)/bin:$(PATH)
endif
 	export PATH=$(_PATH_TMP)
endif

EXE?=
CC=$(COMPILER_DIR)/bin/sdcc$(EXE)
AS=$(COMPILER_DIR)/bin/i51-elf-as$(EXE)
CXX=$(COMPILER_DIR)/bin/sdcc$(EXE)
LD=$(COMPILER_DIR)/bin/i51-elf-ld$(EXE)
AR=$(COMPILER_DIR)/bin/i51-elf-ar$(EXE)

###########################
# targets
###########################

COLOR_END=\033[0m
COLOR_ERR=\033[31;1m
COLOR_WRN=\033[33;1m
COLOR_SUC=\033[32;1m
COLOR_INF=\033[34;1m

.PHONY: all postbuild bin elf prebuild clean build_windows flash

build_windows:
	@echo Building using sdcc toolchain at $(COMPILER_DIR)...
	$(MAKE) COMPILER_DIR=$(COMPILER_DIR) prebuild all

all: postbuild
	@echo ==========

	@echo ==========

clean:
	-rm -fv ./build/ECBMV3/*.elf ./build/ECBMV3/*.axf ./build/ECBMV3/*.out
	-rm -fv ./build/ECBMV3/*.hex ./build/ECBMV3/*.bin ./build/ECBMV3/*.s19
	-rm -rfv ./build/ECBMV3/.obj

prebuild:
	@echo nothing to prebuild.

./build/ECBMV3/.obj/ECBM_LIB:
ifeq ($(OS),Windows_NT)
	$(Q)-@if not exist .\\build\\ECBMV3\\.obj\\ECBM_LIB mkdir .\\build\\ECBMV3\\.obj\\ECBM_LIB
else
	$(Q)mkdir -p $@
endif
-include ./build/ECBMV3/.obj/ECBM_LIB/adc.d
./build/ECBMV3/.obj/ECBM_LIB/adc.o: ./ECBM_LIB/adc.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/adc.o ./ECBM_LIB/adc.c

-include ./build/ECBMV3/.obj/ECBM_LIB/beep.d
./build/ECBMV3/.obj/ECBM_LIB/beep.o: ./ECBM_LIB/beep.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/beep.o ./ECBM_LIB/beep.c

-include ./build/ECBMV3/.obj/ECBM_LIB/cmp.d
./build/ECBMV3/.obj/ECBM_LIB/cmp.o: ./ECBM_LIB/cmp.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/cmp.o ./ECBM_LIB/cmp.c

-include ./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.d
./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.o: ./ECBM_LIB/ecbm_core.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.o ./ECBM_LIB/ecbm_core.c

-include ./build/ECBMV3/.obj/ECBM_LIB/eds.d
./build/ECBMV3/.obj/ECBM_LIB/eds.o: ./ECBM_LIB/eds.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/eds.o ./ECBM_LIB/eds.c

-include ./build/ECBMV3/.obj/ECBM_LIB/eeprom.d
./build/ECBMV3/.obj/ECBM_LIB/eeprom.o: ./ECBM_LIB/eeprom.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/eeprom.o ./ECBM_LIB/eeprom.c

-include ./build/ECBMV3/.obj/ECBM_LIB/exti.d
./build/ECBMV3/.obj/ECBM_LIB/exti.o: ./ECBM_LIB/exti.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/exti.o ./ECBM_LIB/exti.c

-include ./build/ECBMV3/.obj/ECBM_LIB/gpio.d
./build/ECBMV3/.obj/ECBM_LIB/gpio.o: ./ECBM_LIB/gpio.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/gpio.o ./ECBM_LIB/gpio.c

-include ./build/ECBMV3/.obj/ECBM_LIB/iic.d
./build/ECBMV3/.obj/ECBM_LIB/iic.o: ./ECBM_LIB/iic.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/iic.o ./ECBM_LIB/iic.c

-include ./build/ECBMV3/.obj/ECBM_LIB/lcd.d
./build/ECBMV3/.obj/ECBM_LIB/lcd.o: ./ECBM_LIB/lcd.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/lcd.o ./ECBM_LIB/lcd.c

-include ./build/ECBMV3/.obj/ECBM_LIB/lcm.d
./build/ECBMV3/.obj/ECBM_LIB/lcm.o: ./ECBM_LIB/lcm.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/lcm.o ./ECBM_LIB/lcm.c

-include ./build/ECBMV3/.obj/ECBM_LIB/led.d
./build/ECBMV3/.obj/ECBM_LIB/led.o: ./ECBM_LIB/led.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/led.o ./ECBM_LIB/led.c

-include ./build/ECBMV3/.obj/ECBM_LIB/mdu16.d
./build/ECBMV3/.obj/ECBM_LIB/mdu16.o: ./ECBM_LIB/mdu16.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/mdu16.o ./ECBM_LIB/mdu16.c

-include ./build/ECBMV3/.obj/ECBM_LIB/nvic.d
./build/ECBMV3/.obj/ECBM_LIB/nvic.o: ./ECBM_LIB/nvic.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/nvic.o ./ECBM_LIB/nvic.c

-include ./build/ECBMV3/.obj/ECBM_LIB/pca.d
./build/ECBMV3/.obj/ECBM_LIB/pca.o: ./ECBM_LIB/pca.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/pca.o ./ECBM_LIB/pca.c

-include ./build/ECBMV3/.obj/ECBM_LIB/power.d
./build/ECBMV3/.obj/ECBM_LIB/power.o: ./ECBM_LIB/power.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/power.o ./ECBM_LIB/power.c

-include ./build/ECBMV3/.obj/ECBM_LIB/pwm.d
./build/ECBMV3/.obj/ECBM_LIB/pwm.o: ./ECBM_LIB/pwm.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/pwm.o ./ECBM_LIB/pwm.c

-include ./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.d
./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.o: ./ECBM_LIB/pwm16_out.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.o ./ECBM_LIB/pwm16_out.c

-include ./build/ECBMV3/.obj/ECBM_LIB/soft_iic.d
./build/ECBMV3/.obj/ECBM_LIB/soft_iic.o: ./ECBM_LIB/soft_iic.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/soft_iic.o ./ECBM_LIB/soft_iic.c

-include ./build/ECBMV3/.obj/ECBM_LIB/soft_spi.d
./build/ECBMV3/.obj/ECBM_LIB/soft_spi.o: ./ECBM_LIB/soft_spi.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/soft_spi.o ./ECBM_LIB/soft_spi.c

-include ./build/ECBMV3/.obj/ECBM_LIB/spi.d
./build/ECBMV3/.obj/ECBM_LIB/spi.o: ./ECBM_LIB/spi.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/spi.o ./ECBM_LIB/spi.c

-include ./build/ECBMV3/.obj/ECBM_LIB/stream.d
./build/ECBMV3/.obj/ECBM_LIB/stream.o: ./ECBM_LIB/stream.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/stream.o ./ECBM_LIB/stream.c

-include ./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.d
./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.o: ./ECBM_LIB/stream_ecp.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.o ./ECBM_LIB/stream_ecp.c

-include ./build/ECBMV3/.obj/ECBM_LIB/stream_fur.d
./build/ECBMV3/.obj/ECBM_LIB/stream_fur.o: ./ECBM_LIB/stream_fur.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/stream_fur.o ./ECBM_LIB/stream_fur.c

-include ./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.d
./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.o: ./ECBM_LIB/stream_modbus.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.o ./ECBM_LIB/stream_modbus.c

-include ./build/ECBMV3/.obj/ECBM_LIB/timer.d
./build/ECBMV3/.obj/ECBM_LIB/timer.o: ./ECBM_LIB/timer.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/timer.o ./ECBM_LIB/timer.c

-include ./build/ECBMV3/.obj/ECBM_LIB/uart.d
./build/ECBMV3/.obj/ECBM_LIB/uart.o: ./ECBM_LIB/uart.c Makefile | ./build/ECBMV3/.obj/ECBM_LIB
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/ECBM_LIB/uart.o ./ECBM_LIB/uart.c

./build/ECBMV3/.obj:
ifeq ($(OS),Windows_NT)
	$(Q)-@if not exist .\\build\\ECBMV3\\.obj mkdir .\\build\\ECBMV3\\.obj
else
	$(Q)mkdir -p $@
endif
-include ./build/ECBMV3/.obj/main.d
./build/ECBMV3/.obj/main.o: ./main.c Makefile | ./build/ECBMV3/.obj
	@echo compiling $< ...
	$(Q)$(CC) -c -mmcs51 --stack-auto --nooverlay --std-c99 -IECBM_LIB -Idevice --model-small --iram-size 128 --xram-size 0 --code-size 8192 --opt-code-speed -MMD -o ./build/ECBMV3/.obj/main.o ./main.c

objs = ./build/ECBMV3/.obj/ECBM_LIB/adc.o ./build/ECBMV3/.obj/ECBM_LIB/beep.o ./build/ECBMV3/.obj/ECBM_LIB/cmp.o ./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.o ./build/ECBMV3/.obj/ECBM_LIB/eds.o ./build/ECBMV3/.obj/ECBM_LIB/eeprom.o ./build/ECBMV3/.obj/ECBM_LIB/exti.o ./build/ECBMV3/.obj/ECBM_LIB/gpio.o ./build/ECBMV3/.obj/ECBM_LIB/iic.o ./build/ECBMV3/.obj/ECBM_LIB/lcd.o ./build/ECBMV3/.obj/ECBM_LIB/lcm.o ./build/ECBMV3/.obj/ECBM_LIB/led.o ./build/ECBMV3/.obj/ECBM_LIB/mdu16.o ./build/ECBMV3/.obj/ECBM_LIB/nvic.o ./build/ECBMV3/.obj/ECBM_LIB/pca.o ./build/ECBMV3/.obj/ECBM_LIB/power.o ./build/ECBMV3/.obj/ECBM_LIB/pwm.o ./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.o ./build/ECBMV3/.obj/ECBM_LIB/soft_iic.o ./build/ECBMV3/.obj/ECBM_LIB/soft_spi.o ./build/ECBMV3/.obj/ECBM_LIB/spi.o ./build/ECBMV3/.obj/ECBM_LIB/stream.o ./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.o ./build/ECBMV3/.obj/ECBM_LIB/stream_fur.o ./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.o ./build/ECBMV3/.obj/ECBM_LIB/timer.o ./build/ECBMV3/.obj/ECBM_LIB/uart.o ./build/ECBMV3/.obj/main.o


elf: $(objs) Makefile
	@echo linking ./build/ECBMV3/ecbm.elf ...
	$(LD) --oformat=elf32-i51 --no-check-sections --print-memory-usage -L$(COMPILER_DIR)/share/sdcc/lib/small-stack-auto --gc-sections --defsym=__IDATA_SIZE__=128 --defsym=__XDATA_SIZE__=256 --defsym=__FLASH_SIZE__=8192 -Map ./build/ECBMV3/ecbm.map -o ./build/ECBMV3/ecbm.elf ./build/ECBMV3/.obj/ECBM_LIB/adc.o ./build/ECBMV3/.obj/ECBM_LIB/beep.o ./build/ECBMV3/.obj/ECBM_LIB/cmp.o ./build/ECBMV3/.obj/ECBM_LIB/ecbm_core.o ./build/ECBMV3/.obj/ECBM_LIB/eds.o ./build/ECBMV3/.obj/ECBM_LIB/eeprom.o ./build/ECBMV3/.obj/ECBM_LIB/exti.o ./build/ECBMV3/.obj/ECBM_LIB/gpio.o ./build/ECBMV3/.obj/ECBM_LIB/iic.o ./build/ECBMV3/.obj/ECBM_LIB/lcd.o ./build/ECBMV3/.obj/ECBM_LIB/lcm.o ./build/ECBMV3/.obj/ECBM_LIB/led.o ./build/ECBMV3/.obj/ECBM_LIB/mdu16.o ./build/ECBMV3/.obj/ECBM_LIB/nvic.o ./build/ECBMV3/.obj/ECBM_LIB/pca.o ./build/ECBMV3/.obj/ECBM_LIB/power.o ./build/ECBMV3/.obj/ECBM_LIB/pwm.o ./build/ECBMV3/.obj/ECBM_LIB/pwm16_out.o ./build/ECBMV3/.obj/ECBM_LIB/soft_iic.o ./build/ECBMV3/.obj/ECBM_LIB/soft_spi.o ./build/ECBMV3/.obj/ECBM_LIB/spi.o ./build/ECBMV3/.obj/ECBM_LIB/stream.o ./build/ECBMV3/.obj/ECBM_LIB/stream_ecp.o ./build/ECBMV3/.obj/ECBM_LIB/stream_fur.o ./build/ECBMV3/.obj/ECBM_LIB/stream_modbus.o ./build/ECBMV3/.obj/ECBM_LIB/timer.o ./build/ECBMV3/.obj/ECBM_LIB/uart.o ./build/ECBMV3/.obj/main.o  --start-group -lsdcc -lmcs51 -lint -llong -llonglong -lfloat --end-group

bin: elf Makefile
	@echo output binary files ...
	$(COMPILER_DIR)/bin/i51-elf-objcopy$(EXE) -O ihex ./build/ECBMV3/ecbm.elf ./build/ECBMV3/ecbm.hex

postbuild: bin
	@echo postbuild ...
	@echo nothing to postbuild.

# STC flashing configuration (can be overridden on command line)
STCGAL ?= stcgal
STC_PORT ?= COM5
STC_BAUD ?= 115200
STC_TYPE ?= auto

.PHONY: flash
# Flash the generated Intel HEX to the target using stcgal
ifeq ($(OS),Windows_NT)
flash: bin
	@echo windows Flashing ./build/ECBMV3/ecbm.hex to $(STC_PORT) ...
	@$(STCGAL) -p $(STC_PORT) -b $(STC_BAUD) -P $(STC_TYPE) .\\build\\ECBMV3\\ecbm.hex
	@echo windows Flashing success
else
flash: bin
	@echo Linux Flashing ./build/ECBMV3/ecbm.hex to $(STC_PORT) ...
	@$(STCGAL) -p $(STC_PORT) -b $(STC_BAUD) -P $(STC_TYPE) ./build/ECBMV3/ecbm.hex || (echo "stcgal failed"; exit 1)
endif

