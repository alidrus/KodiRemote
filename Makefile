SHELL      := /bin/bash
FQBN       := esp32:esp32:esp32
BUILD_PATH := ./build
SRC_INO     := KodiRemote.ino
SRC_CPP     := Movement.cpp
SRC_H       := Movement.h Secrets.h
ELF        := $(BUILD_PATH)/$(SRC_INO).elf
SERIAL_DEV := /dev/ttyUSB0
BAUD_RATE  := 115200

all: $(ELF)

$(ELF): $(SRC_INO) $(SRC_CPP) $(SRC_H)
	arduino-cli compile --verbose --build-path $(BUILD_PATH) -b $(FQBN) -p $(SERIAL_DEV) $(SRC_INO)

upload: $(ELF)
	arduino-cli upload --verbose -b $(FQBN) -p $(SERIAL_DEV) --input-dir $(BUILD_PATH)

clean:
	rm -vfr $(BUILD_PATH)/*

monitor:
	minicom --device=$(SERIAL_DEV) --baudrate=$(BAUD_RATE)
