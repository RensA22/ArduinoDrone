/*
 * PID.h
 *
 *  Created on: 26 jan. 2022
 *      Author: Rens
 */

#ifndef LIB_PID_PID_H_
#define LIB_PID_PID_H_

class PID {
public:
	PID(const float _desiredValue, const float _Kp, const float _Ki,
			const float _Kd, const short _minValue, const short _maxValue);
	virtual ~PID() = default;

	PID() = delete;
	PID(const PID &other) = delete;
	PID(PID &&other) = delete;

	float compute(const float actualValue);
	void setMaxValue(char maxValue);

private:
	float output;
	float desiredValue;
	float proportional;
	float integral;
	float derivative;
	float error;
	float prevError;
	float elapsedTime;
	double time;
	double prevTime;

	float Kp;
	float Ki;
	float Kd;
	short minValue;
	short maxValue;

};

#endif /* LIB_PID_PID_H_ */
