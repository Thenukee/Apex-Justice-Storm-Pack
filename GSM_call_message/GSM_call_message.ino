#include <SoftwareSerial.h>
SoftwareSerial SIM900A(8,7); // RX | TX // done
// Connect the SIM900A TX to Arduino pin 2 RX. 
// Connect the SIM900A RX to Arduino pin 3 TX. 
char c = ' '; // -n
void setup() 
{
// start th serial communication with the host computer
SIM900A.begin(9600);
Serial.begin(9600);
while(!Serial);
Serial.println("Arduino with SIM900A is ready");

// start communication with the SIM900A in 9600
SIM900A.begin(9600); 
Serial.println("SIM900A started at 9600");
delay(1000);
Serial.println("Setup Complete! SIM900A is Ready!");
}

void loop()
{







// Keep reading from Arduino Serial Monitor and send to SIM900A
/*if (Serial.available())
{ c = Serial.read();
SIM900A.write(c); 
}
*/

if (Serial.available()>0)
switch (Serial.read())
{ 
  case 's':
  sendMessage();
  break;
  case 'c':
  makeCall();
  break;
  case 'x':
  hangupCall();
  break;
  case 'r':
  recieveMessage();
  break;
 /* case 'a':
  receiveCall();
  break;
*/
}
// Keep reading from SIM800 and send to Arduino Serial Monitor
if (SIM900A.available()>0)
{ c = SIM900A.read();
Serial.write(c);}


}


void sendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+94772700815\"\r"); //Mobile phone number to send message//94767196896  772700815  //94752382969
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("This is Apex Justice Storm Pack testing messages: ");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ");

}

 void recieveMessage()
{
  Serial.println ("SIM900A Membaca SMS");
  delay (1000);
  SIM900A.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  Serial.write ("Unread Message done");
 }

  void makeCall() {
 // GSM.print("ATD + "); GSM.print(number); GSM.println(";"); //Call to the specific number, ends with semi-colon,replace X with mobile number
  SIM900A.println("ATD+94772700815;");//94767196896
  Serial.println("Calling  ");
  delay(20000);       // wait for 20 seconds...
  
}
void hangupCall(){

  SIM900A.println("ATH"); //hang up
    Serial.println("Cut Call  ");
  delay(1000);
}
