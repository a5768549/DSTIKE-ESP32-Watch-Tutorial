/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Sensor Project DHT11 SD(NTP)
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 * 
 * DSKIKE Watch 腳位
 * *3.3V *25 SVP 16 RX
 * *GND   26 SVN 17 TX
 */

 /*
 * ***Notice***
 * DSTIKE ESP32 Watch's SD Card Library need use SD_MMC.h
 * The SD card must be removed before uploading the code.
 * ***Notice***
 * 
 * Connect the SD card to the following pins:
 * 
 * SD Card | ESP32
 *    D2       12
 *    D3       13
 *    CMD      15
 *    CLK      14
 *    D0       2  (add 1K pull up after flashing)
 *    D1       4
 */

#include <WiFi.h>
#include "time.h"
#include "DHT.h"
#include "time.h"
#include "FS.h"
#include "SD_MMC.h"
#include "SD_Control.h"

#define DHTPIN 25
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "*********";
const char* password = "*********";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800; //Taipei GMT+8 8*60*60
const int   daylightOffset_sec = 0;

void printLocalTime(float h,float t,float f)
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo);

  char buffer[80];
  strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",&timeinfo);
  String _time = buffer;
  
  appendFile(SD_MMC, "/data.txt", buffer);

  char _h[10];
  sprintf(_h, "%f", h);
  char _t[10];
  sprintf(_t, "%f", t);
  char _f[10];
  sprintf(_f, "%f", f);
  appendFile(SD_MMC, "/data.txt", "Humidity:");
  appendFile(SD_MMC, "/data.txt", _h);
  appendFile(SD_MMC, "/data.txt", "Temperature(C):");
  appendFile(SD_MMC, "/data.txt", _t);
  appendFile(SD_MMC, "/data.txt", "Temperature(F):");
  appendFile(SD_MMC, "/data.txt", _f);
  appendFile(SD_MMC, "/data.txt", "\n");

  
}

void setup() 
{
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo);

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  if(!SD_MMC.begin())
  {
      Serial.println("Card Mount Failed");
      return;
  }

  Serial.println("Initialized");
}

void loop() 
{
  delay(1000);

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

  printLocalTime(h,t,f);
}
