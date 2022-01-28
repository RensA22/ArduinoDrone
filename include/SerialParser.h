/*
 * SerialParser.h
 *
 *  Created on: 28 jan. 2022
 *      Author: Rens
 */

#ifndef SRC_SERIALPARSER_H_
#define SRC_SERIALPARSER_H_

#include <stdint.h>
#include <Arduino.h>

class SerialParser {
public:
	SerialParser() = default;
	virtual ~SerialParser() = default;
	SerialParser(const SerialParser &other) = delete;
	SerialParser(SerialParser &&other) = delete;

	void parseText(String incomingMessage);
private:

};

#endif /* SRC_SERIALPARSER_H_ */
