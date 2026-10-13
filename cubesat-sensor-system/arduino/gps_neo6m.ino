#include <SoftwareSerial.h>

// Create a SoftwareSerial object to communicate with the GPS module
SoftwareSerial gpsSerial(4, 3); // RX, TX

void setup() {
  // Start serial communication with a baud rate of 9600
  Serial.begin(9600);
  while (!Serial);

  // Start serial communication with the GPS module
  gpsSerial.begin(9600);

  // Wait for the GPS module to initialize
  delay(1000);
}

void loop() {
  // Check if data is available from the GPS module
  if (gpsSerial.available() > 0) {
    // Read the data from the GPS module
    String data = gpsSerial.readStringUntil('\n');

    // Check if the data starts with '$GPGGA' (GPS fix data)
    if (data.startsWith("$GPGGA")) {
      // Split the data into tokens separated by commas
      String tokens[15];
      int index = 0;
      int startIndex = 0;
      int endIndex = data.indexOf(',');

      while (endIndex != -1) {
        tokens[index] = data.substring(startIndex, endIndex);
        startIndex = endIndex + 1;
        endIndex = data.indexOf(',', startIndex);
        index++;
      }
      tokens[index] = data.substring(startIndex);

      // Extract time, latitude, and altitude
      String time = tokens[1];
      String latitude = tokens[2];
      String altitude = tokens[9];

      // Print the data to the Serial Monitor
      Serial.print("Time: ");
      Serial.print(time);
      Serial.print(" | Latitude: ");
      Serial.print(latitude);
      Serial.print(" | Altitude: ");
      Serial.println(altitude);
    }
  }
}
