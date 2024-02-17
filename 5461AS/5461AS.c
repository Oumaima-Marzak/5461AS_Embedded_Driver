/*
*   Author : Oumaima MARZAK
*
*
*/

#include "5461AS.h"
#include "DataTypes.h"
#include "BitConfig.h"
#include "dio.h"


static Uch8 NumArr[numbers][segments] = NumbersOnBinary;
static Uch8 CarArr[caracters][segments] = CaractersOnBinary;

void segement_dir(PinConfig seg_arr[segments])
{
    for (int i = 0; i < segments; i++)
    {
        configure_pin_direction(seg_arr[i]);
    }
}

void digit_dir(PinConfig d_arr[digits])
{
    for (int i = 0; i < digits; i++)
    {
        configure_pin_direction(d_arr[i]);
    }
}

void dp_dir(PinConfig dp_arr[dp])
{
    for (int i = 0; i < dp; i++)
    {
        configure_pin_direction(dp_arr[i]);
    }
}

void segement_state(PinConfig SEG, Uch8 STATE)
{
    configure_pin_state(SEG, STATE);
}

void digit_state(PinConfig DIG)
{
    clear_pin_state(DIG);
}

void dp_state(PinConfig dp_x, Uch8 STATE)
{
    configure_pin_state(dp_x, STATE);
}

void digit_init(PinConfig d_arr[digits])
{
    for (int i = 0; i < digits; i++)
    {
        set_pin_state(d_arr[i]);
    }    
}

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


