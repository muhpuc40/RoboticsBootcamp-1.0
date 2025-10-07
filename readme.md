# 🌐 ESP32 WebServer + PHP + XAMPP Integration

![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![PHP](https://img.shields.io/badge/PHP-777BB4?style=for-the-badge&logo=php&logoColor=white)
![XAMPP](https://img.shields.io/badge/XAMPP-FB7A24?style=for-the-badge&logo=xampp&logoColor=white)
![MySQL](https://img.shields.io/badge/MySQL-4479A1?style=for-the-badge&logo=mysql&logoColor=white)

A complete project integrating **ESP32**, **Arduino**, and **PHP backend** using **XAMPP**.  
This system allows you to display live sensor data, store it in a database, and visualize readings with real-time charts.

## 📁 Project Structure

```
├── Arduino/
│   ├── main.ino
│   ├── sensor.ino
│   ├── wifi_connect.ino
│
├── xampp/
│   └── htdocs/
│       ├── backend.php
│       ├── index.php
│       ├── fetch_data.php
│       ├── graph.html
│       ├── style.css
│       └── webserver/
│           └── index.html
```

---

## ⚙️ Setup Guide

### Step 1: Set Up XAMPP

1. **Download & Install XAMPP**
   - [Download XAMPP](https://www.apachefriends.org/download.html)
   - Install and launch **Apache** and **MySQL** from the XAMPP Control Panel.

2. **Database Setup**
   - Open **phpMyAdmin** at: [http://localhost/phpmyadmin](http://localhost/phpmyadmin)
   - Create a new database (e.g., `esp32_data`)
   - Run the following SQL to create your table:

     ```sql
     CREATE TABLE sensor_data (
         id INT AUTO_INCREMENT PRIMARY KEY,
         temperature FLOAT,
         humidity FLOAT,
         created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
     );
     ```

3. **Place Project Files**
   - Move all PHP and HTML files into:
     ```
     C:\xampp\htdocs\
     ```
   - Run locally at:
     ```
     http://localhost/index.php
     ```

---

### Step 2: Set Up Arduino IDE for ESP32

1. **Install Arduino IDE**  
   Download from [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

2. **Add ESP32 Board**
   - Go to **File → Preferences**
   - Add this URL in *Additional Board Manager URLs*:  
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Then go to **Tools → Board → Board Manager**, search for **ESP32** and install it.

3. **Install Required Libraries**
   - Import the provided ZIP library files

4. **Project Files**
   - Move your Arduino `.ino` files into:
     ```
     Documents/Arduino/
     ```
   - Open your main `.ino` file and upload to ESP32

---

### Step 3: Connect ESP32 to Wi-Fi

Upload code to ESP32  
⚠️ **Warning**: When uploading, ensure wires are properly connected and free from interference

---

## 🧩 Project Workflow

### `backend.php`
- Receives data from ESP32 via HTTP POST
- Inserts data into MySQL database

### `index.php` + `style.css`
- Displays stored data in a clean front-end interface

### `fetch_data.php` + `graph.html`
- Uses AJAX to fetch live data from the database
- Updates chart in real-time for monitoring

### `webserver/index.html`
- ESP32's built-in WebServer page
- Displays sensor readings directly from ESP32 without database

---

## 🚀 Run Everything

1. Start **Apache** and **MySQL** from XAMPP
2. Connect your **ESP32** to Wi-Fi
3. Open:

   - Local dashboard: [http://localhost/index.php](http://localhost/index.php)
   - Live graph: [http://localhost/graph.html](http://localhost/graph.html)
   - ESP32 WebServer: use the IP shown in Serial Monitor (e.g. `http://192.168.0.120`)

---

## 🧾 Notes

- Ensure ESP32 and PC are connected to the **same Wi-Fi network**
- If you face database connection issues, check:
  - `backend.php` credentials (hostname, username, password)
  - MySQL running properly in XAMPP

---

## 👨‍💻 Credits

**Developed by Minhaj Udin Hassan**  
GS, Premier University Robotics Club  
Department of Computer Science & Engineering  
Premier University

---

### 🏁 Enjoy building your IoT Dashboard powered by ESP32, PHP, and XAMPP!