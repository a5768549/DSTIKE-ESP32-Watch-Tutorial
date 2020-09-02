/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Sensor Project IOT_DHT11
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 * 
 * DSKIKE Watch 腳位
 * *3.3V *25 SVP 16 RX
 * *GND   26 SVN 17 TX
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 25
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "********";
const char* password = "********";
//thingspeak api
String url = "https://api.thingspeak.com/update?api_key=3I8OW15J65GS1H7P";

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
  
  Serial.println("Initialized");
}

void loop() 
{
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

  HTTPClient http;
  
  String url1 = url + "&field1=" + h + "&field2=" + t + "&field3=" + f;
  http.begin(url1);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK)
  {
    String payload = http.getString();
    //1=OK,0=error
    Serial.println(payload);
  }
  else
  {
    Serial.println("Error");
  }
  http.end();

  delay(20000);
}
