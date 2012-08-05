#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

MCU                   = atmega32u4
ARCH                  = AVR8
BOARD                 = USBKEY
F_CPU                 = 16000000
F_USB                 = $(F_CPU)
FLASH_SIZE_KB         = 32
BOOT_SECTION_SIZE_KB  = 4
OPTIMIZATION          = s
TARGET                = tbase8
SRC                   = $(TARGET).c Descriptors.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH             = ../../../../LUFA/
CC_FLAGS              = -DUSE_LUFA_CONFIG_HEADER -IConfig/
LD_FLAGS              =
AVRDUDE_PROGRAMMER    = avr109
AVRDUDE_PORT          = /dev/tty.usbmodemfd121

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa.core.in
include $(LUFA_PATH)/Build/lufa.sources.in
include $(LUFA_PATH)/Build/lufa.build.in
include $(LUFA_PATH)/Build/lufa.cppcheck.in
include $(LUFA_PATH)/Build/lufa.doxygen.in
include $(LUFA_PATH)/Build/lufa.dfu.in
include $(LUFA_PATH)/Build/lufa.avrdude.in
include $(LUFA_PATH)/Build/lufa.atprogram.in
