<?php
header('Content-Type: application/json');

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "RoboticsBootcamp";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die(json_encode(['error' => 'Database connection failed']));
}

// Get the latest sensor reading
$sql = "SELECT temperature, humidity FROM sensor_data ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    echo json_encode([
        'temperature' => floatval($row['temperature']),
        'humidity' => floatval($row['humidity'])
    ]);
} else {
    echo json_encode(['temperature' => 0, 'humidity' => 0]);
}

$conn->close();
?>