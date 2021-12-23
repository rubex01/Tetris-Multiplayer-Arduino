#ifndef KBS_HIGHSCORE_H
#define KBS_HIGHSCORE_H


#include <stdint.h>

class HighScore {
 public:
    static uint16_t highScores[5];
    static void init();
    static void newScore(uint16_t score);

 private:
    static void addHighScore(uint16_t score, int index);
};


#endif //KBS_HIGHSCORE_H
