// Define pin connections
#define MQ2_PIN A0    // MQ2 sensor connected to A0
#define LED_PIN 2     // LED connected to D2
#define BUZZER_PIN 4  // Buzzer connected to D4

// Define threshold for gas detection
const int gasThreshold = 300; // Adjust based on calibration

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Set pin modes
  pinMode(MQ2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Initial states
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Read the gas sensor value
  int gasValue = analogRead(MQ2_PIN);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);
  
  // Check if the gas value exceeds the threshold
  if (gasValue > gasThreshold) {
    digitalWrite(LED_PIN, HIGH);  // Turn on LED
    digitalWrite(BUZZER_PIN, HIGH); // Activate buzzer
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn off LED
    digitalWrite(BUZZER_PIN, LOW); // Deactivate buzzer
  }
  
  // Delay for stability
  delay(500);
}
