CREATE DATABASE neuracare;

USE neuracare;

CREATE TABLE patients (
    patient_id INT PRIMARY KEY,
    patient_name VARCHAR(100),
    disease VARCHAR(100),
    status VARCHAR(50)
);