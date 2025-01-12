//********************************* DEFINES *******************************

#define SCREEN_WIDTH 128          // OLED display width, in pixels
#define SCREEN_HEIGHT 64          // OLED display height, in pixels
#define OLED_SD1306_ADDRESS 0x3C  //OLED I2C Address

#define DHTPIN 4                  // Digital pin where data will be received from DHT22
#define DHTTYPE DHT22             // DHT22 (AM2302) temperature and relative himidity sensor.

#define led 2                     // Built-in LED for DOIT ESP32 DEVKIT V1 (used to notify when the ESP32 is set in AP mode to configure the WiFi connection)
#define displayBtn 26             // Button to change the data shown in the Oled display
#define wifiBtn 25                // Button to set WiFi connection for ESP32

#define SD_CS 5                   // Define CS pin for the SD card module

//****************************** INCLUDES ********************************
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <WiFiManager.h>
#include <Wire.h>
#include <SPI.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Libraries for SD card
#include "FS.h"
#include "SD.h"
// Library to deal with time values
#include "time.h"
#include <WiFiUdp.h>
#include <DHT.h>
#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
#include "Secrets.h"        // Hold Authorization Credentias that enables the ESP32 HTTP Post to the MySQL database hosted in a GCP Virtual Machine

//************************** GLOBAL VARIABLES  *****************************
unsigned long previousMillisForDataLogs = 0;
unsigned long previousMillisForOledReresh = 0;
const long intervalBetweenDataLogs = 60000;   // Time interval for each SD Card datalog and HTTP POST to the Raspberry Pi LAMP server
const long intervalBetweenOledRefresh = 5000; // Time interval for data refresh for OLED display and Serial Monitor


// Customer identification
String location = "Customer_ID";

// Variables to store the readings from DHT22 sensor
float temperature;
float humidity;

uint8_t oledState = 0;  // Variable do store the Oled counter

uint8_t displayBtnCounter = 0;  // Variable do store the Oled button counter
bool displayBtnStatus = 0; // Variable to store the button status which increments the Oled counter
bool f_displayBtn = 0;     // Variable flag for debouncing the button which increments the Oled counter

bool wifiBtnStatus = 0;    // Variable to store the button status which starts the Wifi connection setup
bool f_wifiBtn = 0;        // Variable flag for debouncing the button which starts the WiFi connection setup
bool AP_mode_status = 0;   // Variable to flag if the ESP32 is in the Access Point (AP) mode
bool shouldSaveConfig = false; // Variable to flag if it was saved the WiFi setup
unsigned int WIFI_CONNECTION_CHECK_TIMEOUT = 0;
bool wifiStatus = 0;      // Variable to store the statu of the WiFi connection (connected = 1 and disconnected = 0)

// Variable to store te reading time of DHT22 and other parameters
String reading_time;

String dataMessage; // Variable to store the string composed by the measured parameters

// Define the constants to store the configuration for getting NTP data
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -3*3600;
const int   daylightOffset_sec = 3600;

bool setDateTimeDS3231RTCUsingNTPClientFlag = 0;

//***************** OBJECTS INSTANTIANTIONS *************

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Declaration for the instace myRTC for DS3232RTC
DS3232RTC myRTC;

// Declaration for the instance DHT for DHT22
DHT dht(DHTPIN, DHTTYPE);

//******************* SUPPORT FUNCTIONS *************************

void setup(){

  
  pinMode(led, OUTPUT);                                         // Set the ledPin as an output of signal pin
  
  pinMode(displayBtn, INPUT);                                   // Set the displayBtn as an input of signal
  pinMode(wifiBtn, INPUT);                                      // Set the wifiBtn as an input of signal

  Serial.begin(115200);                                         // Set and initialize the serial communication

  startOLEDDisplay();                                           // Starts Oled display

  connectToWifi();                                              // Try to connect to WiFi

  myRTC.begin();                                                // Start the Real Time Clock module RTC DS3231

  startSDCard();                                                // Initialize the SD Card

  dht.begin();                                                  // Initialize DHT22 sensor
}

void loop() {

  refreshKeyboardReadings();                                     // Continuously check if some button was pressed
  
  if(WiFi.status() == WL_CONNECTED){                             // If WiFi connected successfuly, then try to pick the timestamp from an NTP client 
                                                                 // and configure (sincronize) the RTC DS3231 module 
    
    if(!setDateTimeDS3231RTCUsingNTPClientFlag){                 // Test the flag !setDateTimeDS3231RTCUsingNTPClientFlag to certifie the RTC module 
                                                                 // has already been sincronized with NTP client timestamp
        getNTPClientDateTimeAndSetDS3231RTC();                   // If it doesn't, call the funtion to to so.
        setDateTimeDS3231RTCUsingNTPClientFlag = 1;              // Set the flag !setDateTimeDS3231RTCUsingNTPClientFlag to prevent enter in sync mode again.
    }
  }

  if (!displayBtnCounter && (millis() - previousMillisForDataLogs >= intervalBetweenDataLogs)) {
    previousMillisForDataLogs = millis();
    logSDCard();
  }
  if (!displayBtnCounter && (millis() - previousMillisForOledReresh >= previousMillisForOledReresh)) {
    previousMillisForOledReresh = millis();
    readTemperatureAndHumidityFromDHT22();
    displayOledData();
    oledState++;
    if(oledState > 1) oledState = 0;
  }
  
}
