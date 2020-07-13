/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 10 timer
 * 
 * ESP32 Tone Lib：https://github.com/lbernstone/Tone
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

#include <Tone32.h>

#define Buzzer 32
/*創建硬件定時器*/ 
hw_timer_t * timer = NULL ;
int count = 0;
void IRAM_ATTR onTimer ()
{
  //一秒+1
  count += 1;
  Serial.println(count);
}
 
void setup () 
{
  Serial.begin(115200);
  /* 1/(80MHZ/80) = 1us */ 
  timer = timerBegin(0 , 80 , true);
 
  /*將onTimer函數附加到我們的計時器*/ 
  timerAttachInterrupt(timer, &onTimer, true);
 
  /* *設置鬧鐘每秒調用onTimer函數1 tick為1us => 1秒為1000000us * / 
  / *重複鬧鐘（第三個參數）*/
  timerAlarmWrite(timer, 1000000 , true);
  timerAlarmEnable(timer);
}
 
void loop ()   
{
    
}
