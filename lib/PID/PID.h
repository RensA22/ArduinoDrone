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
			const float _Kd, const int16_t _minValue, const int16_t _maxValue);
	virtual ~PID() = default;

	PID() = delete;
	PID(const PID &other) = delete;
	PID(PID &&other) = delete;

	/**
	 * Run the PID algorithm
	 *
	 * @param actualValue
	 * @return Output of the PID
	 */
	float compute(const float actualValue, const bool swapError = false);
	/**
	 * Reset the PID values to 0
	 */
	void reset();

	float getDerivative() const;
	float getError() const;
	float getIntegral() const;
	float getProportional() const;
	void setMaxValue(int8_t maxValue);
	float getOutput() const;

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
	int16_t minValue;
	int16_t maxValue;

};

#endif /* LIB_PID_PID_H_ */
