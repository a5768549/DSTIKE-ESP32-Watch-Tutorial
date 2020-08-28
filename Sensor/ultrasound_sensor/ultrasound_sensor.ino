/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Sensor ultrasound(HC-SR04 3V-5V)
 * 
 * ESP32 Tone Lib：https://github.com/lbernstone/Tone
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 * 
 * 感測器必須買可以吃3.3V的，新版HC-SR04就OK
 * 
 * DSKIKE Watch 腳位
 * *3.3V *25 SVP 16 RX
 * *GND  *26 SVN 17 TX
 */
#include <Ultrasonic.h>

//ESP32 is no built-in tone lib
#include <Tone32.h>

#define Buzzer 32

Ultrasonic ultrasonic(25, 26); //ultrasonic(Trig,Echo)
int distance;

void setup()
{
  Serial.begin(115200);
  pinMode(Buzzer, OUTPUT);
}
 
void loop() 
{
  distance = ultrasonic.read();
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);

  if(distance <= 20)
  {
    tone(Buzzer, NOTE_B4, 500, 0);
    noTone(Buzzer, 0);
  }
}
