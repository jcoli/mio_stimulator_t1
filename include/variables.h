/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
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

const byte pot0            = 0x11;    // pot0 addr
const byte pot1            = 0x12;    // pot1 addr
const byte potBoth         = 0x13;    // pot0 and pot1 simultaneous addr
const byte pot0Shutdown    = 0x21;    // pot0 shutdown
const byte pot1Shutdown    = 0x22;    // pot1 shutdown
const byte potBothShutdown = 0x23;    // pot0 and pot1 simultaneous shutdown

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
float voltOutLevel;

volatile int repetitions = 1;

//Channels
bool active_ch[8];
bool detect_ch[8];
int intensity_ch[8];

int global_int = 0;

//trainning
String id_training;
int tr_freq[4];
int timeActive;
int timePause;
int timeTraining;
int typeCurve;


#endif