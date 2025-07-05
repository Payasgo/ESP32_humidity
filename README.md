🌡️ ESP32 + DHT22: Temperature & Humidity Logger with MySQL Backend

This project reads temperature and humidity from a DHT22 sensor using an ESP32 and sends it over Wi-Fi to a PHP API, which stores the data into a MySQL database. It’s a complete IoT solution for smart environment monitoring.

    📌 Ideal for IoT beginners, weather stations, greenhouse monitoring, or home automation dashboards.

📸 Project Snapshot

🔧 Hardware Used
Component	Quantity	Description
ESP32 DevKit	1	Wi-Fi and Bluetooth enabled MCU board
DHT22 Sensor	1	Digital temperature & humidity sensor
Jumper Wires	4	For connecting sensor to ESP32
Breadboard	1	For prototyping (optional)
USB Cable	1	For powering and flashing ESP32
🔌 Circuit Diagram
DHT22 Pin	ESP32 Pin	Description
VCC	3.3V	Power
GND	GND	Ground
Data	GPIO4	Data Signal

    🧠 Add a 10K pull-up resistor between VCC and Data for stable readings.

📱 Functional Flow

graph TD
    DHT22 --> ESP32
    ESP32 -->|POST Temp+Humidity| PHP_API
    PHP_API --> MySQL_DB

    The ESP32 collects temperature and humidity.

    Sends data every 5 seconds to test_data.php using HTTP POST.

    The PHP script inserts this into a MySQL database.

📦 Arduino Code Summary

    Connects to Wi-Fi

    Reads sensor data using DHT22

    Sends data to a PHP script

    Handles connection failures gracefully

🔑 Example POST Payload:

temperature=27&humidity=63

✅ Example Serial Output:

Connecting to WiFi
Connected to: yournamewifi
IP Address: 192.168.1.9
Temperature: 27 °C
Humidity: 63 %
URL: http://192.168.1.8/dht22_project/test_data.php
Data: temperature=27&humidity=63
HTTP Code: 200
Payload: New record inserted successfully

🧾 PHP Backend (test_data.php)

    Validates POST data

    Connects to sensor_db

    Inserts data into dht22 table

📁 PHP Example:

if(isset($_POST["temperature"]) && isset($_POST["humidity"])) {
  $t = $_POST["temperature"];
  $h = $_POST["humidity"];
  $sql = "INSERT INTO dht22 (temperature, humidity) VALUES($t, $h)";
}

    🔐 Use prepared statements for production systems to prevent SQL injection.

🗄️ MySQL Table Structure

CREATE DATABASE sensor_db;

CREATE TABLE dht22 (
  id INT AUTO_INCREMENT PRIMARY KEY,
  temperature FLOAT,
  humidity FLOAT,
  timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);

🧪 Testing Locally with XAMPP

    Install XAMPP

    Place your PHP files in htdocs/dht22_project

    Start Apache and MySQL from the XAMPP control panel

    Open browser: http://localhost/phpmyadmin

    Create the database and table

    Edit the ESP32 code:

String URL = "http://192.168.1.8/dht22_project/test_data.php";

📊 Future Enhancements

📈 Add charts using Google Charts or Chart.js

🌐 Host on cloud platforms like AWS/Heroku

📤 Send alerts via email/SMS when thresholds exceed

🧠 Train a model to detect unusual climate changes
