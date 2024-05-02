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
 * 
 * 
 * 
 * Digital Clock is an example project demonstrating the use of the 5461AS display 
 * with the ATmega328p microcontroller. The clock behavior is illustrated, and 
 * users can adjust the time by modifying the 'hour' and 'minute' macros in the code.
 * 
 * Note: This example serves as a demonstration and may require manual time adjustment
 *       each time the microcontroller loses power. For a real-time clock without this
 *       limitation, consider using external devices such as Real-Time Clock (RTC) Modules.
 */

#include "DataTypes.h"
#include "BitConfig.h"
#include "dio.h"
#include "timer.h"
#include "interrupts.h"
#include "5461AS.h"


/* 
 * Macros: hour and minute
 * Definition: Define the user-set clock time.
 *
 * Note: The time must be readjusted (using these macros) every time the microcontroller
 *       loses power.
 */
#define hour   07
#define minute 14

/**** Global Variables ****/

/*
 * H
 * Definition: Stores the value of the 'hour' macro defined by the user.
 */
volatile Uch8 H = hour;

/*
 * M
 * Definition: Stores the value of the 'minute' macro defined by the user.
 */
volatile Uch8 M = minute;

/*
 * s
 * Definition: Stores the seconds value. Used in the Timer 1 interrupt ISR.
 */
volatile Uch8 s = 0;

/*
 * ms
 * Definition: Stores the milliseconds value. Used in the Timer 0 interrupt ISR.
 */
volatile Uch8 ms = 0;

/* 
 * hTensDigit, hOnesDigit, mTensDigit, mOnesDigit
 * Definitions: Store the tens and ones places of the hour and minute digits.
 */
volatile Uch8 hTensDigit, hOnesDigit, mTensDigit, mOnesDigit;

/*
 * Digit
 * Definition: Represents the digits d1, d2, d3, and d4.
 *
 * DigitValue
 * Definition: Represents the numbers (clock time) that a digit can take.
 */
volatile Uch8 digit, DigitValue;

/* Global Pins Declaration */

/*
 * dp
 * Definition: Decimal point pin.
 */
PinConfig dp = {PD5, Reg_D, Reg_D};

/*
 * d_arr
 * Definition: Array of digit pins.
 */
PinConfig d_arr[digits] = 
{
    {PB2, Reg_B, Reg_B}, // Digit 1
    {PB3, Reg_B, Reg_B}, // Digit 2
    {PB4, Reg_B, Reg_B}, // Digit 3
    {PB5, Reg_B, Reg_B}  // Digit 4
};

/*
 * seg_arr
 * Definition: Array of segment pins.
 */
PinConfig seg_arr[segments] = 
{
    {PD3, Reg_D, Reg_D}, // Segment a
    {PD4, Reg_D, Reg_D}, // Segment b
    {PD7, Reg_D, Reg_D}, // Segment c
    {PB0, Reg_B, Reg_B}, // Segment d
    {PB1, Reg_B, Reg_B}, // Segment e
    {PD2, Reg_D, Reg_D}, // Segment f
    {PD6, Reg_D, Reg_D}  // Segment g
};

/*
 * Timer/Counter0 Compare Match A Interrupt Service Routine (ISR)
 * Description: Executes every 1ms to create the 'persistence of vision' phenomenon.
 *              A 5ms period is executed between the display of each digit, causing
 *              the digits to appear to be displayed simultaneously.
 *
 * Note: The 5ms delay has been chosen to reduce afterglow, but the value may vary
 *       depending on the hardware used.
 */
ISR(TIMER0_COMPA_vect)
{
    ms++;
    
    if (ms == 5)
    {
        digit = d1;
        DigitValue = hTensDigit;
    }

    else if (ms == 10)
    {
        digit = d2;
        DigitValue = hOnesDigit;
    }

    else if (ms == 15)
    {
        digit = d3;
        DigitValue = mTensDigit;
    }

    else if (ms == 20)
    {
        digit = d4;
        DigitValue = mOnesDigit;
        ms = 0;
    }
}

/*
 * Timer/Counter1 Compare Match A Interrupt Service Routine (ISR)
 * Description: Executes every 1s to compute the clock time. Every 60s, the minute
 *              value changes, and every 60 minutes, the hour value changes. During
 *              the execution of this ISR, the 'second blinking' phenomenon is 
 *              executed by blinking the decimal point.
 */
ISR(TIMER1_COMPA_vect)
{
    s++;

    if (s == 60) 
    {
        M++;

        if(M == 60)
        {
            M = 0;
            H++;

            if (H == 24)
            {
                H = 0;
            } 
            
            hTensDigit = H / 10;
            hOnesDigit = H % 10;
        }
        
        mTensDigit = M / 10;
        mOnesDigit = M % 10;

        s = 0;
   }
    
   toggle_pin_state(dp);
}

void main()
{
    /* Initialization of clock time variables */
    hTensDigit = H / 10;
    hOnesDigit = H % 10;
    mTensDigit = M / 10;
    mOnesDigit = M % 10;

    /* Digit initialization */
    digit = d1;

    /* Digit value initialization */
    DigitValue = hTensDigit;

    /* Display Pins direction declaration */
    segement_dir(seg_arr);
    dp_dir(dp);
    digit_dir(d_arr);

    /* Timers Initialization */
    set_ctc0(250);    //1ms takes 250 cycles for a CPU freq of 16Mhz and a prescaler of 64
    set_ctc1(15625);  //1s takes 15625 cycles for a CPU freq of 16Mhz and a prescaler of 1024
    timer0_init();
    timer1_init();

    /* Enable global interrupts */
    sei();

    /* Infinite loop to display the Clock time values */
    while(1)
    {   
        display_number(seg_arr, d_arr, digit, DigitValue); 
    }  
}

