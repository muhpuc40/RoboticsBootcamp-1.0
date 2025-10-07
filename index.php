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

// Fetch data
$sql = "SELECT id, temperature, humidity, timestamp FROM sensor_data";
$result = mysqli_query($conn, $sql);
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Robotics Bootcamp 1.0 - Sensor Data</title>
    <!-- jQuery DataTables CSS -->
    <link rel="stylesheet" href="https://cdn.datatables.net/1.13.6/css/jquery.dataTables.min.css">
    <!-- Custom CSS -->
    <link rel="stylesheet" href="style.css">
    <!-- jQuery -->
    <script src="https://code.jquery.com/jquery-3.7.0.min.js"></script>
    <!-- jQuery DataTables JS -->
    <script src="https://cdn.datatables.net/1.13.6/js/jquery.dataTables.min.js"></script>
</head>

<body>
    <div class="navbar">
        <h1>ROBOTICS BOOTCAMP 1.0</h1>
    </div>
    <div class="container">
        <table id="sensorTable" class="display">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Temperature (°C)</th>
                    <th>Humidity (%)</th>
                    <th>Timestamp</th>
                </tr>
            </thead>
            <tbody>
                <?php
                if (mysqli_num_rows($result) > 0) {
                    while ($row = mysqli_fetch_assoc($result)) {
                        echo "<tr>";
                        echo "<td>" . $row['id'] . "</td>";
                        echo "<td>" . $row['temperature'] . "</td>";
                        echo "<td>" . $row['humidity'] . "</td>";
                        echo "<td>" . $row['timestamp'] . "</td>";
                        echo "</tr>";
                    }
                }
                ?>
            </tbody>
        </table>
    </div>
    <script>
        $(document).ready(function () {
            $('#sensorTable').DataTable({
                paging: true,
                searching: true,
                ordering: true,
                order: [[0, 'desc']],
                info: true,
                lengthChange: true,
                pageLength: 10
            });
        });
    </script>
</body>

</html>
<?php
// Close connection
mysqli_close($conn);
?>