#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include "RFID.h"
#define SS_PIN 10
#define RST_PIN 9
#define Door 4
RFID rfid(SS_PIN, RST_PIN);
SoftwareSerial bluetooth(6, 7);
// Setup variables:
int i, j, cardCount=0;
int buzz(int times,int dlay,int pin);
int Status;
// RFID&Card variable and function
int serNum0, serNum1, serNum2, serNum3, serNum4;
int CardCheck(int serNum0,int serNum1,int serNum2,int serNum3,int serNum4);
int PosCheck(int serNum0,int serNum1,int serNum2,int serNum3,int serNum4);
struct cardNumber{int serNum[5];};
struct cardNumber cards[3];
// EEPROM variable and function
int card_count_address = 0;
// Bluetooth variable and function
String command = "";
char character;
int stopper = 0;
// Door
void door_command(int command);
// 
void setup()
{
Serial.begin(9600);  
SPI.begin();
rfid.init();
pinMode(8, OUTPUT);
bluetooth.begin(9600);
}
void loop()
{
if(rfid.isCard()){
  if(rfid.readCardSerial()){
    Serial.println("Card Detected");
    int temp;
    int etemp;
    temp = CardCheck(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]);
    Serial.println(temp);
    Serial.println(EEPROM.read(0));
    //check if it is a new card or not.
    if(temp == 0){ // New card detected
      buzz(1, 200, 8);
      buzz(2, 100, 8);
      Serial.println("New");
      etemp = EEPROM.read(0);
      etemp += 1;
      int counter = 0;
      EEPROM.update(0, etemp);
      for(i=EEPROM.read(0)*5;i<EEPROM.read(0)*5+5;i++){
        EEPROM.write(i, rfid.serNum[counter]);
        counter += 1;
        }
      Serial.print("Registered, ID : ");
      for(i=0;i<5;i++){
        Serial.print(cards[cardCount].serNum[i], HEX);
        Serial.print(" ");
        }
      Serial.println(" ");
      }
    else{
      buzz(1, 400, 8);
      Serial.println("Already Registered.");
      Serial.print("ID : ");
      for(i=0;i<5;i++){
        Serial.print(rfid.serNum[i], HEX);
        Serial.print(" ");
        }
      Serial.println(" ");
      }
    }
    Serial.print(EEPROM.read(0));
    Serial.println("Cards were stored.");
  }
  rfid.halt();
  //end of RFID coding
  if(bluetooth.available()){
    character = bluetooth.read();
    if(character == 'U'){
      if(Status == 1){
        door_command(2);
        bluetooth.write(2);
        }
      if(Status == 2){
        door_command(1);
        bluetooth.write(1);
        }
    }
    if(character == 'S') bluetooth.write(Status);
    bluetooth.println("Unlocked");
    }
  if(Serial.available()){
    character = Serial.read();
    if(character == 'R'){
      EEPROM.write(0, 0);
      Serial.println("Cards cleared");     }
    }
    if(character == 'S'){
      for(i=1;i<EEPROM.length();i++){
        Serial.print(EEPROM.read(i));
        Serial.print(" ");
        if(i%5 == 0) Serial.println(" ");
        }
      }
}
int buzz(int times,int dlay,int pin){
  int i;
  for(i=0;i<times;i++){
    digitalWrite(pin, HIGH);
    delay(dlay);
    digitalWrite(pin, LOW);
    delay(dlay);
  }
}
int CardCheck(int serNum0,int serNum1,int serNum2,int serNum3,int serNum4){
  // return 0 if it's not a new card. Else return number.
  int temp;
  temp = EEPROM.read(0);
  for(i=1;i<EEPROM.length();i+=5){
    if(EEPROM.read(i) == serNum0)
    if(EEPROM.read(i+1) == serNum1)
    if(EEPROM.read(i+2) == serNum2)
    if(EEPROM.read(i+3) == serNum3)
    if(EEPROM.read(i+4) == serNum4)
    return i;
    }
  return 0;  
}
int PosCheck(int serNum0,int serNum1,int serNum2,int serNum3,int serNum4){
  // return a position stored in card
  int temp = 0;
  for(i=0;i<cardCount+1;i++) if(cards[i].serNum[0] == serNum0 && cards[i].serNum[1] == serNum1 && cards[i].serNum[2] == serNum2 && cards[i].serNum[3] == serNum3 && cards[i].serNum[4] == serNum4){
    return i;
  }
}
void door_command(int command){
  if(command == 1){
    digitalWrite(Door, HIGH);
    }
  else if(command == 2){
    digitalWrite(Door, LOW);
    }
  }
