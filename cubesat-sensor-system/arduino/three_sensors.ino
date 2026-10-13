#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Define the pin where the DHT11 is connected
#define DHTPIN 2
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Create an HMC5883L object
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// Create a SoftwareSerial object to communicate with the GPS module
SoftwareSerial gpsSerial(4, 3); // RX, TX
TinyGPSPlus gps;

void setup() {
  // Start serial communication
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Initialize the DHT sensor
  dht.begin();
  Serial.println("DHT sensor initialized.");

  // Start serial communication with the GPS module
  gpsSerial.begin(9600);
  Serial.println("GPS serial initialized.");

  // Initialize the magnetometer
  if (!mag.begin()) {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    while (1);
  }
  Serial.println("Magnetometer initialized.");
}

void loop() {
  Serial.println("Entering loop...");
  
  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // Read magnetometer data
  sensors_event_t event;
  mag.getEvent(&event);

  // Prepare sensor data string
  String dataString = "----- Sensor Data -----\n";
  dataString += "Humidity: " + String(humidity) + "%\n";
  dataString += "Temperature: " + String(temperature) + "°C\n";
  dataString += "Magnetometer X: " + String(event.magnetic.x) + " µT\n";
  dataString += "Magnetometer Y: " + String(event.magnetic.y) + " µT\n";
  dataString += "Magnetometer Z: " + String(event.magnetic.z) + " µT\n";

  // Process GPS data if available
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    dataString += "----- GPS Data -----\n";
    dataString += "Latitude: " + String(gps.location.lat(), 6) + "\n";
    dataString += "Longitude: " + String(gps.location.lng(), 6) + "\n";
    dataString += "Altitude: " + String(gps.altitude.meters()) + " meters\n";
    dataString += "UTC Time: " + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()) + "\n";
    
    int localHour = gps.time.hour() + 2; // Convert UTC to Egypt time (UTC+2)
    String ampm = (localHour >= 12) ? "PM" : "AM";
    if (localHour > 12) localHour -= 12;
    else if (localHour == 0) localHour = 12;

    dataString += "Local Time (Egypt): " + String(localHour) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()) + " " + ampm + "\n";
    dataString += "Date: " + String(gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year()) + "\n";
    dataString += "----------------------------------------";
  } else {
    dataString += "No GPS data available\n";
  }

  // Send the data string to the Raspberry Pi
  Serial.println(dataString);

  delay(2000); // Delay between readings
}
