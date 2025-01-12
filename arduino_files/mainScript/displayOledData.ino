void displayOledData() {

  if(!AP_mode_status){

    switch (oledState) {

      case 0:
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(10, 0);
        display.print("Temperature");
        display.setTextSize(2);
        display.setCursor(30, 20);
        display.print(temperature,1);
        display.setCursor(90, 20);
        display.print("C");
        display.display();
        break;

      case 1:
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(10, 0);
        display.print("Humidity");
        display.setTextSize(2);
        display.setCursor(30, 20);
        display.print(humidity,1);
        display.setCursor(90, 20);
        display.print("%");
        display.display();
        break;

      // case 2:

      //   display.clearDisplay();
      //   display.setTextSize(1);
      //   display.setCursor(10, 0);
      //   display.print("P_At_a:");
      //   display.setCursor(80, 0);
      //   display.print(p_ativ_a,1);
      //   display.setCursor(120, 0);
      //   display.print("W");

      //   display.setCursor(10, 20);
      //   display.print("P_At_b:");
      //   display.setCursor(80, 20);
      //   display.print(p_ativ_b,1);
      //   display.setCursor(120, 20);
      //   display.print("W");

      //   display.setCursor(10, 40);
      //   display.print("P_At_c:");
      //   display.setCursor(80, 40);
      //   display.print(p_ativ_c,1);
      //   display.setCursor(120, 40);
      //   display.print("W");   
      //   display.display();   
      //   break;
      
      // case 3:

      //   display.clearDisplay();
      //   display.setTextSize(1);
      //   display.setCursor(10, 0);
      //   display.print("P_Re_a:");
      //   display.setCursor(80, 0);
      //   display.print(p_reac_a,1);
      //   display.setCursor(120, 0);
      //   display.print("W");

      //   display.setCursor(10, 20);
      //   display.print("P_Re_b:");
      //   display.setCursor(80, 20);
      //   display.print(p_reac_b,1);
      //   display.setCursor(120, 20);
      //   display.print("W");

      //   display.setCursor(10, 40);
      //   display.print("P_Re_c:");
      //   display.setCursor(80, 40);
      //   display.print(p_reac_c,1);
      //   display.setCursor(120, 40);
      //   display.print("W");
      //   display.display();     
      //   break;
      
      // case 4:

      //   display.clearDisplay();
      //   display.setTextSize(1);
      //   display.setCursor(10, 0);
      //   display.print("P_Ap_a:");
      //   display.setCursor(80, 0);
      //   display.print(p_apar_a,1);
      //   display.setCursor(120, 0);
      //   display.print("W");

      //   display.setCursor(10, 20);
      //   display.print("P_Ap_b:");
      //   display.setCursor(80, 20);
      //   display.print(p_apar_b,1);
      //   display.setCursor(120, 20);
      //   display.print("W");

      //   display.setCursor(10, 40);
      //   display.print("P_Ap_c:");
      //   display.setCursor(80, 40);
      //   display.print(p_apar_c,1);
      //   display.setCursor(120, 40);
      //   display.print("W");
      //   display.display();   
      //   break;
      
      // case 5:

      //   display.clearDisplay();
      //   display.setTextSize(1);
      //   display.setCursor(10, 0);
      //   display.print("FP_a:");
      //   display.setCursor(80, 0);
      //   display.print(fp_a,1);
      //   display.setCursor(120, 0);
      //   display.print("%");

      //   display.setCursor(10, 20);
      //   display.print("FP_b:");
      //   display.setCursor(80, 20);
      //   display.print(fp_b,1);
      //   display.setCursor(120, 20);
      //   display.print("%");

      //   display.setCursor(10, 40);
      //   display.print("FP_c:");
      //   display.setCursor(80, 40);
      //   display.print(fp_c,1);
      //   display.setCursor(120, 40);
      //   display.print("%");
      //   display.display();   
      //   break;

      // case 6:
      //   display.clearDisplay();
      //   display.setTextSize(2);
      //   display.setCursor(0, 0);
      //   display.print("Freq");
      //   display.setCursor(25, 30);
      //   display.print(frequencia, 2);
      //   display.setCursor(100, 30);
      //   display.print("Hz");
      //   display.display();
      //   break;
      
      // case 7:
      //   display.clearDisplay();
      //   display.setTextSize(2);
      //   display.setCursor(0, 0);
      //   display.print("P_At_Total");
      //   display.setCursor(25, 30);
      //   display.print(p_ativ_total, 2);
      //   display.setCursor(100, 30);
      //   display.print("W");
      //   display.display();
      //   break;
      
      // case 8:
      //   display.clearDisplay();
      //   display.setTextSize(2);
      //   display.setCursor(0, 0);
      //   display.print("P_Re_Total");
      //   display.setCursor(25, 30);
      //   display.print(p_reac_total, 2);
      //   display.setCursor(100, 30);
      //   display.print("W");
      //   display.display();
      //   break;
      
      // case 9:
      //   display.clearDisplay();
      //   display.setTextSize(2);
      //   display.setCursor(0, 0);
      //   display.print("P_Ap_Total");
      //   display.setCursor(25, 30);
      //   display.print(p_apar_total, 2);
      //   display.setCursor(100, 30);
      //   display.print("W");
      //   display.display();
      //   break;
      
      // case 10:
      //   display.clearDisplay();
      //   display.setTextSize(2);
      //   display.setCursor(0, 0);
      //   display.print("FP_Total");
      //   display.setCursor(25, 30);
      //   display.print(fp_total, 2);
      //   display.setCursor(100, 30);
      //   display.print("%");
      //   display.display();
      //   break;
      
      // case 11:
      //   display.clearDisplay();
      //   display.setTextSize(1);
      //   display.setCursor(0, 0);
      //   display.print("Energia Ativa");
      //   display.setTextSize(2);
      //   display.setCursor(90, 10);
      //   display.print("kWh");
      //   display.setTextSize(1);
      //   display.setCursor(0, 15);
      //   display.print("D");
      //   display.setTextSize(2);
      //   display.setCursor(10, 25);
      //   display.print(e_ativ_dir,0);
      //   display.setTextSize(1);
      //   display.setCursor(0, 40);
      //   display.print("R");
      //   display.setTextSize(2);
      //   display.setCursor(10, 50);
      //   display.print(e_ativ_rev,0);
      //   display.display();   
      //   break;

      // case 12:
        // display.clearDisplay();
        // display.setTextSize(1);
        // display.setCursor(0, 0);
        // display.print("Energia Reativa");
        // display.setTextSize(2);
        // display.setCursor(90, 10);
        // display.print("kWh");
        // display.setTextSize(1);
        // display.setCursor(0, 15);
        // display.print("D");
        // display.setTextSize(2);
        // display.setCursor(10, 25);
        // display.print(e_ativ_dir,0);
        // display.setTextSize(1);
        // display.setCursor(0, 40);
        // display.print("R");
        // display.setTextSize(2);
        // display.setCursor(10, 50);
        // display.print(e_ativ_rev,0);
        // display.display();   
        // break;

      default:
        break;
    }
  }
  else{
      display.clearDisplay();
      
      display.setTextSize(1);
      display.setCursor(0,0);
      display.print("SET");
      display.setCursor(100,0);
      display.print("WiFi");

      display.setCursor(30,20);
      display.print("CONNECT WITH");
      display.setCursor(30,40);
      display.print("192.168.4.1");  

      display.display();
      configure_WiFi();
      if(WiFi.status() == WL_CONNECTED){
          AP_mode_status = 0;
          digitalWrite(led, 0);
      }
  }
}
