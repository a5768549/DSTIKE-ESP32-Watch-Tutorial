/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Sensor RTC(DS1307)
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 * 
 * DS1307本身不接受5V，但是可以硬改，改成3.3V
 * 把板子上的R2,R3電阻拆掉即可使用3.3V
 * 
 * TimeLib：https://github.com/PaulStoffregen/Time
 * 
 * DS1307RTC：https://github.com/a5768549/DS1307RTC
 * 
 * DSKIKE Watch 腳位
 * *3.3V 25 SVP *16 RX
 * *GND  26 SVN *17 TX
 */
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

void setup() 
{
  Wire.begin(17,16);//Wire.begin(SDA,SCL)
  Serial.begin(115200);
  
  while (!Serial); //Wait for serial
  delay(200);
}

void loop()
{
  tmElements_t tm;

  if (RTC.read(tm)) 
  {
    Serial.print("讀取成功, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } 
  else 
  {
    if (RTC.chipPresent()) 
    {
      Serial.println("晶片尚未初始化，請先使用DS1307_RTC_Setup設定時間");
      Serial.println();
    } else 
    {
      Serial.println("DS1307讀取錯誤，請檢查線路是否正確");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void print2digits(int number) 
{
  if (number >= 0 && number < 10) 
  {
    Serial.write('0');
  }
  Serial.print(number);
}
