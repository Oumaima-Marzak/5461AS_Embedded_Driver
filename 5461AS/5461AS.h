/*
*   Author : Oumaima MARZAK
*
*
*/

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

/*

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


*/


#ifndef _5461AS_H
#define _5461AS_H 

#include "DataTypes.h"

typedef enum 
{
    _OK,
    _INVALID_PARAM

} ErrorStatus;


#define numbers    10  /* 0 to 9 */
#define caracters   4  /* A, C, E and F */ 

#define segments    7  /* a, b, c, d, e, f and g */
#define digits      4  /* d1, d2, d3 and d4 */
#define dpx         4  /* dp1, dp2, dp3 and dp4 */

#define a           0   
#define b           1
#define c           2
#define d           3
#define e           4
#define f           5
#define g           6

#define d1          0
#define d2          1
#define d3          2
#define d4          3

#define dp1         0
#define dp2         1
#define dp3         2
#define dp4         3


/* Numbers from 0 to 9 */
#define NumbersOnBinary {{1,1,1,1,1,1,0}, {0,1,1,0,0,0,0}, {1,1,0,1,1,0,1}, {1,1,1,1,0,0,1}, {0,1,1,0,0,1,1}, {1,0,1,1,0,1,1}, {1,0,1,1,1,1,1}, {1,1,1,0,0,0,0}, {1,1,1,1,1,1,1}, {1,1,1,1,0,1,1}}

/* Caracters A,C,E and F */
#define CaractersOnBinary {{1,1,1,0,1,1,1}, {1,0,0,1,1,1,0}, {1,0,0,1,1,1,1}, {1,0,0,0,1,1,1}}

void digit_init(PinConfig d_arr[digits]);

void segement_dir(PinConfig seg_arr[segments]);
void digit_dir(PinConfig d_arr[digits]);
void dp_dir(PinConfig dp_arr[dpx]);


void segement_state(PinConfig SEG, Uch8 STATE);
void digit_state(PinConfig DIG);
void dp_state(PinConfig dp, Uch8 STATE);


ErrorStatus display_number(PinConfig seg_arr[segments], PinConfig d_arr[digits], Uch8 digit,Uch8 number);
ErrorStatus display_caracter(PinConfig seg_arr[segments], PinConfig d_arr[digits], Uch8 digit, Uch8 caracter);


#endif