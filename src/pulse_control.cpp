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
#include "communication.h"

void pulse_init();
void pulse_control();
void pulse_block();
void stepUp_init();
void stepUp_control();
void stepUp_block();
void pulse_control_dev();
void pulse_init_dev();
void channel_intensity();
void enable_channel();

extern bool bt_enabled;
extern bool bt_connected;
extern bool run_enabled;
extern bool bt_alive;
extern bool test;
extern int tim_alive;
extern int tim_conn;
extern int tim_sleep;

extern bool active_ch[8];
extern bool detect_ch[8];
extern int intensity_ch[8];

extern String retMsg4[4];

extern int global_int; 


void pulse_init(){
    pinMode(PULSE_0, OUTPUT);
    pinMode(PULSE_1, OUTPUT);
    pinMode(PULSE_2, OUTPUT);
    pinMode(PULSE_3, OUTPUT);
    pinMode(PULSE_4, OUTPUT);
    pinMode(PULSE_5, OUTPUT);
    pinMode(PULSE_6, OUTPUT);
    pinMode(PULSE_7, OUTPUT);

    // pinMode(PWM_STUP, OUTPUT);
    

    GPIOB->OSPEEDR = 0x03;
    pulse_init_dev();
}

void pulse_init_dev(){
    for (int i = 0; i<8; i++ ){
        active_ch[i] = true;
        detect_ch[i] = true;
        intensity_ch[i] = 1;
    }
}

void pulse_control(){
}

void enable_channel(){
    if (retMsg4[0].equals("7")) {
        int mChannel = retMsg4[2].toInt();
        if (retMsg4[3] == "1"){
            active_ch[mChannel] = true;
        }else{
            active_ch[mChannel] = false;    
        }    
    }
}

void channel_intensity(){
    
    if (retMsg4[0].equals("8")) {
        int mChannel = retMsg4[2].toInt();
        intensity_ch[mChannel] = retMsg4[3].toInt();
        // Serial.print("Intensity: ");
        // Serial.print(retMsg4[3]);
        // Serial.print(", - ");
        // Serial.println(retMsg4[2]);
    }
    for (int i = 0; i<8; i++){
        if (intensity_ch[i] > global_int){
            global_int = intensity_ch[i];
            // Serial.print("Global Intensity: ");
            // Serial.println(global_int);
        }
    }
}

void pulse_control_dev(){

    if (bt_connected && run_enabled){
        // Serial.print("R");

        int ch[8] = {0,0,0,0,0,0,0,0};

        for (int i = 0; i<25; i++){
            for (int ind_ch = 0; ind_ch<8; ind_ch++){
                if (ch[ind_ch]<intensity_ch[ind_ch] && active_ch[ind_ch] && detect_ch[ind_ch]) GPIOB->BSRR = (1 << ind_ch); 
            }
            // Serial.print("R");
            delayMicroseconds(500);
            for (int ind_ch = 0; ind_ch<8; ind_ch++){   
                if (ch[ind_ch]<=intensity_ch[ind_ch] && active_ch[ind_ch] && detect_ch[ind_ch]) GPIOB->BSRR = ((1 << ind_ch) << 16);
            
            }
            // Serial.print("R1");
            delayMicroseconds(550);
            for (int x = 0; x<8; x++) {
                    ch[x]++;
            }
            // Serial.print("R2");
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

