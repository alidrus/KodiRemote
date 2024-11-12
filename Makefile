SHELL      := /bin/bash
FQBN       := esp32:esp32:esp32
BUILD_PATH := ./build
SRCINO     := KodiRemote.ino
ELF        := $(BUILD_PATH)/$(SRCINO).elf
SERIAL_DEV := /dev/ttyUSB0
BAUD_RATE  := 115200

all: $(ELF)

$(ELF): $(SRCINO) *.cpp *.h
	arduino-cli compile --verbose --build-path $(BUILD_PATH) -b $(FQBN) -p $(SERIAL_DEV) $(SRCINO)

upload: $(ELF)
	arduino-cli upload --verbose -b $(FQBN) -p $(SERIAL_DEV) --input-dir $(BUILD_PATH)

clean:
	rm -vfr $(BUILD_PATH)/*

monitor:
	minicom --device=$(SERIAL_DEV) --baudrate=$(BAUD_RATE)
