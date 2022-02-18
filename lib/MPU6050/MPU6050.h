/*
 * MPU5060.h
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#ifndef LIB_MPU6050_H_
#define LIB_MPU6050_H_

#include <Wire.h>

struct sensor {
	int16_t offsetX;
	int16_t offsetY;
	int16_t offsetZ;

	float angleX;
	float angleY;
	float angleZ;

	int16_t rawX;
	int16_t rawY;
	int16_t rawZ;

	float sensitivity;

	void reset() {
		angleX = 0.0;
		angleY = 0.0;
		angleZ = 0.0;
	}

	void print() {
		Serial.print("offsetX: ");
		Serial.print(offsetX);
		Serial.print(", offsetY: ");
		Serial.print(offsetY);
		Serial.print(", offsetZ: ");
		Serial.println(offsetZ);
		Serial.print("angleX: ");
		Serial.print(angleX);
		Serial.print(", angleY: ");
		Serial.print(angleY);
		Serial.print(", angleZ: ");
		Serial.println(angleZ);
		Serial.print("Sensitivity: ");
		Serial.println(sensitivity);
	}
};

class MPU6050 {
public:
	static MPU6050& getMPU6050Instance();

	virtual ~MPU6050();
	MPU6050(const MPU6050 &other) = delete;
	MPU6050(MPU6050 &&other) = delete;

	void setup();
	void update();
	void reset();

	void calculateOffset();
	float getPitch() const;
	float getRoll() const;
	float getPitchMotion() const;
	float getRollMotion() const;

private:
	MPU6050();

	bool begin();
	bool wakeUp();
	bool isConnected();

	void setRegister(uint8_t reg, uint8_t value);
	uint8_t getRegister(uint8_t reg);

	void updateGyroData();
	void updateAccData();

	TwoWire *wire;
	uint8_t address;
	uint32_t prevMicros;
	float updateHz;

	sensor gyro;
	sensor accel;

	float roll;
	float pitch;
	float yaw;

	float rollMotion;
	float pitchMotion;

	bool first_run;

};

#endif /* LIB_MPU6050_H_ */
