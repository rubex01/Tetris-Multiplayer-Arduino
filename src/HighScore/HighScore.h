#ifndef KBS_HIGHSCORE_H
#define KBS_HIGHSCORE_H


#include <stdint.h>

class HighScore {
 public:
    static bool latestScoreIsOnLeaderBoard;
    static uint8_t latestPlaceOnLeaderBoard;
    static uint16_t highScores[5];

    static void init();
    static void newScore(uint16_t score);
    static uint16_t* getLeaderBoard();
    static bool isLatestScoreOnLeaderBoard();
    static uint8_t getPlaceOnLeaderBoard();
    static void resetHighScores();

 private:
    static void addHighScore(uint16_t score, uint8_t index);
    static void readHighScoresFromMemory();
};


#endif //KBS_HIGHSCORE_H
