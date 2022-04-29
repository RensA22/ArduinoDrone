/*
 * Logger.cpp
 *
 *  Created on: 23 mrt. 2022
 *      Author: Rens
 */

#include "Logger.h"

Logger::Logger() :
		logLevel(INFO) {
}

Logger& Logger::getLoggerInstance() {
	static Logger instance;

	return instance;
}

void Logger::log(const String message, const LOGLEVEL messageLevel) {
	if (messageLevel <= logLevel) {
		switch (messageLevel) {
		case INFO:
			Serial.print("[INFO]\t");
			Serial.println(message);
			break;
		case WARNING:
			Serial.print("[WARNING]\t");
			Serial.println(message);
			break;
		case ERROR:
			Serial.print("[ERROR]\t");
			Serial.println(message);
			break;
		case OFF:
		default:
			break;
		}
	}

}

void Logger::setLogLevel(const LOGLEVEL level) {
	logLevel = level;
}

