# Smart Traffic Light System with Adaptive Signal

This project implements a smart traffic light control system using **ESP32** and **IR sensors** to dynamically manage traffic at a 4-way intersection. It uses sensor data to determine traffic density and safely prioritize lanes with the highest vehicle presence. Built for real-world scalability and safety.

## 🚦 Features

- Vehicle detection using IR sensors (1 per lane)
- Adaptive signal timing based on real-time density
- Ensures only one lane is green at a time to avoid accidents
- 5-second safety delay between transitions
- Prioritization of lanes with vehicles to minimize wait time
- Configurable traffic light durations

## 🧰 Hardware Components

- 1 × ESP32 Dev Board
- 4 × IR Sensors (TCRT5000 or similar)
- 12 × LEDs (Red, Yellow, Green per lane)
- 12 × 220Ω Resistors
- 4 × Breadboards
- Jumper Wires
- Micro-USB Cable

## 🔌 Wiring Overview

Each lane uses one breadboard with 3 LEDs (Red, Yellow, Green) and an IR sensor. All components are wired to the ESP32. LEDs control the traffic lights while IR sensors detect approaching vehicles.

Refer to `Traffic Light Control System.ino` for pin mapping.

## 🛠 Setup Instructions

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board in **Boards Manager**
3. Clone this repository:

```bash
git clone https://github.com/HEETMEHTA18/Smart-Traffic-Light-System-With-Adaptive-Siganal.git
```

4. Open the `.ino` file in Arduino IDE
5. Connect your ESP32 via USB
6. Upload the code
7. Power the setup and test vehicle detection with hand/object

## 📁 File Structure

```
Smart-Traffic-Light-System-With-Adaptive-Siganal/
├── Traffic Light Control System.ino   # Main Arduino Code
├── README.md                          # Project Documentation
```

## 🔒 Safety Measures

- Only one lane has a green light at a time
- 5s delay ensures lights don’t switch immediately between lanes
- Lane transitions are clean to avoid simultaneous green signals

## 📃 License

This project is free to use for educational and personal projects.

---

Built by [HEET MEHTA](https://github.com/HEETMEHTA18)
[URVAL KHENI](https://github.com/urvalkheni) 
[OM MISTRY](https://github.com/ommistry223)
