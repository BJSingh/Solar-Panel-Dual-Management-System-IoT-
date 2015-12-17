#include <Wire.h>      //library to establised I2C communication between LinkIt One and Grove - 3-Axis Digital Accelerometer(±16g)
#include <ADXL345.h>  //This library of ADXL345 used extract data read by sensor in various forms

//Accelerometer variables
ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

//variables to store the initial state of device after installation when power on 
int x_initial,y_initial,z_initial;
double xyz_initial[3];
double ax_initial,ay_initial,az_initial;

//variables for Voltage reading
uint32_t Volt_value = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 470000.0; // resistance of R1 (470k) 
float R2 = 47000.0; // resistance of R2 (47K) 

//variables for Dust Sensor
int pin = 2;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

//Function to Store initial axis value of x,y & z for comparision  
void axis_initialization(){  
  adxl.readXYZ(&x_initial, &y_initial, &z_initial); //read the accelerometer values and store them in variables  x_initial,y_initial,z_initial
  adxl.getAcceleration(xyz_initial);
  ax_initial = xyz_initial[0];
  ay_initial = xyz_initial[1];
  az_initial = xyz_initial[2];
  delay(500);
 }

//To compare initial values with current reading of x,y & z values for theft protection
int compareResult(){
  //Boring accelerometer stuff   
  int x,y,z,Xchange,Ychange,Zchange;  
  adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
  // Output x,y,z values 
  double xyz[3];
  double ax,ay,az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];

  if((int)ax!=(int)ax_initial){
      Xchange=1;   
  } 
  else {
      Xchange=0;
  }

  if((int)ay!=(int)ay_initial){
      Ychange=1;   
  } 
  else {
      Ychange=0;
  }

  if((int)az!=(int)az_initial){
      Zchange=1;   
  } 
  else {
      Zchange=0;
  }
  
  if((Xchange==1)||(Ychange==1)||(Zchange==1)){
    return 1;
  }
  else return 0;
}

void DustCal(){
    duration = pulseIn(pin, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;
  
    if ((millis()-starttime) > sampletime_ms)
    {
      ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
      concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
      Serial.print("  lowpulseoccupancy: ");
      Serial.print(lowpulseoccupancy);
      Serial.print(",");
      Serial.print("ratio: ");
      Serial.print(ratio);
      Serial.print(",");
      Serial.print("concentration: ");
      Serial.println(concentration);
      lowpulseoccupancy = 0;
      starttime = millis();
    } 
    Serial.println();
  }
  
void setup(){
  Serial.begin(9600);
  adxl.powerOn();
  axis_initialization();
  pinMode(2,INPUT);
  starttime = millis();
}

void loop(){
  int unauthorised_activity=0;
  unauthorised_activity=compareResult();
  
  if(unauthorised_activity==1){
    Serial.println("There is unauthorised activity...");
    }
   else {
      float avgCurrent = 0,avgVolt=0,clb=0;
      
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
        Volt_value = analogRead(A2);
        vout = (Volt_value * 5.0) / 1024.0;
        vin = vout*(R1+R2)/R2; 
        clb=vin*0.767;
        vin=vin+clb;
        avgVolt=avgVolt+vin;
      }
      avgVolt=avgVolt/100.0;
      Serial.print("\tVoltage =");
      Serial.print(avgVolt,1);
      Serial.print("V");
      Serial.print("\tPower =");
      Serial.print((avgCurrent/1000.0)*avgVolt);
      Serial.println("W");
      
      DustCal();
      
    }  
 delay(500);
}









