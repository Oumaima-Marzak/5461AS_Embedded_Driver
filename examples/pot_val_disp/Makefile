# Define source code files path variables
SRC_DIR = /home/oumaima/Desktop/5461AS_Embedded_Driver/examples/pot_val_disp
SSEG_DIR = /home/oumaima/Desktop/5461AS_Embedded_Driver/5461AS
DIO_DIR = /home/oumaima/Desktop/Atmega328p_Drivers/DIO
LIB_DIR = /home/oumaima/Desktop/Atmega328p_Drivers/LIB
ADC_DIR = /home/oumaima/Desktop/Atmega328p_Drivers/ADC

SRC = $(SRC_DIR)/pot_value.c
SRC_FILES = $(DIO_DIR)/dio.c $(ADC_DIR)/adc.c $(SSEG_DIR)/5461AS.c $(SRC)
TARGET = pot_val_display

# Compiler and flags
CC = avr-gcc
CFLAGS = -I$(DIO_DIR) -I$(ADC_DIR) -I$(SSEG_DIR) -I$(LIB_DIR) -Os -DF_CPU=16000000UL -mmcu=atmega328p

# Programmer settings
PROGRAMMER = arduino
PORT = /dev/ttyACM0
BAUD_RATE = 115200

# Additional dependencies (header files)
DEPS = $(SSEG_DIR)/5461AS.h $(DIO_DIR)/dio.h $(ADC_DIR)/adc.h $(LIB_DIR)/DataTypes.h $(LIB_DIR)/BitConfig.h

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