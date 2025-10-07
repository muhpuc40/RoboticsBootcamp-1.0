#include <HTTPClient.h>
#include <WiFi.h>
#include "DHT.h"

// WiFi credentials
const char* ssid = "minhaj";
const char* password = "asdf@1234";

// API endpoint
String apiURL = "http://192.168.0.102/ROBOTICSBOOTCAMP/backend.php";

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Task handles for FreeRTOS
TaskHandle_t Task0;
TaskHandle_t Task1;

// Global variables
bool data_upload = false; // Flag to control data upload
float lastTemperature = 0.0;
float lastHumidity = 0.0;

// Function prototypes
void readDHTSensor();
void sendData();

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // Create tasks for Core 0 and Core 1
  xTaskCreatePinnedToCore(
    core0Task,         // Task function
    "SendData",        // Name of task
    10000,             // Stack size
    NULL,              // Parameter
    1,                 // Priority
    &Task0,            // Task handle
    0);                // Core 0

  xTaskCreatePinnedToCore(
    core1Task,         // Task function
    "ReadSensor",      // Name of task
    10000,             // Stack size
    NULL,              // Parameter
    1,                 // Priority
    &Task1,            // Task handle
    1);                // Core 1
}

void loop() {
  // Empty loop, tasks handle everything
  delay(5000);
}

// Task for Core 0: Call sendData function
void core0Task(void *pvParameters) {
  while (true) {
    if (data_upload) {
      sendData();
      data_upload = false; // Reset flag after sending
    }
    vTaskDelay(200 / portTICK_PERIOD_MS); // Delay as in example code
  }
}

// Task for Core 1: Call readDHTSensor function
void core1Task(void *pvParameters) {
  while (true) {
    readDHTSensor();
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Wait 5ms (Note: DHT11 sampling rate is ~1s, consider increasing to 1000ms)
  }
}

// Function to read DHT sensor
void readDHTSensor() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Core 1 - Failed to read from DHT sensor!");
  } else {
    Serial.print("Core 1 - Humidity: ");
    Serial.print(humidity);
    Serial.print(" % | Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Store readings and set upload flag
    lastTemperature = temperature;
    lastHumidity = humidity;
    data_upload = true;
  }
}

// Function to send data (POST request)
void sendData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(apiURL);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"temperature\": " + String(lastTemperature, 2) + ", \"humidity\": " + String(lastHumidity, 2) + "}";

    int httpCode = http.POST(jsonPayload);

    if (httpCode > 0) {
      Serial.print("Core 0 - POST sent, code: ");
      Serial.println(httpCode);
    } else {
      Serial.print("Core 0 - Error sending POST, code: ");
      Serial.println(httpCode);
    }
    http.end();
  } else {
    Serial.println("Core 0 - WiFi Disconnected, attempting to reconnect...");
    WiFi.reconnect();
  }
}