#ifndef SRC_HIGHSCORE_HIGHSCORE_H_
#define SRC_HIGHSCORE_HIGHSCORE_H_

#include <stdint.h>

class HighScore {
 public:
    static bool latestScoreIsOnLeaderBoard;
    static uint8_t latestPlaceOnLeaderBoard;
    static uint16_t highScores[5];

    static void init();
    static void newScore(uint16_t score);
    static bool isLatestScoreOnLeaderBoard();
    static uint16_t* getLeaderBoard();
    static uint8_t getPlaceOnLeaderBoard();
    static void resetHighScores();

 private:
    static void addHighScore(uint16_t score, uint8_t index);
    static void readHighScoresFromMemory();
};


#endif  // SRC_HIGHSCORE_HIGHSCORE_H_
