//Code to measure current AC/DC using ACS712 sensor module(5A model)
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);    // initialize serial communication at 9600 bits per second:
}

// the loop routine runs over and over again forever:
void loop() {
float average = 0;
for(int i = 0; i < 1000; i++) {
average = average + (.0264 * analogRead(A0)-13.51);
delay(1);
}
Serial.print(average);
Serial.println("mA");
}
