#include <avr/eeprom.h>
#include "HighScore.h"
#include "HardwareSerial.h"

#define UINT16_T_MAX 65535

uint16_t HighScore::highScores[5] = {0};
bool HighScore::latestScoreIsOnLeaderBoard = false;
int HighScore::latestPlaceOnLeaderBoard = 0;

void HighScore::init() {
    readHighScoresFromMemory();
}

void HighScore::readHighScoresFromMemory() {
    for (uint8_t i = 0; i < 5; ++i) {
        uint16_t currentRead = eeprom_read_word((uint16_t*)i);
        if (currentRead != UINT16_T_MAX)
            highScores[i] = currentRead;
    }
}

void HighScore::resetHighScores() {
    for (uint8_t i = 0; i < 5; ++i) {
        eeprom_write_word((uint16_t*)i, 0);
    }
    readHighScoresFromMemory();
}

void HighScore::newScore(uint16_t score) {
    for (uint8_t i = 0; i < 5; ++i) {
        if (score > highScores[i]) {
            addHighScore(score, i);
            latestScoreIsOnLeaderBoard = true;
            latestPlaceOnLeaderBoard = i;
            break;
        }
    }
}

bool HighScore::isLatestScoreOnLeaderBoard() {
    return latestScoreIsOnLeaderBoard;
}

int HighScore::getPlaceOnLeaderBoard() {
    latestScoreIsOnLeaderBoard = false;
    return latestPlaceOnLeaderBoard;
}

void HighScore::addHighScore(uint16_t score, uint8_t index) {
    for (uint8_t i = 5; i >= index; --i) {
        highScores[i] = highScores[i-1];
    }
    highScores[index] = score;

    for (uint8_t i = index; i < 5; ++i) {
        eeprom_write_word((uint16_t*)i, (uint16_t)highScores[i]);
    }
}

uint16_t* HighScore::getLeaderBoard() {
    uint16_t* leaderboard = new uint16_t[5];
    for (int i = 0; i < 5; ++i) {
        leaderboard[i] = highScores[i];
    }
    return leaderboard;
}