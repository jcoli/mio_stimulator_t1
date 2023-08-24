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
#include "communication.h"

extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;

extern bool test;

extern int tim_alive;
extern int tim_conn;
extern int tim_sleep;


void pulse_init(){
    
}