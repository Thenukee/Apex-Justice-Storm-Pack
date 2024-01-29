void fullSend(String &url) //sendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+94763701264\"\r"); //Mobile phone number to send message//94767196896  772700815  //94752382969
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println(url);// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ");

}