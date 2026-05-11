<!DOCTYPE html>
<html>

<head>
    <title>Dashboard</title>
    <link rel="stylesheet" href="assets/css/style.css">
</head>

<body>

<header>
    <h1>Patient Monitoring Dashboard</h1>

    <p style="text-align:center;
    font-size:18px;
    font-weight:bold;">

    <?php

    date_default_timezone_set("Asia/Kolkata");

    echo "Last Updated: " .
    date("d-m-Y h:i:s A");

    ?>

    </p>

</header>

<section>

<?php

$name = $_GET['name'];
$mobile = $_GET['mobile'];
$patientid = $_GET['patientid'];

?>

<!-- Patient Information -->

<div class="card">

    <h3>Patient Information</h3>

    <p><strong>Name:</strong>
    <?php echo $name; ?></p>

    <p><strong>Mobile:</strong>
    <?php echo $mobile; ?></p>

    <p><strong>Patient ID:</strong>
    <?php echo $patientid; ?></p>

</div>

<!-- Heart Rate -->

<div class="card">

    <h3>Heart Rate</h3>

    <p>78 BPM</p>

</div>

<!-- SpO2 -->

<div class="card">

    <h3>SpO2</h3>

    <p>97%</p>

</div>

<!-- Temperature -->

<div class="card">

    <h3>Temperature</h3>

    <p>36.8 °C</p>

</div>

<!-- Health Status -->

<div class="card risk">

    <h3>Health Status</h3>

    <?php

    $status = "NORMAL";
    $color = "green";

    if ($patientid == "NC102")
    {
        $status = "MODERATE";
        $color = "orange";
    }

    if ($patientid == "NC103")
    {
        $status = "HIGH RISK";
        $color = "red";
    }

    ?>

    <p style="color: <?php echo $color; ?>;
    font-weight:bold;
    font-size:22px;">

    <?php echo $status; ?>

    </p>

</div>

<!-- Monitoring History -->

<div class="card">

<h3>Patient Monitoring History</h3>

<table>

<tr>
    <th>Date</th>
    <th>Heart Rate</th>
    <th>SpO2</th>
    <th>Temperature</th>
    <th>Status</th>
</tr>

<?php

include 'db_connect.php';

$query = "SELECT * FROM vitals
WHERE patient_id='$patientid'";

$result = mysqli_query($conn, $query);

while($row = mysqli_fetch_assoc($result))
{

$statusColor = "green";

if ($row['status'] == "MODERATE")
{
    $statusColor = "orange";
}

if ($row['status'] == "HIGH RISK")
{
    $statusColor = "red";
}

echo "<tr>

<td>".$row['created_at']."</td>

<td>".$row['heart_rate']."</td>

<td>".$row['spo2']."</td>

<td>".$row['temperature']."</td>

<td style='color:$statusColor;
font-weight:bold;'>

".$row['status']."

</td>

</tr>";

}

?>

</table>

</div>

</section>

</body>
</html>