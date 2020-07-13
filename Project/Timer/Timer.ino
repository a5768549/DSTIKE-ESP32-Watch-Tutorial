/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Project Timer
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

/*
 * Nav_Up = minute + 1
 * Nav_Down = minute - 1
 * Nav_Center = timer start
 */

#include <Adafruit_GFX.h>
#include <Arduino_ST7789.h> 
#include <SPI.h>

#define TFT_DC    22
#define TFT_RST   23
#define TFT_MOSI  17
#define TFT_SCLK  16

//Navigation Button
#define Nav_Up     19
#define Nav_Center 18
#define Nav_Down    5

Arduino_ST7789 TFT_Screen = Arduino_ST7789(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK);

/*創建硬件定時器*/ 
hw_timer_t * timer = NULL ;
 
int minute_num = 0;
int second_num = 0;

void IRAM_ATTR onTimer ()
{
  TFT_Screen.fillRect(80 ,110 ,87 ,110 ,BLACK);
  TFT_Screen.setCursor(80, 110);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(3);
  TFT_Screen.setTextWrap(true);
  if(second_num == 0)
  {
    if(minute_num == 0)
    {
      Serial.println("done");
      timerAlarmDisable(timer);
    }
    else
    {
      minute_num -= 1;
      second_num = 59;
    }
  }
  else
  {
    second_num -= 1;
  }
  
  if(minute_num < 10)TFT_Screen.print("0");
  TFT_Screen.print(minute_num);
  TFT_Screen.print(":");
  if(second_num < 10)TFT_Screen.print("0");
  TFT_Screen.print(second_num);
}
 
void setup () 
{
  Serial.begin(115200);
  pinMode(Nav_Up    , INPUT_PULLUP);
  pinMode(Nav_Center, INPUT_PULLUP);
  pinMode(Nav_Down  , INPUT_PULLUP); //Press = 0

  TFT_Screen.init(240, 240);
  TFT_Screen.setRotation(1);
  Serial.println("Initialized");

  TFT_Screen.fillScreen(BLACK);
  TFT_Screen.setCursor(80, 110);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(3);
  TFT_Screen.setTextWrap(true);
  TFT_Screen.print("INIT");

  
  /* 1/(80MHZ/80) = 1us */ 
  timer = timerBegin(0 , 80 , true);
 
  /*將onTimer函數附加到我們的計時器*/ 
  timerAttachInterrupt(timer, &onTimer, true);
 
  /* *設置鬧鐘每秒調用onTimer函數1 tick為1us => 1秒為1000000us * / 
  / *重複鬧鐘（第三個參數）*/
  timerAlarmWrite(timer, 1000000 , true);

  TFT_Screen.fillScreen(BLACK);
  //TFT_Screen.fillRect(25 ,110 ,190 ,110 ,BLACK);
  TFT_Screen.setCursor(80, 110);
  TFT_Screen.setTextColor(WHITE);
  TFT_Screen.setTextSize(3);
  TFT_Screen.setTextWrap(true);
  TFT_Screen.print("00:00");
}
 
void loop ()   
{
  if(digitalRead(Nav_Center) == LOW)
  {
    /* 啟動警報*/
    timerAlarmEnable(timer);
    Serial.println("start timer");
  }

  if(digitalRead(Nav_Up) == LOW)
  {
    if(minute_num < 99)
    {
      minute_num += 1;
    }
    TFT_Screen.fillRect(80 ,110 ,87 ,110 ,BLACK);
    TFT_Screen.setCursor(80, 110);
    TFT_Screen.setTextColor(WHITE);
    TFT_Screen.setTextSize(3);
    TFT_Screen.setTextWrap(true);
    if(minute_num < 10)TFT_Screen.print("0");
    TFT_Screen.print(minute_num);
    TFT_Screen.print(":00");
    delay(50);
  }

  if(digitalRead(Nav_Down) == LOW)
  {
    if(minute_num > 0)
    {
      minute_num -= 1;
    }
    TFT_Screen.fillRect(80 ,110 ,87 ,110 ,BLACK);
    TFT_Screen.setCursor(80, 110);
    TFT_Screen.setTextColor(WHITE);
    TFT_Screen.setTextSize(3);
    TFT_Screen.setTextWrap(true);
    if(minute_num < 10)TFT_Screen.print("0");
    TFT_Screen.print(minute_num);
    TFT_Screen.print(":00");
    delay(50);
  }
  
}
