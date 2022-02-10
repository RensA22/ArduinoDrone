/*
 * MPU5060.cpp
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#include <Arduino.h>
#include "MPU6050.h"

MPU6050::MPU6050() :
		wire(&Wire), address(0x68), prevMicros(micros()), updateHz(0), offX(0), offY(
				0), offZ(0), angleX(0.0), angleY(0.0), angleZ(0.0) {
	setup();
}

MPU6050::~MPU6050() {
}

MPU6050& MPU6050::getMPU6050Instance() {
	static MPU6050 instance;

	return instance;
}

void MPU6050::setup() {
	if (!begin()) {
		Serial.println("Could not connect to GY521");
	}

	//setGyroSensitivity
	setRegister(0x1b, 0b00000000);
	//setAccelSensitivity
	setRegister(0x1c, 0b00000000);

	offX = -378;
	offY = 11;
	offZ = 103;

}

void MPU6050::update() {

	//Get raw gyro values from the mpu6050 register
	int16_t rawX = getRegister(0x43) << 8 | getRegister(0x44);
	int16_t rawY = getRegister(0x45) << 8 | getRegister(0x46);
	int16_t rawZ = getRegister(0x47) << 8 | getRegister(0x48);

	//add offsets to it;
	rawX += offX;
	rawY += offY;
	rawZ += offZ;

	//Calculate the raw data to degrees per sec
	angleX += rawX * (1.0 / 131.0) * updateHz;
	angleY += rawY * (1.0 / 131.0) * updateHz;
	angleZ += rawZ * (1.0 / 131.0) * updateHz;

	//Calcule the looptime in seconds. Micros are used to up the accuracy.
	updateHz = (float) (micros() - prevMicros) / 1e6;
	prevMicros = micros();
}

bool MPU6050::begin() {
	wire->begin();
	if (isConnected()) {
		return wakeUp();
	}
	return false;
}

bool MPU6050::wakeUp() {
	wire->beginTransmission(address);
	wire->write(0x6B);
	wire->write(0x00);
	return (wire->endTransmission() == 0);
}

bool MPU6050::isConnected() {
	wire->beginTransmission(address);
	return (wire->endTransmission() == 0);
}

void MPU6050::reset() {
	angleX = 0;
	angleY = 0;
	angleZ = 0;
}

void MPU6050::setRegister(uint8_t reg, uint8_t value) {
	wire->beginTransmission(address);
	wire->write(reg);
	wire->write(value);
	// no need to do anything if not connected.
	if (wire->endTransmission() != 0) {
		Serial.println("Error writing to register");
	}
}

uint8_t MPU6050::getRegister(uint8_t reg) {
	wire->beginTransmission(address);
	wire->write(reg);
	if (wire->endTransmission() != 0) {
		Serial.println("Error getting register");
		return 0;
	}
	uint8_t n = wire->requestFrom(address, (uint8_t) 1);
	if (n != 1) {
		Serial.println("Error getting register");
		return 0;
	}
	uint8_t val = wire->read();
	return val;
}

float MPU6050::getAngleX() const {
	return angleX;
}

float MPU6050::getAngleY() const {
	return angleY;
}

float MPU6050::getAngleZ() const {
	return angleZ;
}
