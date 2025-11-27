# Rocket-flight-control-system
stage 1 of development

## 🌟 Highlights
- 
- 

- 
## ℹ️ Overview
Simple rocket flight controll system for the pitch and roll axis

Pin out:
wiring
Gyroscope
scl =A5

sda =A4

vcc =5v

grn =grn

servo
int servopin1 = 9;

int servopin2 = 10;

int servopin3 = 11;

int servopin4 = 12;

###✍️ Authors
This was made by samo2491 I am a young tech enthousiest that wants to try
and make some crazy projects on a budget so that people can do to

## 🚀 Usage
This is the basic principle be hind the basic code it acounts for the angle
of set the spins the fins in the opposet dierection to conter the spining
or rolling of th rocket.
```py
>>>if( mpu6050.getAngleX() == 0){
>>>    servo1.write(90); //set to 90 degrees
>>>}
>>>servo1.write(90 + mpu6050.getAngleY());
```

'Oh yeah!'
## ⬇️ Installation
Download the file
open it in the arduino ide
and then upload the code to a arduino uno 

## 💭 Feedback and Contributing
if u have any feedback please let me know so i can improve it
