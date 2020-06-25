/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Project NTP_Clock
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

#include <WiFi.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789.h>
#include "time.h"

#define TFT_DC    22
#define TFT_RST   23
#define TFT_MOSI  17
#define TFT_SCLK  16

//Navigation Button
#define Nav_Up     19
#define Nav_Center 18
#define Nav_Down    5

const char* ssid     = "MaxPro";
const char* password = "12345678";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800; //Taipei GMT+8 8*60*60
const int   daylightOffset_sec = 0;

int LCD_mode = 1;
Arduino_ST7789 TFT_Screen = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo);

  TFT_Screen.fillRect(25 ,110 ,190 ,110 ,BLACK);
  TFT_Screen.setCursor(25, 110);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(4);
  TFT_Screen.setTextWrap(true);
  if(timeinfo.tm_hour < 10)TFT_Screen.print("0");
  TFT_Screen.print(timeinfo.tm_hour);
  TFT_Screen.print(":");
  if(timeinfo.tm_min < 10)TFT_Screen.print("0");
  TFT_Screen.print(timeinfo.tm_min);
  TFT_Screen.print(":");
  if(timeinfo.tm_sec < 10)TFT_Screen.print("0");
  TFT_Screen.print(timeinfo.tm_sec);
}

void setup()
{
  Serial.begin(115200);
  pinMode(Nav_Up    , INPUT_PULLUP);
  pinMode(Nav_Center, INPUT_PULLUP);
  pinMode(Nav_Down  , INPUT_PULLUP); //Press = 0
  TFT_Screen.init(240, 240);
  TFT_Screen.setRotation(1);
  Serial.println("Initialized");

  TFT_Screen.fillScreen(BLACK);
  TFT_Screen.setCursor(40, 110);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(3);
  TFT_Screen.setTextWrap(true);
  TFT_Screen.print("WIFI_INIT");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  TFT_Screen.fillScreen(BLACK);
  TFT_Screen.setCursor(40, 110);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(3);
  TFT_Screen.setTextWrap(true);
  TFT_Screen.print("WIFI_OKEY");

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  
  TFT_Screen.fillScreen(BLACK);
  TFT_Screen.setCursor(0, 0);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(3);
  TFT_Screen.setTextWrap(true);
  TFT_Screen.print(timeinfo.tm_year + 1900);
  TFT_Screen.print(" ");
  if(timeinfo.tm_mon < 10)TFT_Screen.print("0");
  TFT_Screen.print(timeinfo.tm_mon + 1);
  TFT_Screen.print(" ");
  if(timeinfo.tm_mday < 10)TFT_Screen.print("0");
  TFT_Screen.print(timeinfo.tm_mday);
}

void loop()
{
  delay(900);
  
  if(digitalRead(Nav_Center) == LOW)
  {
    if(LCD_mode == 1)
    {
      LCD_mode = 2;
    }
    if(LCD_mode == 3)
    {
      struct tm timeinfo;
      if(!getLocalTime(&timeinfo))
      {
        Serial.println("Failed to obtain time");
        return;
      }
      LCD_mode = 1;
      TFT_Screen.fillScreen(BLACK);
      TFT_Screen.setCursor(0, 0);
      TFT_Screen.setTextColor(WHITE);
      TFT_Screen.setTextSize(3);
      TFT_Screen.setTextWrap(true);
      TFT_Screen.print(timeinfo.tm_year + 1900);
      TFT_Screen.print(" ");
      if(timeinfo.tm_mon < 10)TFT_Screen.print("0");
      TFT_Screen.print(timeinfo.tm_mon + 1);
      TFT_Screen.print(" ");
      if(timeinfo.tm_mday < 10)TFT_Screen.print("0");
      TFT_Screen.print(timeinfo.tm_mday);
    }
  }

  if(LCD_mode == 1)
  {
    printLocalTime();
  }
  else if(LCD_mode == 2)
  {
    TFT_Screen.fillScreen(BLACK);
    LCD_mode = 3;
  }
}
