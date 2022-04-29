/*
 * IRangeFinder.h
 *
 *  Created on: 5 apr. 2022
 *      Author: Rens
 */

#ifndef LIB_RANGEFINDERDRIVER_IDISTANCEPROVIDER_H_
#define LIB_RANGEFINDERDRIVER_IDISTANCEPROVIDER_H_

#include <cstdint>

namespace RangefinderDriver {
	class IDistanceProvider {
	public:
		virtual ~IDistanceProvider() {
		}

		virtual void setup(const uint8_t _trigPin, const uint8_t _echoPin) = 0;
		virtual float measureDistance() = 0;
		virtual void calcOffset() = 0;
	};
}

#endif /* LIB_RANGEFINDERDRIVER_IDISTANCEPROVIDER_H_ */
