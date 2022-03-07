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
	Motor(const uint8_t _motorPin, const uint16_t _minValue,
			const uint16_t _maxValue);
	virtual ~Motor() = default;

	Motor() = delete;
	Motor(const Motor &other) = delete;
	Motor& operator=(Motor &&other) = delete;

	/**
	 * Write the value to the motor
	 * @param value
	 */
	void writeMotorValue(const uint16_t value);
	uint16_t getCurrentValue() const;
	const uint16_t getMaxValue() const;
	const uint16_t getMinValue() const;

private:
	const uint8_t motorPin;
	const uint16_t minValue;
	const uint16_t maxValue;
	uint16_t currentValue;
	Servo ESC;
};

#endif /* LIB_MOTOR_MOTOR_H_ */
