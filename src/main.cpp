/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/

#include <Arduino.h>
#include <STM32LowPower.h>

#include "defines.h"
#include "io_defines.h"
#include "tools.h"
#include "communication.h"
#include "control.h"
#include "dig_input.h"
#include "dig_output.h"

#define CALX_TEMP 25
#define V25       760
#define AVG_SLOPE 2500
#define VREFINT   1210

#define LL_ADC_RESOLUTION LL_ADC_RESOLUTION_12B
#define ADC_RANGE 4096

#define BT_POWER pinNametoDigitalPin(SYS_WKUP1)

HardwareSerial Serial2(PA3, PA2);

static int32_t readVref();
static int32_t readTempSensor(int32_t VRef);

void serialEvent();
// void serialEvent3();
void serialEvent2();
void serialEventRun(void);
void Update_IT_callback(void);
void wakeUP_fun();

void serialEventRun(void)
{
  // #if defined(HAVE_HWSERIAL2)
    if (serialEvent2 && Serial2.available()) {
      serialEvent2();
     
    }
  // #endif
  // #if defined(USBCON)
    if (serialEvent && Serial.available()) {
      serialEvent();
    }
  // #endif
  // // #if defined(HAVE_HWSERIAL3)  
    // if (serialEvent3 && Serial3.available()) {
    //   serialEvent3();
    // }
  // #endif
}

unsigned long loopDelay_on = millis();
unsigned long loopDelay_int_temp = millis();
unsigned long loopDelay_bit_alive = millis();
unsigned long loopDelay_count_alive = millis();

bool bt_enabled = false;
bool bt_connected = false;
bool bt_alive = false;
bool intLed = true;

int tim_alive = 0;
int tim_conn = 0;
int tim_sleep = 0;

String line         = "";
String line1         = "";
String line2         = "";
bool stringComplete = false;
bool string1Complete = false;
bool string2Complete = false;

int32_t VRef;
float intTemp;

volatile int repetitions = 1;

#if defined(TIM1)
    TIM_TypeDef *Instance1 = TIM1;
#else
    TIM_TypeDef *Instance = TIM2;
#endif
  
HardwareTimer *Tim1 = new HardwareTimer(Instance1);

void setup() {
  Serial.begin(115200);
  Serial1.begin(19200);
  Serial2.begin(19200); 
  analogReadResolution(12);
  delay(1000);
  dig_output_begin();
  dig_input_begin();

  LowPower.begin();
  LowPower.attachInterruptWakeup(BT_POWER, wakeUP_fun, FALLING, SHUTDOWN_MODE);

  Tim1->setOverflow(20, HERTZ_FORMAT); // 10 Hz
  Tim1->attachInterrupt(Update_IT_callback);
  Tim1->resume();

}

void loop() {
  
  if (millis() - loopDelay_on > 20000){
    loopDelay_on = millis();
    // Serial.println("button1");
    // Serial2.print("AT+NAME=TEC2");
    // Serial2.print("teste#");
  } 

  if (millis() - loopDelay_int_temp > 20000){
    loopDelay_int_temp = millis();
    VRef = readVref();
    intTemp = readTempSensor(VRef);
    Serial.print("VRef: ");
    Serial.println(VRef);
    VRef = map(VRef, 0, 4095, 0, 500);
    Serial.println(VRef,DEC);
    Serial.print("Temp: ");
    Serial.println(intTemp);
    Serial2.print("temp,0,"+String(intTemp)+",#");
  }

  if (millis() - loopDelay_bit_alive > 2000){
    loopDelay_bit_alive = millis();
    Serial.print("sleep: ");
    Serial.println(tim_sleep);
    if ((tim_alive>=100) && !(bt_connected)){
       bt_alive = false; 
       on_bit_alive();
    }
    if ((tim_conn>=100) && (bt_connected)){
       bt_connected= false; 
       on_bit_connected();
    }
    if ((tim_sleep>=30000) && (!bt_connected)){
      Serial.println("sleep 1");
      digitalWrite(ESP_WKP,1);
      LowPower.shutdown();
    }


  }
  if (millis() - loopDelay_count_alive > 20){
    loopDelay_count_alive = millis();
    tim_alive++;
    tim_conn++;
    tim_sleep++;
  }  
  
}

void Update_IT_callback(void)
{ 
  digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
}

void serialEvent(){
  while(Serial.available()){
    // delay(30);
    // char inChar = (char)Serial.read();
    // line += inChar;
    // if (inChar == '#'){
    //   stringComplete = true;
    //   on_serial();
    //   // Serial.print(line);
    // }  
    }
}

void serialEvent2(){
  // Serial.print("serial 2: ");
  while(Serial2.available()){
    delay(50);
    char inChar = (char)Serial2.read();
    line2 += inChar;
    // Serial.println(line2);
    if ((inChar == '#') || line2.equals("OK")){
      string2Complete = true;
      // Serial.println(line2);
      on_BT_comm();
    }  
  }
  // Serial.println(line2);
  // line2 = "";
}

void wakeUP_fun() {
  Serial.println("sleep 3");
  tim_sleep=0;
  digitalWrite(ESP_WKP,0);
  
}

static int32_t readVref()
{
#ifdef __LL_ADC_CALC_VREFANALOG_VOLTAGE
#ifdef STM32U5xx
  return (__LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC1, analogRead(AVREF), LL_ADC_RESOLUTION));
#else
  return (__LL_ADC_CALC_VREFANALOG_VOLTAGE(analogRead(AVREF), LL_ADC_RESOLUTION));
#endif
#else
  return (VREFINT * ADC_RANGE / analogRead(AVREF)); // ADC sample to mV
#endif
}

#ifdef ATEMP
static int32_t readTempSensor(int32_t VRef)
{
#ifdef __LL_ADC_CALC_TEMPERATURE
#ifdef STM32U5xx
  return (__LL_ADC_CALC_TEMPERATURE(ADC1, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
#else
  return (__LL_ADC_CALC_TEMPERATURE(VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
#endif
#elif defined(__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS)
  return (__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(AVG_SLOPE, V25, CALX_TEMP, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
#else
  return 0;
#endif
}
#endif

static int32_t readVoltage(int32_t VRef, uint32_t pin)
{
#ifdef STM32U5xx
  return (__LL_ADC_CALC_DATA_TO_VOLTAGE(ADC1, VRef, analogRead(pin), LL_ADC_RESOLUTION));
#else
  return (__LL_ADC_CALC_DATA_TO_VOLTAGE(VRef, analogRead(pin), LL_ADC_RESOLUTION));
#endif
}






