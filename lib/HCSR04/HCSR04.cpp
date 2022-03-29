/*
 * HCSR04.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include <Arduino.h>
#include "HCSR04.h"
#include "Wire.h"
#include "Logger.h"

HCSR04::HCSR04() :
		trigPin(-1), echoPin(-1), duration(0.0), distance(0.0), distOffst(0.0), initialized(
				false) {

}

HCSR04& HCSR04::getHCSR04Instance() {
	static HCSR04 instance;

	return instance;
}

void HCSR04::setup(const uint8_t _trigPin, const uint8_t _echoPin) {
	trigPin = _trigPin;
	echoPin = _echoPin;

	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

	initialized = true;
}

float HCSR04::measureDistance() {
	if (!initialized) {
		Logger::getLoggerInstance().log(
				"measureDistance() - HCSRO4 not initialised", ERROR);
		return -1;
	}
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);

	// Calculating the distance in cm
	distance = duration * 0.034 / 2;
	distance -= distOffst;

	return distance;
}

void HCSR04::calcOffset() {
	if (!initialized) {
		Logger::getLoggerInstance().log("calcOffset() - HCSRO4 not initialised",
				ERROR);
		return;
	}

	float offDistance = 0;
	const uint8_t nRuns = 25;

	for (int i = 0; i < nRuns; i++) {
		offDistance += measureDistance();
	}

	distOffst = offDistance / nRuns;

}
