<!DOCTYPE html>
<html><body>
<?php

require 'vendor/autoload.php'; // Load Composer dependencies

// Load the .env file
$dotenv = Dotenv\Dotenv::createImmutable(__DIR__);
$dotenv->load();

$servername = "localhost";
$dbname = $_ENV['DATABASE_NAME'];
$username = $_ENV['DATABASE_USER_NAME'];
$password = $_ENV['DATABASE_PASSWORD'];

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, location, reading_time, freq, v_a, v_b, v_c FROM SensorData ORDER BY id DESC";

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
      <td>ID</td> 
      <td>location</td> 
      <td>reading_time</td> 
        <td>freq</td> 
        <td>v_a</td>
        <td>v_b</td> 
        <td>v_c</td> 
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_location = $row["location"];
        $row_location = $row["reading_time"];
        $row_freq = $row["freq"];
        $row_v_a = $row["v_a"];
        $row_v_b = $row["v_b"]; 
        $row_v_c = $row["v_c"]; 

      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_reading_time . '</td> 
                <td>' . $row_freq . '</td> 
                <td>' . $row_v_a . '</td> 
                <td>' . $row_v_b . '</td>
                <td>' . $row_v_c . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>
