# IoT Smart Power Strip with Energy Monitoring

## Overview

This project presents an IoT-based Smart Power Strip capable of monitoring electrical parameters and controlling connected loads using ESP32 microcontrollers.

The system measures real-time electrical parameters using two PZEM-004T energy monitoring modules and transmits the data to an Edge Node. The Edge Node performs relay control, over-voltage and under-voltage protection, and provides support for cloud monitoring using Firebase and the Blynk IoT platform.

---

## Features

- Real-time Voltage Monitoring
- Current Monitoring
- Power Monitoring
- Energy Consumption Monitoring
- Frequency Measurement
- Power Factor Measurement
- Dual Load Monitoring
- Automatic Over Voltage Protection
- Automatic Under Voltage Protection
- Relay Control
- ESP32 Based IoT System
- JSON Communication
- Firebase Integration 
- Blynk IoT Integration 

---

## Hardware Used

- ESP32 Development Boards (2)
- PZEM-004T V3.0 Energy Meter Modules (2)
- 2-Channel Relay Module
- Wi-Fi Network
- AC Loads

---

## Software Used

- Arduino IDE
- ESP32 Board Package
- ArduinoJson Library
- PZEM004Tv30 Library
- WiFi Library
- HTTPClient Library
- WebServer Library

---

## Project Architecture

```
PZEM 1 ----\
             \
              --> Sensor Node (ESP32) ----HTTP/JSON----> Edge Node (ESP32)
             /
PZEM 2 ----/

                          |
                          |
             -------------------------
             |                       |
         Relay Control          Firebase
             |
          Blynk Dashboard
```

---

## Repository Structure

```
IoT-Smart-Power-Strip/
│
├── Sensor_Node/
│   └── Sensor_Node.ino
│
├── Edge_Node/
│   └── Edge_Node.ino
│
├── docs/
│   ├── Project_Report.pdf
│   └── Presentation.pptx
│
├── config.h
│
└── README.md
```

---

## Working Principle

1. Sensor Node reads electrical parameters from two PZEM modules.
2. Data is converted into JSON format.
3. JSON is transmitted to the Edge Node over Wi-Fi.
4. Edge Node processes the received data.
5. Relay control logic provides voltage protection.
6. Data can be uploaded to Firebase.
7. Live monitoring can be performed using the Blynk IoT dashboard.

---

## Project Status

This repository contains a reconstructed implementation based on the original academic project. The original source code was unavailable, so the Arduino implementation has been recreated from the project report for educational and portfolio purposes.

---

## Author

**Nivethitha**

Bachelor of Engineering – Electrical and Electronics Engineering

---

## License

This project is intended for educational purposes.
