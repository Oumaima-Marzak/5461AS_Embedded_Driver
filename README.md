# 5461AS_Embedded_Driver


## 1. Introduction

 The 5461AS is a common model of 7-segment LED displays widely utilized in various electronic projects and devices. Each display comprises four digits (DIG1..4), with each digit controlling seven segments labeled A through G and a decimal point (dp). These displays find applications in digital clocks, timers, counters, and similar devices for displaying numerical information.

 Interfacing with the 5461AS display can be challenging due to the multiple pins involved. For example, displaying the number 8 on digit 4 requires all segments (A, B, C ... G) to be turned on, necessitating 8 pins to be set to high state. However, Not all microcontrollers offer digital I/O registers with a sufficient number of pins readily available for connecting to all segments of a 7-segment LED display. For instance, let's consider the ATmega328P microcontroller, a popular choice found on the Arduino Uno board. While it boasts two 8-bit registers, namely PORTD and PORTB, for managing digital I/O pins state, the available pins are not universally dedicated solely to digital I/O operations.

 The ATmega328P on Arduino Uno board, only specific pins within these registers are designated for digital input and output. For example, on PORTD, pins PD2 to PD7 typically handle digital I/O, while PD0 and PD1 are often reserved for communication purposes like UART (Universal Asynchronous Receiver-Transmitter). Similarly, on PORTB, only pins PB0 to PB5 are commonly used for digital I/O tasks.

 To address these challenges, this driver has been developed to simplify the interfacing process with the 5461AS display. It enables connecting the segments to any digital pin on the microcontroller without worrying about segment rankings. Additionally, the driver facilitates the display of numbers from 0 to 9 on any digit from 1 to 4. Furthermore, it supports the display of four letters: A, C, E, and F.

   
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

## 3. Requirements

## 4. Driver Documentation
### 4.1. display numbers & caracters

- display_number();

```
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
- display_caracter();

```
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

### 4.2. segment, dp & digit direction

- configure_pin_direction();

```
void configure_pin_direction(PinConfig pin)
{
    switch (pin.ddr) 
    {
        case Reg_B:
            SET_VAL_BIT(DDRB, pin.pin);
            break;

        case Reg_C:
            SET_VAL_BIT(DDRC, pin.pin);
            break;

        case Reg_D:
            SET_VAL_BIT(DDRD, pin.pin);
            break;
    }
    
}
```

- segement_dir();

```
void segement_dir(PinConfig seg_arr[segments])
{
    for (int i = 0; i < segments; i++)
    {
        configure_pin_direction(seg_arr[i]);
    }
}

```

- dp_dir();

```
void dp_dir(PinConfig dp_arr[dp])
{
    for (int i = 0; i < dp; i++)
    {
        configure_pin_direction(dp_arr[i]);
    }
}

```

- digit_dir();

```
void digit_dir(PinConfig d_arr[digits])
{
    for (int i = 0; i < digits; i++)
    {
        configure_pin_direction(d_arr[i]);
    }
}

```

### 4.3. segment, dp & digit state

- configure_pin_state();

```
(I think the function needs optimization !!)

```

- segement_state();

```
void segement_state(PinConfig SEG, Uch8 STATE)
{
    configure_pin_state(SEG, STATE);
} 

```

- dp_state();

```
void dp_state(PinConfig dp_x, Uch8 STATE)
{
    configure_pin_state(dp_x, STATE);
}
```

- digit_state();

```
void digit_state(PinConfig DIG)
{
    clear_pin_state(DIG);
}
```

### 4.4. display initialisation 

- digit-init(); (je pense que khas tbdli liha smiya)

```
void digit_init(PinConfig d_arr[digits])
{
    for (int i = 0; i < digits; i++)
    {
        set_pin_state(d_arr[i]);
    }    
}
```

### 4.5. macros

## 5. Contributing
## 6. License

