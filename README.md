Health Monitoring System

Overview
This project is an Arduino-based Health Monitoring System that collects real-time health data using multiple sensors. It measures heart rate, body temperature, and integrates an RFID system for user identification.

Features
Heart Rate Monitoring: Uses a Pulse Sensor to measure heart rate.
Body Temperature Measurement: Utilizes an MLX90614 infrared temperature sensor.
User Identification: Integrates an RFID module to recognize users.
LCD Display: Displays measured health data in real-time.

Components Used
Arduino Board (Compatible with Uno, Mega, etc.)
Pulse Sensor (Heart Rate Monitor)
Adafruit MLX90614 (Infrared Temperature Sensor)
RFID Module (RC522) (For User Authentication)
LCD Display (For Visual Output)
SPI and I2C Communication Modules

Libraries Required
Ensure you have the following libraries installed in your Arduino IDE:
#include <SPI.h>
#include <RFID.h>
#include <PulseSensorPlayground.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal.h>

Setup & Installation
Connect all the components to the Arduino as per their respective wiring configurations.
Install the required libraries in the Arduino IDE.
Upload the provided Code_hms.ino file to the Arduino.
Open the Serial Monitor (9600 baud rate) to view real-time data.

Usage

Power on the system.
Place the RFID tag near the RFID reader for user identification.
The Pulse Sensor detects heart rate and displays it on the LCD.
The MLX90614 sensor reads body temperature and displays the value.
The data can also be monitored through the Serial Monitor.

Future Enhancements
Wireless Data Transmission (e.g., Bluetooth/Wi-Fi for remote monitoring)
Cloud Integration (Storing health data for analysis)
Battery-Powered Version (For portability)



