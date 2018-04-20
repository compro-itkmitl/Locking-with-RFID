﻿# Locking-with-RFID

## Introduction
โปรเจค **Locking-with-RFID** คือโปรเจคที่นำอุปกรณ์อ่าน
RFIDและArduinoมาประยุกต์ใช้ในการล็อกสิ่งต่างๆ เช่น ตู้, ล๊อกเกอร์
และอื่นๆอีกมากมาย 
## Equipment
 - Mifare MFRC522 x 1
 - Arduino Uno x 1
 - 5v Relay x 1
 - 12v Lock x 1
 - 3-24v Buzzer x 1
 - 12v Adapter x 1
 - 5v Adapter x 1
 - DC splitter x 1
## Library
 - RFID.h : http://www.mediafire.com/file/ivnioa432cwcl6n/RFID.7z
 - EEPROM.h
## Wiring diagram
**Mifare MFRC522**
-   MOSI -> 11
-   MISO  -> 12
-   SCK  -> 13
-   SDA or NSS  -> 10
-   RST  -> 9
-   VCC  -> 3.3V
-   GND -> GND

**Buzzer**
- Dc+ -> 3
- Dc- -> GND

**Relay**
- DC+ -> 5v
- DC- -> GND
- IN -> 4
- Com -> Dc Splitter

**Locking Module**
- DC+ -> NO of 5v Relay
- DC- -> GND of Dc Splitter
## Instruction
เมื่อทำการเปิดใช้งานครั้งแรก ตัวArduinoจะยังไม่มีข้อมูลของคีย์การ์ด ดังนั้นจึงจำเป็นที่จะลงทะเบียนคีย์การ์ดก่อน โดยต้องลงทะเบียนให้ครบ 3 ใบ ระบบจึงจะสามารถทำงานได้อย่างเต็มที่

เมื่อลงทะเบียนครบทั้ง3ใบแล้ว เมื่อทำการแตะคีย์การ์ดระบบจะปลดล็อกให้เป็นเวลา5วินาที ผู้ใช้งานจะสามารถปลดล็อกสิ่งที่ผู้ใช้งานล็อกไว้ได้ และ เมื่อผู้ใช้งานจะล็อก/ปิด สิ่งที่ผู้ใช้งานได้นำมาล็อกไว้ เพียงแค่แตะอีกครั้งระบบจะทำการปลดล็อกเพื่อให้ผู้ใช้งานสามารถเก็บลิ้นชักหรืออื่นๆให้เข้าที่ได้และจะล็อกกลับภายในเวลา5วินาทีดังเดิม

ผู้ใช้งานสามารถรีเซ็ตคีย์การ์ดทั้งหมดได้ โดยเชื่อมArduinoเข้ากับคอมพิวเตอร์แล้ว
ทำการหาPortที่Arduinoเชื่อมต่ออยู่โดยใช้Device Mamager
 จากนั้นเปิดCMDแล้วพิมพ์  `echo R > PortของArduino` 
 เพียงเท่านี้คียการ์ดทั้งหมดจะถูกลบ
