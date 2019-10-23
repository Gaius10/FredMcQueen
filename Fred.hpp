#ifndef _FRED_HPP_
#define _FRED_HPP_

#include "Arduino.h"
#include "lib/Motor.hpp"
#include "lib/Encoder.hpp"
#include "lib/Ultrasonic.hpp"
#include "lib/LineFollower.hpp"


class Fred
{
private:
    const unsigned int SMP_TIME = 100; // Tempo de amostragem padrão

    /**
     * Componentes do carrinho...
     */
    Motor* motorL;
    Motor* motorR;
    Encoder* encoderL;
    Encoder* encoderR;
    Ultrasonic* ultrassomL;
    Ultrasonic* ultrassomM;
    Ultrasonic* ultrassomR;
    LineFollower* lineFollower;


    void motorsController(float referenceL, float referenceR);
    void turnOnLine(char side);
    void turnOnMaze();
public:
    Fred(
        // Motores
        int pinAMotorL, int pinBMotorL,
        int pinAMotorR, int pinBMotorR,

        // Encoders
        int pinCLKEncL, int pinDTEncL,
        int pinCLKEncR, int pinDTEncR,
        
        // Sensores ultrassom
        int pinTrigUltrassomL, int pinEchoUltrassomL,
        int pinTrigUltrassomM, int pinEchoUltrassomM,
        int pinTrigUltrassomR, int pinEchoUltrassomR,

        // Seguidor de linha
        int pinEnableLF,
        int pinLogicLeftLF, int pinLogicRightLF,
        int pinControlLeftLF, int pinControlMiddleLF, int pinControlRightLF
    );


    void updateEncoderPulses(char side);    // Atualiza quantidade de pulsos do encoder
    void katchau();                            // Trata todo o movimento do carrinho

    void followLinePID();                      // Segue linha
    void followWallPID();             // Segue parede
};

#endif