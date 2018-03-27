#include <SoftwareSerial.h>
#include "SPI.h"
SoftwareSerial bluetooth(2, 3);
#include "RFID.h"
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);
// Setup variables:
int serNum0, serNum1, serNum2, serNum3, serNum4;
int i, j;
void setup()
{
Serial.begin(9600);
SPI.begin();
rfid.init();
pinMode(8, OUTPUT);
}
void loop()
{
if (rfid.isCard()) {
if (rfid.readCardSerial()) {
if (rfid.serNum[0] != serNum0
&& rfid.serNum[1] != serNum1
&& rfid.serNum[2] != serNum2
&& rfid.serNum[3] != serNum3
&& rfid.serNum[4] != serNum4
) {
/* With a new cardnumber, show it. */
Serial.println(" ");
Serial.println("Card found");
serNum0 = rfid.serNum[0];
serNum1 = rfid.serNum[1];
serNum2 = rfid.serNum[2];
serNum3 = rfid.serNum[3];
serNum4 = rfid.serNum[4];
//Serial.println(" ");
Serial.println("Cardnumber: ");
for(i=0;i<5;i++){
  Serial.print(rfid.serNum[i], HEX);
  if(i!=4) Serial.print(" ");
  if(i==4) Serial.println("\n");
  }
//buzzer
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  delay(100);
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  delay(100);  
} else {
/* If we have the same ID, just write a dot. */
Serial.print("Registored Access: Granted\n");
digitalWrite(8, HIGH);
delay(500);
digitalWrite(8, LOW);
      }
  }
}
rfid.halt();
}
