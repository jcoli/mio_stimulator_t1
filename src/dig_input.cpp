/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F401 - Mio Stimulation
**/

#include <Arduino.h>
#include <Bounce2.h>
#include <STM32LowPower.h>

#include "control.h"
#include "defines.h"
#include "io_defines.h"
#include "tools.h"

void dig_input_begin();
void check_button(int btn, int dur);
void wakeUP_fun();

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

void dig_input_begin() { pinMode(BT_POWER, INPUT_PULLUP); }

void check_button(int btn, int dur) {
  Serial.println("btn");
  digitalWrite(ESP_WKP, LOW);
  
  delay(200);
  LowPower.shutdown();
}

void wakeUP_fun() {
  Serial.println("sleep 3");
  tim_sleep = 0;
//   detachInterrupt(BT_POWER);
  digitalWrite(ESP_WKP, HIGH);
}
