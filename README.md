# SENDING ESP32 DATA TO A LAMP SERVER WITH RASPBERRY PI

## Under Construction...

## Description

This repo was a practice experiment based on the awesome material presented by [Random Nerd Tutorials](https://randomnerdtutorials.com/esp32-esp8266-raspberry-pi-lamp-server/)

After setting up a LAMP server using a Raspberry Pi as shown in [this tutorial](https://randomnerdtutorials.com/raspberry-pi-apache-mysql-php-lamp-server/) and also reviewed [here](https://github.com/vgmariucci/Setting_Up_LAMP_Server_With_Raspberry_Pi), we can build some **php** scripts/APIs to receive data from an ESP32 using **HTTP** protocol and **POST** method

## Requirements and Modifications to test this Repo

1- ESP32 WROOM developer board (DOIT ESP32 DEVKIT V1)

2- Raspberry Pi (3 B+)

3- Inclusion of a .env file to store sensible info used to grant access to applications.

4- Install **php**, **composer**, and **vlucas/phpdotenv** library into the Raspberry Pi to use .env file info. 

Note: If you've already set up the LAMP server into Raspberry, then install **composer** only.

**commands**

raspberrypi_user@your_raspberrypi_IP: ~ $ sudo apt install php

raspberrypi_user@your_raspberrypi_IP: ~ $ sudo apt install composer

raspberrypi_user@your_raspberrypi_IP: ~ $ sudo composer require vlucas/phpdotenv

## ESP32 Circuit Setup Used in this Project

The complete circuit is composed by following components and modules:

- DOIT ESP32 DEVKIT V1
- DHT22
- SD Card Module
- Oled Display SSD1306
- Real Time Clock Module (RTC DS3231)
- Two Push Buttons
- Two 10 kohm resistors


The circuit setup is shown below:

![circuit_diagram](images/electronic_setup.png)

### Circuit Functionality

This circuit monitors the DHT22 sensor readings at intervals, adjusted directly in the firmware (this could be improved to be adjustable in the future, using a menu approach just to set the main parameters of the system). The DHT22 readings are logged into an SD Card accompaining some other parameters like the RTC date and time, localization of installation, etc. The same data logged into the SD Card is sent using the HTTP POST method to the LAMP server running in the Raspberry Pi, which saves the data into a MariaDB/MySQL database.