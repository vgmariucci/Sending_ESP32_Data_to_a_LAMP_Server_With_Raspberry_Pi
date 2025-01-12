// Write the sensor readings on the SD card
void logSDCard() {

 reading_time = getDS3231DateTime();

 if(WiFi.status() == WL_CONNECTED){
      sendDataViaHTTPPost();
      wifiStatus = 1;
  }
  else{
    Serial.println("Failed to send data to server: Wifi Disconnected");
    wifiStatus = 0;
  }

 dataMessage = reading_time + 
               ";" + 
               location + 
               ";" + 
               String(temperature) + 
               ";" + 
               String(humidity) + 
               ";" +
               String(wifiStatus) +
               "\r\n";
 

  appendFile(SD, "/data.txt", dataMessage.c_str());


  Serial.println("Saving into the SD Card the following data: ");
  Serial.println(dataMessage);

  
}


// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);
  
  File file = fs.open(path, FILE_WRITE);
   
  
  if(!file) {
    Serial.println("Failed to open file for writing");
    // clear display
    display.clearDisplay(); 
    // display temperature
    display.setTextSize(1);
    display.setCursor(0,20);
    display.print("Failed to open");
    display.setCursor(0,50);
    display.print("file for writing");
    display.display();
    delay(2000);
 
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
    // clear display
   display.clearDisplay(); 
   // display temperature
   display.setTextSize(1);
   display.setCursor(0,20);
   display.print("Failed while recording");
   display.setCursor(0,50);
   display.print("the file...");
   display.display();
   delay(2000);
 
  }
  file.close();
}

// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.println("******************************");
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);

  
  if(!file) {
    Serial.println("******************************");
    Serial.println("Failed to open file for appending");
    // clear display
    display.clearDisplay(); 
    // display temperature
    display.setTextSize(1);
    display.setCursor(0,10);
    display.print("Failed while opening");
    display.setCursor(0,30);
    display.print("the file data.txt");
    display.setCursor(0,50);
    display.print("to include readings");
    display.display();
    delay(2000);
 
    return;
  }
  if(file.print(message)) {
    Serial.println("******************************");
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
     // clear display
   display.clearDisplay(); 
   // display temperature
   display.setTextSize(1);
   display.setCursor(0,10);
   display.print("Failed while including readings");
   display.setCursor(0,40);
   display.print("into the file data.txt");
   display.display();
   delay(2000);
  }
  file.close();
}
