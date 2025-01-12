void sendDataViaHTTPPost(){
    Serial.println("Post data to the Rasp...");
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Set Basic Authentication header
    // http.setAuthorization(RASP_USER_NAME, RASP_PASSWORD);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + API_KEY + 
                             "&reading_time=" + reading_time + 
                             "&location=" + location + 
                             "&temperature=" + String(temperature) + 
                             "&humidity=" + String(humidity) +
                             "&wifi_status=" + String(wifiStatus) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
               
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
}