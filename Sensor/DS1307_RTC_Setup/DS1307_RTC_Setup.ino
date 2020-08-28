/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Sensor RTC_Setup(DS1307)
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 * 
 * DS1307本身不接受5V，但是可以硬改，改成3.3V
 * 把板子上的R2,R3電阻拆掉即可使用3.3V
 * 
 * 此為設定時間的程式，如要查詢時間，請使用DS1307_RTC
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

const char *monthName[12] = 
{
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

void setup() 
{
  Wire.begin(17,16);
  bool parse  = false;
  bool config = false;

  //取得編譯器(Arduino)的時間
  if (getDate(__DATE__) && getTime(__TIME__)) 
  {
    parse = true;
    if (RTC.write(tm)) 
    {
      config = true;
    }
  }

  Serial.begin(115200);
  while (!Serial); // wait for Arduino Serial Monitor
  delay(200);
  if (parse && config) 
  {
    Serial.print("設定時間為=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } 
  else if (parse) 
  {
    Serial.println("DS1307 通訊錯誤，請檢查線路");
  } 
  else 
  {
    Serial.print("無法解析編譯器(Arduino)的訊息, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
}

void loop() {}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) 
  {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}
