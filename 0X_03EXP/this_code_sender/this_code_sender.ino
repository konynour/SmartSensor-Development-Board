//----------------------------------------Load libraries
#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------

//----------------------------------------Function Prototypes
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status); 
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len); 
//----------------------------------------

uint8_t broadcastAddress[] = {0xec, 0x62, 0x60, 0x74, 0xf1, 0x74}; 

//----------------------------------------Variables to accommodate the data to be sent.
int send_rnd_val_1;
int send_rnd_val_2;
//----------------------------------------

//----------------------------------------Define variables to store incoming readings
int receive_rnd_val_1;
int receive_rnd_val_2;
//----------------------------------------

String success; // Variable to store if sending data was successful

//----------------------------------------Structure to send data
typedef struct struct_message {
    int rnd_1;
    int rnd_2;
} struct_message;

struct_message send_Data; 
struct_message receive_Data; 
//----------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  success = (status == ESP_NOW_SEND_SUCCESS) ? "Delivery Success :)" : "Delivery Fail :(";
  Serial.println(">>>>>"); 
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is received
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
  struct_message incomingReadings;  
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  
  Serial.print("Bytes received: ");
  Serial.println(len);
  
  // Print the MAC address of the sender
  Serial.print("Sender MAC Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(recv_info->src_addr[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
  
  // Assign received values
  receive_rnd_val_1 = incomingReadings.rnd_1;  
  receive_rnd_val_2 = incomingReadings.rnd_2;   
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ SETUP FUNCTION
void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA); // Set device as a Wi-Fi Station

  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------

  //----------------------------------------Register Callbacks
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  //----------------------------------------

  //----------------------------------------Register peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  //----------------------------------------
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ LOOP FUNCTION
void loop() {
  send_rnd_val_1 = random(0, 255);
  send_rnd_val_2 = random(0, 255);
  send_Data.rnd_1 = send_rnd_val_1;
  send_Data.rnd_2 = send_rnd_val_2;

  Serial.println();
  Serial.print(">>>>> Sending Data: ");
  Serial.print(send_rnd_val_1);
  Serial.print(", ");
  Serial.println(send_rnd_val_2);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&send_Data, sizeof(send_Data));
   
  Serial.println((result == ESP_OK) ? "Sent successfully" : "Error sending data");
  
  delay(5000);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
