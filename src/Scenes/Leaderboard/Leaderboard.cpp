#include <stdint.h>
#include "Leaderboard.h"
#include "../../HighScore/HighScore.h"
#include "../../Display/Display.h"
#include "../../Controller/Controller.h"

/**
 * Leaderboard scene constructor
 */
Leaderboard::Leaderboard() {
    Display::drawText(50, 30, 2, "Nr. Score", ILI9341_YELLOW);

    drawLeaderboard();

    Display::drawText(10, 300, 1, "(z) to go back   (c) to reset scores", ILI9341_WHITE);
}

/**
 * Draws the leaderboard
 */
void Leaderboard::drawLeaderboard() {
    Display::fillRect(50, 60, 190, 200, ILI9341_BLACK);

    uint16_t* leaderboard = HighScore::getLeaderBoard();

    for (uint8_t i = 0; i < 5; ++i) {
        String leaderboardLine = "";
        leaderboardLine += (i+1);
        leaderboardLine += ".  ";
        leaderboardLine += leaderboard[i];
        Display::drawText(50, 60+(20*i), 2, leaderboardLine, ILI9341_WHITE);
    }

    delete[] leaderboard;
}

/**
 * Called continuously, checks for input to exit this scene or reset high scores.
 */
void Leaderboard::drawScene() {
    bool* actions = Controller::getNonContinuingTriggerActions();
    if (actions[Controller::Z_BUTTON]) {
        Scene::setScene(Scene::START_SCENE);
    } else if (actions[Controller::C_BUTTON]) {
        HighScore::resetHighScores();
        drawLeaderboard();
    }
    delete[] actions;
}
