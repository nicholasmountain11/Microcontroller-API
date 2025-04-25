#include <WiFi.h>

#include "../../../include/secrets.h"

#define LED 2

const char* ssid = HOTSPOT_SSID;
const char* password = HOTSPOT_PASSWORD;

const char* server_ip = "18.118.14.29";
const uint16_t server_port = 9002;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to network");
  Serial.println(WiFi.localIP());

  if (client.connect(server_ip, server_port)) {
    Serial.println("Connected to server!");
  } else {
    Serial.println("Connection to server failed.");
  }
}

void loop() {
  if (client.connected()) {
    if (client.available()) {
      String message = client.readStringUntil('\n');
      Serial.println("Received: " + message);
      if (message == "ON") {
        digitalWrite(LED, HIGH);
      } else if (message == "OFF") {
        digitalWrite(LED, LOW);
      } else {
        Serial.println("Did not recognize message.");
      }
    }
  } else {
    Serial.println("Disconnected from server");
    client.stop();

    for(;;)
    ;
  }

}
