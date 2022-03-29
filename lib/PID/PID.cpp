/*
 * PID.cpp
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#include <arduino.h>
#include "PID.h"
#include "Logger.h"

PID::PID(const float _desiredValue, const float _Kp, const float _Ki,
		const float _Kd, const int16_t _minValue, const int16_t _maxValue) :
		output(0), desiredValue(_desiredValue), proportional(0), integral(0), derivative(
				0), error(0), prevError(0), elapsedTime(0), time(millis()), prevTime(
				millis()), Kp(_Kp), Ki(_Ki), Kd(_Kd), minValue(_minValue), maxValue(
				_maxValue) {
}

float PID::compute(const float actualValue, const bool swapError) {
	time = millis();
	elapsedTime = (time - prevTime) / 1000;

	error = (!swapError) ?
			actualValue - desiredValue : desiredValue - actualValue;

//	error = actualValue - desiredValue;

	proportional = Kp * error;

	integral += error * elapsedTime;
	float newIntegral = integral * Ki;

//	derivative =
//			(!swapError) ?
//					Kd * ((error - prevError) / elapsedTime) :
//					Kd * ((prevError - error) / elapsedTime);

	derivative = ((error - prevError) / elapsedTime) * Kd;

	output = proportional + newIntegral + derivative;

	//making sure the output is never over min and max value
	if (output < minValue) {
		output = minValue;
	} else if (output > maxValue) {
		output = maxValue;
	}
//	else {
//		integral = newIntegral;
//	}

	prevError = error;
	prevTime = time;

	return output;
}

void PID::reset() {
	proportional = 0;
	integral = 0;
	derivative = 0;
	error = 0;
	output = 0;
	prevError = 0;
}

void PID::setMaxValue(int8_t maxValue) {
	this->maxValue = maxValue;
}

float PID::getDerivative() const {
	return derivative;
}

float PID::getError() const {
	return error;
}

float PID::getIntegral() const {
	return integral;
}

float PID::getProportional() const {
	return proportional;
}

float PID::getOutput() const {
	return output;
}
