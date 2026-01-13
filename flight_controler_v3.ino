#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>

MPU6050 mpu6050(Wire);

// Servo pins
const int fin1Pin = 9;
const int fin2Pin = 10;
const int fin3Pin = 11;
const int fin4Pin = 12;

// Servos
Servo fin1, fin2, fin3, fin4;
//
// PID control vairiables
const float gain = 0.8;  // P

// Constants
const int center = 90;
const float gyroDeadZone = 1.5;     // deg/s 
const int maxDeflection = 10;        // degrees (VERY IMPORTANT)

unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  fin1.attach(fin1Pin);
  fin2.attach(fin2Pin);
  fin3.attach(fin3Pin);
  fin4.attach(fin4Pin);

  centerFins();
}

void loop() {
  mpu6050.update();

  float gx = mpu6050.getGyroX();  // roll rate
  float gy = mpu6050.getGyroY();  // pitch rate

  // Dead zone
  if (abs(gx) < gyroDeadZone) gx = 0;
  if (abs(gy) < gyroDeadZone) gy = 0;

  // Control law (damping)
  int rollCorrection  = constrain(-gx * gain, -maxDeflection, maxDeflection);
  int pitchCorrection = constrain(-gy * gain, -maxDeflection, maxDeflection);

  // Apply corrections
  fin1.write(center + pitchCorrection); // +Y
  fin2.write(center - pitchCorrection); // -Y
  fin3.write(center + rollCorrection);  // +X
  fin4.write(center - rollCorrection);  // -X

  // Debug (slow)
  if (millis() - lastUpdate > 100) {
    Serial.print("GX: ");
    Serial.print(gx);
    Serial.print(" | GY: ");
    Serial.println(gy);
    lastUpdate = millis();
  }
}

void centerFins() {
  fin1.write(center);
  fin2.write(center);
  fin3.write(center);
  fin4.write(center);
}

