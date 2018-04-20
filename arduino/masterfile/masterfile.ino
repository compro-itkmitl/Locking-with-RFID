#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include "RFID.h"
#define SS_PIN 10
#define RST_PIN 9
#define Buzz 3
#define Lock 4
RFID rfid(SS_PIN, RST_PIN);
// Card Function
int CardNumber1(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4, char comm);
int CardNumber2(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4, char comm);
int CardNumber3(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4, char comm);
int CardCheck(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4);
// Card availability address
int Card1 = 1;
int Card2 = 2;
int Card3 = 3;
// buzz function
int buzzer(int times, int gap);
void setup(){
Serial.begin(9600);
SPI.begin();
rfid.init();
pinMode(Buzz, OUTPUT);
pinMode(Lock, OUTPUT);
digitalWrite(Buzz, LOW);
}
void loop(){
int temp;
if (rfid.isCard()) {
  if (rfid.readCardSerial()) {
  Serial.println("Card Detected");
  Serial.println("Checking");
  temp = CardCheck(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]);
  Serial.println(temp);
  delay(200);
  if(temp == 0){
    Serial.println("New Card");
    buzzer(2, 100);
    if(EEPROM.read(Card1) == 0){
      CardNumber1(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4], 'W');
      EEPROM.write(Card1, 1);
      Serial.println("Registered in slot1.");
      }
    else if(EEPROM.read(Card2) == 0){
      CardNumber2(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4], 'W');
      EEPROM.write(Card2, 1);
      Serial.println("Registered in slot2.");
      }
    else if(EEPROM.read(Card3) == 0){
      CardNumber3(rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4], 'W');
      EEPROM.write(Card3, 1);
      Serial.println("Registered in slot3.");
      }
    else Serial.println("Limit reached.");
    }
   else if(temp == 1){
      Serial.println("Key card is valid.");
      buzzer(1, 300);
      digitalWrite(Lock, HIGH);
      delay(5000);
      digitalWrite(Lock, LOW);
    }
  }
}
rfid.halt();
//Serial Reset
if(Serial.available()){
  char command;
  int i;
  command = Serial.read();
  if(command == 'R'){
    EEPROM.write(Card1, 0);
    EEPROM.write(Card2, 0);
    EEPROM.write(Card3, 0);
    for(i=10;i<15;i++){
      EEPROM.write(i, 0);
      }
    for(i=20;i<25;i++){
      EEPROM.write(i, 0);
      }
    for(i=30;i<35;i++){
      EEPROM.write(i, 0);
      }
    Serial.println("Key card cleaned.");
    }
  if(command == 'S'){
    Serial.println(EEPROM.read(Card1));
    Serial.println(EEPROM.read(Card2));
    Serial.println(EEPROM.read(Card3));
    for(i=10;i<15;i++){
      Serial.print(EEPROM.read(i), HEX);
      Serial.print(" ");
      }
    Serial.println(" ");
    for(i=20;i<25;i++){
      Serial.print(EEPROM.read(i), HEX);
      Serial.print(" ");
      }
    Serial.println(" ");
    for(i=30;i<35;i++){
      Serial.print(EEPROM.read(i), HEX);
      Serial.print(" ");
      }
    Serial.println(" ");
    }
  }
}
int CardNumber1(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4, char comm){
  int start_address = 10;
  if(sernum0 == EEPROM.read(10) && sernum1 == EEPROM.read(11) && sernum2 == EEPROM.read(12) && sernum3 == EEPROM.read(13) && sernum4 == EEPROM.read(14) && comm == 'C'){
    return 1;
    }
  else if(comm == 'W'){
    EEPROM.write(10, sernum0);
    EEPROM.write(11, sernum1);
    EEPROM.write(12, sernum2);
    EEPROM.write(13, sernum3);
    EEPROM.write(14, sernum4);
    }
  else return 0;
  }
int CardNumber2(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4, char comm){
  int start_address = 20;
  if(sernum0 == EEPROM.read(20) && sernum1 == EEPROM.read(21) && sernum2 == EEPROM.read(22) && sernum3 == EEPROM.read(23) && sernum4 == EEPROM.read(24) && comm == 'C'){
    return 1;
    }
  else if(comm == 'W'){
    EEPROM.write(20, sernum0);
    EEPROM.write(21, sernum1);
    EEPROM.write(22, sernum2);
    EEPROM.write(23, sernum3);
    EEPROM.write(24, sernum4);
    }
  else return 0;
  }
int CardNumber3(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4, char comm){
  int start_address = 30;
  if(sernum0 == EEPROM.read(30) && sernum1 == EEPROM.read(31) && sernum2 == EEPROM.read(32) && sernum3 == EEPROM.read(33) && sernum4 == EEPROM.read(34) && comm == 'C'){
    return 1;
    }
  else if(comm == 'W'){
    EEPROM.write(30, sernum0);
    EEPROM.write(31, sernum1);
    EEPROM.write(32, sernum2);
    EEPROM.write(33, sernum3);
    EEPROM.write(34, sernum4);
    }
  else return 0;
  }
int CardCheck(int sernum0, int sernum1, int sernum2, int sernum3, int sernum4){
  int temp1, temp2, temp3;
  temp1 = CardNumber1(sernum0, sernum1, sernum2, sernum3, sernum4, 'C');
  temp2 = CardNumber2(sernum0, sernum1, sernum2, sernum3, sernum4, 'C');
  temp3 = CardNumber3(sernum0, sernum1, sernum2, sernum3, sernum4, 'C');
  if(temp1 == 1 || temp2 == 1 || temp3 == 1){
    return 1;
    }
  else return 0;
  }
int buzzer(int times, int gap){
  int i;
  for(i=0;i<times;i++){
    digitalWrite(Buzz, HIGH);
    delay(gap);
    digitalWrite(Buzz, LOW);
    delay(gap);
    }
  }
