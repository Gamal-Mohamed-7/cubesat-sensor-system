#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// Create an HMC5883L object
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup(void) {
  Serial.begin(9600);
  Serial.println("HMC5883L Magnetometer Test");

  // Initialize the sensor
  if (!mag.begin()) {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    while (1);
  }
}

void loop(void) {
  sensors_event_t event;
  mag.getEvent(&event);

  // Display the magnetometer x, y, z values
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");
  Serial.println("uT");

  delay(1000);
}
