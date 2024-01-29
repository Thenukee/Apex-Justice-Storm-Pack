String sendDataToServer(String &url,String &acclx,String &accly,String &acclz)
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

       latitude = "latitude"; // Latitude in degrees (double)
      longitude = "longitude";

      
      Serial.print("Latitude= "); 
      Serial.print(latitude);
      Serial.print(" Longitude= "); 
      Serial.println(longitude);
  
      //if (latitude == 0) {return 0;}
      
      String  temp;
      url = "http://gallant-water-56309.pktriot.net/gphw/gpsdata.php?lat=";
      url += latitude;
      url += "&lng=";
      url += longitude;
      url +="&bpm=";
      url +=(String)BPM;    //hr function
      url +="&avgbpm=";
      url +=(String)AvgBPM;
      url +="&accelerometerx=";
      url +=acclx; // accl function
      url +="&accelerometery=";
      url +=accly; // accl function
      url +="&accelerometerz=";
      url +=acclz; // accl function

     




      Serial.println(url);    
      delay(300);
          
    /*sendATcommand("AT+CFUN=1", "OK", 2000);
    //AT+CGATT = 1 Connect modem is attached to GPRS to a network. AT+CGATT = 0, modem is not attached to GPRS to a network
    sendATcommand("AT+CGATT=1", "OK", 2000);
    //Connection type: GPRS - bearer profile 1
  //sendATcommand("AT+CSTT=\"dialogb\",\"\",\"\"","OK"2000);

    sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
    //sets the APN settings for your network provider.
    sendATcommand("AT+SAPBR=3,1,\"APN\",\"dialogbb\"", "OK", 2000);
    //enable the GPRS - enable bearer 1
    sendATcommand("AT+SAPBR=1,1", "OK", 2000);
    //Init HTTP service
    sendATcommand("AT+HTTPINIT", "OK", 2000); 
    sendATcommand("AT+HTTPPARA=\"CID\",1", "OK", 1000);
    //Set the HTTP URL 
    SIM900A.print("AT+HTTPPARA=\"URL\",\"");
    SIM900A.print(url);
    sendATcommand("\"", "OK", 1000);
    //Set up the HTTP action
    sendATcommand("AT+HTTPACTION=0", "0,200", 1000);
    //Terminate the HTTP service
    sendATcommand("AT+HTTPTERM", "OK", 1000);
    //shuts down the GPRS connection. This returns "SHUT OK".
    sendATcommand("AT+CIPSHUT", "SHUT OK", 1000);
*/
  }
  Serial.println(url);
  return url;    
}