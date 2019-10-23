#!/bin/bash

arduino-cli compile -b arduino:avr:uno /home/caio/Arduino/FredMcQueen
arduino-cli upload -b arduino:avr:uno ~/Arduino/FredMcQueen -p /dev/ttyACM0
rm *.elf
rm *.hex
