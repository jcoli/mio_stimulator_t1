/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F401 - Mio Stimulation
**/

#ifndef __DIG_INPUT_H__
#define __DIG_INPUT_H__ 

void dig_input_begin();
void check_button(int btn, int dur);
void wakeUP_fun();

#endif