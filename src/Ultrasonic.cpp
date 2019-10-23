#include "../lib/Ultrasonic.hpp"


float Ultrasonic::distance()
{
    digitalWrite(this->pinTrigger, LOW);
    delayMicroseconds(5);
    digitalWrite(this->pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->pinTrigger, LOW);

    return pulseIn(this->pinEcho, HIGH) / 2 / 29.1;
}

Ultrasonic::Ultrasonic(int pinTrigger, int pinEcho)
{
    this->pinTrigger = pinTrigger;
    this->pinEcho = pinEcho;

    pinMode(this->pinTrigger, OUTPUT);
    pinMode(this->pinEcho, INPUT);
}