/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F401 - Mio Stimulation
**/

#ifndef __IO_DEFINES_H__
#define __IO_DEFINES_H__

// Dig Input
#define BT_POWER PA0 // WakeUp

// Dig Output
#define STATUS_LED PC13
#define RUN_LED PC14
#define BAT_LED PC15 
// #define BUZZER_PIN  PB15
#define ESP_WKP PA1

// Pulses
#define PULSE_0 PB0 
#define PULSE_1 PB1
#define PULSE_2 PB2
#define PULSE_3 PB3
#define PULSE_4 PB4
#define PULSE_5 PB5
#define PULSE_6 PB6
#define PULSE_7 PB7
// PWM
// #define PWM_STUP PA1
#define MISO PB14
#define MOSI PB15
#define SCK PB13 
#define CS PA9

// Ana Input
#define BAT_CEL1 PA12
#define BAT_CEL2 PA13
#define VOLT_OUT PA14

#endif
