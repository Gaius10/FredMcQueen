#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include <Arduino.h>

class Encoder
{
private:
    // Contador de pulsos ao longo do tempo de execução
    volatile int pulses;
    int pinCLK;
    int pinDT;
   
    const float _distanceBetWheels = 190.00f;   // Distancia entre as rodas do Fred
    const float _wheelsPerimeter = 201.062;     // Perímetro da roda
    const int _revolutionInterval = 38;         // Quantidade de pulsos por revolução do encoder

public:
    
    Encoder(int pinCLK, int pinDT = 0);

    void reset(); // this->pulses = 0;
    void updatePulses(); // Método contador de pulsos
    float getVelocity(int timeInterval); // Em m/s
};

#endif