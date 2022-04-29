/*
 * Motor.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include "../MotorDriver/Motor.h"

#include "Logger.h"

namespace MotorDriver {

	Motor::Motor(const uint8_t _motorPin, const uint16_t _minValue,
			const uint16_t _maxValue) :
			motorPin(_motorPin), minValue(_minValue), maxValue(_maxValue), currentValue(
					_minValue) {
		ESC.attach(motorPin);
		ESC.writeMicroseconds(minValue);
	}

	void Motor::writeMotorValue(const uint16_t value) {
		uint16_t actualVal = value;
		if (actualVal <= minValue) {
			actualVal = minValue;
		} else if (actualVal >= maxValue) {
			actualVal = maxValue;
		}

		currentValue = actualVal;
		ESC.writeMicroseconds(actualVal);
	}

	uint16_t Motor::getCurrentValue() const {
		return currentValue;
	}

	const uint16_t Motor::getMaxValue() const {
		return maxValue;
	}

	const uint16_t Motor::getMinValue() const {
		return minValue;
	}

}
