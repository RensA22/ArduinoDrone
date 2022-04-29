/*
 * IMotor.h
 *
 *  Created on: 5 apr. 2022
 *      Author: Rens
 */

#ifndef LIB_MOTORDRIVER_ITHROTTLECONSUMER_H_
#define LIB_MOTORDRIVER_ITHROTTLECONSUMER_H_

#include <cstdint>

namespace MotorDriver {
	class IThrottleConsumer {
	public:
		virtual ~IThrottleConsumer() {
		}

		virtual void writeMotorValue(const uint16_t value)=0;
	};
}

#endif /* LIB_MOTORDRIVER_ITHROTTLECONSUMER_H_ */
