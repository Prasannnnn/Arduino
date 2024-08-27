#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "CADD";       // Your WiFi SSID
const char* password = "matcomcts"; // Your WiFi Password

// ThingSpeak Settings
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "85EYDAX1Y3ABZF46"; // Your ThingSpeak Write API Key

// DHT Settings
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(2000);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Check WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Construct URL for ThingSpeak
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(temp) + "&field2=" + String(humidity);

    http.begin(url);  // Initialize HTTPClient with the URL

    // Send the request
    int httpCode = http.GET();
    
    // Check the response
    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak successfully!");
    } else {
      Serial.println("Error sending data to ThingSpeak.");
    }

    http.end(); // End the HTTP connection
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(20000);  // ThingSpeak recommends at least 15 seconds between updates
}
