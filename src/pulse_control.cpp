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


extern bool active_ch[8];
extern bool detect_ch[8];
extern int intensity_ch[8];


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
    
    for (int i = 0; i<8; i++ ){
        active_ch[i] = true;
        detect_ch[i] = true;
        intensity_ch[i] = 15;
    }

}

void pulse_control(){
    
}

void pulse_control_dev(){

    int ch[8] = {0,0,0,0,0,0,0,0};

    for (int i = 0; i<25; i++){
        for (int ind_ch = 0; ind_ch<8; ind_ch++){
            if (ch[ind_ch]<intensity_ch[ind_ch] && active_ch[ind_ch] && detect_ch[ind_ch]) GPIOB->BSRR = (1 << ind_ch); 
        }
        delayMicroseconds(12);
        for (int ind_ch = 0; ind_ch<8; ind_ch++){   
            if (ch[ind_ch]<=intensity_ch[ind_ch] && active_ch[ind_ch] && detect_ch[ind_ch]) GPIOB->BSRR = ((1 << ind_ch) << 16);
           
        }
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

