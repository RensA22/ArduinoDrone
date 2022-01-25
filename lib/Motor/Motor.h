/*
 * Motor.h
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#ifndef LIB_MOTOR_MOTOR_H_
#define LIB_MOTOR_MOTOR_H_

#include <Servo.h>

class Motor {
public:
	Motor(const int _motorPin);
	virtual ~Motor() = default;

	Motor() = delete;
	Motor(const Motor &other) = delete;
	Motor& operator=(Motor &&other) = delete;

	void writeMotorValue(const char value);
	char getCurrentValue() const;

private:
	const char motorPin;
	char currentValue;
	Servo ESC;
};

#endif /* LIB_MOTOR_MOTOR_H_ */
