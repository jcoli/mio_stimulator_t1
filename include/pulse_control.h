/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/

#ifndef __PULSE_CONTROL_H__
#define __PULSE_CONTROL_H__ 

void pulse_init();
void pulse_control();
void pulse_block();
void stepUp_init();
void stepUp_control();
void stepUp_block();
void pulse_control_dev();
void pulse_init_dev();
void channel_intensity();
void enable_channel();


#endif
