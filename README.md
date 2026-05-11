# NeuraCare Smart Health Monitoring System

NeuraCare is an IoT-based smart health monitoring system designed to collect and monitor real-time patient health data using ESP32 and biomedical sensors. The system captures heart rate, SpO2, temperature, and humidity data for continuous monitoring and remote healthcare support.

## Features
- Real-time health data monitoring
- ESP32-based sensor integration
- Heart rate and SpO2 tracking
- Temperature and humidity monitoring
- Python-based data processing
- Web dashboard for remote monitoring

## Tech Stack
- ESP32
- Embedded C
- Python
- MAX30100 Sensor
- MLX90614 Sensor
- HTML/CSS

## Project Workflow

1. Sensors collect real-time patient health data including heart rate, SpO2, temperature, and humidity.
2. ESP32 processes and transmits the sensor readings.
3. Data is monitored and analyzed using Python-based processing scripts.
4. Health metrics are displayed through a web-based dashboard for remote monitoring.
5. System helps track abnormal readings for continuous patient observation.

## Output Screenshot


### Web Dashboard
<img width="1366" height="768" alt="Dashboard" src="https://github.com/user-attachments/assets/463f39f7-16ef-434b-a681-604e0f2b28e9" />

## Project Structure

NeuraCare-Smart-Health-Monitoring-System/
│
├── sensor_code/        # ESP32 sensor integration code
├── dashboard/          # Web dashboard files
├── data_processing/    # Python scripts for processing data
├── assets/             # Images and screenshots
├── README.md

## Future Improvements

- Add cloud-based health data storage
- Implement real-time alert notifications for abnormal readings
- Improve dashboard visualization and analytics
- Integrate machine learning for predictive health monitoring
- Expand support for additional biomedical sensors
