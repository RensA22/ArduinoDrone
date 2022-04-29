/*
 * HCSR04.h
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#ifndef LIB_RANGEFINDERDRIVER_HCSR04_H_
#define LIB_RANGEFINDERDRIVER_HCSR04_H_

#include "IDistanceProvider.h"

namespace RangefinderDriver {

	class HCSR04: public IDistanceProvider {
	public:
		static HCSR04& getHCSR04Instance();
		virtual ~HCSR04() = default;

		HCSR04(const HCSR04 &other) = delete;
		HCSR04& operator=(const HCSR04 &other) = delete;

		/**This functions sets the initializes the sensor with the correct pins.
		 * NEEDS TO BE RUN BEFORE ANY OTHER FUNCTIONS!!!
		 *
		 * Yellow wire = echo
		 * Green wire = trig
		 *
		 * @param _trigPin
		 * @param _echoPin
		 */
		void setup(const uint8_t _trigPin, const uint8_t _echoPin);

		/**
		 * Measures the distance.
		 * @return Returns the measured distance.
		 */
		float measureDistance();

		/**
		 * The distance sensor is positioned on the drone above the ground.
		 * This function will do a number of measurements and determine the distance to the ground when the drone is idle.
		 * @return offset
		 */
		void calcOffset();

	private:
		HCSR04();

		uint8_t trigPin;
		uint8_t echoPin;
		float duration;
		float distance;
		float distOffst;
		bool initialised;
	};
}
#endif /* LIB_RANGEFINDERDRIVER_HCSR04_H_ */
