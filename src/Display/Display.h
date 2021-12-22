#ifndef SRC_DISPLAY_DISPLAY_H_
#define SRC_DISPLAY_DISPLAY_H_

#include "Adafruit_ILI9341.h"

#define GRAY 0
#define YELLOW 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define ORANGE 6
#define BLUE 7
#define ENEMYBLOCK 8

class Display {
 public:
    static void init();
    static void fillCircle(int x, int y, int r, uint16_t c);
    static void drawCircle(int x, int y, int r, uint16_t c);
    static void fillRect(int x, int y, int w, int h, uint16_t c);
    static void drawRect(int x, int y, int w, int h, uint16_t c);
    static void drawTetrisBlock(int x, int y, int c);
    static void drawSmallTetrisBlok(int x, int y, int c);
    static void drawText(int x, int y, int s, String t, uint16_t c);
    static void drawGameBorder();
    static void drawHoldSection();
    static void drawNextSection();
    static void drawScore(int score);
    static void clearNextSection();
    static void drawDemoBlocks();
    static Adafruit_ILI9341 tft;
    static uint16_t colors[9][3];
};

#endif  // SRC_DISPLAY_DISPLAY_H_
