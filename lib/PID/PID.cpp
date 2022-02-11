/*
 * PID.cpp
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#include <arduino.h>
#include "PID.h"

PID::PID(const float _desiredValue, const float _Kp, const float _Ki,
		const float _Kd, const int16_t _minValue, const int16_t _maxValue) :
		output(0), desiredValue(_desiredValue), proportional(0), integral(0), derivative(
				0), error(0), prevError(0), elapsedTime(0), time(millis()), prevTime(
				0), Kp(_Kp), Ki(_Ki), Kd(_Kd), minValue(_minValue), maxValue(
				_maxValue) {
}

float PID::compute(const float actualValue) {
	prevTime = time;
	time = millis();
	elapsedTime = (time - prevTime) / 1000;

	error = actualValue - desiredValue;

	proportional = Kp * error;

	if (error < 5 || error > -5) {
		integral = integral + (Ki * error);
	}

	derivative = Kd * ((error - prevError) / elapsedTime);

	output = proportional + integral + derivative;

	//making sure the output is never over min and max value
	if (output < -1000) {
		output = -1000;
	} else if (output > 1000) {
		output = 1000;
	}
	prevError = error;

	return output;
}

void PID::reset() {
	proportional = 0;
	integral = 0;
	derivative = 0;
	error = 0;
	prevError = 0;
}

void PID::setMaxValue(int8_t maxValue) {
	this->maxValue = maxValue;
}
