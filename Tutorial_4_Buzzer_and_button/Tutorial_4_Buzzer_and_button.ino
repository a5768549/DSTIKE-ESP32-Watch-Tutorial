/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 4 Buzzer_and_button
 * 
 * ESP32 Tone Lib：https://github.com/lbernstone/Tone
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

//ESP32 is no built-in tone lib
#include <Tone32.h>

#define Buzzer 32
//Navigation Button
#define Nav_Up     19
#define Nav_Center 18
#define Nav_Down    5

void setup()
{
  Serial.begin(9600);
  pinMode(Nav_Up    , INPUT_PULLUP);
  pinMode(Nav_Center, INPUT_PULLUP);
  pinMode(Nav_Down  , INPUT_PULLUP); //Press = 0
  pinMode(Buzzer    , OUTPUT);
}
 
void loop() 
{
  if(digitalRead(Nav_Up) == LOW)
  {
    tone(Buzzer, NOTE_C4, 250, 0); //Do
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_D4, 250, 0); //Re
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_E4, 250, 0); //Mi
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_F4, 250, 0); //Fa
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_G4, 250, 0); //So
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_A4, 250, 0); //La
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_B4, 250, 0); //Si
    noTone(Buzzer, 0);
  }

  if(digitalRead(Nav_Down) == LOW)
  {
    tone(Buzzer, NOTE_B4, 250, 0); //Si
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_A4, 250, 0); //La
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_G4, 250, 0); //So
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_F4, 250, 0); //Fa
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_E4, 250, 0); //Mi
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_D4, 250, 0); //Re
    noTone(Buzzer, 0);
    tone(Buzzer, NOTE_C4, 250, 0); //Do
    noTone(Buzzer, 0);
  }

  if(digitalRead(Nav_Center) == LOW)
  {
    tone(Buzzer, NOTE_B4, 250, 0); //Si
    noTone(Buzzer, 0);
    delay(500);
    tone(Buzzer, NOTE_B4, 250, 0); //Si
    noTone(Buzzer, 0);
    delay(500);
    tone(Buzzer, NOTE_B4, 250, 0); //Si
    noTone(Buzzer, 0);
  }
}
