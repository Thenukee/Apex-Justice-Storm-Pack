#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

#define rxPin 2 //sim900a
#define txPin 3 //sim900a
SoftwareSerial SIM900A(rxPin,txPin); 

//GPS Module RX pin to Arduino 9
//GPS Module TX pin to Arduino 8    
AltSoftSerial neogps;
//here define gps pins

TinyGPSPlus gps; //initializing the object name gps

unsigned long previousMillis = 0; //setting the 660 seconds interval
long interval = 60000; 


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

  //Once the handshake test is successful, it will back to OK
  sendATcommand("AT", "OK", 2000);
  sendATcommand("AT+CMGF=1", "OK", 2000);
  //SIM900A.print("AT+CMGR=40\r");
  
}

void loop()
{
  while(SIM900A.available()){
    Serial.println(SIM900A.readString());
  }
  while(Serial.available())  {
    SIM900A.println(Serial.readString());
  }


///60 s interval
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
       previousMillis = currentMillis;
       sendGpsToServer();//replace with dataToServer
       //sendDataToServer();
    }
}

int sendGpsToServer()
{
    //Can take up to 60 seconds
    boolean newData = false;
    for (unsigned long start = millis(); millis() - start < 2000;){
      while (neogps.available()){
        if (gps.encode(neogps.read())){

          // this gps is an oblject created by TinyGPSPlus 
          newData = true;
          break;
        }
      }
    }
  
    //If newData is true
    if(true){
      newData = false;
      
      String latitude, longitude;
      float altitude;
      unsigned long date, time, speed, satellites;
  
      latitude = String(gps.location.lat(), 6); // Latitude in degrees (double)
      longitude = String(gps.location.lng(), 6); // Longitude in degrees (double)
      altitude = gps.altitude.meters(); // Altitude in meters (double)
      date = gps.date.value(); // Raw date in DDMMYY format (u32)
      time = gps.time.value(); // Raw time in HHMMSSCC format (u32)
      speed = gps.speed.kmph();
      
      Serial.print("Latitude= "); 
      Serial.print(latitude);
      Serial.print(" Longitude= "); 
      Serial.println(longitude);
  
      //if (latitude == 0) {return 0;}
      
      String url, temp;
      url = "http://gallant-water-56309.pktriot.net/gpsdata.php?lat=";
      url += latitude;
      url += "&lng=";
      url += longitude;
      url +="&heartrate";
      //url +=heartrate;    //hr function
      url +="&accelerometerx";
     // url +=accl; // accl function
      url +="&accelerometery";
    //  url +=accly; // accl function
     
      url +="&accelerometerz";
     // url +=acclz; // accl function

      url +="&heartrate";
      //url +=heartrate;





      Serial.println(url);    
      delay(300);
          
    sendATcommand("AT+CFUN=1", "OK", 2000);
    //AT+CGATT = 1 Connect modem is attached to GPRS to a network. AT+CGATT = 0, modem is not attached to GPRS to a network
    sendATcommand("AT+CGATT=1", "OK", 2000);
    //Connection type: GPRS - bearer profile 1
    sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
    //sets the APN settings for your network provider.
    sendATcommand("AT+SAPBR=3,1,\"APN\",\"internet\"", "OK", 2000);
    //enable the GPRS - enable bearer 1
    sendATcommand("AT+SAPBR=1,1", "OK", 2000);
    //Init HTTP service
    sendATcommand("AT+HTTPINIT", "OK", 2000); 
    sendATcommand("AT+HTTPPARA=\"CID\",1", "OK", 1000);
    //Set the HTTP URL sim800.print("AT+HTTPPARA="URL","http://ahmadssd.000webhostapp.com/gpsdata.php?lat=222&lng=222"\r");
    SIM900A.print("AT+HTTPPARA=\"URL\",\"");
    SIM900A.print(url);
    sendATcommand("\"", "OK", 1000);
    //Set up the HTTP action
    sendATcommand("AT+HTTPACTION=0", "0,200", 1000);
    //Terminate the HTTP service
    sendATcommand("AT+HTTPTERM", "OK", 1000);
    //shuts down the GPRS connection. This returns "SHUT OK".
    sendATcommand("AT+CIPSHUT", "SHUT OK", 1000);

  }
  return 1;    
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
