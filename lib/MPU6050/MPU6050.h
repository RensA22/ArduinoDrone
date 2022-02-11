/*
 * MPU5060.h
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#ifndef LIB_MPU6050_H_
#define LIB_MPU6050_H_

#include <Wire.h>

class MPU6050 {
public:
	static MPU6050& getMPU6050Instance();

	virtual ~MPU6050();
	MPU6050(const MPU6050 &other) = delete;
	MPU6050(MPU6050 &&other) = delete;

	void setup();
	void update();
	void reset();

	float getAngleX() const;
	float getAngleY() const;
	float getAngleZ() const;

private:
	MPU6050();

	bool begin();
	bool wakeUp();
	bool isConnected();

	void setRegister(uint8_t reg, uint8_t value);
	uint8_t getRegister(uint8_t reg);

	TwoWire *wire;
	uint8_t address;
	uint32_t prevMicros;
	float updateHz;

	int16_t offXgyro;
	int16_t offYgyro;
	int16_t offZgyro;

	int16_t offXacc;
	int16_t offYacc;
	int16_t offZacc;

	float angleX;
	float angleY;
	float angleZ;

	bool first_run;

};

#endif /* LIB_MPU6050_H_ */
