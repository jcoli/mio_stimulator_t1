/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/

#include <Arduino.h>

#include "control.h"
#include "defines.h"
#include "io_defines.h"
#include "tools.h"

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

void ana_input_begin(){
    analogReadResolution(12);
    read_analog();

}

void read_analog(){
    float cel1 = analogRead(BAT_CEL1);
    float cel2 = analogRead(BAT_CEL2);
    batCel1Level = (map(cel1, 0, 4095, 0, 5000));    
    batCel2Level = (map(cel2, 0, 4095, 0, 5000));    
    batLevel = batCel1Level+batCel2Level;
    Serial.print("BatLevel ");
    Serial.print(batLevel);
    Serial.print(" - ");
    Serial.print(cel1);
    Serial.print(" - ");
    Serial.print(batCel1Level);
    Serial.print(" - ");
    Serial.print(cel2);
    Serial.print(" - ");
    Serial.println(batCel2Level);
}