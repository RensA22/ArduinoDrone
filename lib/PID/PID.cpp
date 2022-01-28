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
		output(0), desiredValue(_desiredValue), proportional(0), integral(0), derivative(
				0), error(0), prevError(0), elapsedTime(0), time(millis()), prevTime(
				0), Kp(_Kp), Ki(_Ki), Kd(_Kd), minValue(_minValue), maxValue(
				_maxValue) {
	//0.65, 0.3, 0.5
}

float PID::compute(const float actualValue) {
	prevTime = time;
	time = millis();
	elapsedTime = (time - prevTime) / 1000;

//	bool updateIntegral = true;
//	float newIntegral;

	error = actualValue - desiredValue;

	proportional = Kp * error;

	if (error < 5 || error > -5) {
		integral = integral + (Ki * error);
	}

	derivative = Kd * ((error - prevError) / elapsedTime);

	output = proportional + integral + derivative;

	if (output < -1000) {
		output = -1000;
	} else if (output > 1000) {
		output = 1000;
	}

	//Voorkomen van integral windup
//	if (output > maxValue) {
//		output = maxValue;
//		if (error > 0) {
//			updateIntegral = false;
//		}
//	} else if (output < minValue) {
//		output = minValue;
//		if (error < 0) {
//			updateIntegral = false;
//		}
//	}
//
//	if (updateIntegral) {
//		integral = newIntegral;
//	}

	prevError = error;

	return output;
}

void PID::setMaxValue(char maxValue) {
	this->maxValue = maxValue;
}
