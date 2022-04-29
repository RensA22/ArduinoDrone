/*
 * MotorController.h
 *
 *  Created on: 2 feb. 2022
 *      Author: Rens
 */

#ifndef INCLUDE_MOTORCONTROLLER_H_
#define INCLUDE_MOTORCONTROLLER_H_

#include "../lib/MotorDriver/Motor.h"

class MotorController {
public:
	static MotorController& getMotorControllerInstance();

	virtual ~MotorController() = default;
	MotorController(const MotorController &other) = delete;
	MotorController(MotorController &&other) = delete;
	MotorController& operator=(const MotorController &other) = delete;

	/**
	 * Initializes the Motors and throttle values
	 */
	void initMotors();

	/** Increases the speed of the motors by 2 until startup speed is received.
	 *
	 * @return False when < startup speed. True > startup speed
	 */
	bool startMotors();

	/**
	 * Stops the motors.
	 */
	void stopMotors();

	/**
	 * Sets all the motors with the given value.
	 * @param value
	 */
	void setMotorsValue(const uint16_t value);

	/**
	 * Sets an unique motors with the given value.
	 * @param motorId
	 * @param value
	 */
	void setMotorValue(const uint8_t motorId, const uint16_t value);

	/**
	 * Add the given value to the current motors throttle.
	 * @param increase
	 */
	void increaseMotorsValue(const uint16_t increase);

	/**
	 * Add the given value the the given motor throttle;
	 * @param motorId
	 * @param increase
	 */
	void increaseMotorValue(const uint8_t motorId, const uint16_t increase);

	uint16_t getThrottle(const uint8_t motorId);

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
	MotorDriver::Motor *motors[4];

};

#endif /* INCLUDE_MOTORCONTROLLER_H_ */
