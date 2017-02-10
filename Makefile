# Arduno-based intelligent pump controller
#
# Arduino.mk variables
ARDUINO_DIR         = /opt/arduino
AVR_TOOLS_DIR       = /usr

TARGET              = pascali
ARDUINO_LIBS        = 

BOARD_TAG           = uno
ARDUINO_PORT        = /dev/ttyACM0
MONITOR_BAUDRATE    = 115200

include /opt/arduino-mk/Arduino.mk

realclean: clean
	rm -f *~

