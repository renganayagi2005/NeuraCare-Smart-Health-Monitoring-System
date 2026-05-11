# NeuraCare Smart Health Monitoring System

NeuraCare is an IoT-based smart health monitoring system designed to monitor real-time patient health parameters using ESP32 and biomedical sensors. The system integrates hardware monitoring with a web-based dashboard for remote patient data visualization and health status tracking.

---

## Features

- Real-time Heart Rate Monitoring
- SpO2 Monitoring
- Body Temperature Monitoring
- Personalized Baseline Learning
- Lightweight Anomaly Detection
- Health Risk Classification
- Remote Doctor Dashboard
- Patient Registration & Record Management
- Monitoring History Tracking
- MySQL Database Integration

---

## Technologies Used

### Embedded & IoT
- ESP32
- Embedded C
- MAX30102
- MLX90614

### Software & Web
- PHP
- MySQL
- HTML
- CSS
- XAMPP

### Data Processing
- Python
- HTTP Communication

---

## System Workflow

Sensor Data → ESP32 Processing → Baseline Analysis → Risk Classification → Web Dashboard Visualization

---

## Project Structure

```text
NeuraCare/
│
├── index.php
├── dashboard.php
├── upload_data.php
├── search_patient.php
├── db_connect.php
├── doctor_login.php
├── patient_database.php
├── about.php
│
├── firmware/
│   └── neuracare_health_monitoring.ino
│
├── assets/
│   └── css/
│       └── style.css
│
├── screenshots/
│
└── README.md
