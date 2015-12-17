#include <Wire.h>      //library to establised I2C communication between LinkIt One and Grove - 3-Axis Digital Accelerometer(±16g)
#include <ADXL345.h>  //This library of ADXL345 used extract data read by sensor in various forms

ADXL345 adxl;       //variable adxl is an instance of the ADXL345 library

int x_initial,y_initial,z_initial;
double xyz_initial[3];
double ax_initial,ay_initial,az_initial;

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
 
  Serial.print("values of X , Y , Z: ");
  Serial.print(x);
  Serial.print(" , ");
  Serial.print(y);
  Serial.print(" , ");
  Serial.println(z);

  
  double xyz[3];
  double ax,ay,az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];


  Serial.print("X=");
  Serial.print(ax);
    Serial.println(" g");
  Serial.print("Y=");
  Serial.print(ay);
    Serial.println(" g");
  Serial.print("Z=");
  Serial.println(az);
    Serial.println(" g");
  Serial.println("**********************");


  if((int)ax!=(int)ax_initial){
      Xchange=1;   
  } 
  else {
      Xchange=0;
  }
  
  Serial.print("Xchange:");
  Serial.println(Xchange);

  if((int)ay!=(int)ay_initial){
      Ychange=1;   
  } 
  else {
      Ychange=0;
  }
 
  Serial.print("Ychange:");
  Serial.println(Ychange);

  if((int)az!=(int)az_initial){
      Zchange=1;   
  } 
  else {
      Zchange=0;
  }
  
  Serial.print("Zchange:");
  Serial.println(Zchange);
  
  if((Xchange==1)||(Ychange==1)||(Zchange==1)){
    return 1;
  }
  else return 0;
  
  }
void setup(){
  Serial.begin(9600);
  delay(5000);
  adxl.powerOn();
  axis_initialization();
  Serial.println("SP DMS");
}

void loop(){
  int unauthorised_activity;
  unauthorised_activity=compareResult();
  if(unauthorised_activity==1){
    Serial.println("There is unauthorised activity...");
    }  
 delay(500);

}
