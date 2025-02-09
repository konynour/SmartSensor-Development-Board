/*

  Receiver Code: The receiver code receives the data, displays it on an OLED screen, 
  and controls the motor based on the detected motion. If motion is detected, 
  the motor is activated.

*/

#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MOTOR_IN1 33
#define MOTOR_IN2 26

typedef struct struct_message {
    float temperature;
    float humidity;
    bool motionDetected;
} struct_message;

struct_message receivedData;

// Callback function to handle received data
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    memcpy(&receivedData, incomingData, sizeof(receivedData));
    Serial.println("✅ Data received:");
    Serial.print("🌡 Temperature: "); Serial.println(receivedData.temperature);
    Serial.print("💧 Humidity: "); Serial.println(receivedData.humidity);
    Serial.print("🚶‍♂ Motion: "); Serial.println(receivedData.motionDetected ? "Motion Detected" : "No Motion");

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.print("Temp: "); display.print(receivedData.temperature); display.println(" C");
    display.print("Humidity: "); display.print(receivedData.humidity); display.println(" %");
    display.print("Motion: "); display.println(receivedData.motionDetected ? "Detected" : "No");
    display.display();

    // Control motor based on motion detection
    if (receivedData.motionDetected) {
        digitalWrite(MOTOR_IN1, HIGH);
        digitalWrite(MOTOR_IN2, LOW);
    } else {
        digitalWrite(MOTOR_IN1, LOW);
        digitalWrite(MOTOR_IN2, LOW);
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("❌ ESP-NOW initialization error");
        return;
    }

    // Register the callback function to handle received data
    esp_now_register_recv_cb(onDataRecv);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("❌ OLED screen initialization failed");
        for (;;);
    }
    
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
    display.clearDisplay();
}

void loop() {
    delay(1000);
}
