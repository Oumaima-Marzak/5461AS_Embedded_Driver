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

void segement_state(PinConfig SEG, Uch8 STATE)
{
    configure_pin_state(SEG, STATE);
}

void digit_state(PinConfig DIG)
{
    switch (DIG.port)
    {
        case Reg_B:

        CLEAR_VAL_BIT(PORTB, DIG.pin);

        break;

        case Reg_C:

        CLEAR_VAL_BIT(PORTC, DIG.pin); 

        break;

        case Reg_D:
        
        CLEAR_VAL_BIT(PORTD, DIG.pin); 

        break;
    
    }
}

void digit_init(PinConfig d_arr[digits])
{
    for (int i = 0; i < digits; i++)
    {
        switch (d_arr[i].port)
        {
            case Reg_B :
            SET_VAL_BIT(PORTB, d_arr[i].pin);
            break;

            case Reg_C :
            SET_VAL_BIT(PORTC, d_arr[i].pin);
            break;

            case Reg_D :
            SET_VAL_BIT(PORTD, d_arr[i].pin);
            break;
        }
    }    
}

void display_number(PinConfig seg_arr[segments], PinConfig d_arr[digits], Uch8 digit, Uch8 number)
{
    digit_state(d_arr[digit - 1]); // Set digit state
    
    if (number >= 0 && number <= 9)
    {
        for (int i = 0; i < segments; i++)
        {
            segement_state(seg_arr[i], NumArr[number][i]);
        }
    }
}

void display_caracter(PinConfig seg_arr[segments], PinConfig d_arr[digits], Uch8 digit, Uch8 caracter)
{
    digit_state(d_arr[digit - 1]); // Set digit state

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

    for (int i = 0; i < segments; i++) {
        segement_state(seg_arr[i], CarArr[charIndex][i]);
    }

}


