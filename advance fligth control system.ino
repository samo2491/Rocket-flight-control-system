#include <MPU6050_tockn.h> //scl =A5 / sda =A4 /vcc =5v / grn =grn
#include <Servo.h>
//GPS
#include<TinyGPSPlus.h>
#include <SoftwareSerial.h>
//BMP388 Altimeter
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

// define

#define SEALEVELPRESSURE_HPA (1000)

//start connection between GPS
SoftwareSerial serial_connection(2,3); 
TinyGPSPlus gps;
// buzzer pin 

int servopin1 = 9;  // Servo pin
int servopin2 = 10;
int servopin3 = 11;
int servopin4 = 12;

Servo servo1;   // Servo object 
Servo servo2;
Servo servo3;
Servo servo4;

int pos = 0; //position

MPU6050 mpu6050(Wire);

long timer = 0;

void setup() {
  Serial.begin(9600);
  serial_connection.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  servo1.attach(servopin1);   //attach object to pin 
  servo2.attach(servopin2);
  servo3.attach(servopin3);
  servo4.attach(servopin4);

  // Setup BMP388 values for Temp Altitude and Pressure
  
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  
}

void loop() {
  
  // Print GPS Data
  
  while(serial_connection.available()){
    
    gps.encode(serial_connection.read());}
    if (gps.location.isUpdated()){
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.println(gps.location.lng(), 6);
      
  }

  // Print Altitude
  Serial.println(" ")
  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  mpu6050.update();

  if(millis() - timer > 1000){
    
    // print Gyroscope X and Y angle
    Serial.print("angleX : ");            
    Serial.print(mpu6050.getAngleX());
    Serial.print("  angleY : ");
    Serial.println(mpu6050.getAngleY());

    timer = millis();

  }
      
       //x-axis / roll
      
  if( mpu6050.getAngleX() == 0){                  
   servo2.write(90);    //set to 90 degrees
    }
   servo2.write(90 - mpu6050.getAngleY()); //unstable angle
   
   if( mpu6050.getAngleX() == 0){
      servo1.write(90); //set to 90 degrees
    }
   servo1.write(90 + mpu6050.getAngleY()); //unstable angle

       //y-axis / pitch 
       
   if(mpu6050.getAngleY() == 0){        
    servo3.write(90);//set to 90 degrees
    }
    servo3.write(90 +mpu6050.getAngleX()); //unstable angle
    
   if(mpu6050.getAngleY() == 0){
    servo4.write(90); //set to 90 degrees
    }
    servo4.write(90 - mpu6050.getAngleX());//unstable angle
  
  }
