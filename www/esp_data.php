<!DOCTYPE html>
<html><body>
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


echo '<table cellspacing="5" cellpadding="5">
      <tr> 
      <td>ID</td> 
      <td>location</td> 
      <td>reading_time</td> 
        <td>temperature</td> 
        <td>humidity</td>
        <td>wifi_status</td> 
      </tr>';

//Readings limit for SQL query
$limit = 100;

if ($result = getAllReadings($limit)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_location = $row["location"];
        $row_reading_time = $row["reading_time"];
        $row_temperature = $row["temperature"];
        $row_humidity = $row["humidity"];
        $row_wifi_status = $row["wifi_status"]; 

      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_reading_time . '</td> 
                <td>' . $row_temperature . '</td> 
                <td>' . $row_humidity . '</td> 
                <td>' . $row_wifi_status . '</td> 
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</body>
</html>
