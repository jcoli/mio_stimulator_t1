/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/
#ifndef __VARIABLES_H__
#define __VARIABLES_H__
#include <Arduino.h>

unsigned long loopDelay = millis();
unsigned long loopDelayInput = millis();
unsigned long loopDelayTFT = millis();
unsigned long loopDelayPot = millis();

bool string1Complete = false;
bool string2Complete = false;
bool string3Complete = false;
bool serial_event = false;
String line         = "";
String line1         = "";
String line2         = "";

uint16_t port_dig_in_ext;
uint16_t port_dig_out_ext;
uint16_t port_inj_ext;
uint16_t port_coil_ext;

bool out_bat = true;
bool out_l15 = true;
bool out_l30 = true;


#endif