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
- 2 Push Buttons
- 3 10 kohm resistors


The circuit setup is shown below:

![circuit_diagram](images/electronic_setup.png)

### Circuit Functionality

This circuit monitors the DHT22 sensor readings at intervals, adjusted directly in the firmware (this could be improved to be adjustable in the future, using a menu approach just to set the main parameters of the system). The DHT22 readings are logged into an SD Card accompaining some other parameters like the RTC date and time, localization of installation, etc. The same data logged into the SD Card is sent using the HTTP POST method to the LAMP server running in the Raspberry Pi, which saves the data into a MariaDB/MySQL database.

The project was developed using **Arduino IDE 2.3.4** and all sketches are found in **arduino_files** directory.

## Accessing the phpMyAdmin to Create the Database to Store the Data from ESP32

Once we have the LAMP server installed and running in Raspberry Pi, we can access the server address by typing in the browser the following:

**http://you_raspberypi_IP_address/phpmyadmin**

When you press Enter, the access page will be shown:

![phpmyadmin_access](images/phpmyadmin_access.png)

To get access, you must fill out the field **Username** (generally **root**) and the **Password** you set during the LAMP server installation. If everything goes nicely you will see the following page:

![phpmyadmin_first_page](images/phpmyadmin_first_page.png)

Click on **New** to create a new database:

![phpmyadmin_new_database](images/phpmyadmin_new_database.png)

Choose a database name and then click in **Create**:

![phpmyadmin_database_name](images/phpmyadmin_database_name.png)

You will see a new database with the name you gave to it:

![phpmyadmin_esp_data_database](images/phpmyadmin_esp_data_database.png)

Now, we need to create a table to store all the ESP32 data in a structured manner(columns). To do so, we can click on the tab **SQL**:

![phpmyadmin_sql](images/phpmyadmin_sql.png)

Then, type in or just copy and paste the following SQL commands to create our desired table and click **Go**:

~~~
    CREATE TABLE sensor_readings (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    reading_time TIMESTAMP,
    location VARCHAR(30) NOT NULL,
    temperature VARCHAR(10),
    humidity VARCHAR(10),
    wifi_status VARCHAR(10)
    )
~~~

![phpmyadmin_create_table](images/phpmyadmin_create_table.png)

You'll see the message below and the newly created table:

![phpmyadmin_table_created](images/phpmyadmin_table_created.png)

If we click on the table, we can see its columns, but of course, the table is empty because no data has been inputted or sent yet.

![phpmyadmin_empty_table](images/phpmyadmin_empty_table.png)

## Creating The Files Responsible to Deal With The Data Sent By The ESP32

Now we will create the files in the server side, which will be responsible to receive the data comming from ESP32 via HTTP POST method and save it into the database. To do this, open the terminal and foollow the steps below.

- Connet to the Raspberry Pi through ssh:

    **command** 
    
    ssh raspberrypi_user@your_raspberrypi_IP

    In my case, the **raspberrypi_user = pi** and **your_raspberrypi_IP = raspberrypi** or you may replace by the actual IP number address like 192.168.*.* and so on.

- Go to the followin directory:

    **command**

    pi@raspberrypi:~ $ cd /var/www/html

- Now we will create the **.env** file to store the credentials and other sensible information of the sistem using **nano** text enviorement:

    **command**

    pi@raspberrypi:/var/www/html $ sudo nano .env

    You will see the screen below:

    ![gnu_nano_editor](images/gnu_nano_editor.png)

    There you will create the enviroment variables we will call in *php* scripts
    which will connect with the database and will hold the API_KEY we will generate to give some kind of security level between data transfer between the ESP32 and the LAMP server running on the Raspberry PI.

    So, in the .env file you will enter the following text lines:

    ~~~~
        # MySQL Database Credentials hosted into Raspberry Pi
        RASP_DATABASE_NAME = "your_database_name" 
        RASP_DATABASE_USER_NAME = "your_database_user_name"
        RASP_DATABASE_PASSWORD = "your_database_password
        RASP_API_KEY = "your_api_key"
    ~~~~

    ![nano_dot_env](images/nano_dot_env.png)

    In this project I used for **RASP_DATABASE_NAME = esp_data** and **RASP_DATABASE_USER_NAME = root**, but if you've set different names for each variable you must use yours.

- To generate the API_KEY for this project, we can access [codepen](https://codepen.io/corenominal/pen/rxOmMJ) and just click in **Generate API Key**. Then copy and paste it in the **RASP_API_KEY** enviroment variable in **.evn** opened at **nano** editor.

![codepen_api_key_example](images/api_key_example.png)

After you have finished the definitions of the evironment variables you must save the **.env** file by pressing **Ctrl+X** and then **Y(es)**

- Now we will use the same **php** files from the [Random Nerd Tutorials](https://randomnerdtutorials.com/esp32-esp8266-raspberry-pi-lamp-server/), but with the adjustments to use the **.env** file and other parameters for this project.

    In the same directory where our **.env** file is saved (in my case is pi@raspberrypi:/var/www/html $), we will create the **php** files. The complete files you can find in the **www** folder in this repo.

    - Creating the file **esp_data.php**:

        **command**

        pi@raspberrypi:/var/www/html $ sudo nano esp_data.php

        ![esp_data_php_nano](images/esp_data_php_nano.png)

        Again type **Ctrl+X** and **Y(es)** to save the file.

    - Creating the file: **post_esp_data.php**

        **command**

        pi@raspberrypi:/var/www/html $ sudo nano post_esp_data.php

        Repeat the proccess as done with the **esp_data.php**

    - Creating the file: **esp_insert_and_get_data_into_from_database.php**

        **commands**

        pi@raspberrypi:/var/www/html $ sudo nano sp_insert_and_get_data_into_from_database.php

        Repeat the proccess as done with the **esp_data.php**



    

