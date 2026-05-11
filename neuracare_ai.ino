#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <Adafruit_MLX90614.h>

// WIFI CREDENTIALS

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// WEBSITE API URL
// Replace YOUR_PC_IP with your laptop IP
// Example:
// http://192.168.1.5/Neuracarae/receive_data.php


String serverName =
"http://YOUR_PC_IP/Neuracarae/receive_data.php";

// SENSOR OBJECTS

MAX30105 particleSensor;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// VARIABLES

long lastBeat = 0;

float beatsPerMinute = 0;
float bodyTemp = 0;
float spo2 = 0;

// PERSONALIZED BASELINE LEARNING

float baselineHR = 0;
float baselineSpO2 = 0;
float baselineTemp = 0;

int calibrationCount = 0;
const int calibrationSamples = 20;

bool baselineCalculated = false;

// RISK VARIABLES

float hrDeviation;
float spo2Deviation;
float tempDeviation;

float healthRiskScore = 0;
float anomalyConfidenceIndex = 0;

String systemStatus = "NORMAL";

// SETUP

void setup()
{
  Serial.begin(115200);

  Wire.begin();

  // WIFI CONNECTION

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  // MAX30102 SENSOR

  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD))
  {
    Serial.println("MAX30102 not found");

    while (1);
  }

  particleSensor.setup();

  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

  // MLX90614 SENSOR

  if (!mlx.begin())
  {
    Serial.println("MLX90614 not found");

    while (1);
  }

  Serial.println("================================");
  Serial.println("NeuraCare AI Started");
  Serial.println("Personalized Baseline Learning");
  Serial.println("================================");
}

// LOOP

void loop()
{
  long irValue = particleSensor.getIR();

  // HEART RATE DETECTION

  if (checkForBeat(irValue) == true)
  {
    long delta = millis() - lastBeat;

    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);
  }

  // SIMULATED SpO2

  spo2 = random(95, 99);

  // TEMPERATURE

  bodyTemp = mlx.readObjectTempC();

  // PERSONALIZED BASELINE LEARNING

  if (calibrationCount < calibrationSamples)
  {
    baselineHR += beatsPerMinute;

    baselineSpO2 += spo2;

    baselineTemp += bodyTemp;

    calibrationCount++;

    Serial.print("Learning Baseline: ");

    Serial.println(calibrationCount);

    delay(1000);

    return;
  }

  // CALCULATE BASELINE ONLY ONCE

  if (!baselineCalculated)
  {
    baselineHR =
    baselineHR / calibrationSamples;

    baselineSpO2 =
    baselineSpO2 / calibrationSamples;

    baselineTemp =
    baselineTemp / calibrationSamples;

    baselineCalculated = true;

    Serial.println("Baseline Learning Completed");
  }

  // AI-ASSISTED DEVIATION ANALYSIS

  hrDeviation =
  abs(beatsPerMinute - baselineHR);

  spo2Deviation =
  abs(spo2 - baselineSpO2);

  tempDeviation =
  abs(bodyTemp - baselineTemp);

  // HEALTH RISK SCORE

  healthRiskScore =
      (hrDeviation * 0.3) +
      (spo2Deviation * 0.5) +
      (tempDeviation * 0.2);

  // ANOMALY CONFIDENCE INDEX

  anomalyConfidenceIndex = 0;

  if (hrDeviation > 10)
  {
    anomalyConfidenceIndex += 30;
  }

  if (spo2 < 92)
  {
    anomalyConfidenceIndex += 50;
  }

  if (bodyTemp > 37.5)
  {
    anomalyConfidenceIndex += 20;
  }
  // HUMAN-IN-THE-LOOP DECISION SUPPORT
  if (anomalyConfidenceIndex >= 70)
  {
    systemStatus =
    "HIGH RISK - Doctor Review Needed";
  }

  else if (anomalyConfidenceIndex >= 40)
  {
    systemStatus =
    "MODERATE RISK - Monitor Patient";
  }

  else
  {
    systemStatus = "NORMAL";
  }

  // SERIAL MONITOR OUTPUT

  Serial.println("================================");

  Serial.print("Heart Rate: ");
  Serial.print(beatsPerMinute);
  Serial.println(" BPM");

  Serial.print("SpO2: ");
  Serial.print(spo2);
  Serial.println(" %");

  Serial.print("Temperature: ");
  Serial.print(bodyTemp);
  Serial.println(" °C");

  Serial.println("--------------------------------");

  Serial.print("Baseline HR: ");
  Serial.println(baselineHR);

  Serial.print("Baseline SpO2: ");
  Serial.println(baselineSpO2);

  Serial.print("Baseline Temp: ");
  Serial.println(baselineTemp);

  Serial.println("--------------------------------");

  Serial.print("Health Risk Score: ");
  Serial.println(healthRiskScore);

  Serial.print("Anomaly Confidence Index: ");
  Serial.println(anomalyConfidenceIndex);

  Serial.print("System Status: ");
  Serial.println(systemStatus);

  // SEND DATA TO WEBSITE DATABASE

  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    http.begin(serverName);

    http.addHeader(
    "Content-Type",
    "application/x-www-form-urlencoded"
    );

    String httpRequestData =

    "heart_rate=" + String(beatsPerMinute) +

    "&spo2=" + String(spo2) +

    "&temperature=" + String(bodyTemp) +

    "&status=" + systemStatus;

    int httpResponseCode =
    http.POST(httpRequestData);

    Serial.print("HTTP Response Code: ");

    Serial.println(httpResponseCode);

    http.end();
  }

  else
  {
    Serial.println("WiFi Disconnected");
  }

  // LOOP DELAY
  delay(5000);
}