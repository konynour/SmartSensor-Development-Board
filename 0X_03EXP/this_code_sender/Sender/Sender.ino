#include <esp_now.h>
#include <WiFi.h>
#include <DHT.h>

#define DHTPIN 25      // DHT11 pin
#define PIRPIN 32      // Motion sensor pin
#define DHTTYPE DHT11  // Sensor type

DHT dht(DHTPIN, DHTTYPE);

typedef struct struct_message {
    float temperature;
    float humidity;
    bool motionDetected;
} struct_message;

struct_message sensorData;

esp_now_peer_info_t peerInfo;
uint8_t receiverMacAddress[] = {0xb8, 0xd6, 0x1a, 0xab, 0xd8, 0x68};  


void onDataSent(const uint8_t *macAddr, esp_now_send_status_t status) {
    Serial.print("📡 Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "✅ Success" : "❌ Failure");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    
    if (esp_now_init() != ESP_OK) {
        Serial.println("❌ Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb(onDataSent);
    memcpy(peerInfo.peer_addr, receiverMacAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("❌ Failed to add receiver device");
        return;
    }

    dht.begin();
    pinMode(PIRPIN, INPUT);
}

void loop() {
    sensorData.temperature = dht.readTemperature();
    sensorData.humidity = dht.readHumidity();
    sensorData.motionDetected = digitalRead(PIRPIN);

    // ✅ Print data before sending
    Serial.println("📡 Sending data...");
    Serial.print("🌡 Temperature: "); Serial.print(sensorData.temperature); Serial.println("°C");
    Serial.print("💧 Humidity: "); Serial.print(sensorData.humidity); Serial.println("%");
    Serial.print("🚶‍♂ Motion Sensor Status: "); Serial.println(sensorData.motionDetected ? "🚨 Motion Detected!" : "✅ No Motion");

    // ✅ Send data via ESP-NOW
    esp_err_t result = esp_now_send(receiverMacAddress, (uint8_t *)&sensorData, sizeof(sensorData));
    if (result == ESP_OK) {
        Serial.println("✅ Sent successfully");
    } else {
        Serial.println("❌ Failed to send");
    }

    delay(2000);
}
