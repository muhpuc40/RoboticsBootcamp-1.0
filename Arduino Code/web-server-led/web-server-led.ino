// WebServer started LED with Random MAC

#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// WiFi credentials
//const char* ssid = "minhaj";
//const char* password = "asdf@1234";

const char* ssid = "Computer Lab 345";
const char* password = "COMlab@60568#";

// Pin setup
int pins[] = {2, 4, 16, 17};
bool pinStates[] = {false, false, false, false}; // Track state of each pin

WebServer server(80);


void handleControl() {
  server.sendHeader("Access-Control-Allow-Origin", "*"); // CORS header

  if (server.hasArg("pin") && server.hasArg("state")) {
    int pin   = server.arg("pin").toInt();
    int state = server.arg("state").toInt();

    bool validPin = false;
    int pinIndex  = -1;

    // Validate pin
    for (int i = 0; i < 4; i++) {
      if (pins[i] == pin) {
        validPin = true;
        pinIndex = i;
        break;
      }
    }

    if (validPin) {
      digitalWrite(pin, state ? HIGH : LOW);
      pinStates[pinIndex] = state;
      Serial.printf("Pin %d set to %s\n", pin, state ? "ON" : "OFF");
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Invalid pin");
    }
  } else {
    server.send(400, "text/plain", "Missing pin/state");
  }
}


void handleInfo() {
  server.sendHeader("Access-Control-Allow-Origin", "*"); // CORS header

  DynamicJsonDocument doc(512);
  doc["ip"]          = WiFi.localIP().toString();
  doc["mac"]         = WiFi.macAddress();
  doc["chipModel"]   = ESP.getChipModel();
  doc["chipRevision"] = ESP.getChipRevision();
  doc["flashSize"]   = ESP.getFlashChipSize() / 1024; // in KB
  doc["freeHeap"]    = ESP.getFreeHeap() / 1024;      // in KB
  doc["sdkVersion"]  = ESP.getSdkVersion();

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}


void handleGetStates() {
  server.sendHeader("Access-Control-Allow-Origin", "*"); // CORS header

  DynamicJsonDocument doc(256);
  JsonArray states = doc.createNestedArray("states");

  for (int i = 0; i < 4; i++) {
    JsonObject state = states.createNestedObject();
    state["pin"]   = pins[i];
    state["state"] = pinStates[i] ? 1 : 0;
  }

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}


void setup() {
  Serial.begin(115200);

  // Initialize pins
  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/control", handleControl);
  server.on("/info", handleInfo);
  server.on("/states", handleGetStates);

  // Start server
  server.begin();
  Serial.println("✅ WebServer started!");
}

void loop() {
  server.handleClient();
}
