

void accel(String &acclx,String &accly,String &acclz) {
/* Get new sensor events with the readings */
sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);

/* Print out the values */
Serial.print(a.acceleration.x);
acclx=a.acceleration.x;
acclx=a.acceleration.y;
acclx=a.acceleration.z;

Serial.print(",");
Serial.print(a.acceleration.y);
Serial.print(",");
Serial.print(a.acceleration.z);
Serial.print(", ");
Serial.print(g.gyro.x);
Serial.print(",");
Serial.print(g.gyro.y);
Serial.print(",");
Serial.print(g.gyro.z);
Serial.println("");

delay(1000);
}
