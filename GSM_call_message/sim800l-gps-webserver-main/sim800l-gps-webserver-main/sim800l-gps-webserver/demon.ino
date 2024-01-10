#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

#define rxPin 2 //sim900a
#define txPin 3 //sim900a
SoftwareSerial SIM900A(txPin,rxPin); 
//SoftwareSerial SIM900A(8,7); // RX | TX // done green-7 orange-8


//GPS Module RX pin to Arduino 9 green
//GPS Module TX pin to Arduino 8    
AltSoftSerial neogps;
//here define gps pins

TinyGPSPlus gps; //initializing the object name gps

unsigned long previousMillis = 0; //setting the 660 seconds interval
long interval = 60000; 


//heart rate
#include <Wire.h>
#include "MAX30105.h"

#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute ,BPM=0.0 ,AvgBPM=0.0;
int beatAvg;

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;





void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(115200);
  
  //Begin serial communication with Arduino and SIM900A
  SIM900A.begin(9600);

  //Begin serial communication with Arduino and SIM900A
  neogps.begin(9600);



  Serial.println("Initializing...");
  //delay(10000);

  // Initialize heart rate sensor

  /*
if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
{
Serial.println("MAX30105 was not found. Please check wiring/power. ");
while (1);
}
*/
//not gonna go in main Serial.println("Place your index finger on the sensor with steady pressure.");

particleSensor.setup(); //Configure sensor with default settings
particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED


//heart rate senser done

  //Once the handshake test is successful, it will back to OK
 //Once the handshake test is successful, it will back to OK
  sendATcommand("AT", "OK", 2000);
  sendATcommand("AT+CMGF=1", "OK", 2000);
  //sim800L.print("AT+CMGR=40\r");
  
/*
  sendATcommand("AT+CSTT=\"dialogb\",\"\",\"\"","OK"2000);
  sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"","OK",2000);
  sendAtcommand("AT+SAPBR=3,1,\"APN\","dialogbb\"","OK",2000);
  sendAtcommand("AT+SAPBR=1,1,","OK",2000);
  sendAtcommand("AT+HTTPINIT","OK",2000);

*/

  //gprsSerial.println("AT");
  
  
  delay(1000);
//AT+CFUN=1
//AT+CGATT=1

//AT+SAPBR=3,1,"APN","internet"
//AT+SAPBR=1,1


  



  // Try to initialize Accelerometer!
if (!mpu.begin()) {
Serial.println("Failed to find MPU6050 chip");
while (1) {
delay(1000);
}
}

// set accelerometer range to +-8G
mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

// set gyro range to +- 500 deg/s
mpu.setGyroRange(MPU6050_RANGE_500_DEG);

// set filter bandwidth to 21 Hz
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

delay(1000);
}

void loop()
{
  /*
  while(SIM900A.available()){
    Serial.println(SIM900A.readString());
  }
  while(Serial.available())  {
    SIM900A.println(Serial.readString());
  }
*/

///60 s interval
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
       previousMillis = currentMillis;
       heartrate();
       accel();
       sendDataToServer();//replace with dataToServer
       //sendDataToServer();
    }
}



int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    //Initialice the string
    memset(response, '\0', 100);
    delay(100);
    
    //Clean the input buffer
    while( SIM900A.available() > 0) SIM900A.read();
    
    if (ATcommand[0] != '\0'){
      //Send the AT command 
      SIM900A.println(ATcommand);
    }

    x = 0;
    previous = millis();

    //this loop waits for the answer with time out
    do{
        //if there are data in the UART input buffer, reads it and checks for the asnwer
        if(SIM900A.available() != 0){
            response[x] = SIM900A.read();
            //Serial.print(response[x]);
            x++;
            // check if the desired answer (OK) is in the response of the module
            if(strstr(response, expected_answer) != NULL){
                answer = 1;
            }
        }
    }while((answer == 0) && ((millis() - previous) < timeout));

  Serial.println(response);
  return answer;
}



//-----------------------------------------------------------------------------------------------------------------------------
//boolean sendATcommand(String expected_answer="OK", unsigned int timeout=2000) //uncomment if syntax error (arduino)
/*
boolean sendATcommand(String ATcommand, String expected_answer, unsigned int timeout) //uncomment if syntax error (esp8266)
{
  uint8_t x=0, answer=0;
  String response;
  unsigned long previous;
    
  //Clean the input buffer
  while( SIM800.available() > 0) SIM800.read();
  SIM900A.println(ATcommand);
  
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  previous = millis();
  do{
    //if data in UART INPUT BUFFER, reads it
    if(SIM800.available() != 0){
        char c = SIM800.read();
        response.concat(c);
        x++;
        //checks if the (response == expected_answer)
        if(response.indexOf(expected_answer) > 0){
            answer = 1;
        }
    }
  }while((answer == 0) && ((millis() - previous) < timeout));
  //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  
  Serial.println(response);
  return answer;
  
} 
*/
//-----------------------------------------------------------------------------------------------------------------------------

//AT+CFUN=1
//AT+CGATT=1
//AT+SAPBR=3,1,"Contype","GPRS"
//AT+SAPBR=3,1,"APN","internet"
//AT+SAPBR=1,1
