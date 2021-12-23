#ifndef SRC_TETRIS_SCORE_H_
#define SRC_TETRIS_SCORE_H_

#include "Score.h"

class Score {
 public:
    static int currentScore;

    static void updateScore(int linesCleared);
    static void clearScore();
    static int getCurrentScore();
};

#endif  // SRC_TETRIS_SCORE_H_
