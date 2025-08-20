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
- **sensor**: ADC sensor reading component (GPIO36)
- **display**: Display component (to be added by team member 2)
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
1. Initialize the sensor component
2. Start reading sensor data every second
3. Display ADC value, voltage, and temperature
4. Wait for display and LED components to be integrated

## Team Members

- **67030011**: Sensor component
- **Team Member 2**: Display component
- **Team Member 3**: LED component
