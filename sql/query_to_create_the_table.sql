CREATE TABLE dht22_sensor_readings (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    reading_time TIMESTAMP,
    customer_ID VARCHAR(30) NOT NULL,
    iot_device_serial_number VARCHAR(30) NOT NULL,
    temperature VARCHAR(10),
    humidity VARCHAR(10),
    wifi_status VARCHAR(10)
)