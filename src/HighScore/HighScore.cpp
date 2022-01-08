#include <avr/eeprom.h>
#include "HighScore.h"

uint16_t HighScore::highScores[5] = {0};
bool HighScore::latestScoreIsOnLeaderBoard = false;
uint8_t HighScore::latestPlaceOnLeaderBoard = 0;

/**
 * Init high score
 */
void HighScore::init() {
    readHighScoresFromMemory();
}

/**
 * Read the high scores from eeprom memory
 */
void HighScore::readHighScoresFromMemory() {
    for (uint16_t i = 0; i < 5; ++i) {
        uint16_t currentRead = eeprom_read_word(reinterpret_cast<const uint16_t *>(i*2));
        highScores[i] = currentRead;
    }
}

/**
 * Reset all the high scores in eeprom memory
 */
void HighScore::resetHighScores() {
    for (uint16_t i = 0; i < 5; ++i) {
        eeprom_write_word(reinterpret_cast<uint16_t*>(i*2), 0);
    }
    readHighScoresFromMemory();
}

/**
 * Analyse a new score and add to leaderboard if it is high enough
 *
 * @param score
 */
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

/**
 * Returns a bool that indicates if the latest score is on the leaderboard
 *
 * @return bool
 */
bool HighScore::isLatestScoreOnLeaderBoard() {
    return latestScoreIsOnLeaderBoard;
}

/**
 * Returns the place of the latest added score to the leaderboard
 *
 * @return uint8_t
 */
uint8_t HighScore::getPlaceOnLeaderBoard() {
    latestScoreIsOnLeaderBoard = false;
    return latestPlaceOnLeaderBoard;
}

/**
 * Adds a high score to the leaderboard and shifts all lower places on leaderboard once.
 *
 * @param score score to add to leaderboard
 * @param index index of place on leaderboard
 */
void HighScore::addHighScore(uint16_t score, uint8_t index) {
    for (uint16_t i = 4; i > index; --i) {
        highScores[i] = highScores[i-1];
    }
    highScores[index] = score;

    for (uint16_t i = index; i < 5; ++i) {
        eeprom_write_word(reinterpret_cast<uint16_t*>(i*2), highScores[i]);
    }
}

/**
 * Returns pointer array of entire leaderboard
 *
 * @return uint16_t*
 */
uint16_t* HighScore::getLeaderBoard() {
    uint16_t* leaderboard = new uint16_t[5];
    for (uint8_t i = 0; i < 5; ++i) {
        leaderboard[i] = highScores[i];
    }
    return leaderboard;
}
