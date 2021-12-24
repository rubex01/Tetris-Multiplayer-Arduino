#include "drawHighScoreMessage.h"
#include "../../Display/Display.h"
#include "../../HighScore/HighScore.h"

/**
 * This function draws a highscore message
 */
void drawHighScoreMessage() {
    if (HighScore::latestScoreIsOnLeaderBoard) {
        uint8_t leaderBoardPlace = HighScore::getPlaceOnLeaderBoard();

        String firstSentence = "You're number ";
        firstSentence += (leaderBoardPlace+1);

        for (uint8_t i = 0; i < 6; ++i) {
            Display::drawText(37+i, 47+i, 2, firstSentence, ILI9341_YELLOW);
        }
        Display::drawText(40, 50, 2, firstSentence, ILI9341_BLUE);
    }
}
