/*
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>

const int SOS = 8;  // the number of the pushbutton pin
bool makeCallFlag = false;

unsigned long previousMillis = 0; 
long interval = 60000; 

void setup(){
    pinMode(SOS, INPUT);// emegancy call button

}

void loop(){
    //checking for call button
    if (digitalRead(SOS) == HIGH){
        makeCallFlag==true; }

        testSOS();
      

    // run this loop with 60 seconds intervals 
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
       previousMillis = currentMillis;
         //  collectHeartRate();
         // collectGPS();
         // collectMPU();
         // sendToServer();


//checking for call button
testSOS();
        

}
// if pin 8 is high, make a call to +94759319649
if (digitalRead(SOS) == HIGH||makeCallFlag==true) {
  makeCall();
  makeCallFlag==false;
}
}
void makeCall() {
  // make a call to +94759319649

// GSM.print("ATD + "); GSM.print(number); GSM.println(";"); //Call to the specific number, ends with semi-colon,replace X with mobile number
  SIM900A.println("ATD+94759319649;");//94767196896 /0759319649
  Serial.println("Calling  ");
  delay(10000);       // wait for 10 seconds...

  //if answered play the talkie 
 
  makeCallFlag==false;


}

void testSOS(){
 if (digitalRead(SOS) == HIGH||makeCallFlag==true) {
  makeCall();
  makeCallFlag==false;

  /*this is for the SOS trigger , 
  define 
  const int SOS = 8;  // the number of the pushbutton pin
  bool makeCallFlag = false;


  inside setup
    pinMode(SOS, INPUT);// emegancy call button
  

}
  */
 //}
//}
void checkSOS() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is LOW:
  if (buttonState == LOW) {
    // Call the function when the button is pressed
    call();
    buttonState=HIGH;
  } else {
    // turn LED off:
  }
}
