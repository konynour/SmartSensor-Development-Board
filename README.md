
### 0. **0X_00EXP: he MQ2 sensor continuously monitors the air for gas particles**

**Descriptions:**
This system is useful in applications where gas leakage detection is essential, such as in kitchens, laboratories, or industrial environments. The combination of visual (LED) and audible (buzzer) alerts ensures that the presence of harmful gases is immediately noticeable.

**components:**
- Arduino Nano: Microcontroller board.
- MQ2 Sensor
- LED
- Buzzer
- Power Supply
**Files:**
- `0X_01EXP.ino`: main code.
- [Circuit Diagram](./images/photo.png)
- [Setup Photo](./images/photo.jpg)


### 1. **0X_01EXP: Fan Speed Control with Temperature & Joystick** 
**Description:**  
Adjust fan speed automatically (via DS18B20 sensor) or manually (via joystick).  

**Components:**  
- Arduino Nano  
- DS18B20 Temperature Sensor  
- Joystick Module  
- DC Motor + MOSFET  

**Files:**  
- `0X_01EXP.ino`: Main code.  
- [Circuit Diagram](./images/photo.png)  
- [Setup Photo](./images/photo.jpg)  


---



### 2 **0X_02EXP: home automation, wireless control of LEDs, and RGB lighting.**

**Description:** 
- This schematic represents an Arduino Nano-based control system with various components 
- like buttons, LEDs, an RGB LED, 
- and an HC-05 Bluetooth module.
- Here's a detailed breakdown of each section:

**Components:**
- Microcontroller:Arduino_nano
- Power(3.3V or 5V.)
- Keys/Buttons
- LEDs
- Resistors (typically 220Ω or 330Ω).
- Bluetooth Modul: (e.g., HC-05, HC-06)


**Files:**  
- `0X_02EXP.ino`: Main code.  
- [Circuit Diagram](./images/photo.png)  
- [Setup Photo](./images/photo.jpg)


### 3. **0X_03EXP ESP32 Communication Setup (Sender & Receiver)**

This project demonstrates how to set up two ESP32 devices to communicate with each other using ESP-NOW. Follow the steps below to configure the system
**Description:**  

------

 ### Example Scenario:
PCB1 (Transmitter): Sends sensor data (e.g., temperature) to PCB2.

PCB2 (Receiver): Receives the data and performs an action (e.g., turns on an LED if the temperature is above a threshold).

---

## Overview
 1. Two Controllers: One ESP32 acts as the Sender, and the other acts as the Receiver
ESP-NOW Protocol: A lightweight communication protocol for direct device-to-device communication.
MAC Address: Each ESP32 has a unique MAC address that must be exchanged for proper pairing.
Setup Instructions
Step 1: Retrieve the MAC Address of Both ESP32 Devices
Before establishing communication, you need the MAC addresses of both ESP32 devices.



**Components:** 
 - Microcontroller:(esp32)
 - Keys/Buttons (KEY6_TH to KEY457_TH)
 - Voltage Regulator:(3.2v)
 - Resistors
 - Capacitors
 - Diodes
 - Crystal Oscillator:
 - LEDs
 - Transistors/MOSFETs
 -----

In the Tools menu:

Select the correct Board (ESP32).
Select the correct Port.
Upload the code to the ESP32.

Open the Serial Monitor (baud rate: 115200).

Note the displayed MAC address.

Repeat steps 3–7 for the second ESP32 to get its MAC address.

Step 2: Code for the Sender (ESP32 #1)
The Sender ESP32 will send data to the Receiver ESP32. The MAC address of the Receiver must be specified in the Sender code.

-------------

Step 3: Code for the Receiver (ESP32 #2)
The Receiver ESP32 will listen for data from the Sender ESP32. The MAC address of the Sender must be specified in the Receiver code.

---------------

Step 4: Establish Communication Between Sender and Receiver
Use the retrieved MAC addresses to configure both ESP32 devices:
Include the Receiver's MAC address in the Sender code.
Include the Sender's MAC address in the Receiver code.
Ensure both ESP32 devices are powered on and within wireless range.
Upload the respective codes to the ESP32 devices.
Notes
ESP-NOW Protocol: Reliable for short-range communication without requiring a Wi-Fi network.
Make sure both ESP32 devices use the same Wi-Fi channel if needed.
For the complete source code for both Sender and Receiver, refer to the sender.ino and receiver.ino files in this repository.

### 4.0X_04EXP: 
RFID-Based Access Control System:
---------
**Description**
This project implements an RFID-based access control system integrated with the following components:

LCD Display: Provides visual feedback to users.
Audio Notifications: Enhances user interaction with pre-recorded sounds.
LED Indicators: Show system status (standby, access granted/denied).

  

**Components:**  
- LCD: Display status (e.g., "Locked", "Unlocked").
- RC522: Read RFID tags and match IDs.
- DFPlayer: Play sounds based on actions.
- Solenoid Lock: Control the locking mechanism.
- LED Indicators: Show system state. 

**Files:**  
- `EXP4.ino`: Main code.  
- [Circuit Diagram](./images/photo.png)  
- [Setup Photo](./images/photo.jpg)  




### 5. **0X_05EXP: Ultrasonic Water Level Monitoring**  
**Description:**  
Measure water levels in real-time using an **HC-SR04 Ultrasonic Sensor**.  

**Components:**  
- Arduino Uno  
- HC-SR04 Sensor  
- 16x2 LCD  
- Buzzer (for alerts)  

**Files:**  
- `EXP5.ino`: Main code.  
- [Setup Photo](./images/photo.jpg)  
- [Circuit Diagram ](./images/photo.png)

## all this PCB is designed by: https://github.com/MazenGomaa

