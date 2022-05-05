/*
 * MPU5060.h
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#ifndef LIB_MPU6050_H_
#define LIB_MPU6050_H_

#include <Wire.h>

#include "IIMUConsumer.h"

namespace IMUDriver {

	struct sensor {
		float offsetX;
		float offsetY;
		float offsetZ;

		float angleX;
		float angleY;
		float angleZ;

		int16_t rawX;
		int16_t rawY;
		int16_t rawZ;

		float sensitivity;

		void reset() {
			angleX = 0.0;
			angleY = 0.0;
			angleZ = 0.0;
		}
	};

	class MPU6050: public IIMUConsumer {
	public:
		static MPU6050& getMPU6050Instance();

		virtual ~MPU6050();
		MPU6050(const MPU6050 &other) = delete;
		MPU6050(MPU6050 &&other) = delete;

		/**
		 * Configures the sensor with the correct speeds.
		 * This is important for calculating the angles.
		 */
		void setup();

		/**
		 * Communicates with the sensors and updates the values.
		 * This functions needs to be run every loop update.
		 */
		void update();

		/**
		 * Resets the sensor values to 0;
		 */
		void reset();

		/**
		 * Calculates the sensor offset. This is run every startup.
		 */
		void calculateOffset();

		float getPitch() const;
		float getRoll() const;
		const sensor& getAccel() const;

	private:
		MPU6050();

		/**
		 * Start communication with the MPU.
		 * @return True if successful. False if not.
		 */
		bool begin();

		/**
		 * Wakes the MPU.
		 * @return True if successful. False if not.
		 */
		bool wakeUp();

		/**
		 * Checks if the MPU is connected correctly
		 * @return True if successful. False if not.
		 */
		bool isConnected();

		void setRegister(uint8_t reg, uint8_t value);
		uint8_t getRegister(uint8_t reg);

		/**
		 * Accesses the registers for the raw data.
		 * Then adds the calculated offset to it.
		 * Then calculates the angles instead of the raw rad/s
		 */
		void updateGyroData();

		/**
		 * Accesses the registers for the raw data.
		 * Then calculates the angles instead of the raw m/s
		 */
		void updateAccData();

		TwoWire *wire;
		uint8_t address;
		uint32_t prevMicros;
		float updateHz;

		sensor gyro;
		sensor accel;

		float roll;
		float pitch;
		float yaw;

	};

}
#endif /* LIB_MPU6050_H_ */
