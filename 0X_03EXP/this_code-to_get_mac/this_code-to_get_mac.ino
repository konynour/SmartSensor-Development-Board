// ESP-NOW: Transmitter


#include <esp_now.h>
#include <WiFi.h>

// Receiver's MAC Address
uint8_t RxMACaddress[] = {0x7C, 0x9E, 0xBD, 0xF5, 0xBE, 0x30};

// Data structure to send
typedef struct TxStruct {
  int potVal; // Variable to store potentiometer value
} TxStruct;

TxStruct sentData;


// Callback function when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

//======================================================================================
// Setup function
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); // Set ESP32 to Station mode
  
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);

  // Add receiver as a peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, RxMACaddress, 6); // Set receiver's MAC address
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

//======================================================================================
// Main loop function
void loop() {
  // Read the potentiometer value
  sentData.potVal = analogRead(A0);

  // Send data using ESP-NOW
  esp_err_t result = esp_now_send(RxMACaddress, (uint8_t *) &sentData, sizeof(sentData));

  // Print the result of the send operation
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }

  delay(500); 
}
