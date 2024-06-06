/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F401 - Mio Stimulation
**/

#include <Arduino.h>

#include "control.h"
#include "defines.h"
#include "io_defines.h"
#include "tools.h"
#include "analog_output.h"

void ana_input_begin();
void read_analog();


extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;

extern int tim_alive;
extern int tim_conn;
extern int tim_sleep;

extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5];

extern int32_t VRef;
extern float batLevel;
extern float batCel1Level;
extern float batCel2Level;
extern float voltOutLevel;

void ana_input_begin(){
    analogReadResolution(12);
    read_analog();

}

void read_analog(){
    float cel1 = analogRead(BAT_CEL1);
    float cel2 = analogRead(BAT_CEL2);
    float volt_out = analogRead(VOLT_OUT);
    batCel2Level = (map(cel2, 0, 4095, 0, 6000));    
   
    voltOutLevel = (map(volt_out, 0, 4095, 0, 11000));   
    batCel1Level = voltOutLevel-batCel2Level; 
    batLevel = batCel1Level+batCel2Level;
    batLevel = batLevel/1000;
    batCel1Level = batCel1Level/1000;
    batCel2Level = batCel2Level/1000;
    Serial.print("BatLevel ");
    Serial.print(batLevel);
    Serial.print(" - ");
    Serial.print(cel1);
    Serial.print(" - ");
    Serial.print(batCel1Level);
    Serial.print(" - ");
    Serial.print(cel2);
    Serial.print(" - ");
    Serial.print(batCel2Level);
    Serial.print(" - ");
    Serial.println(voltOutLevel);
}