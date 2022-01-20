/*
 * Motor.cpp
 *
 *  Created on: Jan 19, 2022
 *      Author: rens
 */

#include "Motor.h"

Motor::Motor(const char _motorPin) : motorPin(_motorPin), currentValue(0)
{
    ESC.attach(motorPin, 1000, 2000);
    ESC.write(currentValue);
}

void Motor::writeMotorValue(const char value)
{
    currentValue = value;
    ESC.write(value);
}

