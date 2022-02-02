/*
 * SerialParser.h
 *
 *  Created on: 28 jan. 2022
 *      Author: Rens
 */

#ifndef SRC_SERIALPARSER_H_
#define SRC_SERIALPARSER_H_

#include <stdint.h>

class SerialParser {
public:
	virtual ~SerialParser() = default;

	static SerialParser& getSerialParser();

	SerialParser(const SerialParser &other) = delete;
	SerialParser(SerialParser&&) = delete;
	const SerialParser& operator=(const SerialParser &other) = delete;
	SerialParser& operator=(SerialParser&&) = delete;

	void handleIncomingMessage(char incomingMessage);

	String getMessage();
	bool isMessageReady() const;

private:
	SerialParser() = default;

	void clearBuffer();

	uint8_t bufferIndex = 0;
	static const uint8_t bufferSize = 10;
	char buffer[bufferSize] = { };

	bool messageReady = false;
	bool bufferFull = false;

};
#endif /* SRC_SERIALPARSER_H_ */
