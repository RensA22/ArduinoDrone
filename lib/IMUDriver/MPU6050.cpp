/*
 * MPU5060.cpp
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#include "../IMUDriver/MPU6050.h"

#include <Arduino.h>
#include "math.h"
#include "Logger.h"

namespace IMUDriver {

	MPU6050::MPU6050() :
			wire(&Wire), address(0x68), prevMicros(micros()), updateHz(0), gyro(
					{ .sensitivity = 65.5 }), accel( { .sensitivity = 4096 }), roll(
					0.0), pitch(0.0), yaw(0.0) {

	}

	MPU6050::~MPU6050() {
	}

	MPU6050& MPU6050::getMPU6050Instance() {
		static MPU6050 instance;

		return instance;
	}

	void MPU6050::setup() {
		while (!begin()) {
			Logger::getLoggerInstance().log("Could not connect to GY521",
					ERROR);
			delay(500);
		}

		//configure power management
		setRegister(0x6B, 0b000000000);

		//low pass filter
		setRegister(0x1a, 0b000000101);

		//setGyroSensitivity 65.5
		setRegister(0x1b, 0b00001000);
		//setAccelSensitivity 4096
		setRegister(0x1c, 0b00010000);

//	setRegister(0x1a, 0b00000011);
//
//	setRegister(0x19, 0b00000100);

		calculateOffset();
	}

	void MPU6050::calculateOffset() {
		Logger::getLoggerInstance().log("Calculating offset", INFO);

		uint32_t nLoops = 2000;
		double offXgyro = 0;
		double offYgyro = 0;
		double offZgyro = 0;

		double offXaccel = 0;
		double offYaccel = 0;

		for (uint32_t i = 0; i < nLoops; i++) {
			int16_t rawXgyro = getRegister(0x43) << 8 | getRegister(0x44);
			int16_t rawYgyro = getRegister(0x45) << 8 | getRegister(0x46);
			int16_t rawZgyro = getRegister(0x47) << 8 | getRegister(0x48);

			int16_t rawXAcc = getRegister(0x3b) << 8 | getRegister(0x3c);
			int16_t rawYAcc = getRegister(0x3d) << 8 | getRegister(0x3e);
			int16_t rawZAcc = getRegister(0x3f) << 8 | getRegister(0x40);

			offXgyro += rawXgyro;
			offYgyro += rawYgyro;
			offZgyro += rawZgyro;

			uint64_t total_acc = sqrt(
					pow(rawXAcc, 2) + pow(rawYAcc, 2) + pow(rawZAcc, 2));

			if (abs(rawXAcc) < total_acc) {
				offXaccel += asin((float) rawYAcc / total_acc) * (180 / PI);
			}

			if (abs(rawYAcc) < total_acc) {
				offYaccel += asin((float) rawXAcc / total_acc) * (180 / PI);
			}

			yield();
		}

		gyro.offsetX = offXgyro / nLoops;
		gyro.offsetY = offYgyro / nLoops;
		gyro.offsetZ = offZgyro / nLoops;

		accel.offsetX = offXaccel / nLoops;
		accel.offsetY = offYaccel / nLoops;

		Logger::getLoggerInstance().log("Calculating offset done!", INFO);
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

		float angX = 0.0;
		float angY = 0.0;
		if (updateHz < 1) {

			//Calculate the raw data to degrees per sec
			angX = (float) gyro.rawX / gyro.sensitivity * updateHz;
			angY = (float) gyro.rawY / gyro.sensitivity * updateHz;

			if (angX > 0.01 || angX < -0.01) {
				gyro.angleX += angX;
			}

			if (angY > 0.01 || angY < -0.01) {
				gyro.angleY += angY;
			}
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

		uint64_t total_acc = sqrt(
				pow(accel.rawX, 2) + pow(accel.rawY, 2) + pow(accel.rawZ, 2));

		if (abs(accel.rawX) < total_acc) {
			accel.angleX = (asin((float) accel.rawY / total_acc)) * (180 / PI)
					- accel.offsetX;
		}

		if (abs(accel.rawY) < total_acc) {
			accel.angleY = (asin((float) accel.rawX / total_acc) * (180 / PI))
					- accel.offsetY;
		}

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
			Logger::getLoggerInstance().log("Error writing to register", ERROR);
		}
	}

	uint8_t MPU6050::getRegister(uint8_t reg) {
		wire->beginTransmission(address);
		wire->write(reg);
		if (wire->endTransmission() != 0) {
			Logger::getLoggerInstance().log(
					"Error getting register endTransmission !=0", ERROR);
			return 0;
		}
		uint8_t n = wire->requestFrom(address, (uint8_t) 1);
		if (n != 1) {
			Logger::getLoggerInstance().log("Error getting register N != 1",
					ERROR);
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

	const sensor& MPU6050::getAccel() const {
		return accel;
	}

}
