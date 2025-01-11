<!--
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/cloud-weather-station-esp32-esp8266/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
-->
<?php
    // Include the php script responsible to insert and read esp32 data into the database
    include_once('esp_insert_and_get_data_into_from_database.php');
    
    if (isset($_GET["readingsCount"])){
      $data = $_GET["readingsCount"];
      $data = trim($data);
      $data = stripslashes($data);
      $data = htmlspecialchars($data);
      $readings_count = $_GET["readingsCount"];
    }
    // default readings count set to 20
    else {
      $readings_count = 20;
    }

    $last_reading = getLastReadings();
    $last_reading_temperature = $last_reading["temperature"];
    $last_reading_humidity = $last_reading["humidity"];
    $last_reading_time = $last_reading["reading_time"];

    $min_temperature = minReading($readings_count, 'temperature');
    $max_temperature = maxReading($readings_count, 'temperature');
    $avg_temperature = avgReading($readings_count, 'temperature');

    $min_humidity = minReading($readings_count, 'humidity');
    $max_humidity = maxReading($readings_count, 'humidity');
    $avg_humidity = avgReading($readings_count, 'humidity');
?>

<!DOCTYPE html>
<html>
    <head><meta http-equiv="Content-Type" content="text/html; charset=utf-8">

        <link rel="stylesheet" type="text/css" href="esp_style.css">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    </head>
    <header class="header">
        <h1>📊 Some IoT Monitoring Corporation</h1>
        <form method="get">
            <input type="number" name="readingsCount" min="5" placeholder="Number of readings (<?php echo $readings_count; ?>)">
            <input type="submit" value="UPDATE">
        </form>
    </header>
<body>
    <p>Last reading: <?php echo $last_reading_time; ?></p>
    <section class="content">
	    <div class="box gauge--1">
	    <h3>temperature</h3>
              <div class="mask">
			  <div class="semi-circle"></div>
			  <div class="semi-circle--mask"></div>
			</div>
		    <p style="font-size: 30px;" id="temperature"><?php echo $last_reading_temperature; ?></p>
		    <table cellspacing="5" cellpadding="5">
		        <tr>
		            <th colspan="3"> temperature <?php echo $readings_count; ?> readings</th>
	            </tr>
		        <tr>
		            <td>Min</td>
                    <td>Max</td>
                    <td>Average</td>
                </tr>
                <tr>
                    <td><?php echo $min_temperature['min_amount']; ?> ºC</td>
                    <td><?php echo $max_temperature['max_amount']; ?> ºC</td>
                    <td><?php echo round($avg_temperature['avg_amount'], 2); ?> ºC</td>
                </tr>
            </table>
        </div>
        <div class="box gauge--2">
            <h3>humidity</h3>
            <div class="mask">
                <div class="semi-circle"></div>
                <div class="semi-circle--mask"></div>
            </div>
            <p style="font-size: 30px;" id="humidity"><?php echo $last_reading_humidity; ?></p>
            <table cellspacing="5" cellpadding="5">
                <tr>
                    <th colspan="3">humidity <?php echo $readings_count; ?> readings</th>
                </tr>
                <tr>
                    <td>Min</td>
                    <td>Max</td>
                    <td>Average</td>
                </tr>
                <tr>
                    <td><?php echo $min_humidity['min_amount']; ?> %</td>
                    <td><?php echo $max_humidity['max_amount']; ?> %</td>
                    <td><?php echo round($avg_humidity['avg_amount'], 2); ?> %</td>
                </tr>
            </table>
        </div>
    </section>
<?php
    echo   '<h2> View Latest ' . $readings_count . ' Readings</h2>
            <table cellspacing="5" cellpadding="5" id="tableReadings">
                <tr>
                    <th>id</th>
                    <th>location</th>
                    <th>temperature</th>
                    <th>humidity</th>
                    <th>reading_time</th>
                </tr>';

    $result = getAllReadings($readings_count);
        if ($result) {
        while ($row = $result->fetch_assoc()) {
            $row_id = $row["id"];
            $row_location = $row["location"];
            $row_temperature = $row["temperature"];
            $row_humidity = $row["humidity"];
            $row_reading_time = $row["reading_time"];

            echo '<tr>
                    <td>' . $row_id . '</td>
                    <td>' . $row_location . '</td>
                    <td>' . $row_temperature . '</td>
                    <td>' . $row_humidity . '</td>
                    <td>' . $row_reading_time . '</td>
                  </tr>';
        }
        echo '</table>';
        $result->free();
    }
?>

<script>
    var temperature = <?php echo $last_reading_temperature; ?>;
    var humidity = <?php echo $last_reading_humidity; ?>;
    set_temperature(temperature);
    set_humidity(humidity);

    function set_temperature((curVal){
    	//set range for temperature in Celsius from 0 to 100
    	var mintemperature = 0.0;
    	var maxtemperature = 100.0;


    	var newVal = scaleValue(curVal, [mintemperature, maxtemperature], [0, 180]);
    	$('.gauge--1 .semi-circle--mask').attr({
    		style: '-webkit-transform: rotate(' + newVal + 'deg);' +
    		'-moz-transform: rotate(' + newVal + 'deg);' +
    		'transform: rotate(' + newVal + 'deg);'
    	});
    	$("#temperature").text(curVal + ' ºC');
    }

    function set_humidity(curVal){
    	//set range for humiditydity percentage 0 % to 100 %
    	var minhumidity = 0;
    	var maxhumidity = 100;

    	var newVal = scaleValue(curVal, [minhumidity, maxhumidity], [0, 180]);
    	$('.gauge--2 .semi-circle--mask').attr({
    		style: '-webkit-transform: rotate(' + newVal + 'deg);' +
    		'-moz-transform: rotate(' + newVal + 'deg);' +
    		'transform: rotate(' + newVal + 'deg);'
    	});
    	$("#humidity").text(curVal + ' %');
    }

    function scaleValue(value, from, to) {
        var scale = (to[1] - to[0]) / (from[1] - from[0]);
        var capped = Math.min(from[1], Math.max(from[0], value)) - from[0];
        return ~~(capped * scale + to[0]);
    }
</script>
</body>
</html>
