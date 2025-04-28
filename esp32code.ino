#include <WiFi.h>

// Pin Definitions
#define RXD2 16
#define TXD2 17

// Connect to WiFi (if needed)
void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin("your-wifi-ssid", "your-wifi-password");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

// Read data from Arduino via Serial2 (connected to Arduino Uno)


void setup() {
  Serial.begin(115200);  // For debugging with the Serial Monitor
  
  // Initialize Serial2 with custom pins (PMS_RX_PIN, PMS_TX_PIN)
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Debugging message
  Serial.println("ESP32 and Arduino Sensor Data: ");
}

void loop() {
Serial.print("data recieved: ");
 Serial.println(Serial2.readString());
  delay(2500); 
}
