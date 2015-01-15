#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

MCU          = atmega32u4
ARCH         = AVR8
BOARD        = MICRO
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = xat_hid
SRC          = main.c Descriptors.c adc_task.c \
	       accelstepper.c wall_time.c stepper_task.c \
	       $(U8G_SRC) display_task.c \
	       $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    = ./LUFA
U8G_PATH     = ./u8glib/src
U8G_SRC      = $(wildcard $(U8G_PATH)/*.c)
GIT_DESC     := $(shell git describe)
CC_FLAGS     = -fdata-sections -DUSE_LUFA_CONFIG_HEADER -IConfig/ -I$(U8G_PATH) -DGIT_DESC=$(GIT_DESC)
LD_FLAGS     =

AVRDUDE_PROGRAMMER ?= avr109
AVRDUDE_PORT       ?= /dev/ttyACM0

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
