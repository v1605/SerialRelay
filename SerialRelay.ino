#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include "SerialRelay.hpp"

WebServer server(WEB_PORT);


void handlePostRequest() {
  if (server.method() == HTTP_POST) {
    StaticJsonDocument<200> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, server.arg("plain"));
    if (error) {
      server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }
    int cmdDelay = jsonDoc["delay"] | 0;
    String ending = jsonDoc["ending"] | "";
    JsonArray commands = jsonDoc["commands"];
    if (!commands.isNull()) {
      for (String cmd : commands) {
        Serial.print(cmd);
        if(ending.length() > 0){
          Serial.print(ending);
        }
        Serial.flush();
        if(cmdDelay > 0){
          delay(cmdDelay);
        }
      }
    }
    server.send(200, "text/plain", "Complete");
  } else {
    server.send(405, "text/plain", "Method Not Allowed");
  }
}

void setup() {
  Serial.begin(BAUD_RATE);
  initWiFi();
  server.on("/", handlePostRequest);
  server.begin();
}

void loop() {
  server.handleClient();
  delay(100);
}

void initWiFi() {
  WiFi.disconnect(true, true);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE); 
  WiFi.setHostname(hostname);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(WiFi.localIP());
  MDNS.begin(hostname);
}
