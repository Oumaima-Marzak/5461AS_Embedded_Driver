# 5461AS_Embedded_Driver


## 1. Introduction
 The 5461AS is a model of 7-segment LED display that consists of 4 digit (DIG1..4), each one controls 7-segments labeled A though G and a decimal point (dp). 
 
![Alt text](<Screenshot from 2024-02-18 18-19-28.png>)

 
 These displays are widely used in various electronic projects and devices for displaying numerical information. They are relatively simple to interface with microcontrollers and are often used in digital clocks, timers, counters and other similar applications. 




- Numbers truth table :

| num | A | B | C | D | E | F | G | Hex |
|-----|---|---|---|---|---|---|---|-----|
| 0   | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 0x7E|
| 1   | 0 | 1 | 1 | 0 | 0 | 0 | 0 | 0x30|
| 2   | 1 | 1 | 0 | 1 | 1 | 0 | 1 | 0x6D|
| 3   | 1 | 1 | 1 | 1 | 0 | 0 | 1 | 0x79|
| 4   | 0 | 1 | 1 | 0 | 0 | 1 | 1 | 0x33|
| 5   | 1 | 0 | 1 | 1 | 0 | 1 | 1 | 0x5B|
| 6   | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 0x5F|
| 7   | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0x70|
| 8   | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0x7F|
| 9   | 1 | 1 | 1 | 1 | 0 | 1 | 0 | 0x7B|


- Caracters truth table :

| car | A | B | C | D | E | F | G | Hex |
|-----|---|---|---|---|---|---|---|-----|
| A   | 1 | 1 | 1 | 0 | 1 | 1 | 1 | 0x7E|
| C   | 1 | 0 | 0 | 1 | 1 | 1 | 1 | 0x30|
| E   | 1 | 0 | 0 | 1 | 1 | 1 | 1 | 0x6D|
| F   | 1 | 0 | 0 | 0 | 1 | 1 | 1 | 0x79|

   
## 2. Features

## 3. Requirements

## 4. Usage
### 4.1. Basic Usage
### 4.2. Example Code

## 5. Driver Documentation
### 5.1. display numbers & caracters

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

### 5.2. segment, dp & digit direction

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

### 5.3. segment, dp & digit state

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

### 5.4. display initialisation 

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

### 5.5. macros

## 6. Contributing
## 7. License

