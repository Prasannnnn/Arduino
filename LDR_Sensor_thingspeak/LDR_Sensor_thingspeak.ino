#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// ThingSpeak Settings
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "your_thingspeak_api_key"; // Your ThingSpeak Write API Key

// LDR Settings
#define LDR_PIN 34  // GPIO pin connected to LDR

void setup() {
  Serial.begin(115200);

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
  // Read the LDR value
  int ldrValue = analogRead(LDR_PIN);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Check WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field1=" + String(ldrValue);
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
