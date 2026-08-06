/*******************************************************
 * Sensor_Node.ino
 * IoT Smart Power Strip with Energy Monitoring
 * ESP32 Sensor Node
 *******************************************************/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <PZEM004Tv30.h>

//========================
// WiFi Credentials
//========================
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

//========================
// Edge Node URL
// Change this to the IP address of your Edge Node ESP32
//========================
String edgeNodeURL = "http://192.168.1.100/update";

//========================
// PZEM Pin Configuration
//========================

// PZEM #1
HardwareSerial PZEMSerial1(1);
PZEM004Tv30 pzem1(PZEMSerial1, 16, 17);

// PZEM #2
HardwareSerial PZEMSerial2(2);
PZEM004Tv30 pzem2(PZEMSerial2, 26, 27);

//========================
// Variables
//========================

float voltage1 = 0;
float current1 = 0;
float power1 = 0;
float energy1 = 0;
float frequency1 = 0;
float pf1 = 0;

float voltage2 = 0;
float current2 = 0;
float power2 = 0;
float energy2 = 0;
float frequency2 = 0;
float pf2 = 0;

//========================
// Function Prototypes
//========================

void connectWiFi();
void checkWiFi();
void readPZEM1();
void readPZEM2();
void sendDataToEdgeNode();
void printSystemStatus();

//========================
// Setup
//========================

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("================================");
    Serial.println(" IoT Smart Power Strip ");
    Serial.println(" Sensor Node Starting...");
    Serial.println("================================");

    // Start Serial Ports

    PZEMSerial1.begin(9600, SERIAL_8N1, 16, 17);
    PZEMSerial2.begin(9600, SERIAL_8N1, 26, 27);

    connectWiFi();
}

//========================
// Main Loop
//========================

void loop()
{
    checkWiFi();

    readPZEM1();

    readPZEM2();

    sendDataToEdgeNode();

    printSystemStatus();

    delay(5000);
}
//========================
// WiFi Connection
//========================

void connectWiFi()
{
    Serial.print("Connecting to WiFi");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    Serial.println("WiFi Connected");

    Serial.print("IP Address : ");

    Serial.println(WiFi.localIP());
}
//=====================================================
// Read PZEM #1
//=====================================================

void readPZEM1()
{
    voltage1 = pzem1.voltage();
    current1 = pzem1.current();
    power1 = pzem1.power();
    energy1 = pzem1.energy();
    frequency1 = pzem1.frequency();
    pf1 = pzem1.pf();

    if (isnan(voltage1))
    {
        Serial.println("PZEM1 Error : Unable to read sensor.");
        return;
    }

    Serial.println("----------------------------");
    Serial.println("PZEM Module 1");

    Serial.print("Voltage      : ");
    Serial.print(voltage1);
    Serial.println(" V");

    Serial.print("Current      : ");
    Serial.print(current1);
    Serial.println(" A");

    Serial.print("Power        : ");
    Serial.print(power1);
    Serial.println(" W");

    Serial.print("Energy       : ");
    Serial.print(energy1);
    Serial.println(" kWh");

    Serial.print("Frequency    : ");
    Serial.print(frequency1);
    Serial.println(" Hz");

    Serial.print("Power Factor : ");
    Serial.println(pf1);

    Serial.println("----------------------------");
}


//=====================================================
// Read PZEM #2
//=====================================================

void readPZEM2()
{
    voltage2 = pzem2.voltage();
    current2 = pzem2.current();
    power2 = pzem2.power();
    energy2 = pzem2.energy();
    frequency2 = pzem2.frequency();
    pf2 = pzem2.pf();

    if (isnan(voltage2))
    {
        Serial.println("PZEM2 Error : Unable to read sensor.");
        return;
    }

    Serial.println("----------------------------");
    Serial.println("PZEM Module 2");

    Serial.print("Voltage      : ");
    Serial.print(voltage2);
    Serial.println(" V");

    Serial.print("Current      : ");
    Serial.print(current2);
    Serial.println(" A");

    Serial.print("Power        : ");
    Serial.print(power2);
    Serial.println(" W");

    Serial.print("Energy       : ");
    Serial.print(energy2);
    Serial.println(" kWh");

    Serial.print("Frequency    : ");
    Serial.print(frequency2);
    Serial.println(" Hz");

    Serial.print("Power Factor : ");
    Serial.println(pf2);

    Serial.println("----------------------------");
}
//=====================================================
// Send Sensor Data to Edge Node
//=====================================================

void sendDataToEdgeNode()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi Disconnected... Reconnecting");
        connectWiFi();
        return;
    }

    HTTPClient http;

    http.begin(edgeNodeURL);

    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<512> jsonDoc;

    //--------------- PZEM 1 ----------------

    jsonDoc["Voltage1"] = voltage1;
    jsonDoc["Current1"] = current1;
    jsonDoc["Power1"] = power1;
    jsonDoc["Energy1"] = energy1;
    jsonDoc["Frequency1"] = frequency1;
    jsonDoc["PF1"] = pf1;

    //--------------- PZEM 2 ----------------

    jsonDoc["Voltage2"] = voltage2;
    jsonDoc["Current2"] = current2;
    jsonDoc["Power2"] = power2;
    jsonDoc["Energy2"] = energy2;
    jsonDoc["Frequency2"] = frequency2;
    jsonDoc["PF2"] = pf2;

    String jsonString;

    serializeJson(jsonDoc, jsonString);

    Serial.println("Sending Data to Edge Node...");
    Serial.println(jsonString);

    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response : ");
        Serial.println(httpResponseCode);

        String response = http.getString();

        Serial.println("Edge Node Reply:");
        Serial.println(response);
    }
    else
    {
        Serial.print("HTTP Error : ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
//=====================================================
// Utility Function
//=====================================================

void printSystemStatus()
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("      SENSOR NODE STATUS");
    Serial.println("========================================");

    Serial.print("WiFi Status : ");

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Connected");
        Serial.print("IP Address : ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("Disconnected");
    }

    Serial.println("----------------------------------------");

    Serial.print("PZEM1 Voltage : ");
    Serial.println(voltage1);

    Serial.print("PZEM2 Voltage : ");
    Serial.println(voltage2);

    Serial.println("========================================");
}


//=====================================================
// Optional Auto Reconnect
//=====================================================

void checkWiFi()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi Lost...");
        connectWiFi();
    }
}
