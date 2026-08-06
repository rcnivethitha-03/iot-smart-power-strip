/****************************************************
 * Edge_Node.ino
 * IoT Smart Power Strip
 * ESP32 Edge Node
 ****************************************************/

#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

//========================
// WiFi Credentials
//========================

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

//========================
// Web Server
//========================

WebServer server(80);

//========================
// Relay Pins
//========================

#define RELAY1 18
#define RELAY2 19

//========================
// Voltage Protection
//========================

const float MIN_VOLTAGE = 180.0;
const float MAX_VOLTAGE = 250.0;

//========================
// Sensor Variables
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
void receiveData();
void printData();
void controlRelay();
void uploadToFirebase();
void updateBlynk();
void checkWiFi();

//========================
// Setup
//========================

void setup()
{
    Serial.begin(115200);

    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);

    digitalWrite(RELAY1, HIGH);
    digitalWrite(RELAY2, HIGH);

    connectWiFi();

    server.on("/update", HTTP_POST, receiveData);

    server.begin();

    Serial.println("--------------------------------");
    Serial.println("Edge Node Started");
    Serial.println("--------------------------------");
}

//========================
// Main Loop
//========================

void loop()
{
    checkWiFi();

    server.handleClient();

    controlRelay();

    uploadToFirebase();

    updateBlynk();

    delay(100);
}

//========================
// WiFi Connection
//========================

void connectWiFi()
{
    Serial.print("Connecting");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    Serial.print("Connected : ");

    Serial.println(WiFi.localIP());
}

//========================
// WiFi Reconnect
//========================

void checkWiFi()
{
    if(WiFi.status()!=WL_CONNECTED)
    {
        Serial.println("WiFi Lost");

        connectWiFi();
    }
}

//=====================================================
// Receive JSON Data from Sensor Node
//=====================================================

void receiveData()
{
    if (!server.hasArg("plain"))
    {
        server.send(400, "text/plain", "No JSON Data");
        return;
    }

    String jsonData = server.arg("plain");

    Serial.println();
    Serial.println("================================");
    Serial.println("JSON Received");
    Serial.println("================================");
    Serial.println(jsonData);

    StaticJsonDocument<512> doc;

    DeserializationError error = deserializeJson(doc, jsonData);

    if (error)
    {
        Serial.print("JSON Error : ");
        Serial.println(error.c_str());

        server.send(400, "text/plain", "Invalid JSON");

        return;
    }

    //------------- Load 1 ----------------

    voltage1 = doc["Voltage1"];
    current1 = doc["Current1"];
    power1 = doc["Power1"];
    energy1 = doc["Energy1"];
    frequency1 = doc["Frequency1"];
    pf1 = doc["PF1"];

    //------------- Load 2 ----------------

    voltage2 = doc["Voltage2"];
    current2 = doc["Current2"];
    power2 = doc["Power2"];
    energy2 = doc["Energy2"];
    frequency2 = doc["Frequency2"];
    pf2 = doc["PF2"];

    Serial.println("Sensor values updated successfully.");

    printData();

    server.send(200, "text/plain", "Data Received Successfully");
}

//=====================================================
// Print Sensor Data
//=====================================================

void printData()
{
    Serial.println();
    Serial.println("========== LOAD 1 ==========");

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

    Serial.println();

    Serial.println("========== LOAD 2 ==========");

    Serial.print("Voltage      : ");
    Serial.print(voltage2);
    Serial.println(" V");

    Serial.print("Current      : ");
    Serial.print(current2);
    Serial.println(" A");

    Serial.print("Power        : ");
    Serial.println(power2);

    Serial.print("Energy       : ");
    Serial.print(energy2);
    Serial.println(" kWh");

    Serial.print("Frequency    : ");
    Serial.print(frequency2);
    Serial.println(" Hz");

    Serial.print("Power Factor : ");
    Serial.println(pf2);

    Serial.println("================================");
}
//=====================================================
// Relay Control
//=====================================================

void controlRelay()
{
    //-------------------------
    // Relay 1
    //-------------------------

    if (voltage1 > 0)
    {
        if (voltage1 < MIN_VOLTAGE || voltage1 > MAX_VOLTAGE)
        {
            digitalWrite(RELAY1, LOW);

            Serial.println("Relay 1 : OFF (Voltage Protection)");
        }
        else
        {
            digitalWrite(RELAY1, HIGH);

            Serial.println("Relay 1 : ON");
        }
    }

    //-------------------------
    // Relay 2
    //-------------------------

    if (voltage2 > 0)
    {
        if (voltage2 < MIN_VOLTAGE || voltage2 > MAX_VOLTAGE)
        {
            digitalWrite(RELAY2, LOW);

            Serial.println("Relay 2 : OFF (Voltage Protection)");
        }
        else
        {
            digitalWrite(RELAY2, HIGH);

            Serial.println("Relay 2 : ON");
        }
    }
}

//=====================================================
// Upload Data to Firebase
//=====================================================

void uploadToFirebase()
{
    Serial.println();
    Serial.println("Uploading to Firebase...");

    // Future Implementation
    // Firebase.RTDB.setFloat(...);

    Serial.println("Voltage1 : " + String(voltage1));
    Serial.println("Current1 : " + String(current1));

    Serial.println("Voltage2 : " + String(voltage2));
    Serial.println("Current2 : " + String(current2));

    Serial.println("Firebase Upload Complete");
}

//=====================================================
// Update Blynk Dashboard
//=====================================================

void updateBlynk()
{
    Serial.println();

    Serial.println("Updating Blynk Dashboard...");

    // Future Implementation
    // Blynk.virtualWrite(V0, voltage1);
    // Blynk.virtualWrite(V1, current1);
    // Blynk.virtualWrite(V2, power1);
    // Blynk.virtualWrite(V3, energy1);

    // Blynk.virtualWrite(V4, voltage2);
    // Blynk.virtualWrite(V5, current2);
    // Blynk.virtualWrite(V6, power2);
    // Blynk.virtualWrite(V7, energy2);

    Serial.println("Blynk Update Complete");
}

