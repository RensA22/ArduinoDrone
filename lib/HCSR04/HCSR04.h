/*
 * HCSR04.h
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#ifndef LIB_HCSR04_HCSR04_H_
#define LIB_HCSR04_HCSR04_H_

class HCSR04 {
public:
	HCSR04(const uint8_t _trigPin, const uint8_t _echoPin);
	virtual ~HCSR04() = default;

	HCSR04() = delete;
	HCSR04(const HCSR04 &other) = delete;
	HCSR04& operator=(const HCSR04 &other) = delete;

	int16_t measureDistance();

private:
	const uint8_t trigPin;
	const uint8_t echoPin;
	float duration;
	int16_t distance;
	uint8_t distOffst;
};

#endif /* LIB_HCSR04_HCSR04_H_ */
