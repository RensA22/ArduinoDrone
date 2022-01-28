/*
 * Motor.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include "Motor.h"

Motor::Motor(const int _motorPin) :
		motorPin(_motorPin), minValue(1000), maxValue(1300), currentValue(0) {
	ESC.attach(motorPin);
	ESC.writeMicroseconds(minValue);
}

void Motor::writeMotorValue(const uint16_t value) {
	uint16_t actualVal = value;
	if (actualVal < minValue) {
		actualVal = minValue;
	} else if (actualVal > maxValue) {
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
