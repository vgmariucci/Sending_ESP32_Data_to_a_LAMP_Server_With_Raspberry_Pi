<?php

require 'vendor/autoload.php'; // Load Composer dependencies

// Load the .env file
$dotenv = Dotenv\Dotenv::createImmutable(__DIR__);
$dotenv->load();

$servername = "localhost";
$dbname = $_ENV['DATABASE_NAME'];
$username = $_ENV['DATABASE_USER_NAME'];
$password = $_ENV['DATABASE_PASSWORD'];
$api_key_value = $_ENV['API_KEY'];

$api_key = $reading_time = $freq = $v_a = $v_b = $v_c = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $reading_time = test_input($_POST["reading_time"]);
        $freq = test_input($_POST["freq"]);
        $v_a = test_input($_POST["v_a"]);
        $v_b = test_input($_POST["v_b"]);
        $v_c = test_input($_POST["v_c"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO SensorData (reading_time, freq, v_a, v_b, v_c)
        VALUES (
            '" . $reading_time . "', 
            '" . $freq . "', 
            '" . $v_a . "', 
            '" . $v_b . "', 
            '" . $v_c . "'
            )";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
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
