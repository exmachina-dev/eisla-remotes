BOARDS_TXT = ../hardware/boards.txt
BOARD_TAG = eislaremotes
BOARD_SUB = 8MHzatmega328

# # Overriding default fuse # Only for debugging purposes
# ISP_LOW_FUSE = 0xFF
# ISP_HIGH_FUSE = 0xDA
# ISP_EXT_FUSE = 0x05

USER_LIB_PATH = ../lib
ARDUINO_LIBS = eisla EEPROM

MONITOR_PORT = 3

include ../hardware/ISP.mk
