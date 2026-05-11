<!DOCTYPE html>
<html>

<head>
    <title>NeuraCare AI</title>
    <link rel="stylesheet" href="assets/css/style.css">
</head>

<body>

<header>
    <h1>NeuraCare AI Health Monitoring System</h1>
</header>

<div class="login-box">

    <h2>Patient Registration</h2>

    <form action="upload_data.php" method="POST">

        <input type="text" name="name" placeholder="Enter Patient Name" required>

        <input type="text" name="mobile" placeholder="Enter Mobile Number" required>

        <input type="text" name="patientid" placeholder="Enter Patient ID" required>

        <button type="submit">Start Monitoring</button>

    </form>

</div>

</body>
</html>

<hr><br>

<h2>Existing Patient</h2>

<form action="search_patient.php" method="POST">

    <input type="text"
    name="patientid"
    placeholder="Enter Patient ID"
    required>

    <button type="submit">
        View Patient Dashboard
    </button>

</form>