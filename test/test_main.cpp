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
#include <unity_internals.h>
#include "PID.h"
#include "SerialParser.h"
#include "FlightController.h"
#include "Logger.h"

namespace TEST_PID {
	void test_PID_compute(void) {
		PID pid = PID(0, 1.5, 0.02, 0.25, -1000, 1000);

		unsigned long time = millis();
		unsigned long prevTime = time;
		unsigned long elapsedTime = 0;

		int i = 0;
		int valueArray[10] = { 1, 5, 8, 12, 6, 3, 2, -5, -7, -15 };
		float awnserArray[10] = { 14.0004, 57.5024, 49.5056, 68.0104, -65.9872, -32.986,
				-9.4852, -94.9872, -35.49, -122.496 };

		while (i < 10) {
			time = millis();
			elapsedTime = (time - prevTime);
			if (elapsedTime >= 20) {
				float value = pid.compute(valueArray[i]);
				TEST_ASSERT_EQUAL_FLOAT(awnserArray[i], value);
				prevTime = millis();
				i++;
			}
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

	void test_statemachine_stop(void) {
		FlightController fc;

	}
}

namespace TEST_LOGGER {
	void test_log_info(void) {
		Logger::getLoggerInstance().log("test", INFO);

		while (true) {
			if (Serial.available() > 0) {
				Serial.print(": ");
				Serial.println(Serial.read());
			}
		}
	}
}

void setup() {
	Serial.begin(115200);
	Logger::getLoggerInstance().setLogLevel(LOGLEVEL::OFF);
	delay(2000);
	UNITY_BEGIN();

	RUN_TEST(TEST_PID::test_PID_compute);
	RUN_TEST(TEST_PID::test_PID_reset);
	RUN_TEST(TEST_STATEMACHINE::test_statemachine_start);
//	RUN_TEST(TEST_LOGGER::test_log_info);

	UNITY_END();

}

void loop() {

}

#endif
