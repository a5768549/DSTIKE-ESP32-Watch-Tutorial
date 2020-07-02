/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 9 BLE and android
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

/*
 * BLE test app download：https://reurl.cc/E70eaR
 */
#include <BluetoothSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789.h>

#define TFT_DC    22
#define TFT_RST   23
#define TFT_MOSI  17
#define TFT_SCLK  16

BluetoothSerial BT;
Arduino_ST7789 TFT_Screen = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);

void setup() 
{
  Serial.begin(115200);
  //BLE device name
  BT.begin("DSTIKE ESP32 Watch");

  TFT_Screen.init(240, 240);
  TFT_Screen.setRotation(1);
  Serial.println("Initialized");
  TFT_Screen.fillScreen(BLACK);
}

void loop() 
{
  while (BT.available()) 
  {
    String BTdata = BT.readString();
    Serial.println("From phone:" + BTdata);
    
    TFT_Screen.fillScreen(BLACK);
    TFT_Screen.setCursor(0, 0);
    TFT_Screen.setTextColor(WHITE);
    TFT_Screen.setTextSize(3);
    TFT_Screen.setTextWrap(true);
    TFT_Screen.print(BTdata);
  }
}
