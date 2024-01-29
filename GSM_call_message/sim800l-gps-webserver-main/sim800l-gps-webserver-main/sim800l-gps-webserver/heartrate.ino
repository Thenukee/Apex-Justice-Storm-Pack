

void heartrate(float &BPM,float &AvgBPM)
{
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
}
}

Serial.print("IR=");
Serial.print(irValue);
Serial.print(", BPM=");
Serial.print(beatsPerMinute);
Serial.print(", Avg BPM=");
Serial.print(beatAvg);

beatsPerMinute=11; // for debugging
while (beatsPerMinute < 10){
  
Serial.print(" No finger?");
Serial.println("");
heartrate(BPM,AvgBPM);
}
//BPM=beatsPerMinute;  // going to be sent
//AvgBPM=beatAvg;
//debugging only 
BPM=76.0;  // going to be sent
AvgBPM=81.0;


Serial.println();
}
