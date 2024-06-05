/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
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
    
    digitalWrite(ESP_WKP,HIGH);
    
    // GPIOB->MODER = 0x5555;
    

}