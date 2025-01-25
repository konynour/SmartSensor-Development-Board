


#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h


#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// OLED Display Configuration
Adafruit_SSD1306 display(128, 64, &Wire, -1);


// Data structure to receive
typedef struct RxStruct {
  int potVal; // Variable to store received potentiometer value
} RxStruct;

RxStruct receivedData;


// Callback function when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));
}


// Setup function
void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }
  display.clearDisplay();

  // Set ESP32 to Station mode
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the receive callback
  esp_now_register_recv_cb(OnDataRecv);
}


// Main loop function
void loop() {
  // Clear the display and set text color
  display.setTextColor(WHITE);
  display.clearDisplay();

  // Display the ESP-NOW title
  display.setTextSize(2);
  display.setCursor(20, 0);
  display.print("ESP-NOW");

  // Display the label for POT value
  display.setCursor(10, 18);
  display.print("POT Value");

  // Display the received potentiometer value
  display.setTextSize(3);
  display.setCursor(25, 42);
  display.print(receivedData.potVal);

  // Update the display
  display.display();
}

#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal.h>

// Define LCD pins
const int RS = 2, EN = 3, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Define RFID pins
#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Define DFPlayer pins
SoftwareSerial mySoftwareSerial(8, 9); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Define control pins
const int solenoidPin = A0; // Solenoid control pin
const int ledRed = A1;      // Red LED
const int ledBlue = A2;     // Blue LED

// Allowed card UID (replace with your card's UID)
byte allowedUID[] = {0xDE, 0xAD, 0xBE, 0xEF};

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("System Ready");
  
  // Initialize RFID
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Initialize DFPlayer
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    lcd.clear();
    lcd.print("DFPlayer Error!");
    while(true);
  }
  myDFPlayer.volume(30); // Set volume (0-30)
  
  // Initialize pins
  pinMode(solenoidPin, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  digitalWrite(solenoidPin, LOW);
  digitalWrite(ledRed, HIGH); // Red LED in standby mode
}

void loop() {
  // Check for a new card
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Read UID
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }

  // Check if the card is allowed
  bool isAllowed = true;
  for (byte i = 0; i < 4; i++) {
    if (mfrc522.uid.uidByte[i] != allowedUID[i]) {
      isAllowed = false;
      break;
    }
  }

  // Execute actions based on card validity
  if (isAllowed) {
    lcd.clear();
    lcd.print("Welcome!");
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(solenoidPin, HIGH); // Unlock the solenoid
    myDFPlayer.play(1); // Play audio file 1
    delay(3000); // Wait for 3 seconds
    digitalWrite(solenoidPin, LOW); // Lock the solenoid
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, HIGH);
  } else {
    lcd.clear();
    lcd.print("Access Denied!");
    digitalWrite(ledRed, HIGH);
    myDFPlayer.play(2); // Play audio file 2
    delay(2000);
  }
  
  lcd.clear();
  lcd.print("System Ready");
  mfrc522.PICC_HaltA();
}