/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/
#ifndef __VARIABLES_H__
#define __VARIABLES_H__
#include <Arduino.h>

static int32_t readVref();
static int32_t readTempSensor(int32_t VRef);

unsigned long loopDelay_on = millis();
unsigned long loopDelay_int_temp = millis();
unsigned long loopDelay_bit_alive = millis();
unsigned long loopDelay_count_alive = millis();

bool bt_enabled = false;
bool bt_connected = false;
bool bt_alive = false;
bool first_loop = true;
bool run_enabled = false;

bool test = true;

int tim_alive = 0;
int tim_conn = 0;
int tim_sleep = 0;

String line = "";
String line1 = "";
String line2 = "";
bool stringComplete = false;
bool string1Complete = false;
bool string2Complete = false;

int32_t VRef;
float intTemp;
float batLevel;
float batCel1Level;
float batCel2Level;

volatile int repetitions = 1;


#endif