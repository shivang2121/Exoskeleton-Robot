#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 accelgyroIC1(0x68);
MPU6050 accelgyroIC2(0x69);

int thighA = 2;
int thighB = 4;
int calfA =  8;
int calfB = 7;
int thighPWM = 5;
int calfPWM = 6;

int transit, thigh, calf;
int gyro1, gyro2;
int16_t gx1, gy1, gz1;
int16_t gx2, gy2, gz2;
char val;

void MotorDriverState(int pin1, int pin2, int pin3, int pwm);

void setup() {
  pinMode(thighA, OUTPUT);
  pinMode(thighB, OUTPUT);
  pinMode(calfA, OUTPUT);
  pinMode(calfB, OUTPUT);
  pinMode(thighPWM, OUTPUT);
  pinMode(calfPWM, OUTPUT);

  Wire.begin();
  Serial.begin(9600);
  accelgyroIC1.initialize();
  accelgyroIC2.initialize();
  
  if(accelgyroIC1.testConnection() || accelgyroIC2.testConnection() == false){
    exit(0);
  }
  
  establishContact();
}

void loop(){
  accelgyroIC1.getRotation(&gx1, &gy1, &gz1);
  accelgyroIC2.getRotation(&gx2, &gy2, &gz2);

  gyro1 = gz1 + 1024;
  gyro2 = gz2;
  
  if (Serial.available() > 0) {
    val = Serial.read();

    if(val<0){
      calf = val + 128;
    }
    else{
      thigh = val;
    }
    MotorDriverState(thighA, thighB, thighPWM, thigh);
    MotorDriverState(calfA, calfB, calfPWM, calf);
    delay(5);
  } 
  else{
    Serial.println(gyro1+gyro2);
    delay(5);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");
  delay(300);
  }
}

void MotorDriverState(int pin1, int pin2, int pin3, int pwm){
  float speed = map(pwm, 0, 126, -255, 255);
  
  if (speed > 0){
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(pin3, speed);
  } else if (speed < 0){
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(pin3, abs(speed));
  } else if (speed == 0){
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    analogWrite(pin3, 0);
  }
}


