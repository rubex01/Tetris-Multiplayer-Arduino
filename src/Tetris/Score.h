#ifndef SRC_TETRIS_SCORE_H_
#define SRC_TETRIS_SCORE_H_

#include "Score.h"

class Score {
 public:
    static int currentScore;
    static void updateScore(int linesCleared);
};

#endif  // SRC_TETRIS_SCORE_H_
