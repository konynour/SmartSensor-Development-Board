### ESP32 Communication Setup (Sender & Receiver)

This project demonstrates how to set up two ESP32 devices to communicate with each other using ESP-NOW. Follow the steps below to configure the system

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

Open the Arduino IDE.

Copy and paste the following code into a new sketch:

cpp
Copy
Edit

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



## all this PCB is designed by: https://github.com/MazenGomaa

