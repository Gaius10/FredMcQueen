#include "../lib/Encoder.hpp"

float Encoder::getVelocity(int timeInterval)
{
    float vel = pulses * Encoder::_wheelsPerimeter / Encoder::_revolutionInterval / timeInterval;
    this->pulses = 0;
    return vel;
}

void Encoder::reset()
{
    this->pulses = 0;
}

void Encoder::updatePulses()
{
    this->pulses++;  
    // if (digitalRead(this->pinCLK) == HIGH) {
    //     if (digitalRead(this->pinDT) == LOW) {
    //         this->pulses--;
    //     } else {
    //         this->pulses++;
    //     }
    // } else {
    //     if (digitalRead(this->pinDT) == LOW) {
    //         this->pulses++;
    //     } else {
    //         this->pulses--;
    //     }
    // }
}

Encoder::Encoder(int pinCLK, int pinDT)
{
    this->pinCLK = pinCLK;
    this->pinDT = pinDT;

    pinMode(this->pinCLK, INPUT);
    pinMode(this->pinDT, INPUT);

    this->pulses = 0;
}