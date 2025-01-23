
// Replace with the URL path or Raspberry Pi IP address and the php script responsible to receive ESP32 data
const char serverName[] = "http://your_raspberrypi_IP_address//post_esp_data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post_esp_data.php also needs to have the same key 
String API_KEY = "change_me_for_your_api_key";

      
// IoT device serial number
String  iot_device_serial_number = "device_serial_number";

// Customer identification
String customer_ID = "Customer_ID";