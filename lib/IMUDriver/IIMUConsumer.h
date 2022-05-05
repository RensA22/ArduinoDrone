/*
 * IIMU.h
 *
 *  Created on: 5 apr. 2022
 *      Author: Rens
 */

namespace IMUDriver {
	class IIMUConsumer {
	public:
		virtual ~IIMUConsumer() {
		}

		/**
		 * Configures the sensor with the correct speeds.
		 * This is important for calculating the angles.
		 */
		virtual void setup() = 0;

		/**
		 * Communicates with the sensors and updates the values.
		 * This functions needs to be run every loop update.
		 */
		virtual void update() = 0;

		/**
		 * Resets the sensor values to 0;
		 */
		virtual void reset() = 0;

		/**
		 * Calculates the sensor offset. This is run every startup.
		 */
		virtual void calculateOffset() = 0;

	};
}

