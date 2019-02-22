# Tiva Makefile
# #####################################
#
# Part of the uCtools project
# uctools.github.com
#
#######################################
# user configuration:
#######################################
# TIVAWARE_PATH: path to tivaware folder
TIVAWARE_PATH = /home/tyler/embedded/SW-EK-TM4C123GXL-2.1.4.178
# TARGET: name of the output file
TARGET = main
# MCU: part number to build for
MCU = TM4C123GH6PM
# SOURCES: list of input source sources
SOURCES = main.c startup_gcc.c adc_commands.c
SOURCES += $(TIVAWARE_PATH)/utils/uartstdio.c
SOURCES += $(TIVAWARE_PATH)/utils/cmdline.c
SOURCES += $(TIVAWARE_PATH)/driverlib/uart.c
SOURCES += $(TIVAWARE_PATH)/driverlib/adc.c
SOURCES += $(TIVAWARE_PATH)/driverlib/sysctl.c
# INCLUDES: list of includes, by default, use Includes directory
INCLUDES = -IInclude
INCLUDES += -I$(TIVAWARE_PATH)
INCLUDES += -I$(TIVAWARE_PATH)/inc/
INCLUDES += -I$(TIVAWARE_PATH)/driverlib/
INCLUDES += -I$(TIVAWARE_PATH)/utils/
# OUTDIR: directory to use for output
OUTDIR = build

# LD_SCRIPT: linker script
LD_SCRIPT = $(MCU).ld

# define flags
#CFLAGS = -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
#CFLAGS +=-Os -ffunction-sections -fdata-sections -MD -std=c99 -Wall
##CFLAGS += -pedantic -DPART_$(MCU) -c -I$(TIVAWARE_PATH)
#CFLAGS += -pedantic -DPART_$(MCU) -c $(INCLUDES)
#CFLAGS += -DTARGET_IS_BLIZZARD_RA1
#LDFLAGS = -T $(LD_SCRIPT) --entry ResetISR --gc-sections

COREFLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
CFLAGS = -g $(COREFLAGS)
CFLAGS +=-Os -ffunction-sections -fdata-sections -MD -std=c99 -Wall
#CFLAGS += -pedantic -DPART_$(MCU) -c -I$(TIVAWARE_PATH)
CFLAGS += -pedantic -DPART_$(MCU) -c $(INCLUDES)
CFLAGS += -DTARGET_IS_BLIZZARD_RA1
LDFLAGS = $(COREFLAGS) -T$(LD_SCRIPT) -Wl,--entry=ResetISR,--gc-sections

#######################################
# end of user configuration
#######################################
#
#######################################
# binaries
#######################################
CC = arm-none-eabi-gcc
#LD = arm-none-eabi-ld
LD = arm-none-eabi-g++
OBJCOPY = arm-none-eabi-objcopy
RM      = rm -f
MKDIR	= mkdir -p
#######################################

# list of object files, placed in the build directory regardless of source path
OBJECTS = $(addprefix $(OUTDIR)/,$(notdir $(SOURCES:.c=.o)))

# default: build bin
all: $(OUTDIR)/$(TARGET).bin

$(OUTDIR)/%.o: src/%.c | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/a.out: $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OUTDIR)/uartstdio.o: $(TIVAWARE_PATH)/utils/uartstdio.c
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/cmdline.o: $(TIVAWARE_PATH)/utils/cmdline.c
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/uart.o: $(TIVAWARE_PATH)/driverlib/uart.c
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/adc.o: $(TIVAWARE_PATH)/driverlib/adc.c
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/sysctl.o: $(TIVAWARE_PATH)/driverlib/sysctl.c
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTDIR)/main.bin: $(OUTDIR)/a.out
	$(OBJCOPY) -O binary $< $@

# create the output directory
$(OUTDIR):
	$(MKDIR) $(OUTDIR)

clean:
	-$(RM) $(OUTDIR)/*

flash:
	lm4flash $(OUTDIR)/$(TARGET).bin

.PHONY: all clean flash
