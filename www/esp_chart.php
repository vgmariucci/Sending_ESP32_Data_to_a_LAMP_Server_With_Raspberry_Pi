<?php

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

*/

// Include the php script responsible to insert and read esp32 data into the database
include_once('esp_insert_and_get_data_into_from_database.php');

$result = getAllReadings(100);

while ($data = $result->fetch_assoc()){
    $sensor_data[] = $data;
}

$readings_time = array_column($sensor_data, 'reading_time');

$reading_time = json_encode(array_reverse($readings_time), JSON_NUMERIC_CHECK);
$temperature = json_encode(array_reverse(array_column($sensor_data, 'temperature')), JSON_NUMERIC_CHECK);
$humidity = json_encode(array_reverse(array_column($sensor_data, 'humidity')), JSON_NUMERIC_CHECK);

$result->free();
?>

<!DOCTYPE html>
<html>
<meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <style>
    body {
      min-width: 310px;
    	max-width: 1280px;
    	height: 500px;
      margin: 0 auto;
    }
    h2 {
      font-family: Arial;
      font-size: 2.5rem;
      text-align: center;
    }
  </style>
  <body>
    <h2>DHT22 TEMPERATURE AND HUMIDITY</h2>
    <div id="chart_temperature" class="container"></div>
    <div id="chart_humidity" class="container"></div>
<script>

var reading_time = <?php echo $reading_time; ?>;
var temperature = <?php echo $temperature; ?>;
var humidity = <?php echo $humidity; ?>;

var chartTemperature = new Highcharts.Chart({
  chart:{ renderTo : 'chart_temperature' },
  title: { text: 'DHT22 Temperature' },
  series: [{
    showInLegend: false,
    data: temperature
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    },
    series: { color: '#059e8a' }
  },
  xAxis: { 
    type: 'datetime',
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Temperature (ºC)' }
  },
  credits: { enabled: false }
});

var chart_humidity = new Highcharts.Chart({
  chart:{ renderTo:'chart_humidity' },
  title: { text: 'DHT22 Humidity' },
  series: [{
    showInLegend: false,
    data: humidity
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: true }
    }
  },
  xAxis: {
    type: 'datetime',
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Relative Humidity (%)' }
  },
  credits: { enabled: false }
});

</script>
</body>
</html>
