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
int serNum0, serNum1, serNum2, serNum3, serNum4;
int i, j, cardCount=0;
int buzz(int times,int dlay,int pin);
int CardCheck(int serNum0,int serNum1,int serNum2,int serNum3,int serNum4);
int PosCheck(int serNum0,int serNum1,int serNum2,int serNum3,int serNum4);
int Status;
struct cardNumber{int serNum[5];};
struct cardNumber cards[3];
// EEPROM variable and function
int card_count_address = 0;
int start_address = 1;
int end_address = start_address + 5;
// Bluetooth variable and function
String command = "";
String test = "Sent From Bluetooth";
char character;
int stopper = 0;
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
    temp = CardCheck(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]);
    if(temp == 0){ //check if it is a new card or not.
      buzz(1, 200, 8);
      buzz(2, 100, 8);
      Serial.println("New");
      for(i=0;i<5;i++){
        cards[cardCount].serNum[i] = rfid.serNum[i];
        }
      Serial.print("Registered, ID : ");
      for(i=0;i<5;i++){
        Serial.print(cards[cardCount].serNum[i], HEX);
        Serial.print(" ");
        }
      Serial.println(" ");
      cardCount += 1;
      }
    else{
      buzz(1, 400, 8);
      Serial.println("Already Registered.");
      temp = PosCheck(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]);
      Serial.print("ID : ");
      for(i=0;i<5;i++){
        Serial.print(cards[temp].serNum[i], HEX);
        Serial.print(" ");
        }
      Serial.println(" ");
      }
    }
  }
  rfid.halt();
  //end of RFID coding
  if(bluetooth.available()){
    character = bluetooth.read();
    if(character == 'U') Serial.println("Hallelujah");
    bluetooth.println("Unlocked");
    }
  if(Serial.available()){
    character = Serial.read();
    command.concat(character);
    bluetooth.print(command);
    Serial.print(command);
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
  int temp = 0;
  for(i=0;i<cardCount+1;i++) if(cards[i].serNum[0] == serNum0 && cards[i].serNum[1] == serNum1 && cards[i]
  .serNum[2] == serNum2 && cards[i].serNum[3] == serNum3 && cards[i].serNum[4] == serNum4){
    temp += 1;
  }
  return temp;
}
int PosCheck(int serNum0,int serNum1,int serNum2,int serNum3,int serNum4){
  int temp = 0;
  for(i=0;i<cardCount+1;i++) if(cards[i].serNum[0] == serNum0 && cards[i].serNum[1] == serNum1 && cards[i].serNum[2] == serNum2 && cards[i].serNum[3] == serNum3 && cards[i].serNum[4] == serNum4){
    return i;
  }
}
