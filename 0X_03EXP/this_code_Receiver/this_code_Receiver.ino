//----------------------------------------Load libraries
#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------

//----------------------------------------Define variables to store incoming readings
int receive_rnd_val_1;
int receive_rnd_val_2;
//----------------------------------------

//----------------------------------------Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int rnd_1;
    int rnd_2;
} struct_message;

struct_message receive_Data; // Create a struct_message to receive data.
//----------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is received
void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data)); // Correct struct

  Serial.print("Bytes received: ");
  Serial.println(len);

  // Correctly use the struct fields
  receive_rnd_val_1 = receive_Data.rnd_1;
  receive_rnd_val_2 = receive_Data.rnd_2;

  Serial.print("Received Value 1: ");
  Serial.println(receive_rnd_val_1);
  Serial.print("Received Value 2: ");
  Serial.println(receive_rnd_val_2);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA); // Set device as a Wi-Fi Station

  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------

  esp_now_register_recv_cb(OnDataRecv); // Correct function signature
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID LOOP
void loop() {
  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
