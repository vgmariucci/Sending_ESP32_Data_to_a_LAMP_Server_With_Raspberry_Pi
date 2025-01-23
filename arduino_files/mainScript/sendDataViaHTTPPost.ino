// Function to send all buffered data via HTTP POST
void sendBufferedData() {
    Serial.println("Sending buffered data to Cloud...");

    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    bool allSent = true; 

    for (size_t i = 0; i < httpDataBuffer.size(); i++) {
        Serial.print("Sending buffered request: ");
        Serial.println(httpDataBuffer[i]);

        int httpResponseCode = http.POST(httpDataBuffer[i]);

        if (httpResponseCode > 0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
        } else {
            Serial.print("HTTP request failed. Error code: ");
            Serial.println(httpResponseCode);
            allSent = false; // Mark as not fully sent
            break; // Exit loop to retry later
        }
    }

    http.end(); // Close the connection

    if (allSent) {
        httpDataBuffer.clear(); // Clear buffer only if all requests succeeded
        Serial.println("All buffered data successfully sent!");
    } else {
        Serial.println("Some requests failed. Keeping data in buffer.");
    }
}

// Function to add data to the buffer
void bufferHttpData(){
  // Create the HTTP request data string
  String httpRequestData = "api_key=" + API_KEY + 
                            "&reading_time=" + reading_time + 
                            "&customer_ID=" + customer_ID + 
                            "&iot_device_serial_number=" + iot_device_serial_number + 
                            "&temperature=" + String(temperature) + 
                            "&humidity=" + String(humidity) +
                            "&wifi_status=" + String(wifiStatus);

                                // Add data to the buffer
    httpDataBuffer.push_back(httpRequestData);
    Serial.println("Data added to HTTP buffer.");

    // Check if buffer is full
    if (httpDataBuffer.size() >= BUFFER_SIZE) {
        sendBufferedData();
    }

}
