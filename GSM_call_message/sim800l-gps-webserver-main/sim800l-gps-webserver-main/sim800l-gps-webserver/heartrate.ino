

void heartrate(float &BPM,float &AvgBPM)
{
int i=0;
//float BPM, avgBPM;
  while (i<800) { 
    buttonState = digitalRead(buttonPin);
    checkSOS();
    //for accuracy 3000 takes 58 secs
long irValue = particleSensor.getIR();

if (checkForBeat(irValue) == true)
{
//We sensed a beat!
long delta = millis() - lastBeat;
lastBeat = millis();

beatsPerMinute = 60 / (delta / 1000.0);

if (beatsPerMinute < 255 && beatsPerMinute > 20)
{
rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
rateSpot %= RATE_SIZE; //Wrap variable

//Take average of readings
beatAvg = 0;
for (byte x = 0 ; x < RATE_SIZE ; x++)
beatAvg += rates[x];
beatAvg /= RATE_SIZE;
buttonState = digitalRead(buttonPin);
checkSOS();
}
}
buttonState = digitalRead(buttonPin);
checkSOS();

//Serial.print("IR=");
//Serial.print(irValue);
//Serial.print(", BPM=");
//Serial.print(beatsPerMinute);
//Serial.print(", Avg BPM=");
//Serial.print(beatAvg);

//beatsPerMinute=11; // for debugging
BPM=beatsPerMinute;  // going to be sent
AvgBPM=beatAvg;



//if (irValue < 50000)
   // Serial.print(" No finger?");

//  Serial.println();
++i;
  }
   Serial.print(" BPM=");
  Serial.print(BPM);
  Serial.print(", Avg BPM=");
  Serial.print(AvgBPM);
  delay(1000);
  Serial.print("done");


Serial.println();
buttonState = digitalRead(buttonPin);
checkSOS();
}
