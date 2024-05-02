# 5461AS_Embedded_Driver

## 1. Introduction

 The 5461AS is a common model of 7-segment LED displays widely utilized in various electronic projects and devices. The model comprises four digits (DIG1..4), with each digit controlling seven segments labeled A through G and a decimal point (dp). These displays find applications in digital clocks, timers, counters, and similar devices for displaying numerical information.

 Interfacing with the 5461AS display can be challenging due to the multiple pins involved. For example, displaying the number 8 on one of the digits requires all segments (A, B, C ... G) to be turned on, necessitating 7 pins to be set to a high state. This means that the pins should be connected rankily to one register of 8 bits to facilitate the assignment of the value 0x7F (representing that all 7 pins are in a high state). However, this approach may not be applicable for all microcontrollers.

 For instance, let's consider the ATmega328P microcontroller on the Arduino Uno board. While it has two 8-bit registers, namely PORTD and PORTB, for managing digital I/O pin states, not all pins controlled by those registers are dedicated to digital I/O. On PORTD, pins PD2 to PD7 typically handle digital I/O, while PD0 and PD1 are reserved for UART communication (on the Arduino Uno board). Similarly, on PORTB, only pins PB0 to PB5 are used for digital I/O tasks.

 To address these challenges, this driver has been developed to simplify the interfacing process with the 5461AS display. It enables connecting the segments to any digital pin on the microcontroller without worrying about segment rankings. Additionally, the driver facilitates the display of numbers from 0 to 9 and four letters: A, C, E, and F on any digit from 1 to 4.

   
## 2. Features
 1. Flexible Pin Assignment: 

 This driver offers the flexibility to assign digital pins for interfacing with the 5461AS display, accommodating different microcontroller pin configurations. This feature allows users to easily adapt the driver to their specific hardware setup, ensuring seamless integration with minimal effort.

 2. Easy Interfacing: 

 Simplifying the interfacing process, this driver abstracts away the complexities of managing multiple pins and segment rankings associated with the 5461AS display. Users can focus on their application logic without worrying about the intricacies of low-level hardware interactions.

 3. Support for Numeric Display: 

 With built-in support for numeric characters (0-9), this driver enables users to display numerical information on any of the four digits (DIG1..4) of the 5461AS display effortlessly. This feature facilitates the implementation of applications such as digital clocks, timers, and counters with ease.

 4. Support for Letter Display: 

 In addition to numeric characters, this driver allows the display of letters A, C, E, and F on the 5461AS display. This feature enhances the versatility of the display, enabling a wider range of applications, including alphanumeric data presentation and messaging systems.

 5. Portability Across Platforms: 

 This driver ensures compatibility with various microcontroller platforms, making it suitable for a wide range of hardware configurations. 

## 3. Driver Documentation
### 3.1. display numbers & caracters

- display_number(): This function displays a numeric number (0-9) on a specified digit of the 5461AS display. 

    Function variables :

    - PinConfig seg_arr[segments]: An array of PinConfig structures representing the segment pins (A-G) of the 5461AS display.

    - PinConfig d_arr[digits]: An array of PinConfig structures representing the digit pins (DIG1-4) of the 5461AS display.

    - Uch8 digit: The digit (DIG1-4) on which to display the number.

    - Uch8 number: The number (0-9) to display on the specified digit.

```c
ErrorStatus display_number(PinConfig seg_arr[segments], PinConfig d_arr[digits], Uch8 digit, Uch8 number)
{
    
    if (digit < 0 || digit > digits  || number < 0 || number > numbers)
    {
        return _INVALID_PARAM;
    }

    else 
    {
        digit_state(d_arr[digit]); 
    
        if (number >= 0 && number <= 9)
        {
            for (int i = 0; i < segments; i++)
            {
                segement_state(seg_arr[i], NumArr[number][i]);
            }
        }

        return _OK;
    }
}    

```
- display_caracter(): This function displays a character ('A', 'C', 'E', or 'F') on a specified digit of the 5461AS display.

    Function variables :

    - PinConfig seg_arr[segments]: An array of PinConfig structures representing the segment pins (A-G) of the 5461AS display.

    - PinConfig d_arr[digits]: An array of PinConfig structures representing the digit pins (DIG1-4) of the 5461AS display.

    - Uch8 digit: The digit (DIG1-4) on which to display the character.

    - Uch8 caracter: The character ('A', 'C', 'E', or 'F') to display on the specified digit.

```c
ErrorStatus display_caracter(PinConfig seg_arr[segments], PinConfig d_arr[digits], Uch8 digit, Uch8 caracter)
{
    if (digit < 1 || digit > digits + 1 )
    {
        return _INVALID_PARAM;
    }

    else 
    {
        digit_state(d_arr[digit]); // Set digit state

        Uch8 charIndex = 0;

        switch (caracter) {
            case 'A':
                charIndex = 0;
                break;
            case 'C':
                charIndex = 1;
                break;
            case 'E':
                charIndex = 2;
                break;
            case 'F':
                charIndex = 3;
                break;
        }

        for (int i = 0; i < segments; i++) 
        {
            segement_state(seg_arr[i], CarArr[charIndex][i]);
        }

        return _OK;

    }

}

```

### 3.2. segment, dp & digit direction

- segement_dir(): This function configures the direction of all segment pins (A-G) of the 5461AS display.

```c
void segement_dir(PinConfig seg_arr[segments])
{
    for (int i = 0; i < segments; i++)
    {
        configure_pin_direction(seg_arr[i]);
    }
}

```

- dp_dir(): This function configures the direction of the decimal point (DP) pins of the 5461AS display.

```c
void dp_dir(PinConfig dp_arr[dp])
{
    for (int i = 0; i < dp; i++)
    {
        configure_pin_direction(dp_arr[i]);
    }
}

```

- digit_dir(): This function configures the direction of all digit pins (DIG1-4) of the 5461AS display.

```c
void digit_dir(PinConfig d_arr[digits])
{
    for (int i = 0; i < digits; i++)
    {
        configure_pin_direction(d_arr[i]);
    }
}

```

### 3.3. segment, dp & digit state

- segement_state(): This function sets the state of a segment pin (A-G) of the 5461AS display.

    - PinConfig SEG: PinConfig structures representing the segment pin of the 5461AS display.
    - Uch8 STATE: The state (high/low) to which the segment pin or decimal point pin is to be set.

```c
void segement_state(PinConfig SEG, Uch8 STATE)
{
    configure_pin_state(SEG, STATE);
} 

```

- dp_state(): This function sets the state of a decimal point (DP) pin of the 5461AS display.

    - PinConfig dp_x: PinConfig structures representing the decimal point pin of the 5461AS display.
    - Uch8 STATE: The state (high/low) to which the segment pin or decimal point pin is to be set.

```c
void dp_state(PinConfig dp_x, Uch8 STATE)
{
    configure_pin_state(dp_x, STATE);
}
```

- digit_state(): This function sets the state of a digit pin (DIG1-4) of the 5461AS display.

    - PinConfig DIG: A PinConfig structure representing the digit pin (DIG1-4) of the 5461AS display.

```c
void digit_state(PinConfig DIG)
{
    clear_pin_state(DIG);
}
```

### 3.4. display initialization 

- digit-init(): This function initializes all digit pins (DIG1-4) of the 5461AS display.

```c
void digit_init(PinConfig d_arr[digits])
{
    for (int i = 0; i < digits; i++)
    {
        set_pin_state(d_arr[i]);
    }    
}
```

## 4.Notes

 The driver has been tested with the Atmega328p microcontroller on the Arduino Uno board, and it is primarily designed to work with the digital I/O (DIO) driver of that specific microcontroller. If you are using the same microcontroller, you can find its drivers in the repository [Atmega328p_Drivers](https://github.com/Oumaima-Marzak/Atmega328p_Drivers).

 For compatibility with other microcontrollers, the driver requires adaptations in terms of the names and addresses of digital I/O registers used. Based on that, some functions may need adjustments to align with the architecture of the target microcontroller.
