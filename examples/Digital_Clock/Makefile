# Define source code and header files path variables
SRC_DIR = /home/oumaima/Desktop/5461AS_Embedded_Driver/examples/Digital_Clock
SSEG_DIR = /home/oumaima/Desktop/5461AS_Embedded_Driver/5461AS
DIO_DIR = /home/oumaima/Desktop/Atmega328p_Drivers/DIO
LIB_DIR = /home/oumaima/Desktop/Atmega328p_Drivers/LIB
TIMER_DIR = /home/oumaima/Desktop/Atmega328p_Drivers/TIMER
INT_DIR = /home/oumaima/Desktop/Atmega328p_Drivers/INTERRUPTS


SRC = $(SRC_DIR)/digital_clock.c
SRC_FILES = $(DIO_DIR)/dio.c $(TIMER_DIR)/timer.c $(SSEG_DIR)/5461AS.c $(SRC)
TARGET = digital_clock

# Compiler and flags
CC = avr-gcc
CFLAGS = -I$(LIB_DIR) -I$(DIO_DIR) -I$(TIMER_DIR) -I$(INT_DIR) -I$(SSEG_DIR) -Os -DF_CPU=16000000UL -mmcu=atmega328p

# Programmer settings
PROGRAMMER = arduino
PORT = /dev/ttyACM0
BAUD_RATE = 115200

# Additional dependencies (header files)
DEPS = $(LIB_DIR)/DataTypes.h $(LIB_DIR)/BitConfig.h $(DIO_DIR)/dio.h $(TIMER_DIR)/timer.h -I$(INT_DIR)/interrupts.h $(SSEG_DIR)/5461AS.h 

# Object files
OBJ = $(SRC_FILES:.c=.o)

# Default target
all: $(TARGET).hex

# Compile C source code to object file
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the binary
$(TARGET).elf: $(OBJ)
	$(CC) -mmcu=atmega328p $^ -o $@

# Convert binary to Intel Hex format
$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

# Program the ATmega328P using avrdude
program: $(TARGET).hex
	avrdude -F -V -c $(PROGRAMMER) -p ATMEGA328P -P $(PORT) -b $(BAUD_RATE) -U flash:w:$<

# Clean up generated files
clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).hex

.PHONY: all program clean