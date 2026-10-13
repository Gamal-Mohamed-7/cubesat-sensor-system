#include "DHT.h"

#define DHTPIN 2    // Pin which is connected to the DHT sensor
#define DHTTYPE DHT11   // KY-015 uses the DHT11 sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 sensor reading");

  dht.begin();
}

void loop() {
  delay(2000);

  Serial.println("Reading data from DHT sensor...");
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" *C\t");
    Serial.print("Heat index: ");
    Serial.print(heatIndex);
    Serial.println(" *C");
  }
}
