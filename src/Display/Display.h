#ifndef KBSMC_SRC_DISPLAY_DISPLAY_H_
#define KBSMC_SRC_DISPLAY_DISPLAY_H_

#include "Adafruit_ILI9341.h"

#define GRAY 0
#define YELLOW 1
#define GREEN 2

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
    static void drawScore();
    static void drawDemoBlocks();
    static Adafruit_ILI9341 tft;
    static uint16_t colors[3][3];
};

#endif  // KBSMC_SRC_DISPLAY_DISPLAY_H_
