void refreshKeyboardReadings() {

  displayBtnStatus = digitalRead(displayBtn);
  wifiBtnStatus = digitalRead(wifiBtn);

  if (!displayBtnStatus && !f_displayBtn) {

    f_displayBtn = 1;

    digitalWrite(led, f_displayBtn);

    if (!displayBtnStatus && f_displayBtn) {
      
        oledState++;
        displayBtnCounter++;
        digitalWrite(led, 1);

        if(oledState > 2){
          oledState = 0;
        }

        if(displayBtnCounter > 3){
            displayBtnCounter = 0;
            digitalWrite(led, 0);
        } 
    }
  } 
  else {
      f_displayBtn = 0;
  }

  if (!wifiBtnStatus && !f_wifiBtn) {

    f_wifiBtn = 1;

    digitalWrite(led, f_wifiBtn);

    if (!wifiBtnStatus && f_wifiBtn) {
      
        //Enalbes the device to AP mode to set the WiFi connection
        AP_mode_status = 1;

        } 
    } 
  else {
      f_wifiBtn = 0;
  }

}