/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Sensor SPO2(MAX30105)
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 * 
 * 血氧手腕心率脈搏檢測心跳感測器
 * MAX30105可以吃3.3V，但是官方建議使用5V
 * 建議把感測器跟手指用橡皮筋或繩子綁起來，避免用錯誤的力道觸碰感測器
 * 
 * 靜脈的血氧飽和度為75%正常
 * 動脈的血氧飽和度為98%正常
 * MAX30105 library：https://github.com/sparkfun/MAX30105_Particle_Sensor_Breakout
 * 
 * DSKIKE Watch 腳位
 * *3.3V 25 SVP *16 RX
 * *GND  26 SVN *17 TX
 */
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"

//ESP32 is no built-in tone lib

MAX30105 particleSensor;

#define MAX_BRIGHTNESS 255

uint32_t irBuffer[100];
uint32_t redBuffer[100];

int32_t bufferLength;   //data length
int32_t spo2;           //SPO2 value
int8_t  validSPO2;      //this is a flag
int32_t heartRate;      //heart rate value
int8_t  validHeartRate; //this is a flag

void setup()
{
  Wire.begin(17,16);    //Wire.begin(SDA,SCL)
  Serial.begin(115200);

  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false)//I2C_SPEED_FAST = 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  Serial.println("將手指放在晶片上，輸入任何鍵開始");
  while (Serial.available() == 0) ; //wait until user presses a key
  Serial.read();

  byte ledBrightness = 60;   //Options: 0=Off to 255=50mA
  byte sampleAverage = 4;    //Options: 1, 2, 4, 8, 16, 32
  byte ledMode       = 2;    //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate    = 100;  //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int  pulseWidth    = 411;  //Options: 69, 118, 215, 411
  int  adcRange      = 4096; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
}
 
void loop() 
{
  bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps

  //read the first 100 samples, and determine the signal range
  for (byte i = 0 ; i < bufferLength ; i++)
  {
    while (particleSensor.available() == false)
    {
      particleSensor.check();
    }

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample(); //We're finished with this sample so move to next sample

    Serial.print(F("red="));
    Serial.print(redBuffer[i], DEC);
    Serial.print(F(", ir="));
    Serial.println(irBuffer[i], DEC);
  }
  
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  
  while (1)
  {
    //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
    for (byte i = 25; i < 100; i++)
    {
      redBuffer[i - 25] = redBuffer[i];
      irBuffer [i - 25] = irBuffer[i];
    }

    //take 25 sets of samples before calculating the heart rate.
    for (byte i = 75; i < 100; i++)
    {
      while (particleSensor.available() == false)
      {
        particleSensor.check();
      }

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample();

      Serial.print(F("red="));
      Serial.print(redBuffer[i], DEC);
      Serial.print(F(", ir="));
      Serial.print(irBuffer[i], DEC);

      Serial.print(F(", HR="));
      Serial.print(heartRate, DEC);

      Serial.print(F(", HRvalid="));
      Serial.print(validHeartRate, DEC);

      Serial.print(F(", SPO2="));
      Serial.print(spo2, DEC);

      Serial.print(F(", SPO2Valid="));
      Serial.println(validSPO2, DEC);
    }

    //After gathering 25 new samples recalculate HR and SP02
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  }
}
