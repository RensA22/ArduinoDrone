/*
 * Logger.h
 *
 *  Created on: 23 mrt. 2022
 *      Author: Rens
 */

#ifndef LIB_LOGGER_LOGGER_H_
#define LIB_LOGGER_LOGGER_H_

#include <Arduino.h>

enum LOGLEVEL {
	OFF, INFO, ERROR
};

class Logger {
public:
	static Logger& getLoggerInstance();
	virtual ~Logger() = default;
	Logger(const Logger &other) = delete;
	Logger(Logger &&other) = delete;
	Logger& operator=(const Logger &other) = delete;

	void log(const String message);

	void setLogLevel(const LOGLEVEL level);

private:
	Logger();

	LOGLEVEL logLevel;
};

#endif /* LIB_LOGGER_LOGGER_H_ */
