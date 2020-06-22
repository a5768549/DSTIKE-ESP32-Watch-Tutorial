/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 2 LED
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

//Pin 27 is back side LED(High light LED)
#define LED 27
 
void setup() 
{
  pinMode(LED,OUTPUT);
}
 
void loop() 
{
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
}
