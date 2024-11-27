# Automated Environmental Hazard Detection System

## 🌐 Project Overview
An advanced multi-sensor security system designed for comprehensive environmental monitoring and hazard detection using Arduino.

## 🛠 Hardware Components

### Main Controller
- **Arduino Uno R3**

### Sensors
- **Temperature Sensor**: KY-028 Thermistor
- **Gas Detector**: MQ-2 Gas Sensor
- **Distance Monitor**: HC-SR04 Ultrasonic Sensor
- **Light Sensor**: Light Dependent Resistor (LDR)

### Actuators
- **Micro Servo Motor**
- **Red LED Indicator**
- **Active Buzzer**

## 🔌 Circuit Schematic
![circuit_image](https://github.com/user-attachments/assets/595a2191-58c0-4a1a-bf61-64e6eb2b70e2)

## 📋 System Specifications

### Sensor Thresholds
- Temperature: < 50 (Raw Value)
- Gas Concentration: > 200 (Raw Value)
- Light Intensity: > 100 (Raw Value)
- Distance: <= 10 cm

### Alarm Mechanism
- Continuous environmental monitoring
- Real-time sensor value tracking
- Automatic alarm activation
- Servo-based access control

## 🔧 Key Features
- Multi-sensor hazard detection
- Adaptive alarm system
- Serial monitor logging
- Automatic system reset

## 📦 Required Libraries
- Servo.h

## 🚀 Installation Steps
1. Clone the repository
2. Open in Arduino IDE
3. Upload to Arduino Uno R3
4. Connect all sensors as per schematic

## 💡 Usage
- Power on the system
- Monitor serial output
- System will automatically detect and respond to environmental changes

## 🔬 Potential Applications
- Home Security
- Industrial Safety
- Environmental Monitoring

## ⚠️ Limitations
- Requires regular sensor calibration
- Analog sensor precision varies
- Not a replacement for professional safety systems

## 🤝 Contributing
1. Fork the repository
2. Create your feature branch
3. Commit changes
4. Push to the branch
5. Create pull request

## 📄 License
MIT License

## 🛡️ Safety Notice
This is a prototype system. Always complement with professional safety equipment.
