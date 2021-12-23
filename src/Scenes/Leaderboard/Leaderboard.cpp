#include <stdint.h>
#include "Leaderboard.h"
#include "../../HighScore/HighScore.h"
#include "../../Display/Display.h"
#include "../../Controller/Controller.h"

void Leaderboard::init() {
    Display::drawText(50, 30, 2, "Nr. Score", ILI9341_YELLOW);

    drawLeaderboard();

    Display::drawText(10, 300, 1, "(z) to go back   (c) to reset scores", ILI9341_WHITE);
}

void Leaderboard::drawLeaderboard() {
    Display::fillRect(50, 60, 190, 200, ILI9341_BLACK);

    uint16_t* leaderboard = HighScore::getLeaderBoard();

    for (int i = 0; i < 5; ++i) {
        String leaderboardLine = "";
        leaderboardLine += (i+1);
        leaderboardLine += ".  ";
        leaderboardLine += leaderboard[i];
        Display::drawText(50, 60+(20*i), 2, leaderboardLine, ILI9341_WHITE);
    }

    delete[] leaderboard;
}

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