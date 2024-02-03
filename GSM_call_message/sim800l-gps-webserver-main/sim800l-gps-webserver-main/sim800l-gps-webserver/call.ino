 void call() {
 // GSM.print("ATD + "); GSM.print(number); GSM.println(";"); //Call to the specific number, ends with semi-colon,replace X with mobile number
  SIM900A.println("ATD+94763701264;");//94767196896 /0759319649
  Serial.println("Calling  ");
  delay(20000);       // wait for 20 seconds...
  
}