#include "Display.h"

#include "SPI.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 Display::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

uint16_t Display::colors[8][3] = {
    {0x7BEF, 0xA534, 0x4A69},
    {0xFF80, 0xFFD0, 0xEEE0},  // O Block Yellow
    {0xB723, 0xCF6D, 0x9602},  // S Block Groen
    {0x3F7E, 0x8FDF, 0x2C52},  // I block Cyan
    {0xEA07, 0xF3AE, 0x78E3},  // Z Block Red
    {0xA3DE, 0xE41F, 0x7294},  // T Block Purple
    {0xED07, 0xFEAE, 0x7AA3},  // L Block Orange
    {0x2B9E, 0x949F, 0x0292}  // J Block Blue
};

/**
 * Init the display
 */
void Display::init() {
    Display::tft.begin();
    Display::tft.fillScreen(ILI9341_BLACK);
}

/**
 * Fills a circle
 *
 * @param x x coordinates
 * @param y y coordinates
 * @param r radius
 * @param c color
 */
void Display::fillCircle(int x, int y, int r, uint16_t c) {
    Display::tft.fillCircle(x, y, r, c);
}

/**
 * Draws a circle
 *
 * @param x x coordinates
 * @param y y coordinates
 * @param r radius
 * @param c color
 */
void Display::drawCircle(int x, int y, int r, uint16_t c) {
    Display::tft.drawCircle(x, y, r, c);
}

/**
 * Draws a rectangle
 *
 * @param x x coordinates
 * @param y y coordinates
 * @param w width
 * @param h height
 * @param c color
 */
void Display::drawRect(int x, int y, int w, int h, uint16_t c) {
    Display::tft.drawRect(x, y, w, h, c);
}

/**
 * Fills a rectangle
 *
 * @param x x coordinates
 * @param y y coordinates
 * @param w width
 * @param h height
 * @param c color
 */
void Display::fillRect(int x, int y, int w, int h, uint16_t c) {
    Display::tft.fillRect(x, y, w, h, c);
}

/**
 * Draws a tetris block
 *
 * @param x x coordinates
 * @param y y coordinates
 * @param color
 */
void Display::drawTetrisBlock(int x, int y, int color) {
    // Draw main color block
    Display::fillRect(x, 0+y, 20, 20, Display::colors[color][0]);

    // Draw outline
    Display::fillRect(x, y, 20, 3, 0x2965);
    Display::fillRect(x, y, 3, 20, 0x2965);
    Display::fillRect(x, 17+y, 20, 3, 0x2965);
    Display::fillRect(17+x, y, 3, 20, 0x2965);

    // Draw light shdadow
    Display::fillRect(3+x, 15+y, 14, 2, colors[color][1]);
    Display::fillRect(3+x+12, 3+y, 2, 14, colors[color][1]);

    // Draw dark outline
    Display::fillRect(3+x, 3+y, 14, 2, colors[color][2]);
    Display::fillRect(3+x, 3+y, 2, 14, colors[color][2]);
}

/**
 * Draws a small tetris block
 *
 * @param x x coordinates
 * @param y y coordinates
 * @param c color
 */
void Display::drawSmallTetrisBlok(int x, int y, int c) {
    // Draw main color
    Display::tft.fillRect(x, y, 10, 10, Display::colors[c][0]);

    // Draw outline
    Display::tft.fillRect(x, y, 10, 1, 0x2965);
    Display::tft.fillRect(x, y, 1, 10, 0x2965);
    Display::tft.fillRect(x, 9+y, 10, 1, 0x2965);
    Display::tft.fillRect(9+x, y, 1, 10, 0x2965);
}

/**
 * Draws a string
 *
 * @param x x coordinates
 * @param y y coordinates
 * @param s size
 * @param t string
 * @param c color
 */
void Display::drawText(int x, int y, int s, String t, uint16_t c) {
    Display::tft.setCursor(x, y);
    Display::tft.setTextColor(c);
    Display::tft.setTextSize(s);
    Display::tft.setTextWrap(true);
    Display::tft.print(t);
}

/**
 * Draws the game border
 */
void Display::drawGameBorder() {
    for (int i = 300; i >= 80;) {
        Display::drawTetrisBlock(0, i, GRAY);
        Display::drawTetrisBlock(220, i, GRAY);
        i -= 20;
    }

    for (int i = 20; i <= 200;) {
        Display::drawTetrisBlock(i, 80, GRAY);
        i += 20;
    }
}

/**
 * Draws hold section from game
 */
void Display::drawHoldSection() {
    Display::drawSmallTetrisBlok(30, 35, GRAY);
    Display::drawSmallTetrisBlok(40, 35, GRAY);
    Display::drawSmallTetrisBlok(30, 45, GRAY);

    Display::drawRect(9, 9, 62, 62, 0x2965);
    Display::drawRect(10, 10, 60, 60, 0x2965);
    Display::fillRect(10, 10, 60, 12, 0x2965);
    Display::drawText(29, 13, 1, "HOLD", ILI9341_WHITE);
}

/**
 * Draws next section
 */
void Display::drawNextSection() {
    Display::drawRect(169, 9, 62, 62, 0x2965);
    Display::drawRect(170, 10, 60, 60, 0x2965);
    Display::fillRect(170, 10, 60, 12, 0x2965);
    Display::drawText(188, 13, 1, "NEXT", ILI9341_WHITE);
}

/**
 * Clear the next section
 */
void Display::clearNextSection() {
    Display::fillRect(169, 21, 62, 62, ILI9341_BLACK);
    Display::drawRect(169, 9, 62, 62, 0x2965);
}

/**
 * Draw demo blocks
 */
void Display::drawDemoBlocks() {
    Display::drawTetrisBlock(20, 240, YELLOW);
    Display::drawTetrisBlock(20, 260, YELLOW);
    Display::drawTetrisBlock(20, 280, YELLOW);
    Display::drawTetrisBlock(20, 300, YELLOW);

    Display::drawTetrisBlock(100, 140, GREEN);
    Display::drawTetrisBlock(120, 140, GREEN);
    Display::drawTetrisBlock(100, 160, GREEN);
    Display::drawTetrisBlock(120, 160, GREEN);
}

/**
 * Draw score
 */
void Display::drawScore() {
    Display::drawText(105, 25, 1, "Score:", ILI9341_WHITE);
    Display::drawText(105, 35, 2, "560", ILI9341_WHITE);
}
