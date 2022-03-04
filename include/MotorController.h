/*
 * MotorController.h
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_MOTORCONTROLLER_H_
#define INCLUDE_MOTORCONTROLLER_H_

#include "Motor.h"

class MotorController {
public:
	static MotorController& getMotorControllerInstance();

	virtual ~MotorController() = default;
	MotorController(const MotorController &other) = delete;
	MotorController(MotorController &&other) = delete;
	MotorController& operator=(const MotorController &other) = delete;

	void initMotors();
	bool startMotors();
	void stopMotors();
	void setMotorsValue(const uint16_t value);
	void setMotorValue(const uint8_t motorId, const uint16_t value);

	void increaseMotorsValue(const uint16_t increase);
	void increaseMotorValue(const uint8_t motorId, const uint16_t increase);

private:
	MotorController();

	const uint8_t nMotors;
	const uint16_t minValue;
	const uint16_t maxValue;

	uint16_t throttleStartTarget;
	/* 0: Links onder
	 * 1: Rechts onder
	 * 2: Rechts boven
	 * 3: Links boven
	 */
	uint16_t throttle[4];
	Motor *motors[4];

};

#endif /* INCLUDE_MOTORCONTROLLER_H_ */
