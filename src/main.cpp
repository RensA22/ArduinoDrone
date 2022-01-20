/*
 * main.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include "HCSR04.h"
#include "Motor.h"


// HCSR04 distSens(2, 0);
//Motor motor(D2);

//int potValue;

Adafruit_MPU6050 mpu;

void setup()
{
  Serial.begin(115200); // Starts the serial communication
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
}

void loop()
{
//  potValue = analogRead(A0); // reads the value of the potentiometer (value between 0 and 1023)
//  potValue = map(potValue, 0, 1023, 0, 180);
//  motor.writeMotorValue(potValue);
//  Serial.println(potValue);
	 /* Get new sensor events with the readings */
	  sensors_event_t a, g, temp;
	  mpu.getEvent(&a, &g, &temp);

	  /* Print out the values */
	  Serial.print("Acceleration X: ");
	  Serial.print(a.acceleration.x);
	  Serial.print(", Y: ");
	  Serial.print(a.acceleration.y);
	  Serial.print(", Z: ");
	  Serial.print(a.acceleration.z);
	  Serial.println(" m/s^2");

	  Serial.print("Rotation X: ");
	  Serial.print(g.gyro.x);
	  Serial.print(", Y: ");
	  Serial.print(g.gyro.y);
	  Serial.print(", Z: ");
	  Serial.print(g.gyro.z);
	  Serial.println(" rad/s");

	  Serial.print("Temperature: ");
	  Serial.print(temp.temperature);
	  Serial.println(" degC");

	  Serial.println("");
	  delay(500);
}




