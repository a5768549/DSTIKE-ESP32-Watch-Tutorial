/*
 * DSTIKE ESP32 Watch(DEV-32)
 * Copyright 2020 a5768549
 *
 * Tutorial 6 SD_Card
 * 
 * GitHub Project：https://github.com/a5768549/DSTIKE-ESP32-Watch-Tutorial
 */

/*
 * listDir   (SD_MMC, dirname, levels)
 * createDir (SD_MMC, dirname)
 * removeDir (SD_MMC, dirname)
 * readFile  (SD_MMC, filepath)
 * writeFile (SD_MMC, filepath, message)
 * appendFile(SD_MMC, filepath, message)
 * renameFile(SD_MMC, filepath, filepath)
 * deleteFile(SD_MMC, filepath)
 */
void listDir(fs::FS &fs, const char * dirname, uint8_t levels)
{
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root)
  {
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory())
  {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file)
  {
    if(file.isDirectory())
    {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels)
      {
        listDir(fs, file.name(), levels -1);
      }
    } 
    else 
    {
      Serial.print("  FILE: ");
      Serial.println(file.name());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char * path)
{
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path))
  {
    Serial.println("Dir created");
  } 
  else 
  {
    Serial.println("Dir create failed");
  }
}

void removeDir(fs::FS &fs, const char * path)
{
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path))
  {
    Serial.println("Dir removed");
  }
  else
  {
    Serial.println("Dir remove failed");
  }
}

void readFile(fs::FS &fs, const char * path)
{
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while(file.available())
  {
    Serial.write(file.read());
  }
}

void writeFile(fs::FS &fs, const char * path, const char * message)
{
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file)
  {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message))
  {
    Serial.println("File written");
  }
  else 
  {
    Serial.println("Write failed");
  }
}

void appendFile(fs::FS &fs, const char * path, const char * message)
{
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file)
  {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message))
  {
    Serial.println("Message appended");
  }
  else 
  {
    Serial.println("Message append failed");
  }
}

void renameFile(fs::FS &fs, const char * path1, const char * path2)
{
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) 
  {
    Serial.println("File renamed");
  }
  else 
  {
    Serial.println("Rename failed");
  }
}

void deleteFile(fs::FS &fs, const char * path)
{
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path))
  {
    Serial.println("File deleted");
  } 
  else 
  {
    Serial.println("Delete failed");
  }
}
