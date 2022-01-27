/*
 * PID.cpp
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#include <arduino.h>
#include "PID.h"

PID::PID(const float _desiredValue, const float _Kp, const float _Ki,
		const float _Kd, const short _minValue, const short _maxValue) :
		output(0), desiredValue(_desiredValue), integral(0), derivative(0), error(
				0), prevError(0), Kp(_Kp), Ki(_Ki), Kd(_Kd), minValue(
				_minValue), maxValue(_maxValue) {
	//0.65, 0.3, 0.5
}

float PID::compute(const float actualValue) {
	bool updateIntegral = true;
	float newIntegral;

	error = desiredValue - actualValue;
	newIntegral = integral + error;

	derivative = (error - prevError);

	output = Kp * error + Ki * newIntegral + Kd * derivative;

	//Voorkomen van integral windup
	if (output > maxValue) {
		output = maxValue;
		if (error > 0) {
			updateIntegral = false;
		}
	} else if (output < minValue) {
		output = minValue;
		if (error < 0) {
			updateIntegral = false;
		}
	}

	if (updateIntegral) {
		integral = newIntegral;
	}

	prevError = error;

	return output;
}

void PID::setMaxValue(char maxValue) {
	this->maxValue = maxValue;
}
