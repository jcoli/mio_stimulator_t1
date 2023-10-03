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
#include "pulse_control.h"

void on_receive(int mSize);
void on_bit_alive();
void on_bit_connected();
void decoder_one();
void decoder_two();
void decoder_three();
void decoder_four();
void decoder_five();
void pulse_output();

extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;
extern bool run_enabled;

extern bool test;

extern int tim_alive;
extern int tim_conn;
extern int tim_sleep;

extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5]; 

// extern HardwareTimer *Tim1;
extern HardwareTimer *tim3;

void pulse_output(){
    
    
}


void on_bit_alive(){
    if (!bt_alive){
        tim3->setOverflow(20, HERTZ_FORMAT);
        bt_enabled = false;
        bt_alive = true;
        tim_alive = 0;
        Serial.println("on_bit_alive");
    }
}

void on_bit_connected(){
    if (!bt_connected){
        tim3->setOverflow(10, HERTZ_FORMAT);
        tim_conn = 0;
        bt_connected = true;
        Serial2.print("0,0,0,1,#");
        Serial.println("on_bit_conn");
    }
}


void on_receive(int mSize){
    switch (mSize) {
        case 0:
          Serial.println("0");
          break;
        case 1:
          Serial.println("1");
          break;
        case 2:
          Serial.println("2");
          break;
        case 3:
          Serial.println("3");
          break;
        case 4:
          Serial.println("4");
          break;
        case 5:
          Serial.println("5");
          break;  
    }      
}

void decoder_one(){
    Serial.println("decoder_one");
}

void decoder_two(){
    Serial.println("decoder_two");

}

void decoder_three(){
    Serial.println("decoder_three");

}

void decoder_four(){
    // Serial.println("decoder_four a");
    // Serial.println("split: "+ retMsg4[0] + " - " +retMsg4[1] + " - " + retMsg4[2] + " - " + retMsg4[3]);
    if ((retMsg4[0].equals("1") && (retMsg4[3].equals("1"))) && (!bt_connected)){   //re
        tim3->setOverflow(10, HERTZ_FORMAT);
        bt_enabled = true;
        bt_alive = true;
        tim_alive = 0;
        // Serial.println("decoder_four - 1");
    }
    if (retMsg4[0].equals("0")){ //connect - bit alive
        if(retMsg4[3].equals("1")){
            tim3->setOverflow(1, HERTZ_FORMAT);
            bt_connected = true;
            tim_conn = 0;
            tim_sleep = 0;
            Serial2.print("0,0,0,1,#");
        }
        if(retMsg4[3].equals("0")){
            tim3->setOverflow(10, HERTZ_FORMAT);
            bt_connected = false;
            tim_conn = 0;
            Serial.println("disconnected");
        } 
    }
    if (retMsg4[0].equals("7")){ //ch enabled
        enable_channel();
        
    }
    if (retMsg4[0].equals("8")){ //decrease & increase
        channel_intensity();
    }    
    
    if (retMsg4[0].equals("3")){   //run
        if(retMsg4[3].equals("1")){
            // Serial2.println("3,0,0,1,#");
            Serial.println("run");
            run_enabled = true;
        }
        if(retMsg4[3].equals("0")){
            // Serial2.println("3,0,0,0,#");
            Serial.println("not run");
            run_enabled = false;
        } 
    }
}

void decoder_five(){
    Serial.println("decoder_five");

}

