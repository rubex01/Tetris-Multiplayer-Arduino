#include <avr/eeprom.h>
#include "HighScore.h"

uint16_t HighScore::highScores[5] = {0};
bool HighScore::latestScoreIsOnLeaderBoard = false;
uint8_t HighScore::latestPlaceOnLeaderBoard = 0;

void HighScore::init() {
    readHighScoresFromMemory();
}

void HighScore::readHighScoresFromMemory() {
    for (uint16_t i = 0; i < 5; ++i) {
        uint16_t currentRead = eeprom_read_word(reinterpret_cast<const uint16_t *>(i*2));
        highScores[i] = currentRead;
    }
}

void HighScore::resetHighScores() {
    for (uint16_t i = 0; i < 5; ++i) {
        eeprom_write_word(reinterpret_cast<uint16_t*>(i*2), 0);
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

uint8_t HighScore::getPlaceOnLeaderBoard() {
    latestScoreIsOnLeaderBoard = false;
    return latestPlaceOnLeaderBoard;
}

void HighScore::addHighScore(uint16_t score, uint8_t index) {
    for (uint16_t i = 4; i > index; --i) {
        highScores[i] = highScores[i-1];
    }
    highScores[index] = score;

    for (uint16_t i = index; i < 5; ++i) {
        eeprom_write_word(reinterpret_cast<uint16_t*>(i*2), highScores[i]);
    }
}

uint16_t* HighScore::getLeaderBoard() {
    uint16_t* leaderboard = new uint16_t[5];
    for (uint8_t i = 0; i < 5; ++i) {
        leaderboard[i] = highScores[i];
    }
    return leaderboard;
}