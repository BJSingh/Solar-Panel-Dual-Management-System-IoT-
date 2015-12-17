
uint32_t analogPin = A0;   
uint32_t value = 0;

float vout = 0.0;
float vin = 0.0;
float R1 = 470000.0;// resistance of R1 (470k) 
float R2 = 47000.0; // resistance of R2 (47K) 

void setup()
{
   Serial.begin(9600);
}
void loop()
{
    // read the value at analog input
    value = analogRead(analogPin);
    Serial.print("Analog Value =");
    Serial.println(value);
    vout = (value * 5.0) / 1024.0;
    vin = vout*(R1+R2)/R2; 
    Serial.print("Voltage =");
    Serial.println(vin);
    delay(2000);
}

