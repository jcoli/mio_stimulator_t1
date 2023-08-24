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

//Channel 0
bool active_ch0 = false;
bool detect_ch0 = false;
int intensity_ch0 = 0;

//Channel 1
bool active_ch1 = false;
bool detect_ch1 = false;
int intensity_ch1 = 0;

//Channel 2
bool active_ch2 = false;
bool detect_ch2 = false;
int intensity_ch2 = 0;

//Channel 3
bool active_ch3 = false;
bool detect_ch3 = false;
int intensity_ch3 = 0;

//Channel 4
bool active_ch4 = false;
bool detect_ch4 = false;
int intensity_ch4 = 0;

//Channel 5
bool active_ch5 = false;
bool detect_ch5 = false;
int intensity_ch5 = 0;

//Channel 6
bool active_ch6 = false;
bool detect_ch6 = false;
int intensity_ch6 = 0;

//Channel 7
bool active_ch7 = false;
bool detect_ch7 = false;
int intensity_ch7 = 0;



#endif