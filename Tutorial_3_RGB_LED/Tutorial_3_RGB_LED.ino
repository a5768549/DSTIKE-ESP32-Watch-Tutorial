/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 3 RGB_LED
 * CPU Frequency must set 160MHZ
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */
#include <Adafruit_NeoPixel.h>

//Pin 33 is front side LED(RGB_LED)
#define RGB_LED 33
Adafruit_NeoPixel pixels(1, RGB_LED, NEO_GRB + NEO_KHZ800);

void setup()
{
  pixels.begin();
  Serial.begin(9600);
}
 
void loop() 
{
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); //Red
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(0, 255, 0)); //Green
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); //Blue
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(255, 255, 0)); //Yellow
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(255, 0, 255)); //Purple
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(0, 255, 255)); //Cyan
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(255, 255, 255)); //White
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); //no
  pixels.show();
  delay(500);

  for(int i = 0;i<256;i++)
  {
    pixels.setPixelColor(0, pixels.Color(i, i, i)); //White Breathing light 0~255
    pixels.show();
    delay(30);
    Serial.println(i);
  }

  for(int i = 255;i>=0;i--)
  {
    pixels.setPixelColor(0, pixels.Color(i, i, i)); //White Breathing light 255~0
    pixels.show();
    delay(30);
    Serial.println(i);
  }
}
