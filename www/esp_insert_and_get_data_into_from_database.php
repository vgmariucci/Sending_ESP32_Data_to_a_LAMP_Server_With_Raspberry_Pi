<!--
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/cloud-weather-station-esp32-esp8266/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
-->
<?php
require 'vendor/autoload.php'; // Load Composer dependencies

// Load the .env file
$dotenv = Dotenv\Dotenv::createImmutable(__DIR__);
$dotenv->load();

$servername = "localhost";
$username = $_ENV['RASP_DATABASE_USER_NAME'];
$password = $_ENV['RASP_DATABASE_PASSWORD'];
$dbname = $_ENV['RASP_DATABASE_NAME_ESP32_AND_DHT22'];
$table = $_ENV['TABLE_NAME_ESP32_AND_DHT22'];

  function insertReading(
            $reading_time,
            $customer_ID,
            $iot_device_serial_number,
            $temperature,
            $humidity,
            $wifi_status
            )
            {
            
            global $servername, $username, $password, $dbname, $table;

            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
              }

              $sql = "INSERT INTO $table(
                  reading_time,
                  customer_ID,
                  iot_device_serial_number, 
                  temperature, 
                  humidity, 
                  wifi_status
                  )
              VALUES (
                  '" . $reading_time . "', 
                  '" . $customer_ID . "', 
                  '" . $iot_device_serial_number . "', 
                  '" . $temperature . "', 
                  '" . $humidity . "', 
                  '" . $wifi_status . "'
                  )";
            if ($conn->query($sql) === TRUE) {
              return "New record created successfully";
            }
            else {
              return "Error: " . $sql . "<br>" . $conn->error;
            }
            $conn->close();
    }
  
  function getAllReadings($limit) {
    
    global $servername, $username, $password, $dbname, $table;

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT id, reading_time, customer_ID, iot_device_serial_number, temperature, humidity, wifi_status FROM " . $table . " ORDER BY  reading_time DESC LIMIT " . $limit;
    if ($result = $conn->query($sql)) {
      return $result;
    }
    else {
      return false;
    }
    $conn->close();
  }
  function getLastReadings() {
    global $servername, $username, $password, $dbname, $table;

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT id, reading_time, customer_ID, iot_device_serial_number, temperature, humidity, wifi_status FROM " . $table . " ORDER BY reading_time DESC LIMIT 1";
    if ($result = $conn->query($sql)) {
      return $result->fetch_assoc();
    }
    else {
      return false;
    }
    $conn->close();
  }

  function minReading($limit, $value) {
     global $servername, $username, $password, $dbname, $table;

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT MIN(" . $value . ") AS min_amount FROM (SELECT " . $value . " FROM " . $table . " ORDER BY reading_time DESC LIMIT " . $limit . ") AS min";
    if ($result = $conn->query($sql)) {
      return $result->fetch_assoc();
    }
    else {
      return false;
    }
    $conn->close();
  }

  function maxReading($limit, $value) {
     global $servername, $username, $password, $dbname, $table;

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT MAX(" . $value . ") AS max_amount FROM (SELECT " . $value . " FROM " . $table . " ORDER BY reading_time DESC LIMIT " . $limit . ") AS max";
    if ($result = $conn->query($sql)) {
      return $result->fetch_assoc();
    }
    else {
      return false;
    }
    $conn->close();
  }

  function avgReading($limit, $value) {
     global $servername, $username, $password, $dbname, $table;

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT AVG(" . $value . ") AS avg_amount FROM (SELECT " . $value . " FROM " . $table . " ORDER BY reading_time DESC LIMIT " . $limit . ") AS avg";
    if ($result = $conn->query($sql)) {
      return $result->fetch_assoc();
    }
    else {
      return false;
    }
    $conn->close();
  }
?>
