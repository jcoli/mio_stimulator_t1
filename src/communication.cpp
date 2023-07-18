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

void bt_init();
void bt_at_command(String at_comm);
void on_serial();
void on_BT_comm();


extern bool bt_enabled;
extern bool bt_connected;

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

void bt_init(){
    Serial.println("bt_init");
    String msg = "";
    Serial2.print("AT");
    


    msg = "";
}

void bt_at_command(String at_comm){
    Serial.println(at_comm);
    Serial2.print(at_comm);

}

void on_serial(){ 
    Serial.print(line);
    stringComplete = false;
    line1 = "";

}


void on_BT_comm(){
    if (line2 == "OK"){
        bt_enabled = true;
    }
    string2Complete = false;
    // Serial.println(line2);
    split_msg_3(line2);
    Serial.println("split: "+ retMsg3[0] + " - " +retMsg3[1] + " - " + retMsg3[2]);
    if (retMsg3[0].equals("pp")){
        Serial.println("pp");
        
    }
    if (retMsg3[0].equals("sw")){
        Serial.println("sw");
        
    }
    line2="";
    retMsg3[0] = "";
    retMsg3[1] = "";
    retMsg3[2] = "";

}