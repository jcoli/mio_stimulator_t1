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

void pulse_init();
void pulse_control();
void pulse_block();
void stepUp_init();
void stepUp_control();
void stepUp_block();

extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;
extern bool test;
extern int tim_alive;
extern int tim_conn;
extern int tim_sleep;

//Channel 0
extern bool active_ch0;
extern bool detect_ch0;
extern int intensity_ch0;
//Channel 1
extern bool active_ch1;
extern bool detect_ch1;
extern int intensity_ch1;
//Channel 2
extern bool active_ch2;
extern bool detect_ch2;
extern int intensity_ch2;
//Channel 3
extern bool active_ch3;
extern bool detect_ch3;
extern int intensity_ch3;
//Channel 4
extern bool active_ch4;
extern bool detect_ch4;
extern int intensity_ch4;
//Channel 5
extern bool active_ch5;
extern bool detect_ch5;
extern int intensity_ch5;
//Channel 6
extern bool active_ch6;
extern bool detect_ch6;
extern int intensity_ch6;
//Channel 7
extern bool active_ch7;
extern bool detect_ch7;
extern int intensity_ch7;



void pulse_init(){
    
}

void pulse_control(){
    
}

void pulse_block(){
    
}

void stepUp_init(){
    
}

void stepUp_control(){
    
}

void stepUp_block(){
    
}

