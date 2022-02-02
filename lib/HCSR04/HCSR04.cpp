/*
 * HCSR04.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include <Arduino.h>
#include "HCSR04.h"

HCSR04::HCSR04(const uint8_t _trigPin, const uint8_t _echoPin) :
		trigPin(_trigPin), echoPin(_echoPin), duration(0), distance(0) {
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

int16_t HCSR04::measureDistance() {
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

	return distance;
}

