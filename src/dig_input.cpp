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

void dig_input_begin();

extern bool bt_enabled;
extern bool bt_connected;

void dig_input_begin(){
    pinMode(BT_POWER, INPUT_PULLUP);
}

