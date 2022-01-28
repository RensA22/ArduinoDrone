/*
 * MPU5060.cpp
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#include "MPU6050.h"

MPU6050::MPU6050() :
		gy521(new GY521(0x68)), angleX(0) {
}

void MPU6050::setup() {
	Wire.begin();
	delay(100);
	while (gy521->wakeup() == false) {
		Serial.print(millis());
		Serial.println("\tCould not connect to GY521");
		delay(1000);
	}
	gy521->setAccelSensitivity(1);  // 8g
	gy521->setGyroSensitivity(1);   // 500 degrees/s

	gy521->setThrottle();

	// set calibration values
	gy521->axe = 0;
	gy521->aye = 0;
	gy521->aze = 0;
	gy521->gxe = 0;
	gy521->gye = 0;
	gy521->gze = 0;
}

void MPU6050::update() {
	gy521->read();

	angleX = gy521->getAngleX();
}

float MPU6050::getAngleX() const {
	return angleX;
}
