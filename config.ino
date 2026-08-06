#ifndef CONFIG_H
#define CONFIG_H

/******************************************************
 * Wi-Fi Configuration
 ******************************************************/
#define WIFI_SSID       "YOUR_WIFI_NAME"
#define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"

/******************************************************
 * Edge Node Configuration
 ******************************************************/
#define EDGE_NODE_PORT 80
#define EDGE_NODE_PATH "/update"

/******************************************************
 * Voltage Protection
 ******************************************************/
#define MIN_VOLTAGE 180.0
#define MAX_VOLTAGE 250.0

/******************************************************
 * Relay Pins (ESP32)
 ******************************************************/
#define RELAY1_PIN 18
#define RELAY2_PIN 19

/******************************************************
 * PZEM UART Pins (Sensor Node)
 ******************************************************/
// PZEM Module 1
#define PZEM1_RX 16
#define PZEM1_TX 17

// PZEM Module 2
#define PZEM2_RX 26
#define PZEM2_TX 27

/******************************************************
 * Timing
 ******************************************************/
#define SENSOR_READ_INTERVAL 5000
#define WIFI_RETRY_DELAY     500
#define SERVER_DELAY         100

/******************************************************
 * Firebase (Fill later)
 ******************************************************/
#define API_KEY        ""
#define DATABASE_URL   ""

/******************************************************
 * Blynk (Fill later)
 ******************************************************/
#define BLYNK_TEMPLATE_ID   ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN    ""

#endif
