/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/

#include <Arduino.h>
#include <Bounce2.h>
#include <STM32LowPower.h>
#include <HardwareTimer.h> 

#include "communication.h"
#include "control.h"
#include "defines.h"
#include "dig_input.h"
#include "dig_output.h"
#include "ana_Input.h"
#include "io_defines.h"
#include "tools.h"

Bounce bounce = Bounce();

HardwareSerial Serial2(PA3, PA2);

static int32_t readVref();
static int32_t readTempSensor(int32_t VRef);

void serialEvent();
// void serialEvent3();
void serialEvent2();
void serialEventRun(void);
void Update_Tim3_callback(void);
void Compare_IT_callback();
void Update_IT_callback();

void serialEventRun(void) {
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
bool first_loop = true;
bool run_enabled = false;

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

volatile int repetitions = 1;

// TIM_TypeDef *Instance = TIM1;
// TIM_TypeDef *Instance3 = TIM3;
// TIM_TypeDef *Instance4 = TIM4;
// TIM_TypeDef *Instance9 = TIM9;

// TIM_TypeDef *Instance3 = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(PULSE_0), PinMap_PWM);
// uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(PULSE_0), PinMap_PWM));

HardwareTimer *tim1 = new HardwareTimer(TIM1);
HardwareTimer *tim2 = new HardwareTimer(TIM2);
HardwareTimer *tim3 = new HardwareTimer(TIM3);
// HardwareTimer *Tim10 = new HardwareTimer(Instance10);
// HardwareTimer *Tim9 = new HardwareTimer(Instance9);

void setup() {
  Serial.begin(115200);
  Serial1.begin(19200);
  Serial2.begin(19200);
  
  delay(1000);
  dig_output_begin();
  dig_input_begin();
  ana_input_begin();
  bounce.attach(BT_POWER, INPUT_PULLDOWN);
  bounce.interval(5);

  LowPower.begin();
  LowPower.attachInterruptWakeup(BT_POWER, wakeUP_fun, RISING, SHUTDOWN_MODE);

  tim1->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PA8);
  tim1->setOverflow(10000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  tim1->setCaptureCompare(1, 100, RESOLUTION_12B_COMPARE_FORMAT); 
  tim1->resume();

  tim2->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PA5);
  tim2->setMode(2, TIMER_OUTPUT_COMPARE_PWM2, PB3);
  // tim2->setPrescaleFactor(8); // Due to setOverflow with MICROSEC_FORMAT, prescaler will be computed automatically based on timer input clock
  tim2->setOverflow(5000, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  tim2->setCaptureCompare(1, 30, RESOLUTION_12B_COMPARE_FORMAT); 
  tim2->setCaptureCompare(2, 10, RESOLUTION_12B_COMPARE_FORMAT); 
  // tim2->attachInterrupt(Update_IT_callback);
  // tim2->attachInterrupt(2, Compare_IT_callback);
  tim2->resume();
 
  tim3->setOverflow(20, HERTZ_FORMAT);
  tim3->attachInterrupt(Update_Tim3_callback);
  tim3->resume();

}

void loop() {

  if (millis() - loopDelay_on > 20000) {
    loopDelay_on = millis();
    // Serial.println("button1");
    // Serial2.print("AT+NAME=TEC2");
    // Serial2.print("teste#");
  }

  if (millis() - loopDelay_int_temp > 7000) {
    loopDelay_int_temp = millis();
    read_analog();
    VRef = readVref();
    intTemp = readTempSensor(VRef);
    // Serial.print("VRef: ");
    // Serial.println(VRef);
    VRef = map(VRef, 0, 4095, 0, 500);
    // Serial.println(VRef, DEC);
    // Serial.print("Temp: ");
    // Serial.println(intTemp);
    sendMsgTimer();
    
    // delay(30);
    // Serial2.println("co,0,0,1,#");
    // if (Tim1->isRunning()){
    //   Tim1->pause();
    // }else{
    //   Tim1->resume();
    // }
    
    
  }

  if (millis() - loopDelay_bit_alive > 2000) {
    loopDelay_bit_alive = millis();
    // Serial.print("sleep: ");
    // Serial.println(tim_sleep);
    if ((tim_alive >= 100) && !(bt_connected)) {
      bt_alive = false;
      on_bit_alive();
    }
    if ((tim_conn >= 1000) && (bt_connected)) {
      bt_connected = false;
      on_bit_connected();
    }

    if ((tim_sleep >= SHUTDOWN_INTERVAL_MS) && (!bt_connected)) {
      // Serial.println("sleep 1");
      digitalWrite(ESP_WKP, 0);
      LowPower.shutdown(0);
    }else if (bt_connected){
      // Serial.print("sleep2: ");
      // Serial.println(tim_sleep);
      tim_sleep=0;  
    }
  }
  if (millis() - loopDelay_count_alive > 20) {
    loopDelay_count_alive = millis();
    bounce.update();
    int btn = bounce.read();
    if (btn == HIGH && bounce.currentDuration() > 3000) {
      check_button(btn, 0);
    }
    tim_alive++;
    tim_conn++;
    tim_sleep++;
  }
}

void Update_Tim3_callback() {
  digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
}

void Update_IT_callback()
{ // Update event correspond to Rising edge of PWM when configured in PWM1 mode
  digitalWrite(STATUS_LED, LOW); // pin2 will be complementary to pin
}

void Compare_IT_callback()
{ // Compare match event correspond to falling edge of PWM when configured in PWM1 mode
  digitalWrite(STATUS_LED, HIGH);
}



void serialEvent() {
  while (Serial.available()) {
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

void serialEvent2() {
  // Serial.print("serial 2: ");
  while (Serial2.available()) {
    delay(50);
    char inChar = (char)Serial2.read();
    line2 += inChar;
    // Serial.println(line2);
    if ((inChar == '#') || line2.equals("OK")) {
      string2Complete = true;
      // Serial.println(line2);
      on_BT_comm();
    }
  }
  // Serial.println(line2);
  // line2 = "";
}

static int32_t readVref() {
#ifdef __LL_ADC_CALC_VREFANALOG_VOLTAGE
#ifdef STM32U5xx
  return (__LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC1, analogRead(AVREF),
                                           LL_ADC_RESOLUTION));
#else
  return (
      __LL_ADC_CALC_VREFANALOG_VOLTAGE(analogRead(AVREF), LL_ADC_RESOLUTION));
#endif
#else
  return (VREFINT * ADC_RANGE / analogRead(AVREF)); // ADC sample to mV
#endif
}

#ifdef ATEMP
static int32_t readTempSensor(int32_t VRef) {
#ifdef __LL_ADC_CALC_TEMPERATURE
#ifdef STM32U5xx
  return (__LL_ADC_CALC_TEMPERATURE(ADC1, VRef, analogRead(ATEMP),
                                    LL_ADC_RESOLUTION));
#else
  return (
      __LL_ADC_CALC_TEMPERATURE(VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
#endif
#elif defined(__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS)
  return (__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(
      AVG_SLOPE, V25, CALX_TEMP, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
#else
  return 0;
#endif
}
#endif

static int32_t readVoltage(int32_t VRef, uint32_t pin) {
#ifdef STM32U5xx
  return (__LL_ADC_CALC_DATA_TO_VOLTAGE(ADC1, VRef, analogRead(pin),
                                        LL_ADC_RESOLUTION));
#else
  return (
      __LL_ADC_CALC_DATA_TO_VOLTAGE(VRef, analogRead(pin), LL_ADC_RESOLUTION));
#endif
}
