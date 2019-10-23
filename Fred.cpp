#include "Fred.hpp"

void Fred::katchau()
{
    static unsigned int previousTime = 0;

    // lineFollower->test();
    
    // followWallPID();
    followLinePID();
    
    // if (lineFollower->online())
    // {
    //     int sideSignal = lineFollower->readSideSignals();
    //     static int sideCounter = 0;

    //     switch(sideSignal)
    //     {
    //         case 1:
    //             if (sideCounter == 0) {
    //                 turnOnLine('l');
    //                 sideCounter++;
    //             } else {
    //                 followLinePID();
    //             }
    //             break;
    //         case -1:
    //             if (sideCounter == 0) {
    //                 turnOnLine('r');
    //                 sideCounter++;
    //             } else {
    //                 followLinePID();
    //             }
    //             break;
    //         default:
    //             followLinePID();
    //             break;
    //     }
    // }
    // else
    // {
    //     Serial.print("Seguir parede... ");
    //     Serial.println(previousTime);
    //     followWallPID('l');
    // }

    do { } while (millis() - previousTime < Fred::SMP_TIME); 
    previousTime = millis();
}

void Fred::followLinePID()
{
    static int recorder = 0;
    static int previousError;
    float auxSignal = 0;

    // Esquerda - Erro positivo
    // Direita - Erro negativo

    float lineSignal = lineFollower->readSensingSignals();
    float error = 0 - lineSignal;

    if (previousError > 0 && error < 0 || previousError < 0 && error > 0) {
        recorder = 0;
    }

    float controlSignal = error * 1.8 + recorder * 0.6 + (error - previousError) * 2;

    recorder += error;
    previousError = error;

    if (controlSignal > 0)
    {
        this->motorL->onoff(130);
        this->motorR->onoff(130 - controlSignal);
    }
    else
    {
        this->motorL->onoff(130 + controlSignal);
        this->motorR->onoff(130);
    }
}

void Fred::turnOnLine(char side)
{
    static int turnBaseTime = millis();

    Serial.println("Virando...");
    switch(side)
    {
        case 'l':
            motorL->onoff(0);
            motorR->onoff(150);
            delay(200);
            while (!lineFollower->online())
            {
                motorL->onoff(0);
                motorR->onoff(140);
            }
            break;
        case 'r':
            motorL->onoff(150);
            motorR->onoff(-70);
            delay(200);
            while(!lineFollower->online())
            {
                motorL->onoff(140);
                motorR->onoff(-70);
            }
            break;
    }

    if (millis() - turnBaseTime < 100)
        motorsController(0.4, 0.4);
}

void Fred::followWallPID()
{
    lineFollower->disable();
    static float recorder = 0;
    static float previousError = 0;
    float distanceR = ultrassomR->distance();
    float distanceM = ultrassomM->distance();


    if (distanceR < 35 && distanceR != 0)
    {
        float error = 12 - distanceR;

        if (error > 0 && previousError < 0 || error < 0 && previousError > 0)
            recorder = 0;

        float controlSignal = error * 20 + recorder * 1.5 + (error - previousError) * 20;
        recorder += error;
        previousError = error;



        if (controlSignal > 0)
        {
            motorL->onoff(170 - controlSignal);
            motorR->onoff(170);
        }
        else
        {
            motorL->onoff(170);
            motorR->onoff(170 + controlSignal);
        }
    }
    else
    {
        turnOnMaze();
    }
}

void Fred::turnOnMaze()
{
    while (ultrassomR->distance() > 35 || ultrassomR->distance() == 0)
    {
        motorL->onoff(255);
        motorR->onoff(70);
    }
    // if (ultrassomR->distance() > 35 || ultrassomR->distance() == 0)
    // {
    //     while (ultrassomR->distance() > 35 || ultrassomR->distance() == 0)
    //     {
    //         motorL->onoff(255);
    //         motorR->onoff(70);
    //     }
    // }
    // else
    // {
    //     while (ultrassomM->distance() < 40 && ultrassomM->distance() != 0)
    //     {
    //         motorL->onoff(70);
    //         motorR->onoff(255);
    //     }
    // }
}

void Fred::motorsController(float referenceL, float referenceR)
{
    float controlSignalL = (referenceL - encoderL->getVelocity(Fred::SMP_TIME)) * 255;
    float controlSignalR = (referenceR + encoderR->getVelocity(Fred::SMP_TIME)) * 255;

    motorL->onoff(controlSignalL);
    motorR->onoff(controlSignalR);
}

void Fred::updateEncoderPulses(char side)
{
    switch(side)
    {
        case 'l':
            this->encoderL->updatePulses();
            break;
        case 'r':
            this->encoderR->updatePulses();
            break;
    }
}

Fred::Fred(
    int pinAMotorL, int pinBMotorL,
    int pinAMotorR, int pinBMotorR,

    int pinCLKEncL, int pinDTEncL,
    int pinCLKEncR, int pinDTEncR,
    
    int pinTrigUltrasonicL, int pinEchoUltrasonicL,
    int pinTrigUltrasonicM, int pinEchoUltrasonicM,
    int pinTrigUltrasonicR, int pinEchoUltrasonicR,

    int pinEnableLF,
    int pinLogicLeftLF, int pinLogicRightLF,
    int pinControlLeftLF, int pinControlMiddleLF, int pinControlRightLF
) {
    this->motorL = new Motor(pinAMotorL, pinBMotorL);
    this->motorR = new Motor(pinAMotorR, pinBMotorR);
    this->encoderL = new Encoder(pinCLKEncL, pinDTEncL);
    this->encoderR = new Encoder(pinCLKEncR, pinDTEncR);

    this->ultrassomL = new Ultrasonic(pinTrigUltrasonicL, pinEchoUltrasonicL);
    this->ultrassomM = new Ultrasonic(pinTrigUltrasonicM, pinEchoUltrasonicM);
    this->ultrassomR = new Ultrasonic(pinTrigUltrasonicR, pinEchoUltrasonicR);

    this->lineFollower = new LineFollower(
        pinEnableLF,
        pinLogicLeftLF, pinLogicRightLF,
        pinControlLeftLF, pinControlMiddleLF, pinControlRightLF
    );

    Serial.begin(9600);

    this->lineFollower->enable();
    this->motorL->onoff(200);
    this->motorR->onoff(200);
    delay(200);
    this->motorL->onoff(0);
    this->motorR->onoff(0);
}