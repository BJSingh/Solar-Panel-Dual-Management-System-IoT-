uint32_t value = 0;

float vout = 0.0;
float vin = 0.0;
float R1 = 470000.0; // resistance of R1 (470k) 
float R2 = 47000.0; // resistance of R2 (47K) 

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);    // initialize serial communication at 9600 bits per second:
}

// the loop routine runs over and over again forever:
void loop() {
    float avgCurrent = 0,avgVolt=0,clb;
// read the value at analog input A0(Current)
    for(int i = 0; i < 1000; i++) {
      avgCurrent = avgCurrent + (.0264 * analogRead(A0)-13.51);
      delay(1);
    }
    Serial.print("  Current =");
    Serial.print(avgCurrent);
    Serial.print("mA");
// read the value at analog input A2(Voltage)
    for(int i=0;i<100;i++){
      value = analogRead(A2);
      vout = (value * 5.0) / 1024.0;
      vin = vout*(R1+R2)/R2; 
      clb=vin*0.767;
      vin=vin+clb;
      avgVolt=avgVolt+vin;
    }
    avgVolt=avgVolt/100.0;
    Serial.print("\tVoltage =");
    Serial.println(avgVolt,1);
}
