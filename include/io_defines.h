/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/

#ifndef __IO_DEFINES_H__
#define __IO_DEFINES_H__

//Dig Input
#define BT_POWER    PA0 //WakeUp


//Dig Output
#define STATUS_LED  PC13
#define RUN_LED     PC14
#define BAT_LED     PC15
// #define BUZZER_PIN  PB15
#define ESP_WKP     PA8

//Pulses
#define PULSE_0     PB0
#define PULSE_1     PB1
#define PULSE_2     PB2
#define PULSE_3     PB3
#define PULSE_4     PB4
#define PULSE_5     PB5
#define PULSE_6     PB6
#define PULSE_7     PB7


//Ana Input
#define BAT_CEL1    PA6
#define BAT_CEL2    PA7


#endif
