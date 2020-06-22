/*
 * DSTIKE ESP32 Watch(WROOM-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 5 Screen
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

#include <Adafruit_GFX.h>
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_DC    22
#define TFT_RST   23
#define TFT_MOSI  17
#define TFT_SCLK  16

Arduino_ST7789 TFT_Screen = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);

void setup()
{
  Serial.begin(9600);
  
  TFT_Screen.init(240, 240);
  TFT_Screen.setRotation(1);
  Serial.println("Initialized");
}
 
void loop() 
{
  TFT_Screen.fillScreen(BLACK);
  delay(500);
  TFT_Screen.fillScreen(RED);
  delay(500);
  TFT_Screen.fillScreen(GREEN);
  delay(500);
  TFT_Screen.fillScreen(BLUE);
  delay(500);
  TFT_Screen.fillScreen(YELLOW);
  delay(500);
  TFT_Screen.fillScreen(MAGENTA);
  delay(500);
  TFT_Screen.fillScreen(WHITE);
  delay(500);

  TFT_Screen.fillScreen(BLACK);
  delay(500);

  for (short int i = 0; i < TFT_Screen.width(); i+=6) 
  {
    TFT_Screen.drawLine(i, 0, i, TFT_Screen.width()-1, WHITE);
    delay(50);
  }

  TFT_Screen.fillScreen(BLACK);
  delay(500);

  for (short int i = 0; i < TFT_Screen.height(); i+=6) 
  {
    TFT_Screen.drawLine(0, i, TFT_Screen.height()-1, i, WHITE);
    delay(50);
  }

  TFT_Screen.fillScreen(BLACK);
  delay(500);
  
  TFT_Screen.setCursor(60, 100);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(5);
  TFT_Screen.setTextWrap(true);
  TFT_Screen.print("TEST");
  delay(1000);
}
