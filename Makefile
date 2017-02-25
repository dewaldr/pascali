# Arduino-based intelligent pump controller
#
# Arduino.mk variables
ARDUINO_DIR         = /usr/share/arduino
AVR_TOOLS_DIR       = /usr
AVRDUDE_CONF		= /etc/avrdude.conf
BOARD_TAG           = pro5v328
ARDUINO_PORT        = /dev/ttyUSB0
MONITOR_PORT		= /dev/ttyUSB0
MONITOR_BAUDRATE    = 9600

TARGET              = pascali

include /opt/arduino-mk/Arduino.mk

realclean: clean
	rm -f *~

