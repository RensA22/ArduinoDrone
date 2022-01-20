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
	HCSR04(const char _trigPin, const char _echoPin);
	virtual ~HCSR04() = default;

	HCSR04() = delete;
	HCSR04(const HCSR04 &other) = delete;
	HCSR04& operator=(const HCSR04 &other) = delete;

	short measureDistance();

private:
    const char trigPin;
    const char echoPin;
    long duration;
    short distance;
};

#endif /* LIB_HCSR04_HCSR04_H_ */
