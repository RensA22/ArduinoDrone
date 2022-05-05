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
	virtual ~SerialParser() = default;

	static SerialParser& getSerialParser();

	SerialParser(const SerialParser &other) = delete;
	SerialParser(SerialParser&&) = delete;
	const SerialParser& operator=(const SerialParser &other) = delete;
	SerialParser& operator=(SerialParser&&) = delete;

	/**
	 * Handles the incoming serial messages. When a char is received it stores it in a buffer.
	 * When character 10 (enter) is received it will say a message is ready. So that this can be accessed.
	 *
	 * @param incomingMessage
	 */
	void handleIncomingMessage(char incomingMessage);

	/**
	 * Clears the array buffer
	 * sets the bufferIndex to = 0
	 * sets the bool messageReady to false
	 */
	void clearBuffer();

	String getMessage();
	bool isMessageReady() const;

private:
	SerialParser() = default;

	uint8_t bufferIndex = 0;
	static const uint8_t bufferSize = 10;
	char buffer[bufferSize] = { };

	bool messageReady = false;
	bool bufferFull = false;

};
#endif /* SRC_SERIALPARSER_H_ */
