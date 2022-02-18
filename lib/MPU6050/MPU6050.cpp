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
				.sensitivity = 65.5 }), accel( { .sensitivity = 8192 }), roll(
				0.0), pitch(0.0), yaw(0.0), rollMotion(0.0), pitchMotion(0.0), first_run(
				true) {

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

	//low pass filter
	setRegister(0x1a, 0b000000101);

	//setGyroSensitivity 65.5
	setRegister(0x1b, 0b00001000);
	//setAccelSensitivity 8192
	setRegister(0x1c, 0b00001000);

//	setRegister(0x1a, 0b00000011);
//
//	setRegister(0x19, 0b00000100);

	calculateOffset();
}

void MPU6050::calculateOffset() {
	uint32_t nLoops = 2000;
	Serial.println("Calculate offset?");
	int64_t offX = 0;
	int64_t offY = 0;
	int64_t offZ = 0;
	for (uint32_t i = 0; i < nLoops; i++) {
		int16_t rawXgyro = getRegister(0x43) << 8 | getRegister(0x44);
		int16_t rawYgyro = getRegister(0x45) << 8 | getRegister(0x46);
		int16_t rawZgyro = getRegister(0x47) << 8 | getRegister(0x48);

		offX += rawXgyro;
		offY += rawYgyro;
		offZ += rawZgyro;
		yield();
	}

	gyro.offsetX = round(offX / nLoops) * -1;
	gyro.offsetY = round(offY / nLoops) * -1;
	gyro.offsetZ = round(offZ / nLoops) * -1;

	Serial.print("XgyroOffset: ");
	Serial.print(gyro.offsetX);
	Serial.print(", YgyroOffset: ");
	Serial.print(gyro.offsetY);
	Serial.print(", ZgyroOffset: ");
	Serial.println(gyro.offsetZ);

}

void MPU6050::update() {
	updateGyroData();
	updateAccData();

//	Serial.print("BeforeAngleX:\t");
//	Serial.print(gyro.angleX);

//	if (!first_run) {
//	gyro.angleX = (0.9996 * gyro.angleX) + (0.0004 * accel.angleX);
//	gyro.angleY = (0.9996 * gyro.angleY) + (0.0004 * accel.angleY);
//	} else {
//		gyro.angleX = accel.angleX;
//		gyro.angleY = accel.angleY;
//
//		first_run = false;
//	}

	roll = roll * 0.9 + gyro.angleX * 0.1;
	pitch = pitch * 0.9 + gyro.angleY * 0.1;

	rollMotion = rollMotion * 0.7 + 0.3 * gyro.rawX / gyro.sensitivity;
	pitchMotion = pitchMotion * 0.7 + 0.3 * gyro.rawY / gyro.sensitivity;

//	Serial.print("\tAngleX:\t");
//	Serial.print(gyro.angleX);
//	Serial.print("\tangleY:\t");
//	Serial.print(gyro.angleY);
//	Serial.print("\taccX:\t");
//	Serial.print(accel.angleX);
//	Serial.print("\taccY:\t");
//	Serial.print(accel.angleY);
//	Serial.print("\troll:\t");
//	Serial.print(roll);
//	Serial.print("\tpitch:\t");
//	Serial.println(pitch);

}

void MPU6050::updateGyroData() {
	//Get raw gyro values from the mpu6050 register
	gyro.rawX = getRegister(0x43) << 8 | getRegister(0x44);
	gyro.rawY = getRegister(0x45) << 8 | getRegister(0x46);
	gyro.rawZ = getRegister(0x47) << 8 | getRegister(0x48);

	//add offsets to it;
	gyro.rawX += round(gyro.offsetX);
	gyro.rawY += round(gyro.offsetY);
	gyro.rawZ += round(gyro.offsetZ);
	float angX = 0.0;
	float angY = 0.0;
	if (updateHz < 2) {

		//Calculate the raw data to degrees per sec
		angX = (float) -gyro.rawX / gyro.sensitivity * updateHz;
		angY = (float) gyro.rawY / gyro.sensitivity * updateHz;

		if (angX > 0.01 || angX < -0.01) {
			gyro.angleX += angX;
		}
		if (angY > 0.01 || angY < -0.01) {
			gyro.angleY += angY;
		}
	}

//	gyro.angleZ += zGryo / gyro.sensitivity * updateHz;
//
//	Serial.print("RawGyroY"
//			":\t");
//	Serial.print(gyro.rawY);
//	Serial.print("\tRawGyroY:\t");
//	Serial.print(gyro.rawY);
//	Serial.print("\tSens:\t");
//	Serial.print(gyro.sensitivity, 5);
//	Serial.print("\tupdateHz:\t");
//	Serial.print(updateHz, 5);
//	Serial.print("\tOutput:\t");
//	Serial.print(angX, 5);
//	Serial.print("\tangleY:\t");
//	Serial.print(gyro.angleY, 5);
//	if (angY > 0.01 || angY < -0.01) {
//		Serial.print("********");
//	}

//Calcule the looptime in seconds. Micros are used to up the accuracy.
	updateHz = (float) (micros() - prevMicros) / 1e6;
	prevMicros = micros();
}

void MPU6050::updateAccData() {
//Get the raw accelero value from the mpu6050 registers
	int16_t rawXAcc = getRegister(0x3b) << 8 | getRegister(0x3c);
	int16_t rawYAcc = getRegister(0x3d) << 8 | getRegister(0x3e);
	int16_t rawZAcc = getRegister(0x3f) << 8 | getRegister(0x40);

	uint64_t total_acc = sqrt(
			pow(rawXAcc, 2) + pow(rawYAcc, 2) + pow(rawZAcc, 2));

	if (abs(rawXAcc) < total_acc) {
		accel.angleX = asin((float) rawYAcc / total_acc) * (180 / PI) * -1;
	}

	if (abs(rawYAcc) < total_acc) {
		accel.angleY = asin((float) rawXAcc / total_acc) * (180 / PI) * -1;
	}

//add offsets to it
//	float xAcc = rawXAcc + accel.offsetX;
//	float yAcc = rawYAcc + accel.offsetY;
//	float zAcc = rawZAcc + accel.offsetZ;

//caculate the G's from the raw data
//	float xAcc = rawXAcc / accel.sensitivity;
//	float yAcc = rawYAcc / accel.sensitivity;
//	float zAcc = rawZAcc / accel.sensitivity;
//
//	accel.angleX = (atan(yAcc / ((xAcc * xAcc) + (zAcc * zAcc))) * (180 / PI));
//	accel.angleY = atan(xAcc / ((yAcc * yAcc) + (zAcc * zAcc))) * (180 / PI);

//	accel.angleX = 180 / PI * (atan2(-yAcc, -zAcc) + PI) - 180;
//	accel.angleY = 180 / PI * (atan2(-xAcc, -zAcc) + PI) - 180;
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

	rollMotion = 0;
	pitchMotion = 0;

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

float MPU6050::getPitchMotion() const {
	return pitchMotion;
}

float MPU6050::getRollMotion() const {
	return rollMotion;
}
