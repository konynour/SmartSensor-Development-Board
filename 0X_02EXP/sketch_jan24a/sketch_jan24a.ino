#include <WiFi.h>

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);
    Serial.println();

    // Print ESP32 MAC Address
    Serial.print("ESP32 MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop() {
    // No loop logic needed
}
Connect one ESP32 to your computer via USB.