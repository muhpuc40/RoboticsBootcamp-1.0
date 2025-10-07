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
}

void loop() {
  delay(10000); 

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Send to backend
  sendData(temperature, humidity);
}

void sendData(float temperature, float humidity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;


    http.begin(apiURL);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"temperature\": " + String(temperature, 2) +", \"humidity\": " + String(humidity, 2) + "}";

    int httpCode = http.POST(jsonPayload);

    if (httpCode > 0) {
      String response = http.getString();
      Serial.println(httpCode);
      Serial.print("Server Response: ");
      Serial.println(response);
    } else {
      Serial.print("Error sending POST, code: ");
      Serial.println(httpCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}
