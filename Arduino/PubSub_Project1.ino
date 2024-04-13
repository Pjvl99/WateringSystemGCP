#include <PZEM004Tv30.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClientSecureBearSSL.h>
#include <DHT11.h>
#define MOISTURE_PIN 36
const char* serverName = ""; //Cloud functions url
String message = "";
HTTPClient https;
const char* ssid = "";
const char* password = "";
#define DHT11_PIN 21
DHT11 dht11(DHT11_PIN);


void setup() {
  WiFi.begin(ssid, password);
  Serial.begin(9600);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    //Check WiFi connection status
    if(WiFi.status() == WL_CONNECTED){
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

      // Ignore SSL certificate validation
      client->setInsecure();
      int temperature = 0;
      int humidity = 0;

      // Attempt to read the temperature and humidity values from the DHT11 sensor.
      int result = dht11.readTemperatureHumidity(temperature, humidity);
      int soil = analogRead(A0);
      if (soil < 60) {
        message = "The plant needs water";
      } else {
        message = "The plant is fine";
      }
      if (result == 0) {
        // Your Domain name with URL path or IP address with path
        https.begin(*client, serverName);
        https.addHeader("Content-Type", "application/json");
        // If you need Node-RED/server authentication, insert user and password below
        //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
        String httpJson = "{ \"message\": \"" + String(message) + "\", \"humidity\": \"" + String(humidity) + "\", ";
        httpJson += "\"temperature\": \"" + String(temperature) + "\", \"soil\": \"" + String(soil) + "\"}";
        // Send HTTP GET request
        int httpResponseCode = https.POST(httpJson);
        if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = https.getString();
          Serial.println(payload);
        }
      https.end();
      }

      delay(5000);
  } else {
      Serial.println("---starting wifi");
      WiFi.begin(ssid, password);
      delay(1000);
  }
}
