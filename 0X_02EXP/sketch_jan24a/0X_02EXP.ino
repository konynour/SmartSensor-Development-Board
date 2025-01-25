#include <SoftwareSerial.h>

// Define pins
#define KEY1 5
#define KEY2 6
#define KEY3 7

#define RGB_RED 2
#define RGB_GREEN 3
#define RGB_BLUE 4

#define LED1 8
#define LED2 10
#define LED3 9
#define LED4 12

// Bluetooth module pins
#define BT_RX 11
#define BT_TX 10

SoftwareSerial bluetooth(BT_RX, BT_TX); // RX, TX

void setup() {
  // Initialize serial communication
  bluetooth.begin(9600); // Bluetooth baud rate
  Serial.begin(9600);    // Debugging

  // Initialize pins
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);

  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // Turn off all LEDs initially
  digitalWrite(RGB_RED, LOW);
  digitalWrite(RGB_GREEN, LOW);
  digitalWrite(RGB_BLUE, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void loop() {
  // Read button states
  bool key1State = !digitalRead(KEY1); // Active LOW
  bool key2State = !digitalRead(KEY2); // Active LOW
  bool key3State = !digitalRead(KEY3); // Active LOW

  // Toggle LEDs with buttons
  if (key1State) {
    digitalWrite(LED1, !digitalRead(LED1));
    delay(200); // Debounce
  }
  if (key2State) {
    digitalWrite(LED2, !digitalRead(LED2));
    delay(200); // Debounce
  }
  if (key3State) {
    digitalWrite(LED3, !digitalRead(LED3));
    delay(200); // Debounce
  }

  // Check for Bluetooth data
  if (bluetooth.available()) {
    char command = bluetooth.read(); // Read the incoming command
    Serial.println(command);         // Debugging

    // Handle RGB LED commands
    switch (command) {
      case 'R': // Red
        setRGBColor(255, 0, 0);
        break;
      case 'G': // Green
        setRGBColor(0, 255, 0);
        break;
      case 'B': // Blue
        setRGBColor(0, 0, 255);
        break;
      case 'Y': // Yellow
        setRGBColor(255, 255, 0);
        break;
      case 'C': // Cyan
        setRGBColor(0, 255, 255);
        break;
      case 'M': // Magenta
        setRGBColor(255, 0, 255);
        break;
      case 'W': // White
        setRGBColor(255, 255, 255);
        break;
      case 'O': // Off
        setRGBColor(0, 0, 0);
        break;
    }
  }
}

// Function to set RGB LED color
void setRGBColor(int red, int green, int blue) {
  analogWrite(RGB_RED, red);
  analogWrite(RGB_GREEN, green);
  analogWrite(RGB_BLUE, blue);
}
