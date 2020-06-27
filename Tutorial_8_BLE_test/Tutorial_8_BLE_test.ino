/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 8 BLE test
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

/*
 * Download Bluetooth Terminal(Qwerty) from Google Play in your phone：
 * https://play.google.com/store/apps/details?id=Qwerty.BluetoothTerminal&hl=zh_TW
 * This APP can receive ESP32 messages(Chinese OK)
 */
#include <BluetoothSerial.h>
BluetoothSerial BT;

void setup() 
{
  Serial.begin(115200);
  //BLE device name
  BT.begin("DSTIKE ESP32 Watch");
}

void loop() 
{
  while (Serial.available()) 
  {
    String Sdata = Serial.readString();
    BT.println("From ESP32:" + Sdata);
  }

  while (BT.available()) 
  {
    String BTdata = BT.readString();
    Serial.println("From phone:" + BTdata);
  }
}
