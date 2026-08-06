# IoT Smart Power Strip with Energy Monitoring using ESP32

An IoT-based Smart Power Strip developed using ESP32 microcontrollers for real-time electrical parameter monitoring and intelligent relay control. The system monitors voltage, current, power, energy consumption, frequency, and power factor using dual PZEM-004T energy meters and supports cloud-ready architecture for remote monitoring.

---

# Project Overview

The project consists of two ESP32 boards:

- **Sensor Node** – Collects electrical parameters from two PZEM-004T energy monitoring modules.
- **Edge Node** – Receives sensor data over Wi-Fi, processes it, controls relays for voltage protection, and provides support for cloud platforms such as Firebase and Blynk.

The objective of this project is to improve electrical safety, monitor energy consumption, and provide a scalable IoT-based smart power management system.

---

# Features

- Real-time Voltage Monitoring
- Real-time Current Monitoring
- Power Monitoring
- Energy Consumption Monitoring
- Frequency Measurement
- Power Factor Monitoring
- Dual Load Monitoring
- Wi-Fi Communication
- JSON Data Transmission
- ESP32-based Distributed Architecture
- Automatic Under Voltage Protection
- Automatic Over Voltage Protection
- Relay Control
- Cloud-ready Architecture
- Firebase Integration (Reconstructed)
- Blynk Dashboard Support (Reconstructed)

---

# Hardware Components

- ESP32 Development Board ×2
- PZEM-004T V3 Energy Meter ×2
- 2-Channel Relay Module
- AC Loads
- Wi-Fi Router
- Power Supply

---

# Software & Libraries

- Arduino IDE
- ESP32 Board Package
- ArduinoJson
- PZEM004Tv30 Library
- WiFi Library
- HTTPClient Library
- WebServer Library

---

# System Architecture

```
            +-----------------------+
            |     PZEM-004T #1      |
            +----------+------------+
                       |
                       |
            +----------v------------+
            |                       |
            |   Sensor Node ESP32   |
            |                       |
            +----------+------------+
                       |
                 HTTP + JSON
                       |
                       |
            +----------v------------+
            |                       |
            |    Edge Node ESP32    |
            |                       |
            +-----+-----------+-----+
                  |           |
             Relay Control    |
                              |
                      Firebase / Blynk
```

---

# Project Workflow

1. Sensor Node reads electrical parameters from two PZEM-004T modules.
2. Sensor data is converted into JSON format.
3. JSON data is transmitted to the Edge Node over Wi-Fi.
4. Edge Node receives and processes the data.
5. Relay control protects connected loads from abnormal voltage.
6. Sensor readings can be uploaded to Firebase.
7. Live monitoring can be performed using the Blynk mobile application.

---

# Repository Structure

```
iot-smart-power-strip
│
├── Sensor_Node.ino
├── Edge_Node.ino
├── config.h
├── README.md
├── Project_Report.pdf
└── images/
```

---

# Images

## Hardware Setup

(Add your hardware image here)

```
images/hardware_setup.jpg
```

---

## Circuit Diagram

(Add your circuit diagram here)

```
images/circuit_diagram.png
```

---

## Working Model

(Add your project demonstration image here)

```
images/working_model.jpg
```

---

# Technologies Used

- Embedded Systems
- Internet of Things (IoT)
- ESP32
- Arduino Programming
- Wi-Fi Networking
- JSON Communication
- Energy Monitoring
- Relay Automation

---

# Future Improvements

- Firebase Realtime Database Integration
- Blynk Cloud Dashboard
- Mobile Notifications
- Energy Usage Analytics
- OTA (Over-the-Air) Firmware Updates
- MQTT Communication
- Historical Data Logging

---

# Project Status

This repository contains a reconstructed implementation based on the original academic project report. The original Arduino source code was unavailable; therefore, the implementation has been recreated for educational and portfolio purposes. The software architecture reflects the project design and may require hardware-specific configuration and testing before deployment.

---

# Author

**Nivethitha**

Bachelor of Engineering (Electrical and Electronics Engineering)

GitHub: https://github.com/YOUR_USERNAME

---

# Acknowledgements

- Arduino Community
- Espressif Systems
- PZEM004T Library Developers
- Open-source IoT Community
