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

void ana_input_begin(){
    analogReadResolution(12);
    read_analog();

}

void read_analog(){
    float bat = analogRead(BAT_VOLT);
    batLevel = (map(bat, 0, 4095, 0, 10300));    
    Serial.print("BatLevel ");
    Serial.print(batLevel);
    Serial.print(" - ");
    Serial.println(bat);
}