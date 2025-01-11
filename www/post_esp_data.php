<?php

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Include the php script responsible to insert and read esp32 data into the database
include_once('esp_insert_and_get_data_into_from_database.php');

require 'vendor/autoload.php'; // Load Composer dependencies

// Load the .env file
$dotenv = Dotenv\Dotenv::createImmutable(__DIR__);
$dotenv->load();

$api_key_value = $_ENV['RASP_API_KEY'];

$api_key = "";
$reading_time = "";
$location = "";
$temperature = "";
$humidity = "";
$wifi_status = "";


// Process the POST request as usual

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    
    if($api_key == $api_key_value) {
        $reading_time = test_input($_POST["reading_time"]);
        $location = test_input($_POST["location"]);
        $temperature = test_input($_POST["temperature"]);
        $humidity = test_input($_POST["humidity"]);
        $wifi_status = test_input($_POST["wifi_status"]);
        
        $result = insertReading(
            $reading_time,
            $location,
            $temperature,
            $humidity,
            $wifi_status
        );
         
        echo $result;
    }
    else{
        echo "Wrong API Key provided.";
    }
}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
