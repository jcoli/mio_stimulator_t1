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

void bt_init();
void bt_at_command(String at_comm);
void on_serial();
void on_BT_comm();
void sendMsgTimer();
void sendMsg(String s);

extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;

extern String line;
extern String line1;
extern String line2;
extern bool stringComplete;
extern bool string1Complete;
extern bool string2Complete;

extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5]; 

extern int32_t VRef;
extern float intTemp;
extern float batLevel;
extern float batCel1Level;
extern float batCel2Level;

void bt_init(){
    // Serial.println("bt_init");
    String msg = "";
    Serial2.print("AT");
    msg = "";
}

void bt_at_command(String at_comm){
    // Serial.println(at_comm);
    Serial2.print(at_comm);
}

void on_serial(){ 
    // Serial.print(line);
    stringComplete = false;
    line1 = "";
}

void on_BT_comm(){
    if (line2 == "OK"){
        bt_enabled = true;
    }else{
        // Serial.println(line2);
        split_msg_4(line2);
        // Serial.println("split: "+ retMsg4[0] + " - " +retMsg4[1] + " - " + retMsg4[2] + " - " + retMsg4[3]);
        decoder_four();
        string2Complete = false;
        line2="";
        retMsg4[0] = "";
        retMsg4[1] = "";
        retMsg4[2] = "";
        retMsg4[3] = "";
    }
    
    
}

void sendMsgTimer(){
    Serial2.print("te,0,0," + String(intTemp) + ",#");
    // Serial.print("send: ");
    delay(50);
    Serial2.print("ba,0,0," + String(batLevel) + ",#");
    Serial2.print("c1,0,0," + String(batCel1Level) + ",#");
    Serial2.print("c2,0,0," + String(batCel2Level) + ",#");
}

void sendMsg(String s){
    Serial2.print(s+",#");
}