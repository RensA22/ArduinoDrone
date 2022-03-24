/*
 * test_main.cpp
 *
 *  Created on: 8 mrt. 2022
 *      Author: Rens
 */
#define UNIT_TEST

#ifdef UNIT_TEST

#include <Arduino.h>
#include <unity.h>
#include "PID.h"
#include "SerialParser.h"
#include "FlightController.h"
#include "Logger.h"

namespace TEST_PID {
	void test_PID_compute(void) {
		PID pid = PID(0, 1.5, 0.02, 0.25, -1000, 1000);

		for (int i = 0; i < 10; i++) {
			float value = pid.compute(i);
			Serial.println(value);
		}
	}

	void test_PID_reset(void) {
		PID pid = PID(0, 1.5, 0.02, 0.25, -1000, 1000);

		for (int i = 0; i < 10; i++) {
			float value = random(-10, 10);
			pid.compute(value);
		}

		pid.reset();
		TEST_ASSERT_EQUAL_FLOAT(0, pid.getDerivative());
		TEST_ASSERT_EQUAL_FLOAT(0, pid.getError());
		TEST_ASSERT_EQUAL_FLOAT(0, pid.getIntegral());
		TEST_ASSERT_EQUAL_FLOAT(0, pid.getProportional());

	}
}

namespace TEST_STATEMACHINE {
	void test_statemachine_start(void) {

		FlightController fc;

		fc.setup();
		fc.run();
		SerialParser::getSerialParser().handleIncomingMessage('s');
		SerialParser::getSerialParser().handleIncomingMessage('t');
		SerialParser::getSerialParser().handleIncomingMessage('a');
		SerialParser::getSerialParser().handleIncomingMessage('r');
		SerialParser::getSerialParser().handleIncomingMessage('t');
		SerialParser::getSerialParser().handleIncomingMessage('\n');
		fc.run();

		TEST_ASSERT_TRUE(fc.getCurrentState()->getName().equals("Start"));

	}
}

void setup() {
	Serial.begin(115200);
	Logger::getLoggerInstance().setLogLevel(LOGLEVEL::INFO);
	delay(2000);
//	TEST_STATEMACHINE::test_statemachine_start();
	UNITY_BEGIN();

	RUN_TEST(TEST_PID::test_PID_compute);
	RUN_TEST(TEST_PID::test_PID_reset);
	RUN_TEST(TEST_STATEMACHINE::test_statemachine_start);

	UNITY_END();

}

void loop() {

}

#endif
