// docs for wifi can be found here: https://docs.arduino.cc/libraries/wifi/
#include <WiFi.h>
// docs for dht11 can be found here: https://github.com/dhrubasaha08/DHT11
#include <DHT11.h>

#include "../../../include/secrets.h"

#define SENSOR 2 // define sensor pin

// Network credentials
const char* ssid = HOTSPOT_SSID;
const char* password = HOTSPOT_PASSWORD;

// server ip and port
const char* server_ip = SERVER_IP;
const uint16_t server_port = 9001;

// TCP client
WiFiClient client;

// create instance of DHT11 temp/humidity sensor
DHT11 dht11(SENSOR);
int temperature = 0;
int humidity = 0;

void setup() {
    Serial.begin(9600);
    // Connect to wifi
    WiFi.begin(ssid, password);


    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
    }
    Serial.println("Connected to network");
    Serial.println(WiFi.localIP()); 
    
    if (client.connect(server_ip, server_port)) {
      Serial.println("Connected to server!");
      client.println("Hello from sensor!");
    } else {
      Serial.println("Connection to server failed");
    }
    dht11.readTemperatureHumidity(temperature, humidity);
    
}

void loop() {
    if (client.connected()) {
      // read temp/humidity
      int result = dht11.readTemperatureHumidity(temperature, humidity);

      if (result == 0) {
        // if read successful, convert to json syntax and send to server
        String data = "{temperature:" + String(temperature) + ", humidity:" + String(humidity) + "}";
        Serial.println("Sending: " + data);
        client.print(data);
      }
      delay(1000);
    } else {
      // if server is disconnected, stop client
      Serial.println("Client disconnected");
      client.stop();
      
      // do nothing
      for(;;)
        ;
    }
}