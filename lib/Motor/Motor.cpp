/*
 * Motor.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include "Motor.h"

Motor::Motor(const int _motorPin) :
		motorPin(_motorPin), currentValue(0) {
	ESC.attach(motorPin, 1000, 2000);
	ESC.write(currentValue);
}

void Motor::writeMotorValue(const char value) {
	char actualVal = value;
	if (actualVal < 0) {
		actualVal = 0;
	} else if (actualVal > 180) {
		actualVal = 180;
	}
	currentValue = actualVal;
	ESC.write(actualVal);
}

char Motor::getCurrentValue() const {
	return currentValue;
}
