# CubeSat Sensor System (2U)

Graduation project, Space Science, Helwan University (2023/2024).

## Overview
An on-board computer for a 2U CubeSat. An Arduino Uno reads three sensors
and sends the data over USB serial to a Raspberry Pi, which reads it with Python.

## Sensors
- DHT11: temperature and humidity
- NEO-6M: GPS (latitude, altitude, time)
- HMC5883L: magnetometer (X, Y, Z in µT)

## How it works
1. Arduino reads all sensors every 2 seconds
2. Data is sent over serial (9600 baud)
3. Raspberry Pi reads it using read_arduino.py

## My role
Soldering and wiring of the sensors inside the satellite, Arduino and
Python code, system assembly.

## Sample output
![Serial output](images/serial_output.png)

## Team
Project built by a team of 5 students, supervised by Prof. Mohamed Youssef
(Helwan University) and the Egyptian Space Agency (EgSA).
