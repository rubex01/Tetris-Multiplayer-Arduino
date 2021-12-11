#ifndef SRC_DISPLAY_DISPLAY_H_
#define SRC_DISPLAY_DISPLAY_H_

#include "Adafruit_ILI9341.h"

class Display {
 public:
    static void init();
    static void fillCircle(int x, int y, int r, uint16_t c);
    static void drawCircle(int x, int y, int r, uint16_t c);
    static Adafruit_ILI9341 tft;
};


#endif  // SRC_DISPLAY_DISPLAY_H_
