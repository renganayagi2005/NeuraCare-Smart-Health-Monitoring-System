<?php

include 'db_connect.php';

$name = $_POST['name'];
$mobile = $_POST['mobile'];
$patientid = $_POST['patientid'];

$sql = "INSERT INTO patients
(patient_name, mobile, patient_id)

VALUES

('$name', '$mobile', '$patientid')";

mysqli_query($conn, $sql);

header("Location: dashboard.php?name=$name&mobile=$mobile&patientid=$patientid");

?>