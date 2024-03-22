#include "BitConfig.h"
#include "DataTypes.h"
#include "dio.h"
#include "adc.h"
#include "5461AS.h"
#include "util/delay.h"


void main()
{
    Unt16 adc_value;
    Uch8 ones, tens, hundreds, thousands; 

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

    adc_ref_config(ADC_REF_AVCC);
    adc_prescaler_config(ADC_PRESCALER_128);
    adc_init();

    while(1)
    {
        adc_value = adc_read(0);

        ones = adc_value % 10;
        tens = (adc_value / 10) % 10;
        hundreds = (adc_value / 100) % 10;
        thousands = (adc_value / 1000) % 10;

        // Display the digits based on the number value
        display_number(seg_arr, d_arr, d4, ones);
        _delay_ms(5); 

        if (adc_value >= 10)
        {
            display_number(seg_arr, d_arr, d3, tens);
            _delay_ms(5); 
        }

        if (adc_value >= 100)
        {
            display_number(seg_arr, d_arr, d2, hundreds);
            _delay_ms(5); 
        }

        if (adc_value >= 1000)
        {
            display_number(seg_arr, d_arr, d1, thousands);
            _delay_ms(5); 
        }        
    }    
}