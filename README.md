# FogCast – UV-Sensor & Temperature Sketches

This repository contains several Arduino sketches (`.ino`, written in C++) for driving various sensors used in the FogCast project. The sketches target development boards and the Raspberry Pi Pico, covering different stages of the sensor setup — from single-sensor tests to the full outdoor/indoor station architecture.

## Sketch Overview

| Folder | Description | Sensors |
|---|---|---|
| `sketch_AS7331` | Basic sketch for driving the UV sensor | AS7331 (UV sensor) |
| `sketch_AS7331_und_SHT-30` | Combination of UV sensor and temperature/humidity sensor | AS7331, SHT-30 |
| `sketch_DHT22` | Temperature and humidity measurement sketch | DHT22 |
| `sketch_Pico2_with_AS7331_SHT30-Outdoor_SHT30-Indoor_MPU6886` | Full architecture for combined outdoor/indoor sensing on the Raspberry Pi Pico 2 (without ceilometer) | AS7331, SHT-30 (outdoor), SHT-30 (indoor), MPU6886 |

## Sensors at a Glance

- **AS7331** – Spectral UV sensor (UVA/UVB/UVC) for UV index measurement
- **SHT-30** – Digital temperature and humidity sensor. In the full setup, two SHT-30 units are used simultaneously: one for outdoor and one for indoor readings.
- **DHT22** – Temperature and humidity sensor (used as an alternative/reference sensor to the SHT-30)
- **MPU6886** – 6-axis Inertial Measurement Unit (IMU) combining a 3-axis accelerometer and a 3-axis gyroscope, used to capture motion, tilt, and orientation data (e.g. for detecting vibration or movement of the sensor housing)

## Requirements

- Arduino IDE (or PlatformIO)
- For the Pico 2 sketch: support for the Raspberry Pi Pico 2 (Arduino-Mbed core or the corresponding board package)
- Required libraries depending on the sketch, including:
  - Adafruit AS7331 library (or manufacturer library)
  - Adafruit SHT31/SHT30 library
  - DHT sensor library (Adafruit)
  - MPU6886 library (e.g. from Sparkfun or M5Stack, depending on the module used)
  - Wire (I2C)

## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/<your-user>/FogCast_sketch_UV-Sensor_and_temperature.git
   ```
2. Open the desired sketch folder in the Arduino IDE
3. Install the required libraries via the Library Manager
4. Select the correct board and port
5. Upload the sketch

## Note

The `sketch_Pico2_with_AS7331_SHT30-Outdoor_SHT30-Indoor_MPU6886` sketch currently represents the most complete architecture, but **does not yet include ceilometer integration**. This is planned for a future version.

## Project Context

FogCast is a project for fog/weather sensing and forecasting based on combined environmental sensor data (UV, temperature, humidity, and motion/orientation).
