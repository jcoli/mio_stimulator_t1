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
void pulse_control_dev();
void pulse_init_dev();

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
    pinMode(PULSE_0, OUTPUT);
    pinMode(PULSE_1, OUTPUT);
    pinMode(PULSE_2, OUTPUT);
    pinMode(PULSE_3, OUTPUT);
    pinMode(PULSE_4, OUTPUT);
    pinMode(PULSE_5, OUTPUT);
    pinMode(PULSE_6, OUTPUT);
    pinMode(PULSE_7, OUTPUT);
    GPIOB->OSPEEDR = 0x03;
    pulse_init_dev();
    
    
}

void pulse_init_dev(){
    active_ch0 = true;
    detect_ch0 = true;
    intensity_ch0 = 25;

    active_ch1 = true;
    detect_ch1 = true;
    intensity_ch1 = 25;

    active_ch2 = true;
    detect_ch2 = true;
    intensity_ch2 = 25;

    active_ch3 = true;
    detect_ch3 = true;
    intensity_ch3 = 10;

    active_ch4 = true;
    detect_ch4 = true;
    intensity_ch4 = 25;

    active_ch5 = true;
    detect_ch5 = true;
    intensity_ch5 = 25;

    active_ch6 = true;
    detect_ch6 = true;
    intensity_ch6 = 25;

    active_ch7 = true;
    detect_ch7 = true;
    intensity_ch7 = 25;

}

void pulse_control(){
    
}

void pulse_control_dev(){

    int ch[8] = {0,0,0,0,0,0,0,0};

    for (int i = 0; i<25; i++){
        if (ch[0]<intensity_ch0) GPIOB->BSRR = (1 << 0);
        if (ch[1]<intensity_ch1) GPIOB->BSRR = (1 << 1);
        if (ch[2]<intensity_ch2) GPIOB->BSRR = (1 << 2);
        if (ch[3]<intensity_ch3) GPIOB->BSRR = (1 << 3);
        if (ch[4]<intensity_ch4) GPIOB->BSRR = (1 << 4);
        if (ch[5]<intensity_ch5) GPIOB->BSRR = (1 << 5);
        if (ch[6]<intensity_ch6) GPIOB->BSRR = (1 << 6);
        if (ch[7]<intensity_ch7) GPIOB->BSRR = (1 << 7);
        delayMicroseconds(12);
        if (ch[0]<=intensity_ch0) GPIOB->BSRR = ((1 << 0) << 16);
        if (ch[1]<=intensity_ch1) GPIOB->BSRR = ((1 << 1) << 16);
        if (ch[2]<=intensity_ch2) GPIOB->BSRR = ((1 << 2) << 16);
        if (ch[3]<=intensity_ch3) GPIOB->BSRR = ((1 << 3) << 16);
        if (ch[4]<=intensity_ch4) GPIOB->BSRR = ((1 << 4) << 16);
        if (ch[5]<=intensity_ch5) GPIOB->BSRR = ((1 << 5) << 16);
        if (ch[6]<=intensity_ch6) GPIOB->BSRR = ((1 << 6) << 16);
        if (ch[7]<=intensity_ch7) GPIOB->BSRR = ((1 << 7) << 16);
        delayMicroseconds(12);
        for (int x = 0; x<8; x++) {
            ch[x]++;
        }
    }
    
}



void pulse_block(){
    
}

void stepUp_init(){
    
}

void stepUp_control(){
    
}

void stepUp_block(){
    
}

