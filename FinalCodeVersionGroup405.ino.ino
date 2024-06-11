#include <Wire.h>
#include <LIS3MDL.h>
#include <LSM6.h>
#include <SimpleTimer.h>
#include <EEPROM.h>
#include <BasicEncoder.h>
#include <TimerOne.h>
#include <Servo.h>



unsigned long previousMillis;

int solenoidPin = 2;
int count;

int CF2 = 0.75;  //A value we mulitplied by the second wheel to keep the wheel base adjustment correct for turning each wheel


LIS3MDL mag;
LSM6 imu;

LIS3MDL::vector<int16_t> m_min = { -3452, -5491, +7697};    //calibrated values for our magnetometer
LIS3MDL::vector<int16_t> m_max = {-120, -2244, +8804};



float  -3452 <= magSet <= -120;

float currentHeading = mag;



//lights, camera!
void setup() {
  // put your setup code here, to run once:

pinMode(solenoidPin, OUTPUT);
Serial.begin(9600);
previousMillis = millis();








}








//Action.
void loop() {
  // put your main code here, to run repeatedly:


if (millis() - previousMillis < 300)

{

  digitalWrite(solenoidPin, HIGH);

}

else if (millis() - previousMillis > 300 and millis() - previousMillis < 600)  {
digitalWrite(solenoidPin, LOW);

}

else if (millis() - previousMillis > 600) {
previousMillis = millis();



}


}








////////////// REED SWITCH ///////////////////////////////////////////////////
  switchState = digitalRead(switchPin);

////////////// Serial Print  ///////////////////////////////////////////////////
  Serial.print("Reed Switch: ");
  Serial.print(switchState);
  Serial.print("   Magnetometer: ");
  Serial.println(heading);
  Serial.print("  CurrentMillis: ");
  Serial.print(currentMillis);
  Serial.print("  SolenoidState: ");
  Serial.print(solenoidState);
  Serial.print("  ");


  //delay(100);
}




//heading function for magnetometer

template <typename T> float computeHeading(LIS3MDL::vector<T> from)
{
  LIS3MDL::vector<int32_t> temp_m = {mag.m.x, mag.m.y, mag.m.z};

  // copy acceleration readings from LSM6::vector into an LIS3MDL::vector
  LIS3MDL::vector<int16_t> a = {imu.a.x, imu.a.y, imu.a.z};

  // compute E and N
  LIS3MDL::vector<float> E;
  LIS3MDL::vector<float> N;
  LIS3MDL::vector_cross(&temp_m, &a, &E);
  LIS3MDL::vector_normalize(&E);
  LIS3MDL::vector_cross(&a, &E, &N);
  LIS3MDL::vector_normalize(&N);

  // compute heading
  float heading = atan2(LIS3MDL::vector_dot(&E, &from), LIS3MDL::vector_dot(&N, &from)) * 180 / PI;
  if (heading < 0) heading += 360;
  return heading;
}

/*
Returns the angular difference in the horizontal plane between a
default vector (the +X axis) and north, in degrees.
*/
float computeHeading()
{
  
  
  return computeHeading((LIS3MDL::vector<int>){1, 0, 0})
  ;



//Our code to keep robot on heading, magSet is based on our magnetometer calibration and maintains the heading of 
//robot from the start of the Arduino code
if (currentHeading < magSet, millis() < 20000) {

  myservo1 += 1;
  myservo2 += 1*CF2;
}
else if (currentHeading > magSet( {

  myservo1 -= 1;
  myservo2 -= 1*CF2;
}





  

 if (20000 < millis() < 30000) {      //We initially wanted our code to go strictly off of the magnetometer direction,
  myservo1 = 80;                      //But decided to leave the mag to only keep the robot straight, and have the servos turn 
  myservo2 = 80*CF2;                  //based off of time for the trench turn specifically, knowing our robot's speed

  
}

else {
myservo1 = 90;
myservo2 = 90*CF2;


}
}

  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(10); 
