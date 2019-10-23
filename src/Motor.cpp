#include "../lib/Motor.hpp"


void Motor::onoff(int targetVelocity)
{    
    if (targetVelocity > 255) targetVelocity =  255;
    if (targetVelocity < -255) targetVelocity =  -255;

    if (targetVelocity > 0)
    {
        analogWrite(this->pinA, targetVelocity);
        analogWrite(this->pinB, 0);
    }
    else
    {
        analogWrite(this->pinA, 0);
        analogWrite(this->pinB, -targetVelocity);
    }

    // Serial.print(" Velocidade em pwm: ");
    // Serial.print(targetVelocity);
}

Motor::Motor(int pinA, int pinB)
{
    this->pinA = pinA;
    this->pinB = pinB;

    pinMode(this->pinA, OUTPUT);
    pinMode(this->pinB, OUTPUT);
}