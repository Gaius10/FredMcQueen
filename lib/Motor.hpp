#ifndef _MOTOR_HPP_
#define _MOTOR_HPP_

#include <Arduino.h>

class Motor
{
private:
    int pinA;
    int pinB;

public:
    Motor(int pinA, int pinB);

    void onoff(int pwmVelocity);
};

#endif