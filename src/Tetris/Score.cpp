#include "Score.h"
#include "../Display/Display.h"

int Score::currentScore = 0;

/**
 * Updates the score based on the amount of lines cleared
 *
 * @param linesCleared
 */
void Score::updateScore(int linesCleared) {
    switch (linesCleared) {
        case 1:
            Score::currentScore += 40;
            break;
        case 2:
            Score::currentScore += 100;
            break;
        case 3:
            Score::currentScore += 300;
            break;
        case 4:
            Score::currentScore += 1200;
            break;
    }
    Display::drawScore(currentScore);
}

/**
 * Clears the score
 */
void Score::clearScore() {
    currentScore = 0;
}

/**
 * Getter for the current score
 *
 * @return int current score
 */
int Score::getCurrentScore() {
    return currentScore;
}
