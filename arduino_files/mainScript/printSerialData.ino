void printSerialData() {

  Serial.println();

  Serial.println("\n*****************************************");
  Serial.println("***** Measured Parameters *****");
  Serial.println("*****************************************\n");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C");
  Serial.print("\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.println();

  
}
