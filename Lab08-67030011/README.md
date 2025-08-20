# Lab08-67030011

ESP32 project for Lab-08 teamwork development.

## Project Structure

```
Lab08-67030011/
├── CMakeLists.txt
├── main/
│   ├── CMakeLists.txt
│   ├── main.c
│   └── idf_component.yml
└── README.md
```

## Components

This project uses the following components:
- **sensor**: ADC sensor reading component (GPIO36) - from https://github.com/Kritternai/Lab-08-teamwork-dev-for-esp32.git
- **display**: Display component - from https://github.com/Job-67/Lab-08-teamwork-dev-for-esp32.git
- **led**: LED control component (to be added by team member 3)

## Building and Running

1. Set up ESP-IDF environment:
   ```bash
   . $IDF_PATH/export.sh
   ```

2. Build the project:
   ```bash
   idf.py build
   ```

3. Flash to ESP32:
   ```bash
   idf.py flash monitor
   ```

## Hardware Requirements

- ESP32 development board
- LM35 temperature sensor (or similar analog sensor)
- Display module (to be specified by team member 2)
- LED module (to be specified by team member 3)

## Sensor Connection

Connect the LM35 temperature sensor:
- VCC → 3.3V
- GND → GND
- Signal → GPIO36 (ADC1_CHANNEL_0)

## Expected Output

The application will:
1. Initialize the sensor and display components
2. Start reading sensor data every second
3. Display sensor data (ADC value, voltage, temperature) on the screen
4. Update display in real-time with sensor readings
5. Wait for LED component to be integrated

## Team Members

- **67030011**: Sensor component
- **Job-67**: Display component
- **Team Member 3**: LED component

## Component Sources

- **Sensor Component**: https://github.com/Kritternai/Lab-08-teamwork-dev-for-esp32.git
- **Display Component**: https://github.com/Job-67/Lab-08-teamwork-dev-for-esp32.git
