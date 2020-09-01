/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Sensor DHT11
 * 
 * 請先從程式庫內下載DHT sensor library
 * DHT11的精度較差，需要準度較高，請購買DHT22
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */
#include "DHT.h"

#define DHTPIN 25
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22
//#define DHTTYPE DHT21   // DHT 21

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(115200);
  dht.begin();
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
}
