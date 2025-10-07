<?php
// Database connection settings
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "RoboticsBootcamp";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);

// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

// Get JSON data
$data = json_decode(file_get_contents("php://input"), true);
$temperature = $data["temperature"];
$humidity = $data["humidity"];

// Insert into database
$sql = "INSERT INTO sensor_data (temperature, humidity) VALUES ('$temperature', '$humidity')";

if (mysqli_query($conn, $sql)) {
    echo "Data inserted successfully: Temperature=$temperature, Humidity=$humidity";
} else {
    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
}

// Close connection
mysqli_close($conn);
?>