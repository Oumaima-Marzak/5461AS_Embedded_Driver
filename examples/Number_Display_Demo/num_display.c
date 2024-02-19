/*
 * Copyright 2024 Oumaima Marzak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "5461AS.h"
#include "dio.h"
#include "DataTypes.h"
#include "BitConfig.h"
#include <util/delay.h>


#define num_display  1999


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
        display_number(seg_arr, d_arr, d4, ones);
        _delay_ms(5); 

        if (i >= 10)
        {
            display_number(seg_arr, d_arr, d3, tens);
            _delay_ms(5); 
        }

        if (i >= 100)
        {
            display_number(seg_arr, d_arr, d2, hundreds);
            _delay_ms(5); 
        }

        if (i >= 1000)
        {
            display_number(seg_arr, d_arr, d1, thousands);
            _delay_ms(5); 
        }
    }

    while (1)
    {
        display_number(seg_arr, d_arr, d4, ones); 
        _delay_ms(1); 

        display_number(seg_arr, d_arr, d3, tens); 
        _delay_ms(1);

        display_number(seg_arr, d_arr, d2, hundreds); 
        _delay_ms(1); 

        display_number(seg_arr, d_arr, d1, thousands); 
        _delay_ms(1); 
    }



}

