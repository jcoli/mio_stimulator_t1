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
#include "communication.h"

HardwareSerial Serial2(PA3, PA2);

static int32_t readVref();
static int32_t readTempSensor(int32_t VRef);

void serialEvent();
// void serialEvent3();
void serialEvent2();
void serialEventRun(void);

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

bool bt_enabled = false;
bool bt_connected = false;
bool intLed = true;

String line         = "";
String line1         = "";
String line2         = "";
bool stringComplete = false;
bool string1Complete = false;
bool string2Complete = false;

int32_t VRef;
float intTemp;


void setup() {
  Serial.begin(115200);
  Serial1.begin(19200);
  Serial2.begin(19200); 
  analogReadResolution(12);
  delay(5000);
  pinMode(INT_LED, OUTPUT);
  digitalWrite(INT_LED, HIGH);
  Serial.println("bt_init0");
  delay(1000);
  bt_init();
  delay(1000);
  Serial.println("bt_init1");
  
}

void loop() {
  
  if (millis() - loopDelay_on > 20000){
    loopDelay_on = millis();
    // Serial.println("button1");
    // Serial2.print("AT+NAME=TEC2");
    intLed = !intLed;  
    digitalWrite(INT_LED, HIGH);
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
    if ((inChar == '#') ){
      string2Complete = true;
      // Serial.println(line2);
      on_BT_comm();
    }  
  }
  // Serial.println(line2);
  // line2 = "";
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






