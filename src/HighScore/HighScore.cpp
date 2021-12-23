#include <avr/eeprom.h>
#include "HighScore.h"
#include "HardwareSerial.h"

#define UINT16_T_MAX 65535

uint16_t HighScore::highScores[5] = {0};

void HighScore::init() {
    for (int i = 0; i < 5; ++i) {
        uint16_t currentRead = eeprom_read_word((uint16_t*)i);
        if (currentRead != UINT16_T_MAX)
            highScores[i] = currentRead;
    }
}

void HighScore::newScore(uint16_t score) {
    for (int i = 0; i < 5; ++i) {
        if (score > highScores[i]) {
            addHighScore(score, i);
            break;
        }
    }
    for (int i = 0; i < 5; ++i) {
        Serial.print(i);
        Serial.print(": ");
        Serial.print(highScores[i]);
        Serial.println();
    }
}

void HighScore::addHighScore(uint16_t score, int index) {
    for (int i = 5; i >= index; --i) {
        highScores[i] = highScores[i-1];
    }
    highScores[index] = score;

    for (int i = index; i < 5; ++i) {
        eeprom_write_word((uint16_t*)i, (uint16_t)highScores[i]);
    }
}