#include <SoftwareSerial.h>
#include <TinyGPS++.h>


#define rxPin 8
#define txPin 9
SoftwareSerial gpsSerial(rxPin,txPin);
TinyGPSPlus gps; //initializing the object name gps


void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(115200);
  
  //Begin serial communication with Arduino and SIM800L
  gpsSerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);
}

void loop()
{
  while (gpsSerial.available() > 0)
    Serial.write(gpsSerial.read());
   // Serial.write(String(gps.location.lat(),6));
    String latt =String(gps.location.lat(),6);
    Serial.print("lattttt"+latt);

}