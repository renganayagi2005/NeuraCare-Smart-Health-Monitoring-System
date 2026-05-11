<?php

include 'db_connect.php';

$patientid = $_POST['patientid'];

$sql = "SELECT * FROM patients
WHERE patient_id='$patientid'";

$result = mysqli_query($conn, $sql);

$row = mysqli_fetch_assoc($result);

if ($row)
{
    header(
    "Location: dashboard.php?name="
    .$row['patient_name'].

    "&mobile=".$row['mobile'].

    "&patientid=".$row['patient_id']
    );
}
else
{
    echo "Patient Not Found";
}

?>