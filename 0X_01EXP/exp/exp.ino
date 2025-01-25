#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// LCD pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(10, 8, 7, 6, 5, 4);

// DS18B20 temperature sensor
#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Joystick pins
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_SW 13


#define FAN_PIN 9
#define LED_PIN 3

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Joystick & Temp");

  // Initialize the temperature sensor
  sensors.begin();

  // Set pin modes
  pinMode(JOYSTICK_SW, INPUT_PULLUP); // Joystick button
  pinMode(FAN_PIN, OUTPUT);           // Fan control
  pinMode(LED_PIN, OUTPUT);           // LED control

  // Initial states
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  delay(2000); // Wait to display initial message
  lcd.clear();
}

void loop() {
  // Read joystick values
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);
  bool buttonPressed = !digitalRead(JOYSTICK_SW); // Button active low

  // Read temperature
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // Control fan and LED
  if (buttonPressed) {
    digitalWrite(FAN_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  // Display values on LCD
  lcd.setCursor(0, 0);
  lcd.print("X:");
  lcd.print(xValue);
  lcd.print(" Y:");
  lcd.print(yValue);

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C ");
  lcd.print(buttonPressed ? "Fan ON" : "Fan OFF");

  delay(400); 
}
