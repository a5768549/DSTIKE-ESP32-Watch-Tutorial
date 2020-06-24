/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 6 SD_Card
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */
 
/*
 * ***Notice***
 * DSTIKE ESP32 Watch's SD Card Library need use SD_MMC.h
 * The SD card must be removed before uploading the code.
 * ***Notice***
 * 
 * Connect the SD card to the following pins:
 * 
 * SD Card | ESP32
 *    D2       12
 *    D3       13
 *    CMD      15
 *    CLK      14
 *    D0       2  (add 1K pull up after flashing)
 *    D1       4
 */

#include "FS.h"
#include "SD_MMC.h"
#include "SD_Control.h"

void setup()
{
  Serial.begin(115200);
  delay(5000);
  if(!SD_MMC.begin())
  {
      Serial.println("Card Mount Failed");
      return;
  }
  uint8_t cardType = SD_MMC.cardType();

  if(cardType == CARD_NONE)
  {
      Serial.println("No SD_MMC card attached");
      return;
  }
  Serial.println("Card type is:");
  switch(cardType)
  {
    case CARD_MMC:  Serial.println("MMC");     break;
    case CARD_SD:   Serial.println("SDSC");    break;
    case CARD_SDHC: Serial.println("SDHC");    break;
    default:        Serial.println("UNKNOWN"); break;
  }

  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD_MMC Card Size: %llu MB\n", cardSize);

  createDir (SD_MMC, "/mydir");
  listDir   (SD_MMC, "/", 0);
  writeFile (SD_MMC, "/mydir/hello.txt", "Hello ");
  appendFile(SD_MMC, "/mydir/hello.txt", "World!\n");
  readFile  (SD_MMC, "/mydir/hello.txt");
  
  Serial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
  Serial.printf("Used space : %lluMB\n", SD_MMC.usedBytes()  / (1024 * 1024));
}

void loop()
{

}
