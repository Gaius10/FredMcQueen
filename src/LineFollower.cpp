#include "../lib/LineFollower.hpp"

bool LineFollower::online()
{
    sensingSignals[1] = (analogRead(controlPinM) - minValues[2]) * 100 / (maxValues[2] - minValues[2]);

    if (sensingSignals[1] > 40)
        return true;
    
    return false;
}

int LineFollower::readSensingSignals()
{
    sensingSignals[0] = (analogRead(controlPinL) - minValues[1]) * 100 / (maxValues[1] - minValues[1]);
    sensingSignals[2] = (analogRead(controlPinR) - minValues[3]) * 100 / (maxValues[3] - minValues[3]);
    
    return sensingSignals[0] - sensingSignals[2];
}

int LineFollower::readSideSignals()
{
    sideSignals[0] = (analogRead(logicPinL) - minValues[0]) * 100 / (maxValues[0] - minValues[0]);
    sideSignals[1] = (analogRead(logicPinR) - minValues[4]) * 100 / (maxValues[4] - minValues[4]);

    if (sideSignals[0] > 70)
        return 1;
    else if (sideSignals[1] > 70)
        return -1;
    else
        return 0;
}

void LineFollower::enable()
{
    digitalWrite(enablePin, HIGH);
}

void LineFollower::disable()
{
    digitalWrite(enablePin, LOW);
    delay(1);
}

LineFollower::LineFollower(
    int enablePin,
    int logicPinL, int logicPinR,
    int controlPinL, int controlPinM, int controlPinR
) {
    this->enablePin = enablePin;
    this->logicPinL = logicPinL;
    this->logicPinR = logicPinR;
    this->controlPinL = controlPinL;
    this->controlPinM = controlPinM;
    this->controlPinR = controlPinR;
    
    pinMode(this->enablePin, OUTPUT);
    pinMode(this->logicPinL, INPUT);
    pinMode(this->logicPinR, INPUT);
    pinMode(this->controlPinL, INPUT);
    pinMode(this->controlPinM, INPUT);
    pinMode(this->controlPinR, INPUT);

    /* Calibração temporaria */

    minValues[0] = 486;
    minValues[1] = 520;
    minValues[2] = 483;
    minValues[3] = 524;
    minValues[4] = 502;

    maxValues[0] = 790;
    maxValues[1] = 852;
    maxValues[2] = 815;
    maxValues[3] = 827;
    maxValues[4] = 827;
}


void LineFollower::test()
{
    Serial.print("LDRs: ");
    Serial.print(analogRead(logicPinL));
    Serial.print("  | ");
    Serial.print(analogRead(controlPinL));
    Serial.print(" | ");
    Serial.print(analogRead(controlPinM));
    Serial.print(" | ");
    Serial.print(analogRead(controlPinR));
    Serial.print(" |  ");
    Serial.print(analogRead(logicPinR));
    // Serial.println();
}