#include "Fred.hpp"

Fred* marquinhos;

void setup()
{
    marquinhos = new Fred(
        6, 5, 9, 10, // Motores
        2, 0, 3, 0, // Encoders
        4, 7, 8, 11, 12, 13, // Ultrassons
        A0, A1, A5, A2, A3, A4 // Seguidor de linha
    );

    attachInterrupt(digitalPinToInterrupt(2), atualizaPulsosL, CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), atualizaPulsosR, CHANGE);
}

void loop()
{
    marquinhos->katchau();
}

void atualizaPulsosL()
{
    marquinhos->updateEncoderPulses('l');
}
void atualizaPulsosR()
{
    marquinhos->updateEncoderPulses('r');
}