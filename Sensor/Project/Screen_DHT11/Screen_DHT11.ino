/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Sensor Project DHT11
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 * 
 * DSKIKE Watch 腳位
 * *3.3V *25 SVP 16 RX
 * *GND   26 SVN 17 TX
 */

#include <Adafruit_GFX.h>
#include <Arduino_ST7789.h> 
#include <SPI.h>
#include "DHT.h"

#define TFT_DC    22
#define TFT_RST   23
#define TFT_MOSI  17
#define TFT_SCLK  16

#define DHTPIN 25
#define DHTTYPE DHT11   // DHT 11

Arduino_ST7789 TFT_Screen = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);

DHT dht(DHTPIN, DHTTYPE);

void printDHT(float h,float t,float f)
{
  TFT_Screen.fillScreen(BLACK);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(3);
  TFT_Screen.setTextWrap(true);
  TFT_Screen.setCursor(20, 80);
  TFT_Screen.print("Humi:");
  TFT_Screen.print(h);
  TFT_Screen.print("%");
  TFT_Screen.setCursor(20, 110);
  TFT_Screen.print("Temp:");
  TFT_Screen.print(t);
  TFT_Screen.print("C");
  TFT_Screen.setCursor(20, 140);
  TFT_Screen.print("Temp:");
  TFT_Screen.print(f);
  TFT_Screen.print("F");
}

void setup() 
{
  Serial.begin(115200);

  TFT_Screen.init(240, 240);
  TFT_Screen.setRotation(1);

  dht.begin();
  Serial.println("Initialized");

  TFT_Screen.fillScreen(BLACK);
}

void loop() 
{
  delay(2000);
  

  float h = dht.readHumidity();//濕度
  float t = dht.readTemperature();//攝氏溫度
  float f = dht.readTemperature(true);//華氏溫度

  
  Serial.print("濕度: ");
  Serial.print(h);
  Serial.print("%,溫度: ");
  Serial.print(t);
  Serial.print("°C ");
  Serial.print(f);
  Serial.println("°F ");

  printDHT(h,t,f);
}
