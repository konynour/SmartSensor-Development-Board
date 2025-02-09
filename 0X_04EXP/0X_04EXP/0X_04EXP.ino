#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal.h>

// Define LCD pins
// const int RS = 7, EN = 2, D4 = 3, D5 = 4, D6 = 5, D7 = 6;
// LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Define LCD pins (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 2, 3, 4, 5, 6);

// Define RFID pins
#define RST_PIN A5
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Define DFPlayer pins
SoftwareSerial mySoftwareSerial(8, 9); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Define control pins
// const int solenoidPin = A0; // Solenoid control pin
const int ledRed = A0;      // Red LED
//const int ledBlue = A0;     // Blue LED

// Allowed card UID (replace with your card's UID)
byte allowedUID[] = {0xAD, 0x15, 0xF2, 0x21};

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("System Ready");
  
  // Initialize RFID
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Initialize DFPlayer
  mySoftwareSerial.begin(9600);
 myDFPlayer.begin(mySoftwareSerial);
 
    lcd.clear();

  myDFPlayer.volume(30); // Set volume (0-30)
  
  // Initialize pins
  // pinMode(solenoidPin, OUTPUT);
  pinMode(ledRed, OUTPUT);
//  pinMode(ledBlue, OUTPUT);
  // digitalWrite(solenoidPin, LOW);
  digitalWrite(ledRed, LOW); // Red LED in standby mode
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
    lcd.print("WelcomeDr ousama");
//    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);
    // digitalWrite(solenoidPin, HIGH); // Unlock the solenoid
    myDFPlayer.play(1); // Play audio file 1
    delay(3000); // Wait for 3 seconds
    // digitalWrite(solenoidPin, LOW); // Lock the solenoid
//    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed, LOW);
  } else {
    lcd.clear();
    lcd.print("Access Denied!");
    digitalWrite(ledRed, LOW);
    myDFPlayer.play(2); // Play audio file 2
    delay(2000);
  }
  
  lcd.clear();
  lcd.print("System Ready");
  mfrc522.PICC_HaltA();
}
