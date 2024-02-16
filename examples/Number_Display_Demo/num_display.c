#include "5461AS.h"
#include "dio.h"
#include "DataTypes.h"
#include "BitConfig.h"
#include <util/delay.h>


#define num_display  1000


void main()
{
    PinConfig seg_a =  {PD3, Reg_D, Reg_D};
    PinConfig seg_b =  {PD4, Reg_D, Reg_D};
    PinConfig seg_c =  {PD7, Reg_D, Reg_D};
    PinConfig seg_d =  {PB0, Reg_B, Reg_B};
    PinConfig seg_e =  {PB1, Reg_B, Reg_B};
    PinConfig seg_f =  {PD2, Reg_D, Reg_D};
    PinConfig seg_g =  {PD6, Reg_D, Reg_D};
    
    PinConfig d_1 = {PB5, Reg_B, Reg_B};
    PinConfig d_2 = {PB4, Reg_B, Reg_B};
    PinConfig d_3 = {PB2, Reg_B, Reg_B};
    PinConfig d_4 = {PB3, Reg_B, Reg_B};

    PinConfig seg_arr[segments] = {seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g};
    PinConfig d_arr[digits] = {d_1, d_2, d_3, d_4};


    segement_dir(seg_arr);
    digit_dir(d_arr);

    Unt16 ones, tens, hundreds, thousands; 

    for(int i = 0; i <= num_display; i++)
    {   
        digit_init(d_arr);
        display_number(seg_arr, d_arr, d1, i); 
        _delay_ms(1); 

        if (i >= 10 && i <= 99)
        {
            ones = i%10;
            tens = ((i%100)- i%10)/10;

            digit_init(d_arr);
            display_number(seg_arr, d_arr, d1, ones); 
            _delay_ms(1); 

            digit_init(d_arr);
            display_number(seg_arr, d_arr, d2, tens); 
            _delay_ms(1); 

        }

        else if (i >= 100 && i<= 999)
        {
            ones = i%10;
            tens = ((i%100)- i%10)/10;
            hundreds = ((i%1000)-(i%100))/100;
            
            digit_init(d_arr);
            display_number(seg_arr, d_arr, d1, ones); 
            _delay_ms(1); 

            digit_init(d_arr);
            display_number(seg_arr, d_arr, d2, tens); 
            _delay_ms(1);

            digit_init(d_arr);
            display_number(seg_arr, d_arr, d3, hundreds); 
            _delay_ms(1); 
        }

        else 
        {
            ones = i%10;
            tens = ((i%100)- i%10)/10;
            hundreds = ((i%1000)-(i%100))/100;
            thousands = ((i%10000)-(i%1000))/1000;
            
            digit_init(d_arr);
            display_number(seg_arr, d_arr, d1, ones); 
            _delay_ms(1); 

            digit_init(d_arr);
            display_number(seg_arr, d_arr, d2, tens); 
            _delay_ms(1);

            digit_init(d_arr);
            display_number(seg_arr, d_arr, d3, hundreds); 
            _delay_ms(1); 

            digit_init(d_arr);
            display_number(seg_arr, d_arr, d4, thousands); 
            _delay_ms(1); 

        }      
    }
}

