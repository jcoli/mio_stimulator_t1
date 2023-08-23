/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/

#include <Arduino.h>

#include "defines.h"
#include "io_defines.h"
#include "tools.h"
#include "control.h"

void dig_output_begin();

extern bool bt_enabled;
extern bool bt_connected;

void dig_output_begin(){
    pinMode(STATUS_LED, OUTPUT);
    pinMode(RUN_LED, OUTPUT);
    pinMode(BAT_LED, OUTPUT);
    pinMode(ESP_WKP, OUTPUT);
    pinMode(PULSE_0, OUTPUT);
    pinMode(PULSE_1, OUTPUT);
    pinMode(PULSE_2, OUTPUT);
    pinMode(PULSE_3, OUTPUT);
    pinMode(PULSE_4, OUTPUT);
    pinMode(PULSE_5, OUTPUT);
    pinMode(PULSE_6, OUTPUT);
    pinMode(PULSE_7, OUTPUT);
    digitalWrite(ESP_WKP,HIGH);
    GPIOB->OSPEEDR = 0x03;
    // GPIOB->MODER = 0x5555;
    

}