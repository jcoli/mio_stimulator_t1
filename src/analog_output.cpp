/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F401 - Mio Stimulation
**/

#include <Arduino.h>
#include <SPI.h>

#include "control.h"
#include "defines.h"
#include "io_defines.h"
#include "tools.h"

void out_ana_begin();
void MCP42010Write(int addr, int pos, int csPin);

extern const byte pot0;    // pot0 addr
extern const byte pot1;    // pot1 addr
extern const byte potBoth;    // pot0 and pot1 simultaneous addr
extern const byte pot0Shutdown;    // pot0 shutdown
extern const byte pot1Shutdown;    // pot1 shutdown
extern const byte potBothShutdown;    // pot0 and pot1 simultaneous shutdown

bool test2 = false;

void out_ana_begin(){
    pinMode(CS, OUTPUT);
    digitalWrite(CS, HIGH); 
    SPI.setMOSI(MOSI);
    SPI.setMISO(MISO);
    SPI.setSCLK(SCK);
    SPI.begin();
}    


void MCP42010Write(int addr, int pos, int csPin){
  pos = constrain(pos, 0, 255); 
  digitalWrite(CS, LOW); 
  SPI.transfer(addr);                      // configure target pot with wiper position
  SPI.transfer(pos);
  // if (test2){
  //   Serial.println("MCP42010Write: up");
  //   // for (int i = 0; i<=255; i++){ 
  //   //   Serial.println("MCP42010Write: up: "+i);              // select chip
  //     SPI.transfer(addr);                      // configure target pot with wiper position
  //     SPI.transfer(pos);
  //     delay(50);
  //  }
  // // } 
  // else{
  //   Serial.println("MCP42010Write: down");
  //   // for (int i = 255; i>=0; i--){ 
  //     // Serial.println("MCP42010Write: down: "+i);              // select chip
  //     SPI.transfer(addr);                      // configure target pot with wiper position
  //     SPI.transfer(i); 
  //     // delay(50);
  //   }
  // }
  // test2 = !test2;

  digitalWrite(CS, HIGH); 
  Serial.print("MCP42010Write: ");
  Serial.print(pos);
  Serial.print(" - ");
  Serial.print(addr, HEX);
  Serial.print(" - ");
  Serial.println(CS);
  


}