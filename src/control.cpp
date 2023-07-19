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

void on_receive(int mSize);
void on_bit_alive();
void decoder_one();
void decoder_two();
void decoder_three();
void decoder_four();
void decoder_five();

extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;

extern int tim_alive;

extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5]; 

extern HardwareTimer *Tim1;

void on_bit_alive(){
    if (!bt_alive){
        Tim1->setOverflow(20, HERTZ_FORMAT);
        bt_enabled = false;
        bt_alive = false;
        tim_alive = 0;
        Serial.println("on_bit_alive");
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
    Serial.println("decoder_four a");
    Serial.println("split: "+ retMsg4[0] + " - " +retMsg4[1] + " - " + retMsg4[2] + " - " + retMsg4[3]);
    if (retMsg4[0].equals("re") && (retMsg4[3].equals("1"))){
        Tim1->setOverflow(10, HERTZ_FORMAT);
        bt_enabled = true;
        bt_alive = true;
        tim_alive = 0;
        Serial.println("decoder_four - 1");
    }else{
        Serial.println("decoder_four - 3");
    }
    // else if (retMsg4[0].equals("re") && (retMsg4[3].equals("0"))){
    //     Tim1->setOverflow(20, HERTZ_FORMAT);
    //     bt_enabled = false;
    //     bt_alive = false;
    //     Serial.println("decoder_four - 2");
    // }
}

void decoder_five(){
    Serial.println("decoder_five");

}

