#ifndef _LINE_FOLLOWER_HPP
#define _LINE_FOLLOWER_HPP

#include <Arduino.h>

class LineFollower
{
private:
    int enablePin;
    int controlPinL; // A2
    int controlPinM; // A3
    int controlPinR; // A4
    int logicPinL;
    int logicPinR;

    int minValues[5]; // left to right -> [0] to [4]
    int maxValues[5]; // left to right -> [0] to [4]

    byte sensingSignals[3];
    byte sideSignals[2];

public:

    LineFollower(
        int enablePin,
        int logicPinL, int logicPinR,
        int controlPinL, int controlPinM, int controlPinR
    );

    void test();

    void enable();
    void disable();

    int readSensingSignals();
    int readSideSignals();
    bool online();
};

#endif