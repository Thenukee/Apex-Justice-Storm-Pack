#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

void setup() {
  Serial.begin(9600);

  // Initialize the MAX30102 sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 was not found. Please check your wiring/power.");
    while (1);
  }

  // Configure sensor with settings for chest placement
  particleSensor.setup(); 
  particleSensor.setPulseAmplitudeRed(0x0A); // Adjust this value for your needs
  particleSensor.setPulseAmplitudeGreen(0); // Adjust this value for your needs
}

void loop() {
  // Read heart rate and blood oxygen levels
  readHeartRateAndSpO2();
  
  // Wait for a moment before the next reading
  delay(1000);
}

void readHeartRateAndSpO2() {
  // Check for new data
  if (particleSensor.available()) {
    // Read the heart rate and blood oxygen levels
    float hr = particleSensor.getHeartRate();
    float spo2 = particleSensor.getSpO2();

    // Print the values
    Serial.print("Heart Rate: ");
    Serial.print(hr);
    Serial.print(" bpm\t");

    Serial.print("SpO2: ");
    Serial.print(spo2);
    Serial.println("%");
  }
}
