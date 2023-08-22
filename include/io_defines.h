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
#define ESP_WKP     PA1

//Pulses
// #define PULSE_0     PA15
// #define PULSE_1     PB13
// #define PULSE_2     PB14
// #define PULSE_3     PB15
// #define PULSE_4     PA8
// #define PULSE_5     PA9
// #define PULSE_6     PA10
// #define PULSE_7     PA11


//Ana Input
#define BAT_CEL1    PB0
#define BAT_CEL2    PB1


#endif
