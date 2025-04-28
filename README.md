# IoT-Based Air Quality Monitoring System

## Overview
This project is an **IoT-based Air Quality Monitoring System** that collects environmental data, including gas levels, particulate matter (PM2.5, PM10), temperature, pressure, and humidity. The system uses **Arduino Uno** to interface with **8 MQ sensors** and sends data to an **ESP32** via **serial communication**. The ESP32 manages additional sensors (**PMS5003** for particulate matter and **BMP280** for environmental conditions) and transmits real-time data to the cloud.

## Components Used
- **Arduino Uno**
  - Interfacing with 8 MQ gas sensors (for detecting gases like CO, LPG, and methane)
- **ESP32**
  - Handling data communication and managing additional sensors
- **MQ Sensors (8 units)**
  - To detect various gases
- **PMS5003**
  - For measuring particulate matter (PM2.5, PM10)
- **BMP280**
  - To monitor temperature, humidity, and atmospheric pressure
- **Jumper Wires, Breadboard**
  - For connections
- **Power Source**
  - To power the Arduino and ESP32

## System Architecture
The system consists of two main modules:
1. **Arduino Uno**: Reads the data from the 8 MQ sensors and transmits it to the ESP32 via serial communication.
2. **ESP32**: Receives data from the Arduino, interfaces with the PMS5003 and BMP280 sensors, and sends all the data to the cloud for remote monitoring.

## Features
- Real-time monitoring of air quality
- Displays environmental data such as gas levels, particulate matter, temperature, pressure, and humidity
- Data transmission from Arduino to ESP32 using serial communication
- Integration of multiple sensors (MQ gas sensors, PMS5003, BMP280)
- Cloud-based data visualization (future enhancements can include web/mobile app integration)

## Software/Programming
- **Arduino Programming Language (C)**: Used for coding the Arduino to read data from the sensors and send it to the ESP32.
- **ESP32 Programming (C)**: Used to manage the communication with the Arduino and the other sensors, and send the data for further analysis or display.

## Circuit Diagram
(Attach the circuit diagram here)

## Setup Instructions
1. **Hardware Setup**:
   - Connect the **8 MQ sensors** to the **Arduino Uno**.
   - Connect the **PMS5003** and **BMP280** sensors to the **ESP32**.
   - Use jumper wires and a breadboard for connections.

2. **Software Setup**:
   - Upload the Arduino code to the **Arduino Uno** via the Arduino IDE.
   - Upload the ESP32 code to the **ESP32** via the Arduino IDE or another compatible platform.
   - Ensure that both the Arduino and ESP32 are connected to the same power source and the communication is set up correctly.

3. **Testing**:
   - Once the code is uploaded, the system will begin collecting data from all sensors and transmitting it to the ESP32.
   - The data can be displayed via the cloud or any interface set up in the future.

## Future Enhancements
- Integration with cloud platforms (e.g., Firebase, ThingSpeak)
- Real-time data visualization on a web app or mobile app
- Integration with alert systems (e.g., email or SMS notifications when air quality is poor)



