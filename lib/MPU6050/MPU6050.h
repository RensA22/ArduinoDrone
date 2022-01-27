/*
 * MPU5060.h
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#ifndef LIB_MPU6050_H_
#define LIB_MPU6050_H_

#include <GY521.h>

class MPU6050 {
public:
	MPU6050();
	virtual ~MPU6050() = default;
	MPU6050(const MPU6050 &other) = delete;
	MPU6050(MPU6050 &&other) = delete;

	void setup();
	void update();
	float getAngleX() const;

private:
	GY521 *gy521;
	float angleX;
};

#endif /* LIB_MPU6050_H_ */
