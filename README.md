# Smart-Gas-Leakage-Detection
This project is an IoT-enabled safety system designed to detect gases in real time. It utilizes an ESP32 microcontroller paired with an MQ-2 gas sensor to continuously monitor air quality and uses ThingSpeak cloud integration.
# Components Used
Microcontroller: ESP32 Development Board

Gas Sensor: MQ-2 (Detects LPG, smoke, methane, etc.)

Sensitivity Control: Potentiometer (for dynamic threshold adjustment)

Alert Actuators: Active Buzzer & Red LED (with 220Ω current-limiting resistor)

Cloud Platform: ThingSpeak IoT

# Circuit Connections
| Component | Component Pin | ESP32 Pin | Description |
| :--- | :--- | :--- | :--- |
| **MQ-2 Gas Sensor** | `VCC` | `5V` (`VIN`) | Sensor heater power supply |
| | `GND` | `GND` | Common Ground |
| | `DOUT` | `GPIO 23` | Digital threshold trigger |
| | `AOUT` | `GPIO 34` | Analog concentration reading |
| **Potentiometer** | `VCC` | `3V3` | 3.3V Power supply |
| | `GND` | `GND` | Common Ground |
| | `SIG` | `GPIO 36` (VP) | Analog signal input for threshold |
| **Buzzer** | Positive (`+`) | `GPIO 18` | Triggers audio alert |
| | Negative (`-`) | `GND` | Common Ground |
| **Red LED & Resistor** | Anode (`+`) *via Resistor* | `GPIO 16` | Triggers visual alert |
| | Cathode (`-`) | `GND` | Common Ground |
