/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * sensor uv
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 * 
 */

#define uv_sensor 25
void setup() 
{
  Serial.begin(115200);
  pinMode(uv_sensor,INPUT);
}

void loop()
{
  int value = analogRead(uv_sensor);
  int uv_level;
  switch(value)
  {
    case 0   ... 227:uv_level = 0;break;
    case 228 ... 317:uv_level = 1;break;
    case 318 ... 407:uv_level = 2;break;
    case 408 ... 502:uv_level = 3;break;
    case 503 ... 605:uv_level = 4;break;
    case 606 ... 695:uv_level = 5;break;
    case 696 ... 794:uv_level = 6;break;
    case 795 ... 880:uv_level = 7;break;
    case 881 ... 975:uv_level = 8;break;
    case 976 ... 1078:uv_level = 9;break;
    case 1079 ... 1169:uv_level = 10;break;
    default:uv_level = 11;break;
  }
  Serial.print("原始數值：");
  Serial.print(value);
  Serial.print("，紫外線等級：");
  Serial.println(uv_level);
  delay(1000);
}
