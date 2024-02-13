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
    switch (SEG.port)
    {
        case Reg_B:
        
        if (STATE == HIGH)
        {
            SET_VAL_BIT(PORTB, SEG.pin);
        }
        else
        {
            CLEAR_VAL_BIT(PORTB, SEG.pin);
        } 

        break;

        case Reg_C:
        
        if (STATE == HIGH)
        {
            SET_VAL_BIT(PORTC, SEG.pin);
        }
        else
        {
            CLEAR_VAL_BIT(PORTC, SEG.pin);
        } 

        break;

        case Reg_D:
        
        if (STATE == HIGH)
        {
            SET_VAL_BIT(PORTD, SEG.pin);
        }
        else
        {
            CLEAR_VAL_BIT(PORTD, SEG.pin);
        } 

        break;
    
    }
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
        switch (d_arr[d1].ddr)
    {
        case Reg_B :
        SET_VAL_BIT(PORTB, d_arr[d1].pin);
        break;

        case Reg_C :
        SET_VAL_BIT(PORTC, d_arr[d1].pin);
        break;

        case Reg_D :
        SET_VAL_BIT(PORTD, d_arr[d1].pin);
        break;
    }

    switch (d_arr[d2].ddr)
    {
        case Reg_B :
        SET_VAL_BIT(PORTB, d_arr[d2].pin);
        break;

        case Reg_C :
        SET_VAL_BIT(PORTC, d_arr[d2].pin);
        break;

        case Reg_D :
        SET_VAL_BIT(PORTD, d_arr[d2].pin);
        break;
    }

    switch (d_arr[d3].ddr)
    {
        case Reg_B :
        SET_VAL_BIT(PORTB, d_arr[d3].pin);
        break;

        case Reg_C :
        SET_VAL_BIT(PORTC, d_arr[d3].pin);
        break;

        case Reg_D :
        SET_VAL_BIT(PORTD, d_arr[d3].pin);
        break;
    }

    switch (d_arr[d4].ddr)
    {
        case Reg_B :
        SET_VAL_BIT(PORTB, d_arr[d4].pin);
        break;

        case Reg_C :
        SET_VAL_BIT(PORTC, d_arr[d4].pin);
        break;

        case Reg_D :
        SET_VAL_BIT(PORTD, d_arr[d4].pin);
        break;
    }
}

void display_number(PinConfig seg_arr[segments], PinConfig d_arr[digits], Uch8 digit, Uch8 number)
{
    switch (digit)
    {
        case 1:
        digit_state(d_arr[d1]);
        break;
        
        case 2:
        digit_state(d_arr[d2]);
        break;
    
        case 3:
        digit_state(d_arr[d3]);
        break;
        
        case 4:
        digit_state(d_arr[d4]);
        break;
        
        
    }
    
    switch (number)
    {
        
        case 0 :
        segement_state(seg_arr[a], NumArr[0][0]);
        segement_state(seg_arr[b], NumArr[0][1]);
        segement_state(seg_arr[c], NumArr[0][2]);
        segement_state(seg_arr[d], NumArr[0][3]);
        segement_state(seg_arr[e], NumArr[0][4]);
        segement_state(seg_arr[f], NumArr[0][5]);
        segement_state(seg_arr[g], NumArr[0][6]);        
        break;

        case 1 :
        segement_state(seg_arr[a], NumArr[1][0]);
        segement_state(seg_arr[b], NumArr[1][1]);
        segement_state(seg_arr[c], NumArr[1][2]);
        segement_state(seg_arr[d], NumArr[1][3]);
        segement_state(seg_arr[e], NumArr[1][4]);
        segement_state(seg_arr[f], NumArr[1][5]);
        segement_state(seg_arr[g], NumArr[1][6]);  
        break;

        case 2 :
        segement_state(seg_arr[a], NumArr[2][0]);
        segement_state(seg_arr[b], NumArr[2][1]);
        segement_state(seg_arr[c], NumArr[2][2]);
        segement_state(seg_arr[d], NumArr[2][3]);
        segement_state(seg_arr[e], NumArr[2][4]);
        segement_state(seg_arr[f], NumArr[2][5]);
        segement_state(seg_arr[g], NumArr[2][6]);  
        break;

        case 3 :
        segement_state(seg_arr[a], NumArr[3][0]);
        segement_state(seg_arr[b], NumArr[3][1]);
        segement_state(seg_arr[c], NumArr[3][2]);
        segement_state(seg_arr[d], NumArr[3][3]);
        segement_state(seg_arr[e], NumArr[3][4]);
        segement_state(seg_arr[f], NumArr[3][5]);
        segement_state(seg_arr[g], NumArr[3][6]);  
        break;

        case 4 :
        segement_state(seg_arr[a], NumArr[4][0]);
        segement_state(seg_arr[b], NumArr[4][1]);
        segement_state(seg_arr[c], NumArr[4][2]);
        segement_state(seg_arr[d], NumArr[4][3]);
        segement_state(seg_arr[e], NumArr[4][4]);
        segement_state(seg_arr[f], NumArr[4][5]);
        segement_state(seg_arr[g], NumArr[4][6]);  
        break;

        case 5 :
        segement_state(seg_arr[a], NumArr[5][0]);
        segement_state(seg_arr[b], NumArr[5][1]);
        segement_state(seg_arr[c], NumArr[5][2]);
        segement_state(seg_arr[d], NumArr[5][3]);
        segement_state(seg_arr[e], NumArr[5][4]);
        segement_state(seg_arr[f], NumArr[5][5]);
        segement_state(seg_arr[g], NumArr[5][6]);  
        break;

        case 6 :
        segement_state(seg_arr[a], NumArr[6][0]);
        segement_state(seg_arr[b], NumArr[6][1]);
        segement_state(seg_arr[c], NumArr[6][2]);
        segement_state(seg_arr[d], NumArr[6][3]);
        segement_state(seg_arr[e], NumArr[6][4]);
        segement_state(seg_arr[f], NumArr[6][5]);
        segement_state(seg_arr[g], NumArr[6][6]);  
        break;

        case 7 :
        segement_state(seg_arr[a], NumArr[7][0]);
        segement_state(seg_arr[b], NumArr[7][1]);
        segement_state(seg_arr[c], NumArr[7][2]);
        segement_state(seg_arr[d], NumArr[7][3]);
        segement_state(seg_arr[e], NumArr[7][4]);
        segement_state(seg_arr[f], NumArr[7][5]);
        segement_state(seg_arr[g], NumArr[7][6]);  
        break;

        case 8 :
        segement_state(seg_arr[a], NumArr[8][0]);
        segement_state(seg_arr[b], NumArr[8][1]);
        segement_state(seg_arr[c], NumArr[8][2]);
        segement_state(seg_arr[d], NumArr[8][3]);
        segement_state(seg_arr[e], NumArr[8][4]);
        segement_state(seg_arr[f], NumArr[8][5]);
        segement_state(seg_arr[g], NumArr[8][6]);  
        break;

        case 9 :
        segement_state(seg_arr[a], NumArr[9][0]);
        segement_state(seg_arr[b], NumArr[9][1]);
        segement_state(seg_arr[c], NumArr[9][2]);
        segement_state(seg_arr[d], NumArr[9][3]);
        segement_state(seg_arr[e], NumArr[9][4]);
        segement_state(seg_arr[f], NumArr[9][5]);
        segement_state(seg_arr[g], NumArr[9][6]);  
        break;

    }
}

void display_caracter(PinConfig seg_arr[segments], PinConfig d_arr[digits], Uch8 digit, Uch8 caracter)
{
    switch (digit)
    {
        case 1:
        digit_state(d_arr[d1]);
        break;

        case 2:
        digit_state(d_arr[d2]);
        break;

        case 3:
        digit_state(d_arr[d3]);
        break;

        case 4:
        digit_state(d_arr[d4]);
        break;
    }

    switch (caracter)
    {
        
        case 'A' :
        segement_state(seg_arr[a], CarArr[0][0]);
        segement_state(seg_arr[b], CarArr[0][1]);
        segement_state(seg_arr[c], CarArr[0][2]);
        segement_state(seg_arr[d], CarArr[0][3]);
        segement_state(seg_arr[e], CarArr[0][4]);
        segement_state(seg_arr[f], CarArr[0][5]);
        segement_state(seg_arr[g], CarArr[0][6]);           
        break;

        case 'C' :
        segement_state(seg_arr[a], CarArr[1][0]);
        segement_state(seg_arr[b], CarArr[1][1]);
        segement_state(seg_arr[c], CarArr[1][2]);
        segement_state(seg_arr[d], CarArr[1][3]);
        segement_state(seg_arr[e], CarArr[1][4]);
        segement_state(seg_arr[f], CarArr[1][5]);
        segement_state(seg_arr[g], CarArr[1][6]);  
        break;

        case 'E' :
        segement_state(seg_arr[a], CarArr[2][0]);
        segement_state(seg_arr[b], CarArr[2][1]);
        segement_state(seg_arr[c], CarArr[2][2]);
        segement_state(seg_arr[d], CarArr[2][3]);
        segement_state(seg_arr[e], CarArr[2][4]);
        segement_state(seg_arr[f], CarArr[2][5]);
        segement_state(seg_arr[g], CarArr[2][6]);  
        break;

        case 'F' :
        segement_state(seg_arr[a], CarArr[3][0]);
        segement_state(seg_arr[b], CarArr[3][1]);
        segement_state(seg_arr[c], CarArr[3][2]);
        segement_state(seg_arr[d], CarArr[3][3]);
        segement_state(seg_arr[e], CarArr[3][4]);
        segement_state(seg_arr[f], CarArr[3][5]);
        segement_state(seg_arr[g], CarArr[3][6]);  
        break;
    }
}


