#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic
{
private:
    int pinTrigger;
    int pinEcho;
    
public:
    Ultrasonic(int pinTrigger, int pinEcho);

    float distance(); // Retorna distância em cm
};

#endif