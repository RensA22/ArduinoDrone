/*
 * MPU5060.cpp
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#include <Arduino.h>
#include "MPU6050.h"
#include "math.h"

MPU6050::MPU6050() :
		wire(&Wire), address(0x68), prevMicros(micros()), updateHz(0), gyro( {
				.sensitivity = 65.5 }), accel( { .sensitivity = 4096 }), roll(
				0.0), pitch(0.0), yaw(0.0), first_run(true) {

}

MPU6050::~MPU6050() {
}

MPU6050& MPU6050::getMPU6050Instance() {
	static MPU6050 instance;

	return instance;
}

void MPU6050::setup() {
	while (!begin()) {
		Serial.println("Could not connect to GY521");
		delay(500);
	}

	//configure power management
	setRegister(0x6B, 0b000000000);

	//low pass filter
	setRegister(0x1a, 0b000000101);

	//setGyroSensitivity 65.5
	setRegister(0x1b, 0b00001000);
	//setAccelSensitivity 8192
	setRegister(0x1c, 0b00010000);

//	setRegister(0x1a, 0b00000011);
//
//	setRegister(0x19, 0b00000100);

	calculateOffset();
}

void MPU6050::calculateOffset() {
	Serial.println("Calculating offset");

	uint32_t nLoops = 2000;
	double offX = 0;
	double offY = 0;
	double offZ = 0;

	for (uint32_t i = 0; i < nLoops; i++) {
		int16_t rawXgyro = getRegister(0x43) << 8 | getRegister(0x44);
		int16_t rawYgyro = getRegister(0x45) << 8 | getRegister(0x46);
		int16_t rawZgyro = getRegister(0x47) << 8 | getRegister(0x48);

		offX += rawXgyro;
		offY += rawYgyro;
		offZ += rawZgyro;
		yield();
	}

	gyro.offsetX = offX / nLoops;
	gyro.offsetY = offY / nLoops;
	gyro.offsetZ = offZ / nLoops;

	offX = 0;
	offY = 0;
	offZ = 0;

	for (uint32_t i = 0; i < nLoops; i++) {
		int16_t rawXAcc = getRegister(0x3b) << 8 | getRegister(0x3c);
		int16_t rawYAcc = getRegister(0x3d) << 8 | getRegister(0x3e);
		int16_t rawZAcc = getRegister(0x3f) << 8 | getRegister(0x40);

		uint64_t total_acc = sqrt(
				pow(rawXAcc, 2) + pow(rawYAcc, 2) + pow(rawZAcc, 2));

		if (abs(rawXAcc) < total_acc) {
			offX += asin((float) rawYAcc / total_acc) * (180 / PI);
		}

		if (abs(rawYAcc) < total_acc) {
			offY += asin((float) rawXAcc / total_acc) * (180 / PI);
		}

		yield();
	}

	accel.offsetX = offX / nLoops;
	accel.offsetY = offY / nLoops;

	Serial.println("Calculating offset done!");
}

void MPU6050::update() {
	updateGyroData();
	updateAccData();

	roll = (0.9 * gyro.angleX) + (0.1 * accel.angleX);

	pitch = (0.9 * gyro.angleY) + (0.1 * accel.angleY);

	yaw = -gyro.rawZ / gyro.sensitivity;

}

void MPU6050::updateGyroData() {
	//Get raw gyro values from the mpu6050 register
	gyro.rawX = getRegister(0x43) << 8 | getRegister(0x44);
	gyro.rawY = getRegister(0x45) << 8 | getRegister(0x46);
	gyro.rawZ = getRegister(0x47) << 8 | getRegister(0x48);

	//add offsets to it;
	gyro.rawX -= round(gyro.offsetX);
	gyro.rawY -= round(gyro.offsetY);
	gyro.rawZ -= round(gyro.offsetZ);

//	Serial.print("GyroRawX:\t");
//	Serial.print(gyro.rawX);
//	Serial.print("\tGyroRawY:\t");
//	Serial.print(gyro.rawY);
//	Serial.print("\tGyroRawZ:\t");
//	Serial.print(gyro.rawZ);

	float angX = 0.0;
	float angY = 0.0;
	if (updateHz < 2) {

		//Calculate the raw data to degrees per sec
		angX = (float) gyro.rawX / gyro.sensitivity * updateHz;
		angY = (float) gyro.rawY / gyro.sensitivity * updateHz;

		if (angX > 0.01 || angX < -0.01) {
			gyro.angleX += angX;
		}
//		Serial.print("\tGyroAngleX:\t");
//		Serial.print(gyro.angleX);
//		Serial.print("\t");
//		Serial.println((float) millis() / 1000, 4);

		if (angY > 0.01 || angY < -0.01) {
			gyro.angleY += angY;
		}
//		Serial.print("\tGyroAngleY:\t");
//		Serial.println(gyro.angleY);
	}

//Calcule the looptime in seconds. Micros are used to up the accuracy.
	updateHz = (float) (micros() - prevMicros) / 1e6;
	prevMicros = micros();
}

void MPU6050::updateAccData() {
//Get the raw accelero value from the mpu6050 registers
	accel.rawX = getRegister(0x3b) << 8 | getRegister(0x3c);
	accel.rawY = getRegister(0x3d) << 8 | getRegister(0x3e);
	accel.rawZ = getRegister(0x3f) << 8 | getRegister(0x40);

//	Serial.print("AccelRawX:\t");
//	Serial.print(accel.rawX);
//	Serial.print("\tAccelRawY:\t");
//	Serial.print(accel.rawY);
//	Serial.print("\tAccelRawZ:\t");
//	Serial.print(accel.rawZ);

	uint64_t total_acc = sqrt(
			pow(accel.rawX, 2) + pow(accel.rawY, 2) + pow(accel.rawZ, 2));

	if (abs(accel.rawX) < total_acc) {
		accel.angleX = (asin((float) accel.rawY / total_acc) * (180 / PI))
				- accel.offsetX;
//		Serial.print("\tAccelAngleX:\t");
//		Serial.print(accel.angleX);
	}

	if (abs(accel.rawY) < total_acc) {
		accel.angleY = (asin((float) accel.rawX / total_acc) * (180 / PI))
				- accel.offsetY;
//		Serial.print("\tAccelAngleY:\t");
//		Serial.print(accel.angleY);
	}
//	Serial.println();

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
	roll = 0;
	pitch = 0;
	yaw = 0;

	gyro.reset();
	accel.reset();
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
		Serial.println("Error getting register endTransmission !=0");
		return 0;
	}
	uint8_t n = wire->requestFrom(address, (uint8_t) 1);
	if (n != 1) {
		Serial.println("Error getting register N != 1");
		return 0;
	}
	uint8_t val = wire->read();
	return val;
}

float MPU6050::getPitch() const {
	return pitch;
}

float MPU6050::getRoll() const {
	return roll;
}

