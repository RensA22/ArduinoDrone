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

	switch (logLevel) {
	case INFO:
		switch (messageLevel) {
		case INFO:
			Serial.print("[INFO]\t");
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
		break;
	case ERROR:
		if (messageLevel == ERROR) {
			Serial.print("[ERROR]\t");
			Serial.println(message);
		}
		break;
	case OFF:
	default:
		break;

	}

}

void Logger::setLogLevel(const LOGLEVEL level) {
	logLevel = level;
}

