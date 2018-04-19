#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include "RFID.h"
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);
// Card Function
int CardNumber1(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4);
int CardNumber2(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4);
int CardNumber3(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4);
int CardCheck(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4);
// Card availability address
int Card1 = 1;
int Card2 = 2;
int Card3 = 3;
void setup(){
Serial.begin(9600);
SPI.begin();
rfid.init();
}
void loop(){
int temp;
if (rfid.isCard()) {
  if (rfid.readCardSerial()) {
  Serial.println("Card Detected");
  Serial.println("Checking");
  temp = CardCheck(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]);
  if(temp == 0){
    Serial.println("New Card");
    if(EEPROM.read(Card1) == 0){
      CardNumber1(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]);
      EEPROM.update(Card1, 1);
      Serial.println("Registered in slot1.");
      }
    else if(EEPROM.read(Card2) == 0){
      CardNumber2(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]);
      EEPROM.update(Card2, 1);
      Serial.println("Registered in slot2.");
      }
    else if(EEPROM.read(Card3) == 0){
      CardNumber3(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]);
      EEPROM.update(Card3, 1);
      Serial.println("Registered in slot3.");
      }
    else Serial.println("Limit reached.");
    }
  }
  else if(temp == 1){
    
    }
}
rfid.halt();
}
int CardNumber1(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4){
  int start_address = 10;
  if(sernum0 == EEPROM.read(10) && sernum1 == EEPROM.read(11) && sernum2 == EEPROM.read(12) && sernum3 == EEPROM.read(13) && sernum4 == EEPROM.read(14)){
    return 1;
    }
  else{
    EEPROM.write(10, sernum0);
    EEPROM.write(11, sernum1);
    EEPROM.write(12, sernum2);
    EEPROM.write(13, sernum3);
    EEPROM.write(14, sernum4);
    return 0;
    }
  }
int CardNumber2(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4){
  int start_address = 20;
  if(sernum0 == EEPROM.read(20) && sernum1 == EEPROM.read(21) && sernum2 == EEPROM.read(22) && sernum3 == EEPROM.read(23) && sernum4 == EEPROM.read(24)){
    return 1;
    }
  else{
    EEPROM.write(20, sernum0);
    EEPROM.write(21, sernum1);
    EEPROM.write(22, sernum2);
    EEPROM.write(23, sernum3);
    EEPROM.write(24, sernum4);
    }
  }
int CardNumber3(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4){
  int start_address = 30;
  if(sernum0 == EEPROM.read(30) && sernum1 == EEPROM.read(31) && sernum2 == EEPROM.read(32) && sernum3 == EEPROM.read(33) && sernum4 == EEPROM.read(34)){
    return 1;
    }
  }
