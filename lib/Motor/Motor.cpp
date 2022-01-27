/*
 * Motor.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include "Motor.h"

Motor::Motor(const int _motorPin) :
		motorPin(_motorPin), minValue(0), maxValue(180), currentValue(0) {
	ESC.attach(motorPin, 1000, 2000);
	ESC.write(currentValue);
}

void Motor::writeMotorValue(const char value) {
	char actualVal = value;
	if (actualVal < minValue) {
		actualVal = minValue;
	} else if (actualVal > maxValue) {
		actualVal = maxValue;
	}
	currentValue = actualVal;
	ESC.write(actualVal);
}

char Motor::getCurrentValue() const {
	return currentValue;
}

const char Motor::getMaxValue() const {
	return maxValue;
}
