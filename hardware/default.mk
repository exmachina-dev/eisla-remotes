BOARDS_TXT = ../hardware/boards.txt
BOARD_TAG = eislaremotes
BOARD_SUB = 8MHzatmega328

# Overriding default fuse
ISP_LOW_FUSE = 0x62
ISP_HIGH_FUSE = 0xD8
ISP_EXT_FUSE = 0x07

USER_LIB_PATH = ../lib
ARDUINO_LIBS = eisla EEPROM

MONITOR_PORT = 3

include ../hardware/ISP.mk
