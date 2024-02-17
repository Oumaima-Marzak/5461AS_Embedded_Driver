#include "5461AS.h"
#include "dio.h"
#include "DataTypes.h"
#include "BitConfig.h"
#include <util/delay.h>


#define num_display  1999

/*

    PinConfig seg_a =  {PD3, Reg_D, Reg_D};  // 11
    PinConfig seg_b =  {PD4, Reg_D, Reg_D};  // 7
    PinConfig seg_c =  {PD7, Reg_D, Reg_D};  // 4
    PinConfig seg_d =  {PB0, Reg_B, Reg_B};  // 2
    PinConfig seg_e =  {PB1, Reg_B, Reg_B};  // 1
    PinConfig seg_f =  {PD2, Reg_D, Reg_D};  // 10
    PinConfig seg_g =  {PD6, Reg_D, Reg_D};  // 5
                                             // 3 for dp   
    PinConfig d_1 = {PB2, Reg_B, Reg_B};     //12
    PinConfig d_2 = {PB3, Reg_B, Reg_B};     //9
    PinConfig d_3 = {PB4, Reg_B, Reg_B};     //8 
    PinConfig d_4 = {PB5, Reg_B, Reg_B};     //6

*/


void main()
{

    // Pin configurations for segments
    PinConfig seg_arr[segments] = {
        {PD3, Reg_D, Reg_D}, // Segment a
        {PD4, Reg_D, Reg_D}, // Segment b
        {PD7, Reg_D, Reg_D}, // Segment c
        {PB0, Reg_B, Reg_B}, // Segment d
        {PB1, Reg_B, Reg_B}, // Segment e
        {PD2, Reg_D, Reg_D}, // Segment f
        {PD6, Reg_D, Reg_D}  // Segment g
    };

    // Pin configurations for digits
    PinConfig d_arr[digits] = {
        {PB2, Reg_B, Reg_B}, // Digit 1
        {PB3, Reg_B, Reg_B}, // Digit 2
        {PB4, Reg_B, Reg_B}, // Digit 3
        {PB5, Reg_B, Reg_B}  // Digit 4
    };

    segement_dir(seg_arr);
    digit_dir(d_arr);

    Uch8 ones, tens, hundreds, thousands; 


    for(int i = 0; i <= num_display; i++)
    {   
        ones = i % 10;
        tens = (i / 10) % 10;
        hundreds = (i / 100) % 10;
        thousands = (i / 1000) % 10;

        // Display the digits based on the number value
        digit_init(d_arr);
        display_number(seg_arr, d_arr, d4, ones);
        _delay_ms(5); 

        if (i >= 10)
        {
            digit_init(d_arr);
            display_number(seg_arr, d_arr, d3, tens);
            _delay_ms(5); 
        }

        if (i >= 100)
        {
            digit_init(d_arr);
            display_number(seg_arr, d_arr, d2, hundreds);
            _delay_ms(5); 
        }

        if (i >= 1000)
        {
            digit_init(d_arr);
            display_number(seg_arr, d_arr, d1, thousands);
            _delay_ms(5); 
        }
    }

    while (1)
    {
        digit_init(d_arr);
        display_number(seg_arr, d_arr, d4, ones); 
        _delay_ms(1); 

        digit_init(d_arr);
        display_number(seg_arr, d_arr, d3, tens); 
        _delay_ms(1);

        digit_init(d_arr);
        display_number(seg_arr, d_arr, d2, hundreds); 
        _delay_ms(1); 

        digit_init(d_arr);
        display_number(seg_arr, d_arr, d1, thousands); 
        _delay_ms(1); 
    }



}

