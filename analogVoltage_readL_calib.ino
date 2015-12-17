
uint32_t analogPin = A2;   
uint32_t value = 0;

float vout = 0.0;
float vin = 0.0;
float R1 = 470000.0; // resistance of R1 (470k) 
float R2 = 47000.0; // resistance of R2 (47K) 

void setup()
{
   Serial.begin(9600);
}
void loop()
{
    float avgVolt=0,clb;
    // read the value at analog input
    for(int i=0;i<100;i++){
      value = analogRead(analogPin);
      vout = (value * 5.0) / 1024.0;
      vin = vout*(R1+R2)/R2; 
      clb=vin*0.767;
      vin=vin+clb;
      avgVolt=avgVolt+vin;
    }
    avgVolt=avgVolt/100.0;
    Serial.print("Voltage =");
    Serial.println(avgVolt,1);
    
}

